/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_HORTRIGGERS_H
#define PLAYERBOTS_HORTRIGGERS_H

#include "Trigger.h"

// Spirit waves and the Lich King escape

class HoRPriorityAddTrigger : public Trigger
{
public:
    HoRPriorityAddTrigger(PlayerbotAI* botAI) : Trigger(botAI, "hor priority add") {}

    bool IsActive() override;
};

#endif
