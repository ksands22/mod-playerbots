/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BRDStrategy.h"

void VanillaDungeonBlackrockDepthsStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Ambassador Flamelash
    triggers.push_back(new TriggerNode("flamelash is active",
                                       {NextAction("flamelash mark burning spirit", ACTION_RAID)}));
}
