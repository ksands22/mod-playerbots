/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "GnomerTriggers.h"
#include "EncounterHelpers.h"
#include "GnomerShared.h"
#include "Playerbots.h"

using namespace EncounterHelpers;
using namespace GnomerShared;

// Mekgineer Thermaplugg

bool ThermapluggWalkingBombTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, GNOMER_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "mekgineer thermaplugg");
}
