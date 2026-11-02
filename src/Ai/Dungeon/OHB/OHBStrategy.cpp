/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "OHBStrategy.h"
#include "OHBMultipliers.h"

void TbcDungeonOldHillsbradStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Lieutenant Drake
    triggers.push_back(new TriggerNode("drake whirlwind",
                                       {NextAction("drake avoid whirlwind", ACTION_EMERGENCY + 1)}));

    // Thrall's escort
    triggers.push_back(new TriggerNode("thrall under attack",
                                       {NextAction("thrall defend", ACTION_RAID)}));
}

void TbcDungeonOldHillsbradStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    // Lieutenant Drake
    multipliers.push_back(new DrakeWhirlwindMultiplier(botAI));

    // Thrall's escort
    multipliers.push_back(new ThrallDefendMultiplier(botAI));
}
