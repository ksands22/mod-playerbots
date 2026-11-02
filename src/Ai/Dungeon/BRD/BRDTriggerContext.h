/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BRDTRIGGERCONTEXT_H
#define PLAYERBOTS_BRDTRIGGERCONTEXT_H

#include "BRDTriggers.h"
#include "NamedObjectContext.h"

class VanillaDungeonBlackrockDepthsTriggerContext : public NamedObjectContext<Trigger>
{
public:
    VanillaDungeonBlackrockDepthsTriggerContext()
    {
        // Ambassador Flamelash
        creators["flamelash is active"] = &VanillaDungeonBlackrockDepthsTriggerContext::flamelash_is_active;
    }

private:
    static Trigger* flamelash_is_active(PlayerbotAI* botAI) { return new FlamelashIsActiveTrigger(botAI); }
};

#endif
