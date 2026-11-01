/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BMActions.h"
#include "BMShared.h"
#include "Playerbots.h"

using namespace BMShared;

// Opening of the Dark Portal (Medivh)

bool BlackMorassAttackRiftMobAction::Execute(Event /*event*/)
{
    Unit* riftMob = FindNearestRiftMob(botAI);
    if (!riftMob)
        return false;

    return Attack(riftMob);
}
