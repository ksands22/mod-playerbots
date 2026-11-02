/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_GNOMERACTIONS_H
#define PLAYERBOTS_GNOMERACTIONS_H

#include "Action.h"

// Mekgineer Thermaplugg

class ThermapluggMarkWalkingBombAction : public Action
{
public:
    ThermapluggMarkWalkingBombAction(PlayerbotAI* botAI) : Action(botAI, "thermaplugg mark walking bomb") {}

    bool Execute(Event event) override;
};

#endif
