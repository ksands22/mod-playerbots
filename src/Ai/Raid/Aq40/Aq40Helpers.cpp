/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq40Helpers.h"

#include <cmath>
#include <mutex>
#include <tuple>
#include <unordered_map>

#include "AiObjectContext.h"
#include "Creature.h"
#include "Group.h"
#include "InstanceScript.h"
#include "Playerbots.h"
#include "SpellAuras.h"

using namespace EncounterHelpers;

namespace TempleOfAhnQirajHelpers
{
namespace
{
std::mutex aq40StateMutex;
std::unordered_map<uint32, Aq40InstanceState> aq40States;
}  // namespace

static constexpr float BUG_TRIO_DYING_HEALTH_PCT = 5.0f;
static constexpr uint32 BUG_TRIO_KILL_ORDER[] = {NPC_KRI, NPC_YAUJ, NPC_VEM};

bool IsBossInProgress(Player* bot, TempleOfAhnQirajBosses boss)
{
    if (bot->GetMapId() != AQ40_MAP_ID)
        return false;

    InstanceScript* instance = bot->GetInstanceScript();
    return instance && instance->GetBossState(boss) == IN_PROGRESS;
}

bool HasLivingGroupMemberOfClass(Player* bot, uint8 playerClass)
{
    Group* group = bot->GetGroup();
    if (!group)
        return false;

    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        Player* member = ref->GetSource();
        if (member && member->IsAlive() && member->GetMapId() == bot->GetMapId() && member->getClass() == playerClass)
            return true;
    }

    return false;
}

// The Prophet Skeram

bool IsSkeramImage(Unit const* unit) { return unit && unit->GetEntry() == NPC_SKERAM && unit->IsSummon(); }

Player* FindMindControlledMemberToControl(Player* bot)
{
    Group* group = bot->GetGroup();
    if (!group)
        return nullptr;

    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        Player* member = ref->GetSource();
        if (!member || member == bot || !member->IsAlive() || member->GetMapId() != bot->GetMapId())
            continue;

        bool const mindControlled = member->HasAura(SPELL_TRUE_FULFILLMENT) || member->HasAura(SPELL_CAUSE_INSANITY);
        if (mindControlled && !member->IsPolymorphed() && !member->HasFearAura())
            return member;
    }

    return nullptr;
}

// Trash

// Nearest living unit from the named GuidVector value that matches, within range of the bot.
template <typename Predicate>
static Unit* FindNearestUnit(PlayerbotAI* botAI, std::string const& listValue, float range, Predicate matches)
{
    Player* bot = botAI->GetBot();
    Unit* nearest = nullptr;
    float nearestDistance = range;
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>(listValue)->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || unit == bot || !unit->IsAlive() || !matches(unit))
            continue;

        float const distance = bot->GetDistance2d(unit);
        if (distance < nearestDistance)
        {
            nearest = unit;
            nearestDistance = distance;
        }
    }

    return nearest;
}

static Unit* FindNearestUnitWithAura(PlayerbotAI* botAI, std::string const& listValue, uint32 spellId, float range)
{
    return FindNearestUnit(botAI, listValue, range, [spellId](Unit const* unit) { return unit->HasAura(spellId); });
}

Unit* FindNearbyExplodingDefender(PlayerbotAI* botAI)
{
    return FindNearestUnitWithAura(botAI, "attackers", SPELL_DEFENDER_EXPLODE, DEFENDER_EXPLODE_SAFE_DISTANCE);
}

Unit* FindNearbyPlagueVictim(PlayerbotAI* botAI)
{
    return FindNearestUnit(botAI, "nearest friendly players", DEFENDER_PLAGUE_SAFE_DISTANCE,
                           [](Unit const*) { return true; });
}

bool CanThunderclap(Unit const* unit)
{
    return unit && (unit->GetEntry() == NPC_ANUBISATH_DEFENDER || unit->HasAura(SPELL_SENTINEL_THUNDERCLAP));
}

Unit* FindNearbyThunderclapper(PlayerbotAI* botAI)
{
    return FindNearestUnit(botAI, "attackers", THUNDERCLAP_SAFE_DISTANCE, CanThunderclap);
}

// Lower dies first. A dying Sentinel hands its ability to every packmate still alive, so the
// raid-wide ones are saved for last instead of being multiplied.
static uint8 GetSentinelKillPriority(Unit const* sentinel)
{
    bool const raidWide = sentinel->HasAura(SPELL_SENTINEL_MANA_BURN) ||
                          sentinel->HasAura(SPELL_SENTINEL_SHADOW_STORM) ||
                          sentinel->HasAura(SPELL_SENTINEL_THUNDERCLAP);
    return raidWide ? 1 : 0;
}

Unit* FindSentinelKillTarget(PlayerbotAI* botAI, GuidVector const& attackers)
{
    Unit* best = nullptr;
    for (ObjectGuid const guid : attackers)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || unit->GetEntry() != NPC_ANUBISATH_SENTINEL)
            continue;

        // Every bot must agree: ability first, then health, then a stable tiebreak.
        auto const key = std::make_tuple(GetSentinelKillPriority(unit), unit->GetHealthPct(), guid.GetCounter());
        if (!best ||
            key < std::make_tuple(GetSentinelKillPriority(best), best->GetHealthPct(), best->GetGUID().GetCounter()))
            best = unit;
    }

    return best;
}

Unit* FindObsidianWithMana(PlayerbotAI* botAI)
{
    AiObjectContext* context = botAI->GetAiObjectContext();
    for (char const* name : {"obsidian eradicator", "obsidian nullifier"})
    {
        Unit* unit = AI_VALUE2(Unit*, "find target", name);
        if (unit && unit->IsAlive() && unit->GetPower(POWER_MANA) > 0)
            return unit;
    }

    return nullptr;
}

// Bug Trio

bool IsBugTrioMember(Unit const* unit)
{
    if (!unit)
        return false;

    uint32 const entry = unit->GetEntry();
    return entry == NPC_KRI || entry == NPC_VEM || entry == NPC_YAUJ;
}

bool IsBugTrioMemberDying(Unit const* unit)
{
    if (!IsBugTrioMember(unit))
        return false;

    Creature const* creature = unit->ToCreature();
    return creature && creature->HasReactState(REACT_PASSIVE) && creature->GetHealthPct() < BUG_TRIO_DYING_HEALTH_PCT;
}

Unit* FindBugTrioKillTarget(PlayerbotAI* botAI, GuidVector const& attackers)
{
    for (uint32 entry : BUG_TRIO_KILL_ORDER)
    {
        for (ObjectGuid const guid : attackers)
        {
            Unit* unit = botAI->GetUnit(guid);
            if (unit && unit->IsAlive() && unit->GetEntry() == entry && !IsBugTrioMemberDying(unit))
                return unit;
        }
    }

    return nullptr;
}

// Battleguard Sartura

bool IsWhirlwinding(Unit const* unit)
{
    return unit && (unit->HasAura(SPELL_SARTURA_WHIRLWIND) || unit->HasAura(SPELL_ROYAL_GUARD_WHIRLWIND));
}

Unit* FindNearbyWhirlwind(PlayerbotAI* botAI)
{
    return FindNearestUnit(botAI, "attackers", WHIRLWIND_SAFE_DISTANCE, IsWhirlwinding);
}

// Fankriss the Unyielding

uint8 GetAuraStacks(Unit const* unit, uint32 spellId)
{
    Aura const* aura = unit ? unit->GetAura(spellId) : nullptr;
    return aura ? aura->GetStackAmount() : 0;
}

bool IsSwapTank(Player* bot) { return PlayerbotAI::IsMainTank(bot) || PlayerbotAI::IsAssistTankOfIndex(bot, 0); }

Player* GetSwapTankPartner(Player* bot)
{
    Player* partner = PlayerbotAI::IsMainTank(bot) ? GetGroupAssistTank(bot, 0) : GetGroupMainTank(bot);
    return partner && partner != bot && partner->IsAlive() ? partner : nullptr;
}

// Princess Huhuran

bool ShouldShedHuhuranThreat(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    if (!IsSwapTank(bot) || GetAuraStacks(bot, SPELL_ACID_SPIT) < ACID_SPIT_SWAP_STACKS)
        return false;

    Player* partner = GetSwapTankPartner(bot);
    if (!partner || GetAuraStacks(partner, SPELL_ACID_SPIT) >= ACID_SPIT_SWAP_STACKS)
        return false;

    AiObjectContext* context = botAI->GetAiObjectContext();
    return AI_VALUE2(Unit*, "find target", "princess huhuran") != nullptr;
}

// Viscidus

bool IsViscidusFreezable(Unit const* viscidus)
{
    return viscidus && viscidus->IsAlive() && !viscidus->HasAura(SPELL_VISCIDUS_FREEZE) &&
           !viscidus->HasAura(SPELL_VISCIDUS_INVISIBLE);
}

// Twin Emperors

bool IsTwinEmperor(Unit const* unit)
{
    return unit && (unit->GetEntry() == NPC_VEKNILASH || unit->GetEntry() == NPC_VEKLOR);
}

bool IsTwinImmuneToBot(Unit const* twin, Player* bot)
{
    SpellSchoolMask const school = PlayerbotAI::IsCaster(bot) ? SPELL_SCHOOL_MASK_MAGIC : SPELL_SCHOOL_MASK_NORMAL;
    return IsTwinEmperor(twin) && twin->IsImmunedToDamage(school);
}

Unit* FindNearbyExplodingBug(PlayerbotAI* botAI)
{
    return FindNearestUnitWithAura(botAI, "nearest npcs", SPELL_EXPLODE_BUG, EXPLODE_BUG_SAFE_DISTANCE);
}

TwinEmperorsSide GetTwinEmperorsSide(WorldObject const* object)
{
    return object->GetExactDist2d(VEKNILASH_SPAWN_POSITION) <= object->GetExactDist2d(VEKLOR_SPAWN_POSITION)
               ? TwinEmperorsSide::Veknilash
               : TwinEmperorsSide::Veklor;
}

std::optional<TwinEmperorsSide> GetTwinEmperorsTankSide(Player* bot)
{
    if (std::optional<TwinEmperorsSide> const side = GetTwinEmperorsWarlockTankSide(bot))
        return side;

    if (PlayerbotAI::IsMainTank(bot))
        return TwinEmperorsSide::Veknilash;

    if (PlayerbotAI::IsAssistTankOfIndex(bot, 0))
        return TwinEmperorsSide::Veklor;

    return std::nullopt;
}

Unit* FindTwinOnSide(PlayerbotAI* botAI, TwinEmperorsSide side)
{
    AiObjectContext* context = botAI->GetAiObjectContext();
    for (char const* name : {"emperor vek'nilash", "emperor vek'lor"})
    {
        Unit* twin = AI_VALUE2(Unit*, "find target", name);
        if (twin && GetTwinEmperorsSide(twin) == side)
            return twin;
    }

    return nullptr;
}

// C'Thun

bool IsInCthunStomach(Player* bot)
{
    // The core's own test: everyone outside the stomach stands above Z 0.
    return bot->GetPositionZ() < 0.0f && IsBossInProgress(bot, BOSS_CTHUN);
}

bool IsCthunTentacleAdd(Unit const* unit)
{
    return unit && (unit->GetEntry() == NPC_EYE_TENTACLE || unit->GetEntry() == NPC_CLAW_TENTACLE);
}

std::optional<uint8> GetCthunTentaclePriority(Unit const* unit)
{
    if (!unit)
        return std::nullopt;

    switch (unit->GetEntry())
    {
        case NPC_GIANT_EYE_TENTACLE:
            return 0;
        case NPC_EYE_TENTACLE:
            return 1;
        case NPC_GIANT_CLAW_TENTACLE:
            return 2;
        default:
            return std::nullopt;
    }
}

Unit* FindDarkGlaringEye(PlayerbotAI* botAI)
{
    AiObjectContext* context = botAI->GetAiObjectContext();
    Unit* eye = AI_VALUE2(Unit*, "find target", "eye of c'thun");
    return eye && eye->HasAura(SPELL_DARK_GLARE_COLORATION) ? eye : nullptr;
}

float GetAngleFromDarkGlare(Unit const* eye, Unit const* unit)
{
    return std::remainder(eye->GetAngle(unit) - eye->GetOrientation(), 2.0f * static_cast<float>(M_PI));
}

// Shared encounter state

Aq40InstanceState& Aq40State(uint32 instanceId)
{
    std::lock_guard lock(aq40StateMutex);
    return aq40States[instanceId];
}

Aq40InstanceState* FindAq40State(uint32 instanceId)
{
    std::lock_guard lock(aq40StateMutex);
    auto it = aq40States.find(instanceId);
    return it != aq40States.end() ? &it->second : nullptr;
}

bool UpdateAq40ClassRoles(PlayerbotAI* botAI)
{
    Aq40InstanceState& state = Aq40State(botAI->GetBot()->GetInstanceId());
    return UpdateClassRoleAssignments(botAI, AQ40_MAP_ID,
                                      {
                                          {VEKLOR_SIDE_WARLOCK_TANK_ROLE, state.veklorSideWarlockTank},
                                          {VEKNILASH_SIDE_WARLOCK_TANK_ROLE, state.veknilashSideWarlockTank},
                                      });
}

bool UpdateTwinEmperorsClassRoleAnnouncement(PlayerbotAI* botAI)
{
    Aq40InstanceState& state = Aq40State(botAI->GetBot()->GetInstanceId());
    return UpdateClassRoleAnnouncement(botAI, NPC_VEKLOR, VEKLOR_SPAWN_POSITION,
                                       TWIN_EMPERORS_CLASS_ROLE_ANNOUNCE_DISTANCE,
                                       TWIN_EMPERORS_CLASS_ROLE_REARM_DISTANCE,
                                       {
                                           {VEKLOR_SIDE_WARLOCK_TANK_ROLE, state.veklorSideWarlockTank},
                                           {VEKNILASH_SIDE_WARLOCK_TANK_ROLE, state.veknilashSideWarlockTank},
                                       });
}

std::optional<TwinEmperorsSide> GetTwinEmperorsWarlockTankSide(Player* bot)
{
    if (bot->getClass() != CLASS_WARLOCK)
        return std::nullopt;

    Aq40InstanceState const* state = FindAq40State(bot->GetInstanceId());
    if (!state)
        return std::nullopt;

    if (IsClassRolePlayer(bot, state->veklorSideWarlockTank))
        return TwinEmperorsSide::Veklor;

    if (IsClassRolePlayer(bot, state->veknilashSideWarlockTank))
        return TwinEmperorsSide::Veknilash;

    return std::nullopt;
}
}  // namespace TempleOfAhnQirajHelpers
