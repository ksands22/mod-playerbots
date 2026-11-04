/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ONYTRIGGERCONTEXT_H
#define PLAYERBOTS_ONYTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "OnyTriggers.h"

class RaidOnyxiaTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidOnyxiaTriggerContext()
    {
        creators["ony near tail"] = &RaidOnyxiaTriggerContext::near_tail;
        creators["ony deep breath warning"] = &RaidOnyxiaTriggerContext::deep_breath;
        creators["ony fireball splash incoming"] = &RaidOnyxiaTriggerContext::fireball_splash;
        creators["ony whelps spawn"] = &RaidOnyxiaTriggerContext::whelps_spawn;
        creators["ony avoid eggs"] = &RaidOnyxiaTriggerContext::avoid_eggs;
        creators["ony phase 3 tremor totem"] = &RaidOnyxiaTriggerContext::phase_3_tremor_totem;
        creators["ony main tank needs fear ward"] = &RaidOnyxiaTriggerContext::main_tank_needs_fear_ward;
        creators["ony bellowing roar"] = &RaidOnyxiaTriggerContext::bellowing_roar;
    }

private:
    static Trigger* near_tail(PlayerbotAI* botAI) { return new OnyxiaNearTailTrigger(botAI); }
    static Trigger* deep_breath(PlayerbotAI* botAI) { return new OnyxiaDeepBreathTrigger(botAI); }
    static Trigger* fireball_splash(PlayerbotAI* botAI) { return new RaidOnyxiaFireballSplashTrigger(botAI); }
    static Trigger* whelps_spawn(PlayerbotAI* botAI) { return new RaidOnyxiaWhelpsSpawnTrigger(botAI); }
    static Trigger* avoid_eggs(PlayerbotAI* botAI) { return new OnyxiaAvoidEggsTrigger(botAI); }
    static Trigger* phase_3_tremor_totem(PlayerbotAI* botAI) { return new OnyxiaPhase3TremorTotemTrigger(botAI); }
    static Trigger* main_tank_needs_fear_ward(PlayerbotAI* botAI)
    {
        return new OnyxiaMainTankNeedsFearWardTrigger(botAI);
    }
    static Trigger* bellowing_roar(PlayerbotAI* botAI) { return new OnyxiaBellowingRoarTrigger(botAI); }
};

#endif
