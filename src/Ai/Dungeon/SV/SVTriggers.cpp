/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SVTriggers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SVShared.h"

using namespace EncounterHelpers;
using namespace SVShared;

// Mekgineer Steamrigger

bool SteamriggerIsActiveTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, SV_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "mekgineer steamrigger");
}

// Warlord Kalithresh

bool KalithreshIsActiveTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, SV_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "warlord kalithresh");
}
