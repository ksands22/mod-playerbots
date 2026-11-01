/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZFTRIGGERS_H
#define PLAYERBOTS_ZFTRIGGERS_H

#include "Trigger.h"

// Antu'sul

class AntusulIsActiveTrigger : public Trigger
{
public:
    AntusulIsActiveTrigger(PlayerbotAI* botAI) : Trigger(botAI, "antusul is active") {}

    bool IsActive() override;
};

// Witch Doctor Zum'rah

class ZumrahIsActiveTrigger : public Trigger
{
public:
    ZumrahIsActiveTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zumrah is active") {}

    bool IsActive() override;
};

#endif
