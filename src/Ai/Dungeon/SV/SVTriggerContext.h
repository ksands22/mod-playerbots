/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SVTRIGGERCONTEXT_H
#define PLAYERBOTS_SVTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "SVTriggers.h"

class TbcDungeonSteamvaultTriggerContext : public NamedObjectContext<Trigger>
{
public:
    TbcDungeonSteamvaultTriggerContext()
    {
        // Mekgineer Steamrigger
        creators["steamrigger is active"] = &TbcDungeonSteamvaultTriggerContext::steamrigger_is_active;

        // Warlord Kalithresh
        creators["kalithresh is active"] = &TbcDungeonSteamvaultTriggerContext::kalithresh_is_active;
    }

private:
    static Trigger* steamrigger_is_active(PlayerbotAI* botAI) { return new SteamriggerIsActiveTrigger(botAI); }
    static Trigger* kalithresh_is_active(PlayerbotAI* botAI) { return new KalithreshIsActiveTrigger(botAI); }
};

#endif
