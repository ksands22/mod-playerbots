/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MTACTIONS_H
#define PLAYERBOTS_MTACTIONS_H

#include "Action.h"

// Pandemonius

class PandemoniusStopAttackingAction : public Action
{
public:
    PandemoniusStopAttackingAction(PlayerbotAI* botAI) : Action(botAI, "pandemonius stop attacking") {}

    bool Execute(Event event) override;
};

// Nexus-Prince Shaffar

class ShaffarMarkBeaconAction : public Action
{
public:
    ShaffarMarkBeaconAction(PlayerbotAI* botAI) : Action(botAI, "shaffar mark beacon") {}

    bool Execute(Event event) override;
};

#endif
