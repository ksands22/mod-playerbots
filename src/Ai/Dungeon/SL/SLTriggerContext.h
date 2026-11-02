/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SLTRIGGERCONTEXT_H
#define PLAYERBOTS_SLTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "SLTriggers.h"

class TbcDungeonShadowLabyrinthTriggerContext : public NamedObjectContext<Trigger>
{
public:
    TbcDungeonShadowLabyrinthTriggerContext()
    {
        // Grandmaster Vorpil
        creators["vorpil is active"] = &TbcDungeonShadowLabyrinthTriggerContext::vorpil_is_active;

        // Murmur
        creators["murmur sonic boom"] = &TbcDungeonShadowLabyrinthTriggerContext::murmur_sonic_boom;
        creators["murmurs touch"] = &TbcDungeonShadowLabyrinthTriggerContext::murmurs_touch;
    }

private:
    static Trigger* vorpil_is_active(PlayerbotAI* botAI) { return new VorpilIsActiveTrigger(botAI); }
    static Trigger* murmur_sonic_boom(PlayerbotAI* botAI) { return new MurmurSonicBoomTrigger(botAI); }
    static Trigger* murmurs_touch(PlayerbotAI* botAI) { return new MurmursTouchTrigger(botAI); }
};

#endif
