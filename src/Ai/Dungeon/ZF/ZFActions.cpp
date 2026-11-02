/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ZFActions.h"
#include "DungeonHelpers.h"
#include "Playerbots.h"
#include "ZFShared.h"

using namespace DungeonHelpers;
using namespace ZFShared;

// Antu'sul

bool AntusulMarkHealingWardAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_ANTUSUL_HEALING_WARD});
}

// Witch Doctor Zum'rah

bool ZumrahMarkWardAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_WARD_OF_ZUMRAH});
}
