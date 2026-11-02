/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SLStrategy.h"
#include "SLMultipliers.h"

void TbcDungeonShadowLabyrinthStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Grandmaster Vorpil
    triggers.push_back(new TriggerNode("vorpil is active",
                                       {NextAction("vorpil mark void traveler", ACTION_RAID)}));

    // Murmur
    triggers.push_back(new TriggerNode("murmur sonic boom",
                                       {NextAction("murmur avoid sonic boom", ACTION_EMERGENCY + 2)}));
    triggers.push_back(new TriggerNode("murmurs touch",
                                       {NextAction("murmurs touch move from group", ACTION_EMERGENCY + 1)}));
}

void TbcDungeonShadowLabyrinthStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    // Murmur
    multipliers.push_back(new MurmurSonicBoomMultiplier(botAI));
}
