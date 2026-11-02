/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGACTIONCONTEXT_H
#define PLAYERBOTS_ZGACTIONCONTEXT_H

#include "Action.h"
#include "NamedObjectContext.h"
#include "ZGActions.h"

class RaidZulGurubActionContext : public NamedObjectContext<Action>
{
public:
    RaidZulGurubActionContext()
    {
        creators["zg kill order mark"] = &RaidZulGurubActionContext::kill_order_mark;
        creators["zg cc mark"] = &RaidZulGurubActionContext::cc_mark;
        creators["zg interrupt"] = &RaidZulGurubActionContext::interrupt;
        creators["zg jeklik spread"] = &RaidZulGurubActionContext::jeklik_spread;
        creators["zg venoxis move away"] = &RaidZulGurubActionContext::venoxis_move_away;
        creators["zg thekal attack tiger"] = &RaidZulGurubActionContext::thekal_attack_tiger;
        creators["zg mandokir stop attacking"] = &RaidZulGurubActionContext::mandokir_stop_attacking;
        creators["zg ohgan tank"] = &RaidZulGurubActionContext::ohgan_tank;
        creators["zg jindo attack shade"] = &RaidZulGurubActionContext::jindo_attack_shade;
        creators["zg hakkar stand in cloud"] = &RaidZulGurubActionContext::hakkar_stand_in_cloud;
        creators["zg hakkar pull son"] = &RaidZulGurubActionContext::hakkar_pull_son;
        creators["zg gahzranka tank"] = &RaidZulGurubActionContext::gahzranka_tank;
        creators["zg gahzranka avoid breath"] = &RaidZulGurubActionContext::gahzranka_avoid_breath;
        creators["zg grilek kite"] = &RaidZulGurubActionContext::grilek_kite;
        creators["zg caster spread"] = &RaidZulGurubActionContext::caster_spread;
        creators["zg hazzarah attack illusion"] = &RaidZulGurubActionContext::hazzarah_attack_illusion;
    }

private:
    static Action* kill_order_mark(PlayerbotAI* botAI) { return new ZgKillOrderMarkAction(botAI); }
    static Action* cc_mark(PlayerbotAI* botAI) { return new ZgCcMarkAction(botAI); }
    static Action* interrupt(PlayerbotAI* botAI) { return new ZgInterruptAction(botAI); }
    static Action* jeklik_spread(PlayerbotAI* botAI) { return new ZgJeklikSpreadAction(botAI); }
    static Action* venoxis_move_away(PlayerbotAI* botAI) { return new ZgVenoxisMoveAwayAction(botAI); }
    static Action* thekal_attack_tiger(PlayerbotAI* botAI) { return new ZgThekalAttackTigerAction(botAI); }
    static Action* mandokir_stop_attacking(PlayerbotAI* botAI) { return new ZgMandokirStopAttackingAction(botAI); }
    static Action* ohgan_tank(PlayerbotAI* botAI) { return new ZgTankUnitAction(botAI, "zg ohgan tank", "ohgan"); }
    static Action* jindo_attack_shade(PlayerbotAI* botAI) { return new ZgJindoAttackShadeAction(botAI); }
    static Action* hakkar_stand_in_cloud(PlayerbotAI* botAI) { return new ZgHakkarStandInCloudAction(botAI); }
    static Action* hakkar_pull_son(PlayerbotAI* botAI) { return new ZgHakkarPullSonAction(botAI); }
    static Action* gahzranka_tank(PlayerbotAI* botAI)
    {
        return new ZgTankUnitAction(botAI, "zg gahzranka tank", "gahz'ranka");
    }
    static Action* gahzranka_avoid_breath(PlayerbotAI* botAI) { return new ZgGahzrankaAvoidBreathAction(botAI); }
    static Action* grilek_kite(PlayerbotAI* botAI) { return new ZgGrilekKiteAction(botAI); }
    static Action* caster_spread(PlayerbotAI* botAI) { return new ZgCasterSpreadAction(botAI); }
    static Action* hazzarah_attack_illusion(PlayerbotAI* botAI) { return new ZgHazzarahAttackIllusionAction(botAI); }
};

#endif
