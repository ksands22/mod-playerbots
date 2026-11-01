/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BRSActions.h"
#include "BRSHelpers.h"
#include "BRSShared.h"
#include "Playerbots.h"

using namespace BRSShared;

// Warchief Rend Blackhand

bool RendAvoidWhirlwindAction::Execute(Event /*event*/)
{
    Unit* rend = AI_VALUE2(Unit*, "find target", "warchief rend blackhand");
    if (!rend)
        return false;

    float const distance = bot->GetExactDist2d(rend);
    if (distance >= REND_WHIRLWIND_SAFE_DISTANCE)
        return false;

    return MoveAway(rend, REND_WHIRLWIND_SAFE_DISTANCE - distance);
}

// General Drakkisath

bool DrakkisathAvoidConflagrationAction::Execute(Event /*event*/)
{
    Player* conflagrated = GetNearbyConflagratedMember(bot);
    if (!conflagrated)
        return false;

    return MoveAway(conflagrated, CONFLAGRATION_SAFE_DISTANCE - bot->GetExactDist2d(conflagrated));
}
