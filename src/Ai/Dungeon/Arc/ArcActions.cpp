/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ArcActions.h"
#include "ArcShared.h"
#include "Playerbots.h"

using namespace ArcShared;

// Dalliah the Doomsayer

bool DalliahAvoidWhirlwindAction::Execute(Event /*event*/)
{
    Unit* dalliah = AI_VALUE2(Unit*, "find target", "dalliah the doomsayer");
    if (!dalliah)
        return false;

    float const distance = bot->GetExactDist2d(dalliah);
    if (distance >= DALLIAH_WHIRLWIND_SAFE_DISTANCE)
        return false;

    return MoveAway(dalliah, DALLIAH_WHIRLWIND_SAFE_DISTANCE - distance);
}
