/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ARCTRIGGERCONTEXT_H
#define PLAYERBOTS_ARCTRIGGERCONTEXT_H

#include "ArcTriggers.h"
#include "NamedObjectContext.h"

class TbcDungeonArcatrazTriggerContext : public NamedObjectContext<Trigger>
{
public:
    TbcDungeonArcatrazTriggerContext()
    {
        // Dalliah the Doomsayer
        creators["dalliah whirlwind"] = &TbcDungeonArcatrazTriggerContext::dalliah_whirlwind;
    }

private:
    static Trigger* dalliah_whirlwind(PlayerbotAI* botAI) { return new DalliahWhirlwindTrigger(botAI); }
};

#endif
