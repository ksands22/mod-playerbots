/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_RFDTRIGGERS_H
#define PLAYERBOTS_RFDTRIGGERS_H

#include "Trigger.h"

// Extinguishing the Idol (Belnistrasz)

class BelnistraszUnderAttackTrigger : public Trigger
{
public:
    BelnistraszUnderAttackTrigger(PlayerbotAI* botAI) : Trigger(botAI, "belnistrasz under attack") {}

    bool IsActive() override;
};

#endif
