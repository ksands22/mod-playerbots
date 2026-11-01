/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_OHBTRIGGERCONTEXT_H
#define PLAYERBOTS_OHBTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "OHBTriggers.h"

class TbcDungeonOldHillsbradTriggerContext : public NamedObjectContext<Trigger>
{
public:
    TbcDungeonOldHillsbradTriggerContext()
    {
        // Lieutenant Drake
        creators["drake whirlwind"] = &TbcDungeonOldHillsbradTriggerContext::drake_whirlwind;

        // Thrall's escort
        creators["thrall under attack"] = &TbcDungeonOldHillsbradTriggerContext::thrall_under_attack;
    }

private:
    static Trigger* drake_whirlwind(PlayerbotAI* botAI) { return new DrakeWhirlwindTrigger(botAI); }
    static Trigger* thrall_under_attack(PlayerbotAI* botAI) { return new ThrallUnderAttackTrigger(botAI); }
};

#endif
