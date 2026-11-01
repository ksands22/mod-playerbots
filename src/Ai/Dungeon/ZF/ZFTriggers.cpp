/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ZFTriggers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "ZFShared.h"

using namespace EncounterHelpers;
using namespace ZFShared;

// Antu'sul

bool AntusulIsActiveTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, ZF_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "antu'sul");
}

// Witch Doctor Zum'rah

bool ZumrahIsActiveTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, ZF_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "witch doctor zum'rah");
}
