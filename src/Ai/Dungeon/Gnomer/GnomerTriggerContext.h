/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_GNOMERTRIGGERCONTEXT_H
#define PLAYERBOTS_GNOMERTRIGGERCONTEXT_H

#include "GnomerTriggers.h"
#include "NamedObjectContext.h"

class VanillaDungeonGnomereganTriggerContext : public NamedObjectContext<Trigger>
{
public:
    VanillaDungeonGnomereganTriggerContext()
    {
        // Mekgineer Thermaplugg
        creators["thermaplugg walking bomb"] = &VanillaDungeonGnomereganTriggerContext::thermaplugg_walking_bomb;
    }

private:
    static Trigger* thermaplugg_walking_bomb(PlayerbotAI* botAI) { return new ThermapluggWalkingBombTrigger(botAI); }
};

#endif
