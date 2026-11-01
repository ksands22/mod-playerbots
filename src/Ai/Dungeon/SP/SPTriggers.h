/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SPTRIGGERS_H
#define PLAYERBOTS_SPTRIGGERS_H

#include "Trigger.h"

// Mennu the Betrayer

class MennuIsActiveTrigger : public Trigger
{
public:
    MennuIsActiveTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mennu is active") {}

    bool IsActive() override;
};

#endif
