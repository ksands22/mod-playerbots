/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BFTRIGGERCONTEXT_H
#define PLAYERBOTS_BFTRIGGERCONTEXT_H

#include "BFTriggers.h"
#include "NamedObjectContext.h"

class TbcDungeonBloodFurnaceTriggerContext : public NamedObjectContext<Trigger>
{
public:
    TbcDungeonBloodFurnaceTriggerContext()
    {
        // Keli'dan the Breaker
        creators["kelidan burning nova"] = &TbcDungeonBloodFurnaceTriggerContext::kelidan_burning_nova;
    }

private:
    static Trigger* kelidan_burning_nova(PlayerbotAI* botAI) { return new KelidanBurningNovaTrigger(botAI); }
};

#endif
