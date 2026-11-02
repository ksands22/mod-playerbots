/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MTACTIONCONTEXT_H
#define PLAYERBOTS_MTACTIONCONTEXT_H

#include "MTActions.h"
#include "NamedObjectContext.h"

class TbcDungeonManaTombsActionContext : public NamedObjectContext<Action>
{
public:
    TbcDungeonManaTombsActionContext()
    {
        // Pandemonius
        creators["pandemonius stop attacking"] = &TbcDungeonManaTombsActionContext::pandemonius_stop_attacking;

        // Nexus-Prince Shaffar
        creators["shaffar mark beacon"] = &TbcDungeonManaTombsActionContext::shaffar_mark_beacon;
    }

private:
    static Action* pandemonius_stop_attacking(PlayerbotAI* botAI) { return new PandemoniusStopAttackingAction(botAI); }
    static Action* shaffar_mark_beacon(PlayerbotAI* botAI) { return new ShaffarMarkBeaconAction(botAI); }
};

#endif
