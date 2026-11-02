/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZFACTIONS_H
#define PLAYERBOTS_ZFACTIONS_H

#include "Action.h"

// Antu'sul

class AntusulMarkHealingWardAction : public Action
{
public:
    AntusulMarkHealingWardAction(PlayerbotAI* botAI) : Action(botAI, "antusul mark healing ward") {}

    bool Execute(Event event) override;
};

// Witch Doctor Zum'rah

class ZumrahMarkWardAction : public Action
{
public:
    ZumrahMarkWardAction(PlayerbotAI* botAI) : Action(botAI, "zumrah mark ward") {}

    bool Execute(Event event) override;
};

#endif
