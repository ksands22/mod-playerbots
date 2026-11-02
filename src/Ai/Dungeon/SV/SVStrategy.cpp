/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SVStrategy.h"
#include "DungeonMultipliers.h"
#include "SVShared.h"

void TbcDungeonSteamvaultStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Mekgineer Steamrigger
    triggers.push_back(new TriggerNode("steamrigger is active",
                                       {NextAction("steamrigger mark mechanic", ACTION_RAID)}));

    // Warlord Kalithresh
    triggers.push_back(new TriggerNode("kalithresh is active",
                                       {NextAction("kalithresh mark distiller", ACTION_RAID)}));
}

void TbcDungeonSteamvaultStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    // Warlord Kalithresh
    multipliers.push_back(new ReflectingTargetMultiplier(botAI, "kalithresh spell reflection",
                                                         {SVShared::SPELL_KALITHRESH_REFLECTION}));
}
