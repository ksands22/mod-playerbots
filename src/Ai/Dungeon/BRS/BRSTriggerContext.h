/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BRSTRIGGERCONTEXT_H
#define PLAYERBOTS_BRSTRIGGERCONTEXT_H

#include "BRSTriggers.h"
#include "NamedObjectContext.h"

class VanillaDungeonBlackrockSpireTriggerContext : public NamedObjectContext<Trigger>
{
public:
    VanillaDungeonBlackrockSpireTriggerContext()
    {
        // Warchief Rend Blackhand
        creators["rend whirlwind"] = &VanillaDungeonBlackrockSpireTriggerContext::rend_whirlwind;

        // General Drakkisath
        creators["drakkisath conflagration"] = &VanillaDungeonBlackrockSpireTriggerContext::drakkisath_conflagration;
    }

private:
    static Trigger* rend_whirlwind(PlayerbotAI* botAI) { return new RendWhirlwindTrigger(botAI); }
    static Trigger* drakkisath_conflagration(PlayerbotAI* botAI) { return new DrakkisathConflagrationTrigger(botAI); }
};

#endif
