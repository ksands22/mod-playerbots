/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20MULTIPLIERS_H
#define PLAYERBOTS_AQ20MULTIPLIERS_H

#include "Multiplier.h"

class KurinnaxxMortalWoundMultiplier : public Multiplier
{
public:
    KurinnaxxMortalWoundMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "kurinnaxx mortal wound multiplier") {}
    float GetValue(Action* action) override;
};

class AyamissMultiplier : public Multiplier
{
public:
    AyamissMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "ayamiss multiplier") {}
    float GetValue(Action* action) override;
};

class BuruChasedMultiplier : public Multiplier
{
public:
    BuruChasedMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "buru chased multiplier") {}
    float GetValue(Action* action) override;
};

#endif
