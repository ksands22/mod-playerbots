/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "UldamanStrategy.h"
#include "DungeonMultipliers.h"
#include "UldamanShared.h"

void VanillaDungeonUldamanStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    // Obsidian Sentinel
    multipliers.push_back(new ReflectingTargetMultiplier(botAI, "obsidian sentinel reflection",
                                                         {UldamanShared::SPELL_OBSIDIAN_REFLECTION}));
}
