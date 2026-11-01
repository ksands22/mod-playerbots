/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BFACTIONCONTEXT_H
#define PLAYERBOTS_BFACTIONCONTEXT_H

#include "BFActions.h"
#include "NamedObjectContext.h"

class TbcDungeonBloodFurnaceActionContext : public NamedObjectContext<Action>
{
public:
    TbcDungeonBloodFurnaceActionContext()
    {
        // Keli'dan the Breaker
        creators["kelidan avoid burning nova"] = &TbcDungeonBloodFurnaceActionContext::kelidan_avoid_burning_nova;
    }

private:
    static Action* kelidan_avoid_burning_nova(PlayerbotAI* botAI) { return new KelidanAvoidBurningNovaAction(botAI); }
};

#endif
