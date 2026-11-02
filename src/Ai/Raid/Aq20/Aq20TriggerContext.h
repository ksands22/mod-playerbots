/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20TRIGGERCONTEXT_H
#define PLAYERBOTS_AQ20TRIGGERCONTEXT_H

#include "Aq20Triggers.h"
#include "NamedObjectContext.h"

class RaidAq20TriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidAq20TriggerContext()
    {
        creators["aq20 move to crystal"] = &RaidAq20TriggerContext::move_to_crystal;
        creators["aq20 kill order mark"] = &RaidAq20TriggerContext::kill_order_mark;
        creators["aq20 cc mark"] = &RaidAq20TriggerContext::cc_mark;
        creators["aq20 kurinnaxx tank swap"] = &RaidAq20TriggerContext::kurinnaxx_tank_swap;
        creators["aq20 moam drain mana"] = &RaidAq20TriggerContext::moam_drain_mana;
        creators["aq20 ayamiss larva"] = &RaidAq20TriggerContext::ayamiss_larva;
        creators["aq20 buru chased"] = &RaidAq20TriggerContext::buru_chased;
    }

private:
    static Trigger* move_to_crystal(PlayerbotAI* botAI) { return new Aq20MoveToCrystalTrigger(botAI); }
    static Trigger* kill_order_mark(PlayerbotAI* botAI) { return new Aq20KillOrderMarkTrigger(botAI); }
    static Trigger* cc_mark(PlayerbotAI* botAI) { return new Aq20CcMarkTrigger(botAI); }
    static Trigger* kurinnaxx_tank_swap(PlayerbotAI* botAI) { return new Aq20KurinnaxxTankSwapTrigger(botAI); }
    static Trigger* moam_drain_mana(PlayerbotAI* botAI) { return new Aq20MoamDrainManaTrigger(botAI); }
    static Trigger* ayamiss_larva(PlayerbotAI* botAI) { return new Aq20AyamissLarvaTrigger(botAI); }
    static Trigger* buru_chased(PlayerbotAI* botAI) { return new Aq20BuruChasedTrigger(botAI); }
};

#endif
