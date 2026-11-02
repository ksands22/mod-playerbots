/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SVACTIONS_H
#define PLAYERBOTS_SVACTIONS_H

#include "Action.h"

// Mekgineer Steamrigger

class SteamriggerMarkMechanicAction : public Action
{
public:
    SteamriggerMarkMechanicAction(PlayerbotAI* botAI) : Action(botAI, "steamrigger mark mechanic") {}

    bool Execute(Event event) override;
};

// Warlord Kalithresh

class KalithreshMarkDistillerAction : public Action
{
public:
    KalithreshMarkDistillerAction(PlayerbotAI* botAI) : Action(botAI, "kalithresh mark distiller") {}

    bool Execute(Event event) override;
};

#endif
