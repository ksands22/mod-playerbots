/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_STACTIONCONTEXT_H
#define PLAYERBOTS_STACTIONCONTEXT_H

#include "NamedObjectContext.h"
#include "STActions.h"

class VanillaDungeonSunkenTempleActionContext : public NamedObjectContext<Action>
{
public:
    VanillaDungeonSunkenTempleActionContext()
    {
        // Atal'ai defenders (Mijan, Zolo)
        creators["atalai defenders mark totem"] =
            &VanillaDungeonSunkenTempleActionContext::atalai_defenders_mark_totem;
    }

private:
    static Action* atalai_defenders_mark_totem(PlayerbotAI* botAI)
    {
        return new AtalaiDefendersMarkTotemAction(botAI);
    }
};

#endif
