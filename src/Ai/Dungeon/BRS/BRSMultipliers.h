/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BRSMULTIPLIERS_H
#define PLAYERBOTS_BRSMULTIPLIERS_H

#include "Multiplier.h"

// Warchief Rend Blackhand

class RendWhirlwindMultiplier : public Multiplier
{
public:
    RendWhirlwindMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "rend whirlwind") {}

    float GetValue(Action* action) override;
};

#endif
