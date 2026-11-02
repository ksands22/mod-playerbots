/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MTTRIGGERS_H
#define PLAYERBOTS_MTTRIGGERS_H

#include "Trigger.h"

// Pandemonius

class PandemoniusDarkShellTrigger : public Trigger
{
public:
    PandemoniusDarkShellTrigger(PlayerbotAI* botAI) : Trigger(botAI, "pandemonius dark shell") {}

    bool IsActive() override;
};

// Nexus-Prince Shaffar

class ShaffarIsActiveTrigger : public Trigger
{
public:
    ShaffarIsActiveTrigger(PlayerbotAI* botAI) : Trigger(botAI, "shaffar is active") {}

    bool IsActive() override;
};

#endif
