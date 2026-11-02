/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BMACTIONCONTEXT_H
#define PLAYERBOTS_BMACTIONCONTEXT_H

#include "BMActions.h"
#include "NamedObjectContext.h"

class TbcDungeonBlackMorassActionContext : public NamedObjectContext<Action>
{
public:
    TbcDungeonBlackMorassActionContext()
    {
        // Opening of the Dark Portal (Medivh)
        creators["black morass attack rift mob"] = &TbcDungeonBlackMorassActionContext::black_morass_attack_rift_mob;
    }

private:
    static Action* black_morass_attack_rift_mob(PlayerbotAI* botAI)
    {
        return new BlackMorassAttackRiftMobAction(botAI);
    }
};

#endif
