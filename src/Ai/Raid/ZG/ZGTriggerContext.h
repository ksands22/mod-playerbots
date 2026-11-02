/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGTRIGGERCONTEXT_H
#define PLAYERBOTS_ZGTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "ZGTriggers.h"

class RaidZulGurubTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidZulGurubTriggerContext()
    {
        creators["zg kill order mark"] = &RaidZulGurubTriggerContext::kill_order_mark;
        creators["zg cc mark"] = &RaidZulGurubTriggerContext::cc_mark;
        creators["zg interrupt"] = &RaidZulGurubTriggerContext::interrupt;
        creators["zg jeklik spread"] = &RaidZulGurubTriggerContext::jeklik_spread;
        creators["zg venoxis snake form too close"] = &RaidZulGurubTriggerContext::venoxis_snake_form_too_close;
        creators["zg thekal tiger"] = &RaidZulGurubTriggerContext::thekal_tiger;
        creators["zg mandokir gaze"] = &RaidZulGurubTriggerContext::mandokir_gaze;
        creators["zg ohgan not tanked"] = &RaidZulGurubTriggerContext::ohgan_not_tanked;
        creators["zg jindo shade"] = &RaidZulGurubTriggerContext::jindo_shade;
        creators["zg hakkar poisonous cloud"] = &RaidZulGurubTriggerContext::hakkar_poisonous_cloud;
        creators["zg hakkar son pull"] = &RaidZulGurubTriggerContext::hakkar_son_pull;
        creators["zg gahzranka not tanked"] = &RaidZulGurubTriggerContext::gahzranka_not_tanked;
        creators["zg gahzranka not victim"] = &RaidZulGurubTriggerContext::gahzranka_not_victim;
        creators["zg grilek pursued"] = &RaidZulGurubTriggerContext::grilek_pursued;
        creators["zg caster spread"] = &RaidZulGurubTriggerContext::caster_spread;
        creators["zg hazzarah illusion"] = &RaidZulGurubTriggerContext::hazzarah_illusion;
    }

private:
    static Trigger* kill_order_mark(PlayerbotAI* botAI) { return new ZgKillOrderMarkTrigger(botAI); }
    static Trigger* cc_mark(PlayerbotAI* botAI) { return new ZgCcMarkTrigger(botAI); }
    static Trigger* interrupt(PlayerbotAI* botAI) { return new ZgInterruptTrigger(botAI); }
    static Trigger* jeklik_spread(PlayerbotAI* botAI) { return new ZgJeklikSpreadTrigger(botAI); }
    static Trigger* venoxis_snake_form_too_close(PlayerbotAI* botAI)
    {
        return new ZgVenoxisSnakeFormTooCloseTrigger(botAI);
    }
    static Trigger* thekal_tiger(PlayerbotAI* botAI) { return new ZgThekalTigerTrigger(botAI); }
    static Trigger* mandokir_gaze(PlayerbotAI* botAI) { return new ZgMandokirGazeTrigger(botAI); }
    static Trigger* ohgan_not_tanked(PlayerbotAI* botAI) { return new ZgOhganNotTankedTrigger(botAI); }
    static Trigger* jindo_shade(PlayerbotAI* botAI) { return new ZgJindoShadeTrigger(botAI); }
    static Trigger* hakkar_poisonous_cloud(PlayerbotAI* botAI) { return new ZgHakkarPoisonousCloudTrigger(botAI); }
    static Trigger* hakkar_son_pull(PlayerbotAI* botAI) { return new ZgHakkarSonPullTrigger(botAI); }
    static Trigger* gahzranka_not_tanked(PlayerbotAI* botAI) { return new ZgGahzrankaNotTankedTrigger(botAI); }
    static Trigger* gahzranka_not_victim(PlayerbotAI* botAI) { return new ZgGahzrankaNotVictimTrigger(botAI); }
    static Trigger* grilek_pursued(PlayerbotAI* botAI) { return new ZgGrilekPursuedTrigger(botAI); }
    static Trigger* caster_spread(PlayerbotAI* botAI) { return new ZgCasterSpreadTrigger(botAI); }
    static Trigger* hazzarah_illusion(PlayerbotAI* botAI) { return new ZgHazzarahIllusionTrigger(botAI); }
};

#endif
