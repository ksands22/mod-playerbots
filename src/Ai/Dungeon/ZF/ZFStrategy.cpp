/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ZFStrategy.h"

void VanillaDungeonZulFarrakStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Antu'sul
    triggers.push_back(new TriggerNode("antusul is active",
                                       {NextAction("antusul mark healing ward", ACTION_RAID)}));

    // Witch Doctor Zum'rah
    triggers.push_back(new TriggerNode("zumrah is active",
                                       {NextAction("zumrah mark ward", ACTION_RAID)}));
}
