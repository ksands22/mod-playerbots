/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SLActions.h"
#include "DungeonHelpers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SLShared.h"

using namespace DungeonHelpers;
using namespace EncounterHelpers;
using namespace SLShared;

// Grandmaster Vorpil

bool VorpilMarkVoidTravelerAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_VOID_TRAVELER});
}

// Murmur

bool MurmurAvoidSonicBoomAction::Execute(Event /*event*/)
{
    Unit* murmur = AI_VALUE2(Unit*, "find target", "murmur");
    if (!murmur)
        return false;

    float const distance = bot->GetExactDist2d(murmur);
    if (distance >= SONIC_BOOM_SAFE_DISTANCE)
        return false;

    bot->CastStop();

    return MoveAway(murmur, SONIC_BOOM_SAFE_DISTANCE - distance);
}

bool MurmursTouchMoveFromGroupAction::Execute(Event /*event*/)
{
    if (!GetNearestPlayerInRadius(bot, MURMURS_TOUCH_SAFE_DISTANCE))
        return false;

    return MoveFromGroup(MURMURS_TOUCH_SAFE_DISTANCE);
}
