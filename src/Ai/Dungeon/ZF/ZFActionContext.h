/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZFACTIONCONTEXT_H
#define PLAYERBOTS_ZFACTIONCONTEXT_H

#include "NamedObjectContext.h"
#include "ZFActions.h"

class VanillaDungeonZulFarrakActionContext : public NamedObjectContext<Action>
{
public:
    VanillaDungeonZulFarrakActionContext()
    {
        // Antu'sul
        creators["antusul mark healing ward"] = &VanillaDungeonZulFarrakActionContext::antusul_mark_healing_ward;

        // Witch Doctor Zum'rah
        creators["zumrah mark ward"] = &VanillaDungeonZulFarrakActionContext::zumrah_mark_ward;
    }

private:
    static Action* antusul_mark_healing_ward(PlayerbotAI* botAI) { return new AntusulMarkHealingWardAction(botAI); }
    static Action* zumrah_mark_ward(PlayerbotAI* botAI) { return new ZumrahMarkWardAction(botAI); }
};

#endif
