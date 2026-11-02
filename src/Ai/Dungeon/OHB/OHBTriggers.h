/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_OHBTRIGGERS_H
#define PLAYERBOTS_OHBTRIGGERS_H

#include "Trigger.h"

// Lieutenant Drake

class DrakeWhirlwindTrigger : public Trigger
{
public:
    DrakeWhirlwindTrigger(PlayerbotAI* botAI) : Trigger(botAI, "drake whirlwind") {}

    bool IsActive() override;
};

// Thrall's escort

class ThrallUnderAttackTrigger : public Trigger
{
public:
    ThrallUnderAttackTrigger(PlayerbotAI* botAI) : Trigger(botAI, "thrall under attack") {}

    bool IsActive() override;
};

#endif
