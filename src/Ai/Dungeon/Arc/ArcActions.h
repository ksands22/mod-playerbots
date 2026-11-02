/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ARCACTIONS_H
#define PLAYERBOTS_ARCACTIONS_H

#include "MovementActions.h"

// Dalliah the Doomsayer

class DalliahAvoidWhirlwindAction : public MovementAction
{
public:
    DalliahAvoidWhirlwindAction(PlayerbotAI* botAI) : MovementAction(botAI, "dalliah avoid whirlwind") {}

    bool Execute(Event event) override;
};

#endif
