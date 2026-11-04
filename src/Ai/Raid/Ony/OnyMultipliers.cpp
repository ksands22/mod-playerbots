/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "OnyMultipliers.h"
#include "OnyTriggers.h"
#include "Playerbots.h"
#include "ShamanActions.h"

float OnyxiaKeepTremorTotemMultiplier::GetValue(Action* action)
{
    if (bot->getClass() != CLASS_SHAMAN)
        return 1.0f;

    if (!dynamic_cast<CastStrengthOfEarthTotemAction*>(action) &&
        !dynamic_cast<CastStoneskinTotemAction*>(action) &&
        !dynamic_cast<CastStoneclawTotemAction*>(action) &&
        !dynamic_cast<CastEarthbindTotemAction*>(action))
    {
        return 1.0f;
    }

    return OnyxiaHelpers::IsOnyxiaPhase3(AI_VALUE2(Unit*, "find target", "onyxia")) ? 0.0f : 1.0f;
}
