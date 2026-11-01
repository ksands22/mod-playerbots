/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_OHBACTIONS_H
#define PLAYERBOTS_OHBACTIONS_H

#include "AttackAction.h"
#include "MovementActions.h"

// Lieutenant Drake

class DrakeAvoidWhirlwindAction : public MovementAction
{
public:
    DrakeAvoidWhirlwindAction(PlayerbotAI* botAI) : MovementAction(botAI, "drake avoid whirlwind") {}

    bool Execute(Event event) override;
};

// Thrall's escort

class ThrallDefendAction : public AttackAction
{
public:
    ThrallDefendAction(PlayerbotAI* botAI) : AttackAction(botAI, "thrall defend") {}

    bool Execute(Event event) override;
};

#endif
