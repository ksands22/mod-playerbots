/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_STACTIONS_H
#define PLAYERBOTS_STACTIONS_H

#include "Action.h"

// Atal'ai defenders (Mijan, Zolo)

class AtalaiDefendersMarkTotemAction : public Action
{
public:
    AtalaiDefendersMarkTotemAction(PlayerbotAI* botAI) : Action(botAI, "atalai defenders mark totem") {}

    bool Execute(Event event) override;
};

#endif
