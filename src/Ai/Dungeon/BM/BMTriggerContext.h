/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BMTRIGGERCONTEXT_H
#define PLAYERBOTS_BMTRIGGERCONTEXT_H

#include "BMTriggers.h"
#include "NamedObjectContext.h"

class TbcDungeonBlackMorassTriggerContext : public NamedObjectContext<Trigger>
{
public:
    TbcDungeonBlackMorassTriggerContext()
    {
        // Opening of the Dark Portal (Medivh)
        creators["black morass idle rift mob"] = &TbcDungeonBlackMorassTriggerContext::black_morass_idle_rift_mob;
    }

private:
    static Trigger* black_morass_idle_rift_mob(PlayerbotAI* botAI) { return new BlackMorassIdleRiftMobTrigger(botAI); }
};

#endif
