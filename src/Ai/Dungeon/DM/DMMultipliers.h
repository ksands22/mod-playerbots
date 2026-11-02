/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_DMMULTIPLIERS_H
#define PLAYERBOTS_DMMULTIPLIERS_H

#include "Multiplier.h"

// Prince Tortheldrin

class TortheldrinWhirlwindMultiplier : public Multiplier
{
public:
    TortheldrinWhirlwindMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "tortheldrin whirlwind") {}

    float GetValue(Action* action) override;
};

#endif
