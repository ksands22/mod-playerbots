/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40TRIGGERCONTEXT_H
#define PLAYERBOTS_AQ40TRIGGERCONTEXT_H

#include "Aq40Triggers.h"
#include "NamedObjectContext.h"

class RaidAq40TriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidAq40TriggerContext()
    {
        creators["aq40 no encounter in progress"] = &RaidAq40TriggerContext::no_encounter_in_progress;
        creators["aq40 class roles should be assigned"] = &RaidAq40TriggerContext::class_roles_should_be_assigned;
        creators["aq40 mind control"] = &RaidAq40TriggerContext::mind_control;
        creators["aq40 fear"] = &RaidAq40TriggerContext::fear;
        creators["aq40 defender explode"] = &RaidAq40TriggerContext::defender_explode;
        creators["aq40 defender plague"] = &RaidAq40TriggerContext::defender_plague;
        creators["aq40 thunderclap"] = &RaidAq40TriggerContext::thunderclap;
        creators["aq40 obsidian mana"] = &RaidAq40TriggerContext::obsidian_mana;
        creators["aq40 kri poison cloud"] = &RaidAq40TriggerContext::kri_poison_cloud;
        creators["aq40 sartura whirlwind"] = &RaidAq40TriggerContext::sartura_whirlwind;
        creators["aq40 sartura stun"] = &RaidAq40TriggerContext::sartura_stun;
        creators["aq40 huhuran shed threat"] = &RaidAq40TriggerContext::huhuran_shed_threat;
        creators["aq40 viscidus poison shock"] = &RaidAq40TriggerContext::viscidus_poison_shock;
        creators["aq40 twin emperors tank station"] = &RaidAq40TriggerContext::twin_emperors_tank_station;
        creators["aq40 twin emperors healer blizzard"] = &RaidAq40TriggerContext::twin_emperors_healer_blizzard;
        creators["aq40 fankriss tank swap"] = &RaidAq40TriggerContext::fankriss_tank_swap;
        creators["aq40 viscidus frost"] = &RaidAq40TriggerContext::viscidus_frost;
        creators["aq40 viscidus toxic slime"] = &RaidAq40TriggerContext::viscidus_toxic_slime;
        creators["aq40 veklor needs warlock tank"] = &RaidAq40TriggerContext::veklor_needs_warlock_tank;
        creators["aq40 twin emperors exploding bug"] = &RaidAq40TriggerContext::twin_emperors_exploding_bug;
        creators["aq40 ouro sand blast"] = &RaidAq40TriggerContext::ouro_sand_blast;
        creators["aq40 ouro dirt mound"] = &RaidAq40TriggerContext::ouro_dirt_mound;
        creators["aq40 cthun dark glare"] = &RaidAq40TriggerContext::cthun_dark_glare;
        creators["aq40 cthun stomach exit"] = &RaidAq40TriggerContext::cthun_stomach_exit;
    }

private:
    static Trigger* no_encounter_in_progress(PlayerbotAI* botAI) { return new Aq40NoEncounterInProgressTrigger(botAI); }
    static Trigger* class_roles_should_be_assigned(PlayerbotAI* botAI)
    {
        return new Aq40ClassRolesShouldBeAssignedTrigger(botAI);
    }
    static Trigger* mind_control(PlayerbotAI* botAI) { return new Aq40MindControlTrigger(botAI); }
    static Trigger* fear(PlayerbotAI* botAI) { return new Aq40FearTrigger(botAI); }
    static Trigger* defender_explode(PlayerbotAI* botAI) { return new Aq40DefenderExplodeTrigger(botAI); }
    static Trigger* defender_plague(PlayerbotAI* botAI) { return new Aq40DefenderPlagueTrigger(botAI); }
    static Trigger* thunderclap(PlayerbotAI* botAI) { return new Aq40ThunderclapTrigger(botAI); }
    static Trigger* obsidian_mana(PlayerbotAI* botAI) { return new Aq40ObsidianManaTrigger(botAI); }
    static Trigger* kri_poison_cloud(PlayerbotAI* botAI) { return new Aq40KriPoisonCloudTrigger(botAI); }
    static Trigger* sartura_whirlwind(PlayerbotAI* botAI) { return new Aq40SarturaWhirlwindTrigger(botAI); }
    static Trigger* fankriss_tank_swap(PlayerbotAI* botAI) { return new Aq40FankrissTankSwapTrigger(botAI); }
    static Trigger* viscidus_frost(PlayerbotAI* botAI) { return new Aq40ViscidusFrostTrigger(botAI); }
    static Trigger* viscidus_toxic_slime(PlayerbotAI* botAI) { return new Aq40ViscidusToxicSlimeTrigger(botAI); }
    static Trigger* veklor_needs_warlock_tank(PlayerbotAI* botAI)
    {
        return new Aq40VeklorNeedsWarlockTankTrigger(botAI);
    }
    static Trigger* twin_emperors_exploding_bug(PlayerbotAI* botAI)
    {
        return new Aq40TwinEmperorsExplodingBugTrigger(botAI);
    }
    static Trigger* ouro_sand_blast(PlayerbotAI* botAI) { return new Aq40OuroSandBlastTrigger(botAI); }
    static Trigger* ouro_dirt_mound(PlayerbotAI* botAI) { return new Aq40OuroDirtMoundTrigger(botAI); }
    static Trigger* cthun_dark_glare(PlayerbotAI* botAI) { return new Aq40CthunDarkGlareTrigger(botAI); }
    static Trigger* cthun_stomach_exit(PlayerbotAI* botAI) { return new Aq40CthunStomachExitTrigger(botAI); }
    static Trigger* sartura_stun(PlayerbotAI* botAI) { return new Aq40SarturaStunTrigger(botAI); }
    static Trigger* huhuran_shed_threat(PlayerbotAI* botAI) { return new Aq40HuhuranShedThreatTrigger(botAI); }
    static Trigger* viscidus_poison_shock(PlayerbotAI* botAI) { return new Aq40ViscidusPoisonShockTrigger(botAI); }
    static Trigger* twin_emperors_tank_station(PlayerbotAI* botAI)
    {
        return new Aq40TwinEmperorsTankStationTrigger(botAI);
    }
    static Trigger* twin_emperors_healer_blizzard(PlayerbotAI* botAI)
    {
        return new Aq40TwinEmperorsHealerBlizzardTrigger(botAI);
    }
};

#endif
