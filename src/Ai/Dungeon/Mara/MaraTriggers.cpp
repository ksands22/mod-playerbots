/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "MaraTriggers.h"
#include "MaraShared.h"
#include "Playerbots.h"

using namespace MaraShared;

// Tinkerer Gizlock

bool GizlockDragonGunTrigger::IsActive()
{
    if (PlayerbotAI::IsTank(bot))
        return false;

    Unit* gizlock = AI_VALUE2(Unit*, "find target", "tinkerer gizlock");
    // A channel may carry its aura on the targets rather than the caster, so check the channel too
    if (!gizlock ||
        (!gizlock->HasAura(SPELL_GOBLIN_DRAGON_GUN) && !gizlock->FindCurrentSpellBySpellId(SPELL_GOBLIN_DRAGON_GUN)))
        return false;

    return  bot->GetExactDist2d(gizlock) < GOBLIN_DRAGON_GUN_SAFE_DISTANCE &&
            gizlock->HasInArc(GOBLIN_DRAGON_GUN_ARC, bot);
}

// Princess Theradras

bool TheradrasDustFieldTrigger::IsActive()
{
    Unit* theradras = AI_VALUE2(Unit*, "find target", "princess theradras");
    if (!theradras || !theradras->HasAura(SPELL_DUST_FIELD))
        return false;

    return bot->GetExactDist2d(theradras) < DUST_FIELD_SAFE_DISTANCE;
}
