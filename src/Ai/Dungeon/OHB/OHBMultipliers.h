/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_OHBMULTIPLIERS_H
#define PLAYERBOTS_OHBMULTIPLIERS_H

#include "Multiplier.h"

// Lieutenant Drake

class DrakeWhirlwindMultiplier : public Multiplier
{
public:
    DrakeWhirlwindMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "drake whirlwind") {}

    float GetValue(Action* action) override;
};

// Thrall's escort

class ThrallDefendMultiplier : public Multiplier
{
public:
    ThrallDefendMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "thrall defend") {}

    float GetValue(Action* action) override;
};

#endif
