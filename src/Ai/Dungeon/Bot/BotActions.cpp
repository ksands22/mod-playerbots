/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BotActions.h"
#include "BotShared.h"
#include "DungeonHelpers.h"
#include "Playerbots.h"

using namespace BotShared;
using namespace DungeonHelpers;

// High Botanist Freywinn

bool FreywinnMarkFrayerAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_FRAYER});
}

// Thorngrin the Tender

bool ThorngrinAvoidHellfireAction::Execute(Event /*event*/)
{
    Unit* thorngrin = AI_VALUE2(Unit*, "find target", "thorngrin the tender");
    if (!thorngrin)
        return false;

    float const distance = bot->GetExactDist2d(thorngrin);
    if (distance >= HELLFIRE_SAFE_DISTANCE)
        return false;

    return MoveAway(thorngrin, HELLFIRE_SAFE_DISTANCE - distance);
}

// Warp Splinter

bool WarpSplinterMarkSaplingAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_SAPLING});
}
