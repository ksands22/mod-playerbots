/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BRSTRIGGERS_H
#define PLAYERBOTS_BRSTRIGGERS_H

#include "Trigger.h"

// Warchief Rend Blackhand

class RendWhirlwindTrigger : public Trigger
{
public:
    RendWhirlwindTrigger(PlayerbotAI* botAI) : Trigger(botAI, "rend whirlwind") {}

    bool IsActive() override;
};

// General Drakkisath

class DrakkisathConflagrationTrigger : public Trigger
{
public:
    DrakkisathConflagrationTrigger(PlayerbotAI* botAI) : Trigger(botAI, "drakkisath conflagration") {}

    bool IsActive() override;
};

#endif
