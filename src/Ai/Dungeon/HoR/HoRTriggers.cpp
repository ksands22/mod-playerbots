/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "HoRTriggers.h"
#include "EncounterHelpers.h"
#include "HoRShared.h"
#include "Playerbots.h"

using namespace EncounterHelpers;
using namespace HoRShared;

// Spirit waves and the Lich King escape

bool HoRPriorityAddTrigger::IsActive()
{
    return bot->IsInCombat() && IsMechanicTrackerBot(bot, HOR_MAP_ID);
}
