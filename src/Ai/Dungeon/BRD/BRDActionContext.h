/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BRDACTIONCONTEXT_H
#define PLAYERBOTS_BRDACTIONCONTEXT_H

#include "BRDActions.h"
#include "NamedObjectContext.h"

class VanillaDungeonBlackrockDepthsActionContext : public NamedObjectContext<Action>
{
public:
    VanillaDungeonBlackrockDepthsActionContext()
    {
        // Ambassador Flamelash
        creators["flamelash mark burning spirit"] =
            &VanillaDungeonBlackrockDepthsActionContext::flamelash_mark_burning_spirit;
    }

private:
    static Action* flamelash_mark_burning_spirit(PlayerbotAI* botAI)
    {
        return new FlamelashMarkBurningSpiritAction(botAI);
    }
};

#endif
