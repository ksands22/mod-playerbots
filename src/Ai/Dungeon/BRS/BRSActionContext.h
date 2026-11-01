/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BRSACTIONCONTEXT_H
#define PLAYERBOTS_BRSACTIONCONTEXT_H

#include "BRSActions.h"
#include "NamedObjectContext.h"

class VanillaDungeonBlackrockSpireActionContext : public NamedObjectContext<Action>
{
public:
    VanillaDungeonBlackrockSpireActionContext()
    {
        // Warchief Rend Blackhand
        creators["rend avoid whirlwind"] = &VanillaDungeonBlackrockSpireActionContext::rend_avoid_whirlwind;

        // General Drakkisath
        creators["drakkisath avoid conflagration"] =
            &VanillaDungeonBlackrockSpireActionContext::drakkisath_avoid_conflagration;
    }

private:
    static Action* rend_avoid_whirlwind(PlayerbotAI* botAI) { return new RendAvoidWhirlwindAction(botAI); }

    static Action* drakkisath_avoid_conflagration(PlayerbotAI* botAI)
    {
        return new DrakkisathAvoidConflagrationAction(botAI);
    }
};

#endif
