/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_GNOMERTRIGGERS_H
#define PLAYERBOTS_GNOMERTRIGGERS_H

#include "Trigger.h"

// Mekgineer Thermaplugg

class ThermapluggWalkingBombTrigger : public Trigger
{
public:
    ThermapluggWalkingBombTrigger(PlayerbotAI* botAI) : Trigger(botAI, "thermaplugg walking bomb") {}

    bool IsActive() override;
};

#endif
