/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SPActions.h"
#include "DungeonHelpers.h"
#include "Playerbots.h"
#include "SPShared.h"

using namespace DungeonHelpers;
using namespace SPShared;

// Mennu the Betrayer

bool MennuMarkTotemAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_CORRUPTED_NOVA_TOTEM, NPC_MENNUS_HEALING_WARD});
}
