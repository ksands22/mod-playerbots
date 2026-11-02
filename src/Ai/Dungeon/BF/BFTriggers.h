/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BFTRIGGERS_H
#define PLAYERBOTS_BFTRIGGERS_H

#include "Trigger.h"

// Keli'dan the Breaker

class KelidanBurningNovaTrigger : public Trigger
{
public:
    KelidanBurningNovaTrigger(PlayerbotAI* botAI) : Trigger(botAI, "kelidan burning nova") {}

    bool IsActive() override;
};

#endif
