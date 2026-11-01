/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "GnomerActions.h"
#include "DungeonHelpers.h"
#include "GnomerShared.h"
#include "Playerbots.h"

using namespace DungeonHelpers;
using namespace GnomerShared;

// Mekgineer Thermaplugg

// Walking Bombs explode within 5 yards of a player
bool ThermapluggMarkWalkingBombAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_WALKING_BOMB});
}
