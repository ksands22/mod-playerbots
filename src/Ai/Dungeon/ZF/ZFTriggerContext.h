/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZFTRIGGERCONTEXT_H
#define PLAYERBOTS_ZFTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "ZFTriggers.h"

class VanillaDungeonZulFarrakTriggerContext : public NamedObjectContext<Trigger>
{
public:
    VanillaDungeonZulFarrakTriggerContext()
    {
        // Antu'sul
        creators["antusul is active"] = &VanillaDungeonZulFarrakTriggerContext::antusul_is_active;

        // Witch Doctor Zum'rah
        creators["zumrah is active"] = &VanillaDungeonZulFarrakTriggerContext::zumrah_is_active;
    }

private:
    static Trigger* antusul_is_active(PlayerbotAI* botAI) { return new AntusulIsActiveTrigger(botAI); }
    static Trigger* zumrah_is_active(PlayerbotAI* botAI) { return new ZumrahIsActiveTrigger(botAI); }
};

#endif
