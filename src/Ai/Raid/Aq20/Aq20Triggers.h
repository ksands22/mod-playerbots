/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20TRIGGERS_H
#define PLAYERBOTS_AQ20TRIGGERS_H

#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "Trigger.h"

class Aq20MoveToCrystalTrigger : public Trigger
{
public:
    Aq20MoveToCrystalTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq20 move to crystal") {}
    bool IsActive() override;
};

class Aq20KillOrderMarkTrigger : public Trigger
{
public:
    Aq20KillOrderMarkTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq20 kill order mark") {}
    bool IsActive() override;
};

class Aq20CcMarkTrigger : public Trigger
{
public:
    Aq20CcMarkTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq20 cc mark") {}
    bool IsActive() override;
};

class Aq20KurinnaxxTankSwapTrigger : public Trigger
{
public:
    Aq20KurinnaxxTankSwapTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq20 kurinnaxx tank swap") {}
    bool IsActive() override;
};

class Aq20MoamDrainManaTrigger : public Trigger
{
public:
    Aq20MoamDrainManaTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq20 moam drain mana") {}
    bool IsActive() override;
};

class Aq20AyamissLarvaTrigger : public Trigger
{
public:
    Aq20AyamissLarvaTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq20 ayamiss larva") {}
    bool IsActive() override;
};

class Aq20BuruChasedTrigger : public Trigger
{
public:
    Aq20BuruChasedTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq20 buru chased") {}
    bool IsActive() override;
};

#endif
