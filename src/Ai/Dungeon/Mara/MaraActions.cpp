/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "MaraActions.h"
#include "MaraShared.h"
#include "Playerbots.h"

using namespace MaraShared;

// Tinkerer Gizlock

bool GizlockAvoidDragonGunAction::Execute(Event /*event*/)
{
    Unit* gizlock = AI_VALUE2(Unit*, "find target", "tinkerer gizlock");
    if (!gizlock)
        return false;

    float const distance = bot->GetExactDist2d(gizlock);
    if (distance >= GOBLIN_DRAGON_GUN_SAFE_DISTANCE)
        return false;

    return MoveAway(gizlock, GOBLIN_DRAGON_GUN_SAFE_DISTANCE - distance);
}

// Princess Theradras

bool TheradrasAvoidDustFieldAction::Execute(Event /*event*/)
{
    Unit* theradras = AI_VALUE2(Unit*, "find target", "princess theradras");
    if (!theradras)
        return false;

    float const distance = bot->GetExactDist2d(theradras);
    if (distance >= DUST_FIELD_SAFE_DISTANCE)
        return false;

    return MoveAway(theradras, DUST_FIELD_SAFE_DISTANCE - distance);
}
