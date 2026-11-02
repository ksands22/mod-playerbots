/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SLMultipliers.h"
#include "Playerbots.h"
#include "SLActions.h"
#include "SLShared.h"

using namespace SLShared;

// Murmur

// He is rooted, so keep chasing from walking bots back into Sonic Boom range during the cast
float MurmurSonicBoomMultiplier::GetValue(Action* action)
{
    if (!dynamic_cast<MovementAction*>(action) || dynamic_cast<MurmurAvoidSonicBoomAction*>(action))
        return 1.0f;

    if (!IsCastingSonicBoom(AI_VALUE2(Unit*, "find target", "murmur")))
        return 1.0f;

    return 0.0f;
}
