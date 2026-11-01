/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BMStrategy.h"

void TbcDungeonBlackMorassStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Opening of the Dark Portal (Medivh)
    triggers.push_back(new TriggerNode("black morass idle rift mob",
                                       {NextAction("black morass attack rift mob", ACTION_RAID)}));
}
