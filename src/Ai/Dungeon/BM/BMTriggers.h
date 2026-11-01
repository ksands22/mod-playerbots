/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BMTRIGGERS_H
#define PLAYERBOTS_BMTRIGGERS_H

#include "Trigger.h"

// Opening of the Dark Portal (Medivh)

class BlackMorassIdleRiftMobTrigger : public Trigger
{
public:
    BlackMorassIdleRiftMobTrigger(PlayerbotAI* botAI) : Trigger(botAI, "black morass idle rift mob") {}

    bool IsActive() override;
};

#endif
