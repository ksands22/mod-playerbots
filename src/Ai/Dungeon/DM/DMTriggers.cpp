/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "DMTriggers.h"
#include "DMShared.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"

using namespace DMShared;
using namespace EncounterHelpers;

// Immol'thar

bool ImmoltharIsActiveTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, DM_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "immol'thar");
}

// Prince Tortheldrin

bool TortheldrinWhirlwindTrigger::IsActive()
{
    if (PlayerbotAI::IsTank(bot))
        return false;

    Unit* tortheldrin = AI_VALUE2(Unit*, "find target", "prince tortheldrin");
    if (!tortheldrin || !tortheldrin->HasAura(SPELL_TORTHELDRIN_WHIRLWIND))
        return false;

    return bot->GetExactDist2d(tortheldrin) < TORTHELDRIN_WHIRLWIND_SAFE_DISTANCE;
}
