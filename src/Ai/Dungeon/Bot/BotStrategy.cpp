/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BotStrategy.h"
#include "BotMultipliers.h"

void TbcDungeonBotanicaStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // High Botanist Freywinn
    triggers.push_back(new TriggerNode("freywinn is active",
                                       {NextAction("freywinn mark frayer", ACTION_RAID)}));

    // Thorngrin the Tender
    triggers.push_back(new TriggerNode("thorngrin hellfire",
                                       {NextAction("thorngrin avoid hellfire", ACTION_EMERGENCY + 1)}));

    // Warp Splinter
    triggers.push_back(new TriggerNode("warp splinter is active",
                                       {NextAction("warp splinter mark sapling", ACTION_RAID)}));
}

void TbcDungeonBotanicaStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    // Thorngrin the Tender
    multipliers.push_back(new ThorngrinHellfireMultiplier(botAI));
}
