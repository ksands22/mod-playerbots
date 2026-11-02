/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SPACTIONCONTEXT_H
#define PLAYERBOTS_SPACTIONCONTEXT_H

#include "NamedObjectContext.h"
#include "SPActions.h"

class TbcDungeonSlavePensActionContext : public NamedObjectContext<Action>
{
public:
    TbcDungeonSlavePensActionContext()
    {
        // Mennu the Betrayer
        creators["mennu mark totem"] = &TbcDungeonSlavePensActionContext::mennu_mark_totem;
    }

private:
    static Action* mennu_mark_totem(PlayerbotAI* botAI) { return new MennuMarkTotemAction(botAI); }
};

#endif
