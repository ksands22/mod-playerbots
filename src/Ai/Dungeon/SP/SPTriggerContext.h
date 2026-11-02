/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SPTRIGGERCONTEXT_H
#define PLAYERBOTS_SPTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "SPTriggers.h"

class TbcDungeonSlavePensTriggerContext : public NamedObjectContext<Trigger>
{
public:
    TbcDungeonSlavePensTriggerContext()
    {
        // Mennu the Betrayer
        creators["mennu is active"] = &TbcDungeonSlavePensTriggerContext::mennu_is_active;
    }

private:
    static Trigger* mennu_is_active(PlayerbotAI* botAI) { return new MennuIsActiveTrigger(botAI); }
};

#endif
