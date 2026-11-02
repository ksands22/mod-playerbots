/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SMActions.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SMShared.h"

using namespace EncounterHelpers;
using namespace SMShared;

// Arcanist Doan

bool DoanAvoidDetonationAction::Execute(Event /*event*/)
{
    Unit* doan = AI_VALUE2(Unit*, "find target", "arcanist doan");
    if (!doan)
        return false;

    float const distance = bot->GetExactDist2d(doan);
    if (distance >= DETONATION_SAFE_DISTANCE)
        return false;

    bot->CastStop();

    return MoveAway(doan, DETONATION_SAFE_DISTANCE - distance);
}

// Herod

bool HerodAvoidWhirlwindAction::Execute(Event /*event*/)
{
    Unit* herod = AI_VALUE2(Unit*, "find target", "herod");
    if (!herod)
        return false;

    float const distance = bot->GetExactDist2d(herod);
    if (distance >= HEROD_WHIRLWIND_SAFE_DISTANCE)
        return false;

    return MoveAway(herod, HEROD_WHIRLWIND_SAFE_DISTANCE - distance);
}

// High Inquisitor Whitemane

// After she resurrects Mograine, Whitemane heals him and mind controls, so DPS kills her first
bool WhitemaneMarkBossAction::Execute(Event /*event*/)
{
    return MarkTargetWithSkull(bot, AI_VALUE2(Unit*, "find target", "high inquisitor whitemane"));
}
