/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGMULTIPLIERS_H
#define PLAYERBOTS_ZGMULTIPLIERS_H

#include "Multiplier.h"

class VenoxisSnakeFormMultiplier : public Multiplier
{
public:
    VenoxisSnakeFormMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "venoxis snake form multiplier") {}
    float GetValue(Action* action) override;
};

class MandokirGazeMultiplier : public Multiplier
{
public:
    MandokirGazeMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "mandokir gaze multiplier") {}
    float GetValue(Action* action) override;
};

class JindoMultiplier : public Multiplier
{
public:
    JindoMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "jindo multiplier") {}
    float GetValue(Action* action) override;
};

class GrilekPursuitMultiplier : public Multiplier
{
public:
    GrilekPursuitMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "grilek pursuit multiplier") {}
    float GetValue(Action* action) override;
};

class HakkarPoisonousBloodMultiplier : public Multiplier
{
public:
    HakkarPoisonousBloodMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "hakkar poisonous blood multiplier") {}
    float GetValue(Action* action) override;
};

#endif
