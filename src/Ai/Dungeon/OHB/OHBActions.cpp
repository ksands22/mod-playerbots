/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "OHBActions.h"
#include "OHBShared.h"
#include "Playerbots.h"

using namespace OHBShared;

// Lieutenant Drake

bool DrakeAvoidWhirlwindAction::Execute(Event /*event*/)
{
    Unit* drake = AI_VALUE2(Unit*, "find target", "lieutenant drake");
    if (!drake)
        return false;

    float const distance = bot->GetExactDist2d(drake);
    if (distance >= DRAKE_WHIRLWIND_SAFE_DISTANCE)
        return false;

    return MoveAway(drake, DRAKE_WHIRLWIND_SAFE_DISTANCE - distance);
}

// Thrall's escort

bool ThrallDefendAction::Execute(Event /*event*/)
{
    // Don't swap between attackers while already on one
    if (IsAttackingEscort(AI_VALUE(Unit*, "current target")))
        return false;

    Unit* attacker = FindAttackerOfEscort(botAI);
    if (!attacker)
        return false;

    return Attack(attacker);
}
