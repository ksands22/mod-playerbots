/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BOTTRIGGERS_H
#define PLAYERBOTS_BOTTRIGGERS_H

#include "Trigger.h"

// High Botanist Freywinn

class FreywinnIsActiveTrigger : public Trigger
{
public:
    FreywinnIsActiveTrigger(PlayerbotAI* botAI) : Trigger(botAI, "freywinn is active") {}

    bool IsActive() override;
};

// Thorngrin the Tender

class ThorngrinHellfireTrigger : public Trigger
{
public:
    ThorngrinHellfireTrigger(PlayerbotAI* botAI) : Trigger(botAI, "thorngrin hellfire") {}

    bool IsActive() override;
};

// Warp Splinter

class WarpSplinterIsActiveTrigger : public Trigger
{
public:
    WarpSplinterIsActiveTrigger(PlayerbotAI* botAI) : Trigger(botAI, "warp splinter is active") {}

    bool IsActive() override;
};

#endif
