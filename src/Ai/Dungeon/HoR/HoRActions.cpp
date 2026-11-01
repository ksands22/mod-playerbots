/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "HoRActions.h"
#include "DungeonHelpers.h"
#include "HoRShared.h"
#include "Playerbots.h"

using namespace DungeonHelpers;
using namespace HoRShared;

// Spirit waves and the Lich King escape

bool HoRMarkPriorityAddAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_WAVE_PRIEST, NPC_WAVE_MAGE, NPC_RISEN_WITCH_DOCTOR});
}
