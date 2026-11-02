/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SVACTIONCONTEXT_H
#define PLAYERBOTS_SVACTIONCONTEXT_H

#include "NamedObjectContext.h"
#include "SVActions.h"

class TbcDungeonSteamvaultActionContext : public NamedObjectContext<Action>
{
public:
    TbcDungeonSteamvaultActionContext()
    {
        // Mekgineer Steamrigger
        creators["steamrigger mark mechanic"] = &TbcDungeonSteamvaultActionContext::steamrigger_mark_mechanic;

        // Warlord Kalithresh
        creators["kalithresh mark distiller"] = &TbcDungeonSteamvaultActionContext::kalithresh_mark_distiller;
    }

private:
    static Action* steamrigger_mark_mechanic(PlayerbotAI* botAI) { return new SteamriggerMarkMechanicAction(botAI); }
    static Action* kalithresh_mark_distiller(PlayerbotAI* botAI) { return new KalithreshMarkDistillerAction(botAI); }
};

#endif
