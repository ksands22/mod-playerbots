/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_HORACTIONCONTEXT_H
#define PLAYERBOTS_HORACTIONCONTEXT_H

#include "HoRActions.h"
#include "NamedObjectContext.h"

class WotlkDungeonHallsOfReflectionActionContext : public NamedObjectContext<Action>
{
public:
    WotlkDungeonHallsOfReflectionActionContext()
    {
        // Spirit waves and the Lich King escape
        creators["hor mark priority add"] = &WotlkDungeonHallsOfReflectionActionContext::hor_mark_priority_add;
    }

private:
    static Action* hor_mark_priority_add(PlayerbotAI* botAI) { return new HoRMarkPriorityAddAction(botAI); }
};

#endif
