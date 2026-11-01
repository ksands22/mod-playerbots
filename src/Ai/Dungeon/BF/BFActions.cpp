/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BFActions.h"
#include "BFShared.h"
#include "Playerbots.h"

using namespace BFShared;

// Keli'dan the Breaker

bool KelidanAvoidBurningNovaAction::Execute(Event /*event*/)
{
    Unit* kelidan = AI_VALUE2(Unit*, "find target", "keli'dan the breaker");
    if (!kelidan)
        return false;

    float const distance = bot->GetExactDist2d(kelidan);
    if (distance >= BURNING_NOVA_SAFE_DISTANCE)
        return false;

    bot->CastStop();

    return MoveAway(kelidan, BURNING_NOVA_SAFE_DISTANCE - distance);
}
