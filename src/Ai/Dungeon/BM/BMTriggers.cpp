/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BMTriggers.h"
#include "BMShared.h"
#include "Playerbots.h"

using namespace BMShared;

// Opening of the Dark Portal (Medivh)

// Only while the bot has nothing to attack, so it doesn't leave mobs that are hitting the group
bool BlackMorassIdleRiftMobTrigger::IsActive()
{
    if (PlayerbotAI::IsHeal(bot))
        return false;

    Unit* target = AI_VALUE(Unit*, "current target");
    if (target && target->IsAlive())
        return false;

    return FindNearestRiftMob(botAI);
}
