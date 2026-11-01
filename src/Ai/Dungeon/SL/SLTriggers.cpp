/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SLTriggers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SLShared.h"

using namespace EncounterHelpers;
using namespace SLShared;

// Grandmaster Vorpil

bool VorpilIsActiveTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, SL_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "grandmaster vorpil");
}

// Murmur

bool MurmurSonicBoomTrigger::IsActive()
{
    Unit* murmur = AI_VALUE2(Unit*, "find target", "murmur");
    if (!IsCastingSonicBoom(murmur))
        return false;

    return bot->GetExactDist2d(murmur) < SONIC_BOOM_SAFE_DISTANCE;
}

bool MurmursTouchTrigger::IsActive()
{
    if (!HasMurmursTouch(bot))
        return false;

    return GetNearestPlayerInRadius(bot, MURMURS_TOUCH_SAFE_DISTANCE);
}
