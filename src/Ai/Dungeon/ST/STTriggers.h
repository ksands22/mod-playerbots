/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_STTRIGGERS_H
#define PLAYERBOTS_STTRIGGERS_H

#include "Trigger.h"

// Atal'ai defenders (Mijan, Zolo)

class AtalaiDefendersTotemsTrigger : public Trigger
{
public:
    AtalaiDefendersTotemsTrigger(PlayerbotAI* botAI) : Trigger(botAI, "atalai defenders totems") {}

    bool IsActive() override;
};

#endif
