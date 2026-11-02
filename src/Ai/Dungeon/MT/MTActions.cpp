/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "MTActions.h"
#include "DungeonHelpers.h"
#include "MTShared.h"
#include "Playerbots.h"

using namespace DungeonHelpers;
using namespace MTShared;

// Pandemonius

bool PandemoniusStopAttackingAction::Execute(Event /*event*/)
{
    Unit* victim = bot->GetVictim();
    if (!victim || !HasDarkShell(victim))
        return false;

    bot->AttackStop();
    bot->CastStop();
    return true;
}

// Nexus-Prince Shaffar

bool ShaffarMarkBeaconAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_ETHEREAL_BEACON});
}
