/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BFMultipliers.h"
#include "BFActions.h"
#include "BFShared.h"
#include "Playerbots.h"

using namespace BFShared;

// Keli'dan the Breaker

// He is stunned during Burning Nova, so keep chasing from walking bots back in before it goes off
float KelidanBurningNovaMultiplier::GetValue(Action* action)
{
    if (!dynamic_cast<MovementAction*>(action) || dynamic_cast<KelidanAvoidBurningNovaAction*>(action))
        return 1.0f;

    Unit* kelidan = AI_VALUE2(Unit*, "find target", "keli'dan the breaker");
    if (!kelidan || !kelidan->HasAura(SPELL_BURNING_NOVA))
        return 1.0f;

    return 0.0f;
}
