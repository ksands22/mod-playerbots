/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_DMTRIGGERCONTEXT_H
#define PLAYERBOTS_DMTRIGGERCONTEXT_H

#include "DMTriggers.h"
#include "NamedObjectContext.h"

class VanillaDungeonDireMaulTriggerContext : public NamedObjectContext<Trigger>
{
public:
    VanillaDungeonDireMaulTriggerContext()
    {
        // Immol'thar
        creators["immolthar is active"] = &VanillaDungeonDireMaulTriggerContext::immolthar_is_active;

        // Prince Tortheldrin
        creators["tortheldrin whirlwind"] = &VanillaDungeonDireMaulTriggerContext::tortheldrin_whirlwind;
    }

private:
    static Trigger* immolthar_is_active(PlayerbotAI* botAI) { return new ImmoltharIsActiveTrigger(botAI); }
    static Trigger* tortheldrin_whirlwind(PlayerbotAI* botAI) { return new TortheldrinWhirlwindTrigger(botAI); }
};

#endif
