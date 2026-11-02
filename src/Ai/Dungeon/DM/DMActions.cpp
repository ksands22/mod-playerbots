/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "DMActions.h"
#include "DMShared.h"
#include "DungeonHelpers.h"
#include "Playerbots.h"

using namespace DMShared;
using namespace DungeonHelpers;

// Immol'thar

bool ImmoltharMarkEyeAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_EYE_OF_IMMOLTHAR});
}

// Prince Tortheldrin

bool TortheldrinAvoidWhirlwindAction::Execute(Event /*event*/)
{
    Unit* tortheldrin = AI_VALUE2(Unit*, "find target", "prince tortheldrin");
    if (!tortheldrin)
        return false;

    float const distance = bot->GetExactDist2d(tortheldrin);
    if (distance >= TORTHELDRIN_WHIRLWIND_SAFE_DISTANCE)
        return false;

    return MoveAway(tortheldrin, TORTHELDRIN_WHIRLWIND_SAFE_DISTANCE - distance);
}
