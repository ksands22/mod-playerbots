/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_HORACTIONS_H
#define PLAYERBOTS_HORACTIONS_H

#include "Action.h"

// Spirit waves and the Lich King escape

class HoRMarkPriorityAddAction : public Action
{
public:
    HoRMarkPriorityAddAction(PlayerbotAI* botAI) : Action(botAI, "hor mark priority add") {}

    bool Execute(Event event) override;
};

#endif
