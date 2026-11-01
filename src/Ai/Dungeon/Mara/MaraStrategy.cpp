/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "MaraStrategy.h"
#include "MaraMultipliers.h"

void VanillaDungeonMaraudonStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Tinkerer Gizlock
    triggers.push_back(new TriggerNode("gizlock dragon gun",
                                       {NextAction("gizlock avoid dragon gun", ACTION_EMERGENCY + 1)}));

    // Princess Theradras
    triggers.push_back(new TriggerNode("theradras dust field",
                                       {NextAction("theradras avoid dust field", ACTION_EMERGENCY + 1)}));
}

void VanillaDungeonMaraudonStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new TheradrasDustFieldMultiplier(botAI));
}
