/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BOTACTIONS_H
#define PLAYERBOTS_BOTACTIONS_H

#include "MovementActions.h"

// High Botanist Freywinn

class FreywinnMarkFrayerAction : public Action
{
public:
    FreywinnMarkFrayerAction(PlayerbotAI* botAI) : Action(botAI, "freywinn mark frayer") {}

    bool Execute(Event event) override;
};

// Thorngrin the Tender

class ThorngrinAvoidHellfireAction : public MovementAction
{
public:
    ThorngrinAvoidHellfireAction(PlayerbotAI* botAI) : MovementAction(botAI, "thorngrin avoid hellfire") {}

    bool Execute(Event event) override;
};

// Warp Splinter

class WarpSplinterMarkSaplingAction : public Action
{
public:
    WarpSplinterMarkSaplingAction(PlayerbotAI* botAI) : Action(botAI, "warp splinter mark sapling") {}

    bool Execute(Event event) override;
};

#endif
