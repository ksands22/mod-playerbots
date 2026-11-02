/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SVTRIGGERS_H
#define PLAYERBOTS_SVTRIGGERS_H

#include "Trigger.h"

// Mekgineer Steamrigger

class SteamriggerIsActiveTrigger : public Trigger
{
public:
    SteamriggerIsActiveTrigger(PlayerbotAI* botAI) : Trigger(botAI, "steamrigger is active") {}

    bool IsActive() override;
};

// Warlord Kalithresh

class KalithreshIsActiveTrigger : public Trigger
{
public:
    KalithreshIsActiveTrigger(PlayerbotAI* botAI) : Trigger(botAI, "kalithresh is active") {}

    bool IsActive() override;
};

#endif
