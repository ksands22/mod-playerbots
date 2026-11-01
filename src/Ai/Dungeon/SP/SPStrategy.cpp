/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SPStrategy.h"

void TbcDungeonSlavePensStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Mennu the Betrayer
    triggers.push_back(new TriggerNode("mennu is active",
                                       {NextAction("mennu mark totem", ACTION_RAID)}));
}
