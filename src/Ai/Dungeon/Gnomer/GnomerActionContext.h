/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_GNOMERACTIONCONTEXT_H
#define PLAYERBOTS_GNOMERACTIONCONTEXT_H

#include "GnomerActions.h"
#include "NamedObjectContext.h"

class VanillaDungeonGnomereganActionContext : public NamedObjectContext<Action>
{
public:
    VanillaDungeonGnomereganActionContext()
    {
        // Mekgineer Thermaplugg
        creators["thermaplugg mark walking bomb"] =
            &VanillaDungeonGnomereganActionContext::thermaplugg_mark_walking_bomb;
    }

private:
    static Action* thermaplugg_mark_walking_bomb(PlayerbotAI* botAI)
    {
        return new ThermapluggMarkWalkingBombAction(botAI);
    }
};

#endif
