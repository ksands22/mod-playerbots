/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SPACTIONS_H
#define PLAYERBOTS_SPACTIONS_H

#include "Action.h"

// Mennu the Betrayer

class MennuMarkTotemAction : public Action
{
public:
    MennuMarkTotemAction(PlayerbotAI* botAI) : Action(botAI, "mennu mark totem") {}

    bool Execute(Event event) override;
};

#endif
