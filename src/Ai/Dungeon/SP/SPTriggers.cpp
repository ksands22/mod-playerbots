/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SPTriggers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SPShared.h"

using namespace EncounterHelpers;
using namespace SPShared;

// Mennu the Betrayer

bool MennuIsActiveTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, SP_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "mennu the betrayer");
}
