/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BRDACTIONS_H
#define PLAYERBOTS_BRDACTIONS_H

#include "Action.h"

// Ambassador Flamelash

class FlamelashMarkBurningSpiritAction : public Action
{
public:
    FlamelashMarkBurningSpiritAction(PlayerbotAI* botAI) : Action(botAI, "flamelash mark burning spirit") {}

    bool Execute(Event event) override;
};

#endif
