/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ARCMULTIPLIERS_H
#define PLAYERBOTS_ARCMULTIPLIERS_H

#include "Multiplier.h"

// Dalliah the Doomsayer

class DalliahWhirlwindMultiplier : public Multiplier
{
public:
    DalliahWhirlwindMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "dalliah whirlwind") {}

    float GetValue(Action* action) override;
};

#endif
