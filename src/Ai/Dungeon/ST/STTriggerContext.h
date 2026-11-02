/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_STTRIGGERCONTEXT_H
#define PLAYERBOTS_STTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "STTriggers.h"

class VanillaDungeonSunkenTempleTriggerContext : public NamedObjectContext<Trigger>
{
public:
    VanillaDungeonSunkenTempleTriggerContext()
    {
        // Atal'ai defenders (Mijan, Zolo)
        creators["atalai defenders totems"] = &VanillaDungeonSunkenTempleTriggerContext::atalai_defenders_totems;
    }

private:
    static Trigger* atalai_defenders_totems(PlayerbotAI* botAI) { return new AtalaiDefendersTotemsTrigger(botAI); }
};

#endif
