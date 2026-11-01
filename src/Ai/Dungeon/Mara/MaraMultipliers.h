/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MARAMULTIPLIERS_H
#define PLAYERBOTS_MARAMULTIPLIERS_H

#include "Multiplier.h"

// Princess Theradras

class TheradrasDustFieldMultiplier : public Multiplier
{
public:
    TheradrasDustFieldMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "theradras dust field") {}

    float GetValue(Action* action) override;
};

#endif
