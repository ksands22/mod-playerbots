/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BRSTriggers.h"
#include "BRSHelpers.h"
#include "BRSShared.h"
#include "Playerbots.h"

using namespace BRSShared;

// Warchief Rend Blackhand

bool RendWhirlwindTrigger::IsActive()
{
    if (PlayerbotAI::IsTank(bot))
        return false;

    Unit* rend = AI_VALUE2(Unit*, "find target", "warchief rend blackhand");
    if (!rend || !rend->HasAura(SPELL_REND_WHIRLWIND))
        return false;

    return bot->GetExactDist2d(rend) < REND_WHIRLWIND_SAFE_DISTANCE;
}

// General Drakkisath

bool DrakkisathConflagrationTrigger::IsActive()
{
    if (!AI_VALUE2(Unit*, "find target", "general drakkisath"))
        return false;

    return GetNearbyConflagratedMember(bot);
}
