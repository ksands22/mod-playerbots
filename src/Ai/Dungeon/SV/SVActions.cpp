/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SVActions.h"
#include "DungeonHelpers.h"
#include "Playerbots.h"
#include "SVShared.h"

using namespace DungeonHelpers;
using namespace SVShared;

// Mekgineer Steamrigger

bool SteamriggerMarkMechanicAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_STEAMRIGGER_MECHANIC});
}

// Warlord Kalithresh

// Only the channeling distiller is attackable, so it is the only one among possible targets
bool KalithreshMarkDistillerAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_NAGA_DISTILLER});
}
