/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BRDActions.h"
#include "BRDShared.h"
#include "DungeonHelpers.h"
#include "Playerbots.h"

using namespace BRDShared;
using namespace DungeonHelpers;

// Ambassador Flamelash

bool FlamelashMarkBurningSpiritAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_BURNING_SPIRIT});
}
