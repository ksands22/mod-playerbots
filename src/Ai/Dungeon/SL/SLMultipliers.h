/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SLMULTIPLIERS_H
#define PLAYERBOTS_SLMULTIPLIERS_H

#include "Multiplier.h"

// Murmur

class MurmurSonicBoomMultiplier : public Multiplier
{
public:
    MurmurSonicBoomMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "murmur sonic boom") {}

    float GetValue(Action* action) override;
};

#endif
