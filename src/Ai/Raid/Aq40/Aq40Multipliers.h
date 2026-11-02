/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40MULTIPLIERS_H
#define PLAYERBOTS_AQ40MULTIPLIERS_H

#include "Multiplier.h"

class AnubisathSpellReflectMultiplier : public Multiplier
{
public:
    AnubisathSpellReflectMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "anubisath spell reflect multiplier") {}
    float GetValue(Action* action) override;
};

class AnubisathDefenderMultiplier : public Multiplier
{
public:
    AnubisathDefenderMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "anubisath defender multiplier") {}
    float GetValue(Action* action) override;
};

class AnubisathThunderclapMultiplier : public Multiplier
{
public:
    AnubisathThunderclapMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "anubisath thunderclap multiplier") {}
    float GetValue(Action* action) override;
};

class KriPoisonCloudMultiplier : public Multiplier
{
public:
    KriPoisonCloudMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "kri poison cloud multiplier") {}
    float GetValue(Action* action) override;
};

class SarturaWhirlwindMultiplier : public Multiplier
{
public:
    SarturaWhirlwindMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "sartura whirlwind multiplier") {}
    float GetValue(Action* action) override;
};

class FankrissMortalWoundMultiplier : public Multiplier
{
public:
    FankrissMortalWoundMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "fankriss mortal wound multiplier") {}
    float GetValue(Action* action) override;
};

class HuhuranAcidSpitMultiplier : public Multiplier
{
public:
    HuhuranAcidSpitMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "huhuran acid spit multiplier") {}
    float GetValue(Action* action) override;
};

class ViscidusPoisonShockMultiplier : public Multiplier
{
public:
    ViscidusPoisonShockMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "viscidus poison shock multiplier") {}
    float GetValue(Action* action) override;
};

class HuhuranWyvernStingMultiplier : public Multiplier
{
public:
    HuhuranWyvernStingMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "huhuran wyvern sting multiplier") {}
    float GetValue(Action* action) override;
};

#endif
