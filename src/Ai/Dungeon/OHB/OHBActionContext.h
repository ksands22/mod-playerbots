/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_OHBACTIONCONTEXT_H
#define PLAYERBOTS_OHBACTIONCONTEXT_H

#include "NamedObjectContext.h"
#include "OHBActions.h"

class TbcDungeonOldHillsbradActionContext : public NamedObjectContext<Action>
{
public:
    TbcDungeonOldHillsbradActionContext()
    {
        // Lieutenant Drake
        creators["drake avoid whirlwind"] = &TbcDungeonOldHillsbradActionContext::drake_avoid_whirlwind;

        // Thrall's escort
        creators["thrall defend"] = &TbcDungeonOldHillsbradActionContext::thrall_defend;
    }

private:
    static Action* drake_avoid_whirlwind(PlayerbotAI* botAI) { return new DrakeAvoidWhirlwindAction(botAI); }
    static Action* thrall_defend(PlayerbotAI* botAI) { return new ThrallDefendAction(botAI); }
};

#endif
