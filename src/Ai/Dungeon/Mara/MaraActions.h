/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MARAACTIONS_H
#define PLAYERBOTS_MARAACTIONS_H

#include "MovementActions.h"

// Tinkerer Gizlock

class GizlockAvoidDragonGunAction : public MovementAction
{
public:
    GizlockAvoidDragonGunAction(PlayerbotAI* botAI) : MovementAction(botAI, "gizlock avoid dragon gun") {}

    bool Execute(Event event) override;
};

// Princess Theradras

class TheradrasAvoidDustFieldAction : public MovementAction
{
public:
    TheradrasAvoidDustFieldAction(PlayerbotAI* botAI) : MovementAction(botAI, "theradras avoid dust field") {}

    bool Execute(Event event) override;
};

#endif
