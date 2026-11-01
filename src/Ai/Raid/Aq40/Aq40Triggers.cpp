/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq40Triggers.h"

#include <cmath>

#include "Aq40Helpers.h"
#include "Playerbots.h"

using namespace TempleOfAhnQirajHelpers;
using namespace EncounterHelpers;

// Shared

bool Aq40NoEncounterInProgressTrigger::IsActive() { return !IsEncounterInProgress(bot, AQ40_MAP_ID); }

bool Aq40ClassRolesShouldBeAssignedTrigger::IsActive() { return IsMechanicTrackerBot(bot, AQ40_MAP_ID); }

bool Aq40MindControlTrigger::IsActive()
{
    // Mages polymorph; warlocks fear only when no mage is left to do it.
    uint8 const botClass = bot->getClass();
    if (botClass != CLASS_MAGE && botClass != CLASS_WARLOCK)
        return false;

    if (!FindMindControlledMemberToControl(bot))
        return false;

    return botClass == CLASS_MAGE || !HasLivingGroupMemberOfClass(bot, CLASS_MAGE);
}

bool Aq40FearTrigger::IsActive()
{
    if (bot->getClass() != CLASS_SHAMAN)
        return false;

    return AI_VALUE2(Unit*, "find target", "princess yauj") || AI_VALUE2(Unit*, "find target", "anubisath warder") ||
           AI_VALUE2(Unit*, "find target", "qiraji champion");
}

// Trash

bool Aq40DefenderExplodeTrigger::IsActive() { return FindNearbyExplodingDefender(botAI) != nullptr; }

bool Aq40DefenderPlagueTrigger::IsActive()
{
    return !PlayerbotAI::IsTank(bot) && bot->HasAura(SPELL_DEFENDER_PLAGUE) && FindNearbyPlagueVictim(botAI);
}

bool Aq40ThunderclapTrigger::IsActive()
{
    return PlayerbotAI::IsRanged(bot) && !PlayerbotAI::IsTank(bot) && FindNearbyThunderclapper(botAI);
}

bool Aq40ObsidianManaTrigger::IsActive()
{
    // Priests Mana Burn and hunters Viper Sting so the mob never fills up for its raid-wide blast.
    uint8 const botClass = bot->getClass();
    return (botClass == CLASS_PRIEST || botClass == CLASS_HUNTER) && FindObsidianWithMana(botAI);
}

// Bug Trio

bool Aq40KriPoisonCloudTrigger::IsActive()
{
    return IsBossInProgress(bot, BOSS_BUG_TRIO) &&
           bot->FindNearestCreature(NPC_POISON_CLOUD, POISON_CLOUD_SAFE_DISTANCE);
}

// Battleguard Sartura

bool Aq40SarturaWhirlwindTrigger::IsActive() { return FindNearbyWhirlwind(botAI) != nullptr; }

bool Aq40SarturaStunTrigger::IsActive()
{
    // Whirlwind makes her immune to stuns; between spins she can be stunned.
    Unit* boss = AI_VALUE2(Unit*, "find target", "battleguard sartura");
    return boss && boss->IsAlive() && !IsWhirlwinding(boss) && !boss->HasAuraType(SPELL_AURA_MOD_STUN);
}

// Princess Huhuran

bool Aq40HuhuranShedThreatTrigger::IsActive() { return bot->GetVictim() && ShouldShedHuhuranThreat(botAI); }

// Fankriss the Unyielding

bool Aq40FankrissTankSwapTrigger::IsActive()
{
    if (!IsSwapTank(bot) || GetAuraStacks(bot, SPELL_MORTAL_WOUND) > 0)
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "fankriss the unyielding");
    Unit* victim = boss ? boss->GetVictim() : nullptr;
    Player* victimPlayer = victim ? victim->ToPlayer() : nullptr;
    return victimPlayer && victimPlayer != bot && PlayerbotAI::IsTank(victimPlayer) &&
           GetAuraStacks(victimPlayer, SPELL_MORTAL_WOUND) >= MORTAL_WOUND_SWAP_STACKS;
}

// Viscidus

bool Aq40ViscidusFrostTrigger::IsActive()
{
    uint8 const botClass = bot->getClass();
    if (PlayerbotAI::IsHeal(bot) ||
        (botClass != CLASS_MAGE && botClass != CLASS_SHAMAN && botClass != CLASS_DEATH_KNIGHT))
        return false;

    return IsViscidusFreezable(AI_VALUE2(Unit*, "find target", "viscidus"));
}

bool Aq40ViscidusPoisonShockTrigger::IsActive()
{
    // Melee wait outside Poison Shock until he is frozen solid.
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsRanged(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "viscidus");
    return IsViscidusFreezable(boss) && bot->GetDistance2d(boss) < POISON_SHOCK_SAFE_DISTANCE;
}

bool Aq40ViscidusToxicSlimeTrigger::IsActive()
{
    return IsBossInProgress(bot, BOSS_VISCIDUS) && bot->FindNearestCreature(NPC_TOXIC_SLIME, TOXIN_SAFE_DISTANCE);
}

// Twin Emperors

bool Aq40VeklorNeedsWarlockTankTrigger::IsActive()
{
    std::optional<TwinEmperorsSide> const side = GetTwinEmperorsWarlockTankSide(bot);
    Unit* twin = side ? FindTwinOnSide(botAI, *side) : nullptr;
    return twin && twin->GetEntry() == NPC_VEKLOR;
}

bool Aq40TwinEmperorsTankStationTrigger::IsActive()
{
    // Only the physical tanks wait by Vek'lor; the warlock tanks fight him.
    if (GetTwinEmperorsWarlockTankSide(bot))
        return false;

    std::optional<TwinEmperorsSide> const side = GetTwinEmperorsTankSide(bot);
    Unit* twin = side ? FindTwinOnSide(botAI, *side) : nullptr;
    if (!twin || twin->GetEntry() != NPC_VEKLOR)
        return false;

    float const distance = bot->GetExactDist2d(twin);
    return distance < TWIN_TANK_STATION_MIN_DISTANCE || distance > TWIN_TANK_STATION_MAX_DISTANCE;
}

bool Aq40TwinEmperorsHealerBlizzardTrigger::IsActive()
{
    if (!PlayerbotAI::IsHeal(bot))
        return false;

    Unit* veklor = AI_VALUE2(Unit*, "find target", "emperor vek'lor");
    return veklor && bot->GetExactDist2d(veklor) < VEKLOR_BLIZZARD_SAFE_DISTANCE;
}

bool Aq40TwinEmperorsExplodingBugTrigger::IsActive()
{
    return IsBossInProgress(bot, BOSS_TWIN_EMPERORS) && FindNearbyExplodingBug(botAI);
}

// Ouro

bool Aq40OuroSandBlastTrigger::IsActive()
{
    if (PlayerbotAI::IsTank(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "ouro");
    return boss && boss->GetVictim() != bot && boss->HasInArc(2.0f * SAND_BLAST_AVOID_ANGLE, bot);
}

bool Aq40OuroDirtMoundTrigger::IsActive()
{
    return IsBossInProgress(bot, BOSS_OURO) && bot->FindNearestCreature(NPC_DIRT_MOUND, QUAKE_SAFE_DISTANCE);
}

// C'Thun

bool Aq40CthunDarkGlareTrigger::IsActive()
{
    Unit* eye = FindDarkGlaringEye(botAI);
    return eye && std::abs(GetAngleFromDarkGlare(eye, bot)) < DARK_GLARE_DANGER_ANGLE;
}

bool Aq40CthunStomachExitTrigger::IsActive()
{
    if (!IsInCthunStomach(bot))
        return false;

    return GetAuraStacks(bot, SPELL_DIGESTIVE_ACID) >= DIGESTIVE_ACID_EXIT_STACKS ||
           !bot->FindNearestCreature(NPC_FLESH_TENTACLE, CTHUN_STOMACH_SEARCH_RANGE);
}
