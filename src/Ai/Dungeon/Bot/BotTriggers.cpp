/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BotTriggers.h"
#include "BotShared.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"

using namespace BotShared;
using namespace EncounterHelpers;

// High Botanist Freywinn

bool FreywinnIsActiveTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, BOT_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "high botanist freywinn");
}

// Thorngrin the Tender

bool ThorngrinHellfireTrigger::IsActive()
{
    Unit* thorngrin = AI_VALUE2(Unit*, "find target", "thorngrin the tender");
    if (!thorngrin || !thorngrin->HasAura(SPELL_HELLFIRE))
        return false;

    return bot->GetExactDist2d(thorngrin) < HELLFIRE_SAFE_DISTANCE;
}

// Warp Splinter

bool WarpSplinterIsActiveTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, BOT_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "warp splinter");
}
