/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BOTMULTIPLIERS_H
#define PLAYERBOTS_BOTMULTIPLIERS_H

#include "Multiplier.h"

// Thorngrin the Tender

class ThorngrinHellfireMultiplier : public Multiplier
{
public:
    ThorngrinHellfireMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "thorngrin hellfire") {}

    float GetValue(Action* action) override;
};

#endif
