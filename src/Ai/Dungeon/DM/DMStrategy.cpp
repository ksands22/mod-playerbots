/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "DMStrategy.h"
#include "DMMultipliers.h"

void VanillaDungeonDireMaulStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Immol'thar
    triggers.push_back(new TriggerNode("immolthar is active",
                                       {NextAction("immolthar mark eye", ACTION_RAID)}));

    // Prince Tortheldrin
    triggers.push_back(new TriggerNode("tortheldrin whirlwind",
                                       {NextAction("tortheldrin avoid whirlwind", ACTION_EMERGENCY + 1)}));
}

void VanillaDungeonDireMaulStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    // Prince Tortheldrin
    multipliers.push_back(new TortheldrinWhirlwindMultiplier(botAI));
}
