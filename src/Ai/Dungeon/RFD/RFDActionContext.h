/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_RFDACTIONCONTEXT_H
#define PLAYERBOTS_RFDACTIONCONTEXT_H

#include "NamedObjectContext.h"
#include "RFDActions.h"

class VanillaDungeonRazorfenDownsActionContext : public NamedObjectContext<Action>
{
public:
    VanillaDungeonRazorfenDownsActionContext()
    {
        // Extinguishing the Idol (Belnistrasz)
        creators["belnistrasz defend"] = &VanillaDungeonRazorfenDownsActionContext::belnistrasz_defend;
    }

private:
    static Action* belnistrasz_defend(PlayerbotAI* botAI) { return new BelnistraszDefendAction(botAI); }
};

#endif
