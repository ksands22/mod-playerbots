/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BRSACTIONS_H
#define PLAYERBOTS_BRSACTIONS_H

#include "MovementActions.h"

// Warchief Rend Blackhand

class RendAvoidWhirlwindAction : public MovementAction
{
public:
    RendAvoidWhirlwindAction(PlayerbotAI* botAI) : MovementAction(botAI, "rend avoid whirlwind") {}

    bool Execute(Event event) override;
};

// General Drakkisath

class DrakkisathAvoidConflagrationAction : public MovementAction
{
public:
    DrakkisathAvoidConflagrationAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "drakkisath avoid conflagration")
    {
    }

    bool Execute(Event event) override;
};

#endif
