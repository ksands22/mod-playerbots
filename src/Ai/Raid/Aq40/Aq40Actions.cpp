/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq40Actions.h"

#include <cmath>
#include <span>

#include "Playerbots.h"

using namespace TempleOfAhnQirajHelpers;

static char const* FindCastableSpell(PlayerbotAI* botAI, std::span<char const* const> spells, Unit* target)
{
    if (!target)
        return nullptr;

    for (char const* spell : spells)
    {
        if (botAI->CanCastSpell(spell, target))
            return spell;
    }

    return nullptr;
}

// Mind control: Skeram and Qiraji Brainwashers

bool Aq40ControlMindControlledAction::Execute(Event /*event*/)
{
    char const* spell = bot->getClass() == CLASS_MAGE ? "polymorph" : "fear";
    Player* target = FindMindControlledMemberToControl(bot);
    if (!target || !botAI->CanCastSpell(spell, target))
        return false;

    return botAI->CastSpell(spell, target);
}

// Trash

bool Aq40DefenderAvoidExplodeAction::Execute(Event /*event*/)
{
    Unit* defender = FindNearbyExplodingDefender(botAI);
    if (!defender)
        return false;

    float const distToTravel = DEFENDER_EXPLODE_SAFE_DISTANCE - bot->GetDistance2d(defender);
    return distToTravel > 0.0f && MoveAway(defender, distToTravel);
}

bool Aq40DefenderPlagueSpreadAction::Execute(Event /*event*/)
{
    Unit* neighbour = FindNearbyPlagueVictim(botAI);
    if (!neighbour)
        return false;

    float const distToTravel = DEFENDER_PLAGUE_SAFE_DISTANCE - bot->GetDistance2d(neighbour);
    return distToTravel > 0.0f && MoveAway(neighbour, distToTravel);
}

bool Aq40AvoidThunderclapAction::Execute(Event /*event*/)
{
    Unit* clapper = FindNearbyThunderclapper(botAI);
    if (!clapper)
        return false;

    float const distToTravel = THUNDERCLAP_SAFE_DISTANCE - bot->GetDistance2d(clapper);
    return distToTravel > 0.0f && MoveAway(clapper, distToTravel);
}

// Viper Sting drains for its whole duration, so a hunter does not reapply its own.
static char const* GetObsidianManaSpell(PlayerbotAI* botAI, Unit* target)
{
    if (!target)
        return nullptr;

    char const* spell = botAI->GetBot()->getClass() == CLASS_PRIEST ? "mana burn" : "viper sting";
    if (botAI->HasAura(spell, target, false, true) || !botAI->CanCastSpell(spell, target))
        return nullptr;

    return spell;
}

bool Aq40BurnObsidianManaAction::Execute(Event /*event*/)
{
    Unit* target = FindObsidianWithMana(botAI);
    char const* spell = GetObsidianManaSpell(botAI, target);
    return spell && botAI->CastSpell(spell, target);
}

bool Aq40BurnObsidianManaAction::isPossible()
{
    return GetObsidianManaSpell(botAI, FindObsidianWithMana(botAI)) != nullptr;
}

// Battleguard Sartura

bool Aq40SarturaAvoidWhirlwindAction::Execute(Event /*event*/)
{
    Unit* whirlwind = FindNearbyWhirlwind(botAI);
    if (!whirlwind)
        return false;

    float const distToTravel = WHIRLWIND_SAFE_DISTANCE - bot->GetDistance2d(whirlwind);
    if (distToTravel <= 0.0f)
        return false;

    return MoveAway(whirlwind, distToTravel);
}

static constexpr char const* STUN_SPELLS[] = {"kidney shot", "hammer of justice", "concussion blow", "shockwave",
                                              "bash"};

bool Aq40SarturaStunAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "battleguard sartura");
    char const* spell = FindCastableSpell(botAI, STUN_SPELLS, boss);
    return spell && botAI->CastSpell(spell, boss);
}

bool Aq40SarturaStunAction::isPossible()
{
    return FindCastableSpell(botAI, STUN_SPELLS, AI_VALUE2(Unit*, "find target", "battleguard sartura")) != nullptr;
}

// Princess Huhuran

bool Aq40HuhuranShedThreatAction::Execute(Event /*event*/)
{
    // Huhuran ignores taunts: stop attacking until the partner tank overtakes on threat.
    bot->AttackStop();
    bot->InterruptNonMeleeSpells(false);
    return true;
}

// Fankriss the Unyielding

static constexpr char const* TAUNT_SPELLS[] = {"taunt", "hand of reckoning", "growl", "dark command"};

bool Aq40FankrissTauntAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "fankriss the unyielding");
    char const* spell = FindCastableSpell(botAI, TAUNT_SPELLS, boss);
    return spell && botAI->CastSpell(spell, boss);
}

bool Aq40FankrissTauntAction::isPossible()
{
    return FindCastableSpell(botAI, TAUNT_SPELLS, AI_VALUE2(Unit*, "find target", "fankriss the unyielding")) !=
           nullptr;
}

// Viscidus

// Only the number of direct frost hits counts towards freezing him, so the fastest spells go first.
// Frost Strike is left out: melee wait outside Poison Shock until he freezes.
static constexpr char const* FROST_SPELLS[] = {"ice lance", "frostbolt", "frost shock", "icy touch", "howling blast"};

bool Aq40ViscidusFrostSpellAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "viscidus");
    char const* spell = FindCastableSpell(botAI, FROST_SPELLS, boss);
    return spell && botAI->CastSpell(spell, boss);
}

bool Aq40ViscidusFrostSpellAction::isPossible()
{
    return FindCastableSpell(botAI, FROST_SPELLS, AI_VALUE2(Unit*, "find target", "viscidus")) != nullptr;
}

bool Aq40ViscidusAvoidPoisonShockAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "viscidus");
    if (!boss)
        return false;

    float const distToTravel = POISON_SHOCK_SAFE_DISTANCE - bot->GetDistance2d(boss);
    return distToTravel > 0.0f && MoveAway(boss, distToTravel);
}

// Twin Emperors

// Vek'lor while he stands on the side the bot holds as a twin tank.
static Unit* FindVeklorOnTankSide(PlayerbotAI* botAI)
{
    std::optional<TwinEmperorsSide> const side = GetTwinEmperorsTankSide(botAI->GetBot());
    Unit* twin = side ? FindTwinOnSide(botAI, *side) : nullptr;
    return twin && twin->GetEntry() == NPC_VEKLOR ? twin : nullptr;
}

bool Aq40WarlockTankAttackVeklorAction::Execute(Event /*event*/)
{
    // Searing Pain carries enough threat to hold Vek'lor, who is immune to the tanks' physical damage.
    Unit* veklor = FindVeklorOnTankSide(botAI);
    return veklor && botAI->CastSpell("searing pain", veklor);
}

bool Aq40WarlockTankAttackVeklorAction::isPossible()
{
    Unit* veklor = FindVeklorOnTankSide(botAI);
    return veklor && botAI->CanCastSpell("searing pain", veklor);
}

bool Aq40TwinEmperorsTankStationAction::Execute(Event /*event*/)
{
    Unit* veklor = FindVeklorOnTankSide(botAI);
    if (!veklor)
        return false;

    // Stand on the bot's side of Vek'lor, close enough to be nearest when Vek'nilash appears there.
    float const angle = bot->GetExactDist2d(veklor) > 0.1f ? veklor->GetAngle(bot) : veklor->GetOrientation();
    float const radius = (TWIN_TANK_STATION_MIN_DISTANCE + TWIN_TANK_STATION_MAX_DISTANCE) / 2.0f;
    float const destX = veklor->GetPositionX() + radius * std::cos(angle);
    float const destY = veklor->GetPositionY() + radius * std::sin(angle);
    return MoveTo(bot->GetMapId(), destX, destY, bot->GetPositionZ(), false, false, false, false,
                  MovementPriority::MOVEMENT_COMBAT, true);
}

bool Aq40TwinEmperorsHealerAvoidBlizzardAction::Execute(Event /*event*/)
{
    Unit* veklor = AI_VALUE2(Unit*, "find target", "emperor vek'lor");
    if (!veklor)
        return false;

    float const distToTravel = VEKLOR_BLIZZARD_SAFE_DISTANCE - bot->GetExactDist2d(veklor);
    return distToTravel > 0.0f && MoveAway(veklor, distToTravel);
}

bool Aq40TwinEmperorsAvoidExplodingBugAction::Execute(Event /*event*/)
{
    Unit* bug = FindNearbyExplodingBug(botAI);
    if (!bug)
        return false;

    float const distToTravel = EXPLODE_BUG_SAFE_DISTANCE - bot->GetDistance2d(bug);
    return distToTravel > 0.0f && MoveAway(bug, distToTravel);
}

// Ouro

bool Aq40OuroAvoidSandBlastAction::Execute(Event event)
{
    distance = PlayerbotAI::IsRanged(bot) ? OURO_RANGED_FLANK_DISTANCE : 0.0f;
    return BossRearFlankAction::Execute(event);
}

bool Aq40OuroAvoidSandBlastAction::isUseful()
{
    // Ouro has no tail, so only his front matters.
    Unit const* boss = GetTarget();
    return boss && boss->HasInArc(2.0f * minAngle, bot);
}

// C'Thun

bool Aq40CthunAvoidDarkGlareAction::Execute(Event /*event*/)
{
    Unit* eye = FindDarkGlaringEye(botAI);
    if (!eye)
        return false;

    // Stepping further out on the bot's own side never crosses the beam, whichever way it turns.
    float const offset = GetAngleFromDarkGlare(eye, bot);
    float const escapeAngle = eye->GetOrientation() + (offset < 0.0f ? -1.0f : 1.0f) * DARK_GLARE_ESCAPE_ANGLE;
    float const radius = bot->GetExactDist2d(eye);
    float const destX = eye->GetPositionX() + radius * std::cos(escapeAngle);
    float const destY = eye->GetPositionY() + radius * std::sin(escapeAngle);

    return MoveTo(bot->GetMapId(), destX, destY, bot->GetPositionZ(), false, false, false, false,
                  MovementPriority::MOVEMENT_FORCED, true);
}

bool Aq40CthunLeaveStomachAction::Execute(Event /*event*/)
{
    return MoveTo(bot->GetMapId(), CTHUN_STOMACH_EXIT_POSITION.GetPositionX(),
                  CTHUN_STOMACH_EXIT_POSITION.GetPositionY(), CTHUN_STOMACH_EXIT_POSITION.GetPositionZ(), false, false,
                  false, false, MovementPriority::MOVEMENT_FORCED, true);
}

// Shared

bool Aq40AssignClassRolesAction::Execute(Event /*event*/) { return UpdateAq40ClassRoles(botAI); }

bool Aq40TwinEmperorsAnnounceClassRolesAction::Execute(Event /*event*/)
{
    return EncounterHelpers::IsMechanicTrackerBot(bot, AQ40_MAP_ID) && UpdateTwinEmperorsClassRoleAnnouncement(botAI);
}
