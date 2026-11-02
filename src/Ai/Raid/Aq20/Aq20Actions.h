/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20ACTIONS_H
#define PLAYERBOTS_AQ20ACTIONS_H

#include "AttackAction.h"
#include "MovementActions.h"
#include "PlayerbotAI.h"
#include "Playerbots.h"

class Aq20UseCrystalAction : public MovementAction
{
public:
    Aq20UseCrystalAction(PlayerbotAI* botAI, std::string const name = "aq20 use crystal") : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

class Aq20KillOrderMarkAction : public Action
{
public:
    Aq20KillOrderMarkAction(PlayerbotAI* botAI) : Action(botAI, "aq20 kill order mark") {}
    bool Execute(Event event) override;
};

class Aq20CcMarkAction : public Action
{
public:
    Aq20CcMarkAction(PlayerbotAI* botAI) : Action(botAI, "aq20 cc mark") {}
    bool Execute(Event event) override;
};

class Aq20KurinnaxxTauntAction : public AttackAction
{
public:
    Aq20KurinnaxxTauntAction(PlayerbotAI* botAI) : AttackAction(botAI, "aq20 kurinnaxx taunt") {}
    bool Execute(Event event) override;
};

class Aq20MoamDrainManaAction : public Action
{
public:
    Aq20MoamDrainManaAction(PlayerbotAI* botAI) : Action(botAI, "aq20 moam drain mana") {}
    bool Execute(Event event) override;
};

class Aq20AyamissAttackLarvaAction : public AttackAction
{
public:
    Aq20AyamissAttackLarvaAction(PlayerbotAI* botAI) : AttackAction(botAI, "aq20 ayamiss attack larva") {}
    bool Execute(Event event) override;
};

class Aq20BuruKiteToEggAction : public MovementAction
{
public:
    Aq20BuruKiteToEggAction(PlayerbotAI* botAI) : MovementAction(botAI, "aq20 buru kite to egg") {}
    bool Execute(Event event) override;
};

#endif
