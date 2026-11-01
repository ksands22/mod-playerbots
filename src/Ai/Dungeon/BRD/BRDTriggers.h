/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BRDTRIGGERS_H
#define PLAYERBOTS_BRDTRIGGERS_H

#include "Trigger.h"

// Ambassador Flamelash

class FlamelashIsActiveTrigger : public Trigger
{
public:
    FlamelashIsActiveTrigger(PlayerbotAI* botAI) : Trigger(botAI, "flamelash is active") {}

    bool IsActive() override;
};

#endif
