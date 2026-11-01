/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Triggers.h"
#include "Aq20Helpers.h"
#include "Aq20Utils.h"
#include "EncounterHelpers.h"

using namespace Aq20Helpers;
using namespace EncounterHelpers;

bool Aq20MoveToCrystalTrigger::IsActive()
{
    if (Unit* boss = AI_VALUE2(Unit*, "find target", "ossirian the unscarred"))
    {
        if (boss->IsInCombat())
        {
            // if buff is active move to crystal
            if (RaidAq20Utils::IsOssirianBuffActive(boss))
                return true;

            // if buff is not active a debuff will be, buff becomes active once debuff expires
            // so move to crystal when debuff almost done, or based debuff time left and
            // distance bot is from crystal (ie: start moving early enough to make it)
            int32 debuffTimeRemaining = RaidAq20Utils::GetOssirianDebuffTimeRemaining(boss);
            if (debuffTimeRemaining < 5000)
                return true;
            if (debuffTimeRemaining < 30000)
            {
                if (GameObject* crystal = RaidAq20Utils::GetNearestCrystal(boss))
                {
                    float botDist = bot->GetDistance(crystal);
                    float timeToReach = botDist / bot->GetSpeed(MOVE_RUN);
                    // bot should ideally activate crystal a ~5 seconds early (due to time it takes for crystal
                    // to activate) so aim to get there in time to do so
                    return debuffTimeRemaining - 5 * IN_MILLISECONDS < timeToReach * IN_MILLISECONDS;
                }
            }
        }
    }
    return false;
}

bool Aq20KillOrderMarkTrigger::IsActive()
{
    // One marker per raid. No encounter gate: Rajaxx's waves run before his encounter starts, and the
    // marked entries only exist in their own fights.
    return bot->IsInCombat() && IsMechanicTrackerBot(bot, MAP_RUINS_OF_AHNQIRAJ) && GetKillOrderMarkTarget(botAI);
}

bool Aq20CcMarkTrigger::IsActive()
{
    return bot->IsInCombat() && IsEncounterInProgress(bot, MAP_RUINS_OF_AHNQIRAJ) &&
           IsMechanicTrackerBot(bot, MAP_RUINS_OF_AHNQIRAJ) && GetCcMarkTarget(botAI);
}

bool Aq20KurinnaxxTankSwapTrigger::IsActive()
{
    if (!PlayerbotAI::IsTank(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "kurinnaxx");
    Unit* victim = boss ? boss->GetVictim() : nullptr;
    if (!victim || victim == bot || GetAuraStacks(victim, SPELL_MORTAL_WOUND) < KURINNAXX_SWAP_STACKS)
        return false;

    // One tank takes over: the first of the main tank and off-tanks not carrying the stacks
    // itself, so the main tank resumes once its own have faded.
    for (Player* tank : { GetGroupMainTank(bot), GetGroupAssistTank(bot, 0), GetGroupAssistTank(bot, 1) })
    {
        if (!tank || tank == victim || GetAuraStacks(tank, SPELL_MORTAL_WOUND) >= KURINNAXX_SWAP_STACKS)
            continue;
        return tank == bot;
    }
    return false;
}

bool Aq20MoamDrainManaTrigger::IsActive()
{
    // Guides drain with every warlock, priest and hunter; healing priests keep healing.
    switch (bot->getClass())
    {
        case CLASS_WARLOCK:
        case CLASS_HUNTER:
            break;
        case CLASS_PRIEST:
            if (PlayerbotAI::IsHeal(bot))
                return false;
            break;
        default:
            return false;
    }

    Unit* boss = AI_VALUE2(Unit*, "find target", "moam");
    if (!boss || !boss->IsAlive() || IsMoamStoned(boss) || !boss->GetPower(POWER_MANA))
        return false;

    // Already channelling Drain Mana, or Viper Sting already ticking on him.
    if (bot->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
        return false;

    return !(bot->getClass() == CLASS_HUNTER && botAI->HasAura("viper sting", boss));
}

bool Aq20AyamissLarvaTrigger::IsActive()
{
    // All melee kill the larva before it reaches the shackled player; her tank stays on her.
    if (!PlayerbotAI::IsMelee(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "ayamiss the hunter");
    if (!boss || boss->GetVictim() == bot)
        return false;

    Unit* victim = bot->GetVictim();
    if (victim && victim->GetEntry() == NPC_HIVEZARA_LARVA)
        return false;

    return GetNearestNpc(botAI, NPC_HIVEZARA_LARVA, AQ20_ADD_SEARCH_DISTANCE) != nullptr;
}

bool Aq20BuruChasedTrigger::IsActive()
{
    Unit* buru = AI_VALUE2(Unit*, "find target", "buru the gorger");
    return IsBuruEggPhase(buru) && buru->GetVictim() == bot &&
           GetNearestNpc(botAI, NPC_BURU_EGG, AQ20_ADD_SEARCH_DISTANCE) != nullptr;
}
