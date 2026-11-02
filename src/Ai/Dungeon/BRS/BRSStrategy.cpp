/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BRSStrategy.h"
#include "BRSMultipliers.h"

void VanillaDungeonBlackrockSpireStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Warchief Rend Blackhand
    triggers.push_back(new TriggerNode("rend whirlwind",
                                       {NextAction("rend avoid whirlwind", ACTION_EMERGENCY + 1)}));

    // General Drakkisath
    triggers.push_back(new TriggerNode("drakkisath conflagration",
                                       {NextAction("drakkisath avoid conflagration", ACTION_EMERGENCY + 1)}));
}

void VanillaDungeonBlackrockSpireStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new RendWhirlwindMultiplier(botAI));
}
