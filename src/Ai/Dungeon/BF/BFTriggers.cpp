/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BFTriggers.h"
#include "BFShared.h"
#include "Playerbots.h"

using namespace BFShared;

// Keli'dan the Breaker

bool KelidanBurningNovaTrigger::IsActive()
{
    Unit* kelidan = AI_VALUE2(Unit*, "find target", "keli'dan the breaker");
    if (!kelidan || !kelidan->HasAura(SPELL_BURNING_NOVA))
        return false;

    return bot->GetExactDist2d(kelidan) < BURNING_NOVA_SAFE_DISTANCE;
}
