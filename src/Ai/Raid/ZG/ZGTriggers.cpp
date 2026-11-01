/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ZGTriggers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "Timer.h"
#include "ZGHelpers.h"

using namespace EncounterHelpers;
using namespace ZulGurubHelpers;

bool ZgKillOrderMarkTrigger::IsActive()
{
    // One marker per raid; encounter-only, so trash with the same entries keeps normal targeting.
    return bot->IsInCombat() && IsEncounterInProgress(bot, MAP_ZUL_GURUB) &&
           IsMechanicTrackerBot(bot, MAP_ZUL_GURUB) && GetKillOrderMarkTarget(botAI);
}

bool ZgCcMarkTrigger::IsActive()
{
    return bot->IsInCombat() && IsEncounterInProgress(bot, MAP_ZUL_GURUB) &&
           IsMechanicTrackerBot(bot, MAP_ZUL_GURUB) && GetCcMarkTarget(botAI);
}

bool ZgInterruptTrigger::IsActive()
{
    // Classes without one of the interrupts the action casts skip the attacker scan.
    switch (bot->getClass())
    {
        case CLASS_WARRIOR:
        case CLASS_ROGUE:
        case CLASS_SHAMAN:
        case CLASS_MAGE:
        case CLASS_DEATH_KNIGHT:
        case CLASS_HUNTER:
            break;
        default:
            return false;
    }

    return bot->IsInCombat() && IsEncounterInProgress(bot, MAP_ZUL_GURUB) && GetInterruptTarget(botAI);
}

bool ZgJeklikSpreadTrigger::IsActive()
{
    // Melee stay on the tank to dodge the bat riders' fire bombs.
    if (PlayerbotAI::IsMelee(bot) || PlayerbotAI::IsTank(bot))
        return false;

    if (!IsJeklikPriestPhase(AI_VALUE2(Unit*, "find target", "high priestess jeklik")))
        return false;

    return GetNearestPlayerInRadius(bot, JEKLIK_SPREAD_DISTANCE) != nullptr;
}

bool ZgVenoxisSnakeFormTooCloseTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "high priest venoxis");
    if (!IsVenoxisSnakeForm(boss) || boss->GetVictim() == bot)
        return false;

    return bot->GetDistance2d(boss) < VENOXIS_SNAKE_SAFE_DISTANCE;
}

bool ZgThekalTigerTrigger::IsActive()
{
    // Melee kill the tigers one at a time; ranged stay on Thekal.
    if (!PlayerbotAI::IsMelee(bot) || PlayerbotAI::IsTank(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "high priest thekal");
    if (!boss || IsThekalCouncilPhase(boss))
        return false;

    Unit* victim = bot->GetVictim();
    if (victim && victim->GetEntry() == NPC_ZULIAN_TIGER)
        return false;

    return AI_VALUE2(Unit*, "find target", "zulian tiger") != nullptr;
}

bool ZgMandokirGazeTrigger::IsActive()
{
    // Any threat made under the gaze gets the bot charged when it ends.
    return bot->HasAura(SPELL_THREATENING_GAZE) && (bot->GetVictim() || bot->IsNonMeleeSpellCast(false));
}

bool ZgOhganNotTankedTrigger::IsActive()
{
    if (!PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        return false;

    Unit* ohgan = AI_VALUE2(Unit*, "find target", "ohgan");
    return ohgan && ohgan->IsAlive() && ohgan->GetVictim() != bot;
}

bool ZgJindoShadeTrigger::IsActive()
{
    // Only cursed players can hit a Shade of Jin'do.
    if (PlayerbotAI::IsTank(bot) || !bot->HasAura(SPELL_DELUSIONS_OF_JINDO))
        return false;

    Unit* victim = bot->GetVictim();
    if (victim && victim->GetEntry() == NPC_SHADE_OF_JINDO)
        return false;

    return GetNearestNpc(botAI, NPC_SHADE_OF_JINDO, sPlayerbotAIConfig.SightDistance) != nullptr;
}

bool ZgHakkarPoisonousCloudTrigger::IsActive()
{
    // Poisonous Blood lasts 90s, the same as the Blood Siphon interval, so any time is the right time.
    if (bot->HasAura(SPELL_POISONOUS_BLOOD))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "hakkar");
    if (!boss || boss->GetVictim() == bot)
        return false;

    return GetNearestNpc(botAI, NPC_POISONOUS_CLOUD, POISONOUS_CLOUD_SEARCH_DISTANCE) != nullptr;
}

bool ZgHakkarSonPullTrigger::IsActive()
{
    // Already poisoned means this cycle's Son died and its cloud was used. Blood Siphon removes the
    // poison, which re-arms the pull for the next cycle; checking for a cloud instead would re-pull
    // once the 10s cloud expires.
    if (!PlayerbotAI::IsAssistTankOfIndex(bot, 0, true) || bot->HasAura(SPELL_POISONOUS_BLOOD))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "hakkar");
    bool const engaged = boss && boss->IsAlive() && boss->IsInCombat();
    uint32 const now = getMSTime();

    // A gap in evaluation (out of combat, dead) means the old pull time no longer applies.
    constexpr uint32 MAX_EVALUATION_GAP_MS = 5000;
    if (!engaged || (_lastSeenMs && getMSTimeDiff(_lastSeenMs, now) > MAX_EVALUATION_GAP_MS))
        _engagedMs = 0;
    _lastSeenMs = now;

    if (!engaged)
        return false;

    if (!_engagedMs)
        _engagedMs = now;

    uint32 const untilSiphon =
        HAKKAR_BLOOD_SIPHON_INTERVAL_MS - getMSTimeDiff(_engagedMs, now) % HAKKAR_BLOOD_SIPHON_INTERVAL_MS;
    return untilSiphon <= HAKKAR_SON_PULL_LEAD_MS;
}

bool ZgGahzrankaNotTankedTrigger::IsActive()
{
    // A Slam that misses part of the raid wipes the threat of everyone it hit, tank included.
    if (!PlayerbotAI::IsTank(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "gahz'ranka");
    Unit* victim = boss ? boss->GetVictim() : nullptr;
    if (!victim || victim == bot)
        return false;

    Player* victimPlayer = victim->ToPlayer();
    if (victimPlayer && PlayerbotAI::IsTank(victimPlayer))
        return false;

    // One tank takes over, as the guide's tanks trade him one at a time: the first of the main
    // tank and off-tanks that isn't airborne from a knockback. Several taunting at once would
    // steal him back and forth.
    for (Player* tank : { GetGroupMainTank(bot), GetGroupAssistTank(bot, 0), GetGroupAssistTank(bot, 1) })
    {
        if (!tank || tank == victim || tank->IsFalling())
            continue;
        return tank == bot;
    }
    return false;
}

bool ZgGahzrankaNotVictimTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "gahz'ranka");
    return boss && boss->GetVictim() != bot;
}

bool ZgGrilekPursuedTrigger::IsActive()
{
    // During Avatar his target holds a million threat for the pursuit; it runs, tank or not.
    Unit* boss = AI_VALUE2(Unit*, "find target", "gri'lek");
    return boss && boss->HasAura(SPELL_GRILEK_AVATAR) && boss->GetVictim() == bot &&
           bot->GetDistance2d(boss) < GRILEK_KITE_DISTANCE;
}

bool ZgCasterSpreadTrigger::IsActive()
{
    if (PlayerbotAI::IsMelee(bot) || PlayerbotAI::IsTank(bot))
        return false;

    if (!AI_VALUE2(Unit*, "find target", "gri'lek") && !AI_VALUE2(Unit*, "find target", "wushoolay"))
        return false;

    return GetNearestPlayerInRadius(bot, CASTER_SPREAD_DISTANCE) != nullptr;
}

bool ZgHazzarahIllusionTrigger::IsActive()
{
    // Illusions are immune to AoE and die to one ranged hit; ranged DPS each take the nearest.
    if (!PlayerbotAI::IsRangedDps(bot) || !AI_VALUE2(Unit*, "find target", "hazza'rah"))
        return false;

    Unit* victim = bot->GetVictim();
    if (victim && victim->GetEntry() == NPC_NIGHTMARE_ILLUSION && victim->IsAlive())
        return false;

    return GetNearestNpc(botAI, NPC_NIGHTMARE_ILLUSION, botAI->GetRange("spell")) != nullptr;
}
