/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MARATRIGGERCONTEXT_H
#define PLAYERBOTS_MARATRIGGERCONTEXT_H

#include "MaraTriggers.h"
#include "NamedObjectContext.h"

class VanillaDungeonMaraudonTriggerContext : public NamedObjectContext<Trigger>
{
public:
    VanillaDungeonMaraudonTriggerContext()
    {
        // Tinkerer Gizlock
        creators["gizlock dragon gun"] = &VanillaDungeonMaraudonTriggerContext::gizlock_dragon_gun;

        // Princess Theradras
        creators["theradras dust field"] = &VanillaDungeonMaraudonTriggerContext::theradras_dust_field;
    }

private:
    static Trigger* gizlock_dragon_gun(PlayerbotAI* botAI) { return new GizlockDragonGunTrigger(botAI); }
    static Trigger* theradras_dust_field(PlayerbotAI* botAI) { return new TheradrasDustFieldTrigger(botAI); }
};

#endif
