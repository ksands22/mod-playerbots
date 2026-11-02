/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ZGHelpers.h"
#include "AiObjectContext.h"
#include "EncounterHelpers.h"
#include "Group.h"
#include "Playerbots.h"
#include "RtiTargetValue.h"
#include "Spell.h"
#include "SpellInfo.h"
#include <algorithm>
#include <array>
#include <vector>

using namespace EncounterHelpers;

namespace ZulGurubHelpers
{
// Guide order: adds before their boss; at Jin'do the Healing Ward, then the Brain Wash Totem.
// Shades of Jin'do are left to the cursed players, the only ones who can hit them.
static uint8 GetKillPriority(uint32 entry)
{
    switch (entry)
    {
        case NPC_POWERFUL_HEALING_WARD:
            return 3;
        case NPC_RAZZASHI_COBRA:
        case NPC_SPAWN_OF_MARLI:
        case NPC_BRAIN_WASH_TOTEM:
        case NPC_SON_OF_HAKKAR:
            return 2;
        case NPC_VENOXIS:
        case NPC_MARLI:
        case NPC_JINDO:
            return 1;
        default:
            return 0;
    }
}

// Thekal and his zealots revive unless all three die within 10s, so each is brought down to a
// hold point first (the wiki's 20% / 15% / 10%), then all three are burned together.
static float GetCouncilHoldPct(uint32 entry)
{
    switch (entry)
    {
        case NPC_THEKAL:
            return 20.0f;
        case NPC_ZEALOT_ZATH:
            return 15.0f;
        case NPC_ZEALOT_LORKHAN:
            return 10.0f;
        default:
            return -1.0f;
    }
}

static Unit* GetThekalCouncilMarkTarget(Unit* skull, std::vector<Unit*> const& council)
{
    bool const skullOnCouncil = skull && skull->IsAlive() && GetCouncilHoldPct(skull->GetEntry()) >= 0.0f;

    // Bring the member furthest above its hold point down first.
    Unit* best = nullptr;
    float bestMargin = 0.0f;
    for (Unit* member : council)
    {
        float const margin = member->GetHealthPct() - GetCouncilHoldPct(member->GetEntry());
        if (margin > bestMargin)
        {
            best = member;
            bestMargin = margin;
        }
    }

    if (best)
    {
        if (skullOnCouncil && skull->GetHealthPct() > GetCouncilHoldPct(skull->GetEntry()))
            return nullptr;
        return best;
    }

    // All at their hold points: burn the healthiest first, so the last two die soon after the first.
    if (skullOnCouncil)
        return nullptr;

    Unit* healthiest = nullptr;
    for (Unit* member : council)
        if (!healthiest || member->GetHealthPct() > healthiest->GetHealthPct())
            healthiest = member;

    return healthiest;
}

Unit* GetKillOrderMarkTarget(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    Group* group = bot->GetGroup();
    if (!group)
        return nullptr;

    Unit* skull = botAI->GetUnit(group->GetTargetIcon(RtiTargetValue::skullIndex));

    Unit* best = nullptr;
    uint8 bestPriority = 0;
    std::vector<Unit*> council;
    bool councilPhase = false;
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("possible targets")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || !bot->IsValidAttackTarget(unit))
            continue;

        if (unit->GetEntry() == NPC_THEKAL && IsThekalCouncilPhase(unit))
            councilPhase = true;

        if (GetCouncilHoldPct(unit->GetEntry()) >= 0.0f)
        {
            council.push_back(unit);
            continue;
        }

        uint8 const priority = GetKillPriority(unit->GetEntry());
        if (!priority)
            continue;

        // Only the Son the tank has brought to the raid: the rest wait on the steps, and one killed
        // on the way would leave its 10s cloud where nobody stands.
        if (unit->GetEntry() == NPC_SON_OF_HAKKAR)
        {
            Player* mainTank = GetGroupMainTank(bot);
            if (!unit->IsInCombat() || !mainTank ||
                unit->GetExactDist2d(mainTank) > HAKKAR_SON_ARRIVED_DISTANCE)
                continue;
        }

        if (priority > bestPriority || (priority == bestPriority && unit->GetHealthPct() < best->GetHealthPct()))
        {
            best = unit;
            bestPriority = priority;
        }
    }

    // A fake-dead Thekal is unselectable, so the zealots alone can still mean the council phase.
    if (!council.empty() && (councilPhase || std::none_of(council.begin(), council.end(), [](Unit* member)
        { return member->GetEntry() == NPC_THEKAL; })))
        return GetThekalCouncilMarkTarget(skull, council);

    if (!best)
        return nullptr;

    // Keep a skull that is still in the top tier, so the raid doesn't split as add health values cross.
    if (skull && skull->IsAlive() && GetKillPriority(skull->GetEntry()) >= bestPriority)
        return nullptr;

    return best;
}

Unit* GetCcMarkTarget(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    Group* group = bot->GetGroup();
    if (!group)
        return nullptr;

    ObjectGuid const skullGuid = group->GetTargetIcon(RtiTargetValue::skullIndex);
    Unit* moon = botAI->GetUnit(group->GetTargetIcon(RtiTargetValue::moonIndex));
    if (moon && moon->IsAlive() && moon->GetGUID() != skullGuid)
        return nullptr;

    // Guides crowd-control the cobras and tigers that aren't being killed. Moon goes on the
    // healthiest, the one the skull reaches last; the bots' own cc picks up any others.
    Unit* best = nullptr;
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("attackers")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || unit->GetGUID() == skullGuid)
            continue;

        if (unit->GetEntry() != NPC_RAZZASHI_COBRA && unit->GetEntry() != NPC_ZULIAN_TIGER)
            continue;

        if (!best || unit->GetHealthPct() > best->GetHealthPct())
            best = unit;
    }
    return best;
}

Unit* GetInterruptTarget(PlayerbotAI* botAI)
{
    Unit* drainer = nullptr;
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("attackers")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive())
            continue;

        for (CurrentSpellTypes type : { CURRENT_GENERIC_SPELL, CURRENT_CHANNELED_SPELL })
        {
            Spell const* spell = unit->GetCurrentSpell(type);
            if (!spell)
                continue;

            switch (spell->m_spellInfo->Id)
            {
                case SPELL_JEKLIK_GREATER_HEAL:
                case SPELL_LORKHAN_GREATER_HEAL:
                    return unit;
                case SPELL_MARLI_DRAIN_LIFE:
                case SPELL_JEKLIK_MIND_FLAY:
                    drainer = unit;
                    break;
                default:
                    break;
            }
        }
    }
    return drainer;
}

bool IsJeklikPriestPhase(Unit const* jeklik)
{
    return jeklik && jeklik->IsAlive() && !jeklik->HasAura(SPELL_JEKLIK_BAT_FORM);
}

bool IsVenoxisSnakeForm(Unit const* venoxis)
{
    return venoxis && venoxis->IsAlive() && venoxis->HasAura(SPELL_VENOXIS_TRANSFORM);
}

bool IsThekalCouncilPhase(Unit const* thekal)
{
    return thekal && thekal->IsAlive() && !thekal->HasAura(SPELL_THEKAL_TIGER_FORM);
}

Unit* GetNearestNpc(PlayerbotAI* botAI, uint32 entry, float maxDistance)
{
    Player* bot = botAI->GetBot();
    Unit* nearest = nullptr;
    float nearestDistance = maxDistance;
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("nearest npcs")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || unit->GetEntry() != entry)
            continue;

        float const distance = bot->GetExactDist2d(unit);
        if (distance < nearestDistance)
        {
            nearest = unit;
            nearestDistance = distance;
        }
    }
    return nearest;
}

static constexpr std::array<char const*, 6> POISON_CURE_SPELLS = {
    "cure poison", "abolish poison", "cleanse", "purify", "cure toxins", "cleanse spirit"};
static constexpr std::array<char const*, 3> CURSE_REMOVAL_SPELLS = {
    "remove curse", "remove lesser curse", "cleanse spirit"};

bool IsPoisonCureSpell(std::string const& spell)
{
    return std::find(POISON_CURE_SPELLS.begin(), POISON_CURE_SPELLS.end(), spell) != POISON_CURE_SPELLS.end();
}

bool IsCurseRemovalSpell(std::string const& spell)
{
    return std::find(CURSE_REMOVAL_SPELLS.begin(), CURSE_REMOVAL_SPELLS.end(), spell) != CURSE_REMOVAL_SPELLS.end();
}
}
