/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_HORTRIGGERCONTEXT_H
#define PLAYERBOTS_HORTRIGGERCONTEXT_H

#include "HoRTriggers.h"
#include "NamedObjectContext.h"

class WotlkDungeonHallsOfReflectionTriggerContext : public NamedObjectContext<Trigger>
{
public:
    WotlkDungeonHallsOfReflectionTriggerContext()
    {
        // Spirit waves and the Lich King escape
        creators["hor priority add"] = &WotlkDungeonHallsOfReflectionTriggerContext::hor_priority_add;
    }

private:
    static Trigger* hor_priority_add(PlayerbotAI* botAI) { return new HoRPriorityAddTrigger(botAI); }
};

#endif
