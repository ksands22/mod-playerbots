/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SLACTIONS_H
#define PLAYERBOTS_SLACTIONS_H

#include "MovementActions.h"

// Grandmaster Vorpil

class VorpilMarkVoidTravelerAction : public Action
{
public:
    VorpilMarkVoidTravelerAction(PlayerbotAI* botAI) : Action(botAI, "vorpil mark void traveler") {}

    bool Execute(Event event) override;
};

// Murmur

class MurmurAvoidSonicBoomAction : public MovementAction
{
public:
    MurmurAvoidSonicBoomAction(PlayerbotAI* botAI) : MovementAction(botAI, "murmur avoid sonic boom") {}

    bool Execute(Event event) override;
};

class MurmursTouchMoveFromGroupAction : public MovementAction
{
public:
    MurmursTouchMoveFromGroupAction(PlayerbotAI* botAI) : MovementAction(botAI, "murmurs touch move from group") {}

    bool Execute(Event event) override;
};

#endif
