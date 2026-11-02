/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_DMACTIONS_H
#define PLAYERBOTS_DMACTIONS_H

#include "MovementActions.h"

// Immol'thar

class ImmoltharMarkEyeAction : public Action
{
public:
    ImmoltharMarkEyeAction(PlayerbotAI* botAI) : Action(botAI, "immolthar mark eye") {}

    bool Execute(Event event) override;
};

// Prince Tortheldrin

class TortheldrinAvoidWhirlwindAction : public MovementAction
{
public:
    TortheldrinAvoidWhirlwindAction(PlayerbotAI* botAI) : MovementAction(botAI, "tortheldrin avoid whirlwind") {}

    bool Execute(Event event) override;
};

#endif
