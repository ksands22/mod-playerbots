/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_RFDTRIGGERCONTEXT_H
#define PLAYERBOTS_RFDTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "RFDTriggers.h"

class VanillaDungeonRazorfenDownsTriggerContext : public NamedObjectContext<Trigger>
{
public:
    VanillaDungeonRazorfenDownsTriggerContext()
    {
        // Extinguishing the Idol (Belnistrasz)
        creators["belnistrasz under attack"] = &VanillaDungeonRazorfenDownsTriggerContext::belnistrasz_under_attack;
    }

private:
    static Trigger* belnistrasz_under_attack(PlayerbotAI* botAI) { return new BelnistraszUnderAttackTrigger(botAI); }
};

#endif
