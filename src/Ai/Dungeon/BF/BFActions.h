/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BFACTIONS_H
#define PLAYERBOTS_BFACTIONS_H

#include "MovementActions.h"

// Keli'dan the Breaker

class KelidanAvoidBurningNovaAction : public MovementAction
{
public:
    KelidanAvoidBurningNovaAction(PlayerbotAI* botAI) : MovementAction(botAI, "kelidan avoid burning nova") {}

    bool Execute(Event event) override;
};

#endif
