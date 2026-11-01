/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MARAACTIONCONTEXT_H
#define PLAYERBOTS_MARAACTIONCONTEXT_H

#include "MaraActions.h"
#include "NamedObjectContext.h"

class VanillaDungeonMaraudonActionContext : public NamedObjectContext<Action>
{
public:
    VanillaDungeonMaraudonActionContext()
    {
        // Tinkerer Gizlock
        creators["gizlock avoid dragon gun"] = &VanillaDungeonMaraudonActionContext::gizlock_avoid_dragon_gun;

        // Princess Theradras
        creators["theradras avoid dust field"] = &VanillaDungeonMaraudonActionContext::theradras_avoid_dust_field;
    }

private:
    static Action* gizlock_avoid_dragon_gun(PlayerbotAI* botAI) { return new GizlockAvoidDragonGunAction(botAI); }
    static Action* theradras_avoid_dust_field(PlayerbotAI* botAI) { return new TheradrasAvoidDustFieldAction(botAI); }
};

#endif
