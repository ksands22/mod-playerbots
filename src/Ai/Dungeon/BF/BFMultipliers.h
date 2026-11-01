/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BFMULTIPLIERS_H
#define PLAYERBOTS_BFMULTIPLIERS_H

#include "Multiplier.h"

// Keli'dan the Breaker

class KelidanBurningNovaMultiplier : public Multiplier
{
public:
    KelidanBurningNovaMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "kelidan burning nova") {}

    float GetValue(Action* action) override;
};

#endif
