/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "MTTriggers.h"
#include "EncounterHelpers.h"
#include "MTShared.h"
#include "Playerbots.h"

using namespace EncounterHelpers;
using namespace MTShared;

// Pandemonius

bool PandemoniusDarkShellTrigger::IsActive()
{
    Unit* victim = bot->GetVictim();
    return victim && HasDarkShell(victim);
}

// Nexus-Prince Shaffar

bool ShaffarIsActiveTrigger::IsActive()
{
    return  IsMechanicTrackerBot(bot, MT_MAP_ID) &&
            AI_VALUE2(Unit*, "find target", "nexus-prince shaffar");
}
