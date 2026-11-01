/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "RFDStrategy.h"
#include "RFDMultipliers.h"

void VanillaDungeonRazorfenDownsStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Extinguishing the Idol (Belnistrasz)
    triggers.push_back(new TriggerNode("belnistrasz under attack",
                                       {NextAction("belnistrasz defend", ACTION_RAID)}));
}

void VanillaDungeonRazorfenDownsStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new BelnistraszDefendMultiplier(botAI));
}
