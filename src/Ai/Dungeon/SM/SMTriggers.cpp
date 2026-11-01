/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SMTriggers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SMHelpers.h"

using namespace EncounterHelpers;
using namespace SMShared;

// Arcanist Doan

bool DoanDetonationTrigger::IsActive()
{
    Unit* doan = AI_VALUE2(Unit*, "find target", "arcanist doan");
    if (!IsDoanDetonating(doan))
        return false;

    return bot->GetExactDist2d(doan) < DETONATION_SAFE_DISTANCE;
}

// Herod

bool HerodWhirlwindTrigger::IsActive()
{
    if (PlayerbotAI::IsTank(bot))
        return false;

    Unit* herod = AI_VALUE2(Unit*, "find target", "herod");
    if (!IsHerodWhirlwinding(herod))
        return false;

    return bot->GetExactDist2d(herod) < HEROD_WHIRLWIND_SAFE_DISTANCE;
}

// High Inquisitor Whitemane

bool WhitemaneIsActiveTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, SM_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "high inquisitor whitemane");
}
