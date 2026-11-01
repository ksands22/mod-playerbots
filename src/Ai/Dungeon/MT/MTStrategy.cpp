/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "MTStrategy.h"
#include "MTMultipliers.h"

void TbcDungeonManaTombsStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Pandemonius
    triggers.push_back(new TriggerNode("pandemonius dark shell",
                                       {NextAction("pandemonius stop attacking", ACTION_EMERGENCY + 1)}));

    // Nexus-Prince Shaffar
    triggers.push_back(new TriggerNode("shaffar is active",
                                       {NextAction("shaffar mark beacon", ACTION_RAID)}));
}

void TbcDungeonManaTombsStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    // Pandemonius
    multipliers.push_back(new PandemoniusDarkShellMultiplier(botAI));
}
