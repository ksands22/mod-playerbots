/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ARCACTIONCONTEXT_H
#define PLAYERBOTS_ARCACTIONCONTEXT_H

#include "ArcActions.h"
#include "NamedObjectContext.h"

class TbcDungeonArcatrazActionContext : public NamedObjectContext<Action>
{
public:
    TbcDungeonArcatrazActionContext()
    {
        // Dalliah the Doomsayer
        creators["dalliah avoid whirlwind"] = &TbcDungeonArcatrazActionContext::dalliah_avoid_whirlwind;
    }

private:
    static Action* dalliah_avoid_whirlwind(PlayerbotAI* botAI) { return new DalliahAvoidWhirlwindAction(botAI); }
};

#endif
