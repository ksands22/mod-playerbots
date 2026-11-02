/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "STTriggers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "STShared.h"

using namespace EncounterHelpers;
using namespace STShared;

// Atal'ai defenders (Mijan, Zolo)

bool AtalaiDefendersTotemsTrigger::IsActive()
{
    if (!IsMechanicTrackerBot(bot, ST_MAP_ID))
        return false;

    return  AI_VALUE2(Unit*, "find target", "mijan") ||
            AI_VALUE2(Unit*, "find target", "zolo");
}
