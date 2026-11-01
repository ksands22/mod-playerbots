/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SLTRIGGERS_H
#define PLAYERBOTS_SLTRIGGERS_H

#include "Trigger.h"

// Grandmaster Vorpil

class VorpilIsActiveTrigger : public Trigger
{
public:
    VorpilIsActiveTrigger(PlayerbotAI* botAI) : Trigger(botAI, "vorpil is active") {}

    bool IsActive() override;
};

// Murmur

class MurmurSonicBoomTrigger : public Trigger
{
public:
    MurmurSonicBoomTrigger(PlayerbotAI* botAI) : Trigger(botAI, "murmur sonic boom") {}

    bool IsActive() override;
};

class MurmursTouchTrigger : public Trigger
{
public:
    MurmursTouchTrigger(PlayerbotAI* botAI) : Trigger(botAI, "murmurs touch") {}

    bool IsActive() override;
};

#endif
