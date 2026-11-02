/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "OHBTriggers.h"
#include "OHBShared.h"
#include "Playerbots.h"

using namespace OHBShared;

// Lieutenant Drake

bool DrakeWhirlwindTrigger::IsActive()
{
    if (PlayerbotAI::IsTank(bot))
        return false;

    Unit* drake = AI_VALUE2(Unit*, "find target", "lieutenant drake");
    if (!drake || !drake->HasAura(SPELL_DRAKE_WHIRLWIND))
        return false;

    return bot->GetExactDist2d(drake) < DRAKE_WHIRLWIND_SAFE_DISTANCE;
}

// Thrall's escort

bool ThrallUnderAttackTrigger::IsActive()
{
    if (PlayerbotAI::IsHeal(bot))
        return false;

    return FindAttackerOfEscort(botAI);
}
