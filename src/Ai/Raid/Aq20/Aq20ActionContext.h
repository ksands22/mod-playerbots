/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20ACTIONCONTEXT_H
#define PLAYERBOTS_AQ20ACTIONCONTEXT_H

#include "Action.h"
#include "Aq20Actions.h"
#include "NamedObjectContext.h"

class RaidAq20ActionContext : public NamedObjectContext<Action>
{
public:
    RaidAq20ActionContext()
    {
        creators["aq20 use crystal"] = &RaidAq20ActionContext::use_crystal;
        creators["aq20 kill order mark"] = &RaidAq20ActionContext::kill_order_mark;
        creators["aq20 cc mark"] = &RaidAq20ActionContext::cc_mark;
        creators["aq20 kurinnaxx taunt"] = &RaidAq20ActionContext::kurinnaxx_taunt;
        creators["aq20 moam drain mana"] = &RaidAq20ActionContext::moam_drain_mana;
        creators["aq20 ayamiss attack larva"] = &RaidAq20ActionContext::ayamiss_attack_larva;
        creators["aq20 buru kite to egg"] = &RaidAq20ActionContext::buru_kite_to_egg;
    }

private:
    static Action* use_crystal(PlayerbotAI* botAI) { return new Aq20UseCrystalAction(botAI); }
    static Action* kill_order_mark(PlayerbotAI* botAI) { return new Aq20KillOrderMarkAction(botAI); }
    static Action* cc_mark(PlayerbotAI* botAI) { return new Aq20CcMarkAction(botAI); }
    static Action* kurinnaxx_taunt(PlayerbotAI* botAI) { return new Aq20KurinnaxxTauntAction(botAI); }
    static Action* moam_drain_mana(PlayerbotAI* botAI) { return new Aq20MoamDrainManaAction(botAI); }
    static Action* ayamiss_attack_larva(PlayerbotAI* botAI) { return new Aq20AyamissAttackLarvaAction(botAI); }
    static Action* buru_kite_to_egg(PlayerbotAI* botAI) { return new Aq20BuruKiteToEggAction(botAI); }
};

#endif
