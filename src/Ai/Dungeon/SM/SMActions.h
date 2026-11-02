/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SMACTIONS_H
#define PLAYERBOTS_SMACTIONS_H

#include "Action.h"
#include "MovementActions.h"

// Arcanist Doan

class DoanAvoidDetonationAction : public MovementAction
{
public:
    DoanAvoidDetonationAction(PlayerbotAI* botAI) : MovementAction(botAI, "doan avoid detonation") {}

    bool Execute(Event event) override;
};

// Herod

class HerodAvoidWhirlwindAction : public MovementAction
{
public:
    HerodAvoidWhirlwindAction(PlayerbotAI* botAI) : MovementAction(botAI, "herod avoid whirlwind") {}

    bool Execute(Event event) override;
};

// High Inquisitor Whitemane

class WhitemaneMarkBossAction : public Action
{
public:
    WhitemaneMarkBossAction(PlayerbotAI* botAI) : Action(botAI, "whitemane mark boss") {}

    bool Execute(Event event) override;
};

#endif
