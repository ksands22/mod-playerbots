/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_DMTRIGGERS_H
#define PLAYERBOTS_DMTRIGGERS_H

#include "Trigger.h"

// Immol'thar

class ImmoltharIsActiveTrigger : public Trigger
{
public:
    ImmoltharIsActiveTrigger(PlayerbotAI* botAI) : Trigger(botAI, "immolthar is active") {}

    bool IsActive() override;
};

// Prince Tortheldrin

class TortheldrinWhirlwindTrigger : public Trigger
{
public:
    TortheldrinWhirlwindTrigger(PlayerbotAI* botAI) : Trigger(botAI, "tortheldrin whirlwind") {}

    bool IsActive() override;
};

#endif
