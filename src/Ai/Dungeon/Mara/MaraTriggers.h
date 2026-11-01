/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MARATRIGGERS_H
#define PLAYERBOTS_MARATRIGGERS_H

#include "Trigger.h"

// Tinkerer Gizlock

class GizlockDragonGunTrigger : public Trigger
{
public:
    GizlockDragonGunTrigger(PlayerbotAI* botAI) : Trigger(botAI, "gizlock dragon gun") {}

    bool IsActive() override;
};

// Princess Theradras

class TheradrasDustFieldTrigger : public Trigger
{
public:
    TheradrasDustFieldTrigger(PlayerbotAI* botAI) : Trigger(botAI, "theradras dust field") {}

    bool IsActive() override;
};

#endif
