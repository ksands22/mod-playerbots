/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BOTACTIONCONTEXT_H
#define PLAYERBOTS_BOTACTIONCONTEXT_H

#include "BotActions.h"
#include "NamedObjectContext.h"

class TbcDungeonBotanicaActionContext : public NamedObjectContext<Action>
{
public:
    TbcDungeonBotanicaActionContext()
    {
        // High Botanist Freywinn
        creators["freywinn mark frayer"] = &TbcDungeonBotanicaActionContext::freywinn_mark_frayer;

        // Thorngrin the Tender
        creators["thorngrin avoid hellfire"] = &TbcDungeonBotanicaActionContext::thorngrin_avoid_hellfire;

        // Warp Splinter
        creators["warp splinter mark sapling"] = &TbcDungeonBotanicaActionContext::warp_splinter_mark_sapling;
    }

private:
    static Action* freywinn_mark_frayer(PlayerbotAI* botAI) { return new FreywinnMarkFrayerAction(botAI); }
    static Action* thorngrin_avoid_hellfire(PlayerbotAI* botAI) { return new ThorngrinAvoidHellfireAction(botAI); }
    static Action* warp_splinter_mark_sapling(PlayerbotAI* botAI) { return new WarpSplinterMarkSaplingAction(botAI); }
};

#endif
