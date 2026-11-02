/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SMTRIGGERS_H
#define PLAYERBOTS_SMTRIGGERS_H

#include "Trigger.h"

// Arcanist Doan

class DoanDetonationTrigger : public Trigger
{
public:
    DoanDetonationTrigger(PlayerbotAI* botAI) : Trigger(botAI, "doan detonation") {}

    bool IsActive() override;
};

// Herod

class HerodWhirlwindTrigger : public Trigger
{
public:
    HerodWhirlwindTrigger(PlayerbotAI* botAI) : Trigger(botAI, "herod whirlwind") {}

    bool IsActive() override;
};

// High Inquisitor Whitemane

class WhitemaneIsActiveTrigger : public Trigger
{
public:
    WhitemaneIsActiveTrigger(PlayerbotAI* botAI) : Trigger(botAI, "whitemane is active") {}

    bool IsActive() override;
};

#endif
