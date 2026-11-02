/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BOTTRIGGERCONTEXT_H
#define PLAYERBOTS_BOTTRIGGERCONTEXT_H

#include "BotTriggers.h"
#include "NamedObjectContext.h"

class TbcDungeonBotanicaTriggerContext : public NamedObjectContext<Trigger>
{
public:
    TbcDungeonBotanicaTriggerContext()
    {
        // High Botanist Freywinn
        creators["freywinn is active"] = &TbcDungeonBotanicaTriggerContext::freywinn_is_active;

        // Thorngrin the Tender
        creators["thorngrin hellfire"] = &TbcDungeonBotanicaTriggerContext::thorngrin_hellfire;

        // Warp Splinter
        creators["warp splinter is active"] = &TbcDungeonBotanicaTriggerContext::warp_splinter_is_active;
    }

private:
    static Trigger* freywinn_is_active(PlayerbotAI* botAI) { return new FreywinnIsActiveTrigger(botAI); }
    static Trigger* thorngrin_hellfire(PlayerbotAI* botAI) { return new ThorngrinHellfireTrigger(botAI); }
    static Trigger* warp_splinter_is_active(PlayerbotAI* botAI) { return new WarpSplinterIsActiveTrigger(botAI); }
};

#endif
