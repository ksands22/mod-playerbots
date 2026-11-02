/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SMMULTIPLIERS_H
#define PLAYERBOTS_SMMULTIPLIERS_H

#include "Multiplier.h"

// Arcanist Doan

class DoanDetonationMultiplier : public Multiplier
{
public:
    DoanDetonationMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "doan detonation") {}

    float GetValue(Action* action) override;
};

// Herod

class HerodWhirlwindMultiplier : public Multiplier
{
public:
    HerodWhirlwindMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "herod whirlwind") {}

    float GetValue(Action* action) override;
};

#endif
