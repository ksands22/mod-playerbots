/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BRDTriggers.h"
#include "BRDShared.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"

using namespace BRDShared;
using namespace EncounterHelpers;

// Ambassador Flamelash

bool FlamelashIsActiveTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, BRD_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "ambassador flamelash");
}
