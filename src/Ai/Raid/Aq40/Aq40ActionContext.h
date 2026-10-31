/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40ACTIONCONTEXT_H
#define PLAYERBOTS_AQ40ACTIONCONTEXT_H

#include "Action.h"
#include "Aq40Actions.h"
#include "NamedObjectContext.h"

class RaidAq40ActionContext : public NamedObjectContext<Action>
{
public:
    RaidAq40ActionContext()
    {
        creators["aq40 assign class roles"] = &RaidAq40ActionContext::assign_class_roles;
        creators["aq40 twin emperors announce class roles"] =
            &RaidAq40ActionContext::twin_emperors_announce_class_roles;
        creators["aq40 control mind controlled"] = &RaidAq40ActionContext::control_mind_controlled;
        creators["aq40 defender avoid explode"] = &RaidAq40ActionContext::defender_avoid_explode;
        creators["aq40 defender plague spread"] = &RaidAq40ActionContext::defender_plague_spread;
        creators["aq40 avoid thunderclap"] = &RaidAq40ActionContext::avoid_thunderclap;
        creators["aq40 burn obsidian mana"] = &RaidAq40ActionContext::burn_obsidian_mana;
        creators["aq40 kri avoid poison cloud"] = &RaidAq40ActionContext::kri_avoid_poison_cloud;
        creators["aq40 sartura avoid whirlwind"] = &RaidAq40ActionContext::sartura_avoid_whirlwind;
        creators["aq40 sartura stun"] = &RaidAq40ActionContext::sartura_stun;
        creators["aq40 huhuran shed threat"] = &RaidAq40ActionContext::huhuran_shed_threat;
        creators["aq40 viscidus avoid poison shock"] = &RaidAq40ActionContext::viscidus_avoid_poison_shock;
        creators["aq40 twin emperors tank station"] = &RaidAq40ActionContext::twin_emperors_tank_station;
        creators["aq40 twin emperors healer avoid blizzard"] =
            &RaidAq40ActionContext::twin_emperors_healer_avoid_blizzard;
        creators["aq40 fankriss taunt"] = &RaidAq40ActionContext::fankriss_taunt;
        creators["aq40 viscidus frost spell"] = &RaidAq40ActionContext::viscidus_frost_spell;
        creators["aq40 viscidus avoid toxic slime"] = &RaidAq40ActionContext::viscidus_avoid_toxic_slime;
        creators["aq40 warlock tank attack veklor"] = &RaidAq40ActionContext::warlock_tank_attack_veklor;
        creators["aq40 twin emperors avoid exploding bug"] = &RaidAq40ActionContext::twin_emperors_avoid_exploding_bug;
        creators["aq40 ouro avoid sand blast"] = &RaidAq40ActionContext::ouro_avoid_sand_blast;
        creators["aq40 ouro avoid dirt mound"] = &RaidAq40ActionContext::ouro_avoid_dirt_mound;
        creators["aq40 cthun avoid dark glare"] = &RaidAq40ActionContext::cthun_avoid_dark_glare;
        creators["aq40 cthun leave stomach"] = &RaidAq40ActionContext::cthun_leave_stomach;
    }

private:
    static Action* assign_class_roles(PlayerbotAI* botAI) { return new Aq40AssignClassRolesAction(botAI); }
    static Action* twin_emperors_announce_class_roles(PlayerbotAI* botAI)
    {
        return new Aq40TwinEmperorsAnnounceClassRolesAction(botAI);
    }
    static Action* control_mind_controlled(PlayerbotAI* botAI) { return new Aq40ControlMindControlledAction(botAI); }
    static Action* defender_avoid_explode(PlayerbotAI* botAI) { return new Aq40DefenderAvoidExplodeAction(botAI); }
    static Action* defender_plague_spread(PlayerbotAI* botAI) { return new Aq40DefenderPlagueSpreadAction(botAI); }
    static Action* avoid_thunderclap(PlayerbotAI* botAI) { return new Aq40AvoidThunderclapAction(botAI); }
    static Action* burn_obsidian_mana(PlayerbotAI* botAI) { return new Aq40BurnObsidianManaAction(botAI); }
    static Action* kri_avoid_poison_cloud(PlayerbotAI* botAI) { return new Aq40KriAvoidPoisonCloudAction(botAI); }
    static Action* sartura_avoid_whirlwind(PlayerbotAI* botAI) { return new Aq40SarturaAvoidWhirlwindAction(botAI); }
    static Action* fankriss_taunt(PlayerbotAI* botAI) { return new Aq40FankrissTauntAction(botAI); }
    static Action* viscidus_frost_spell(PlayerbotAI* botAI) { return new Aq40ViscidusFrostSpellAction(botAI); }
    static Action* viscidus_avoid_toxic_slime(PlayerbotAI* botAI)
    {
        return new Aq40ViscidusAvoidToxicSlimeAction(botAI);
    }
    static Action* warlock_tank_attack_veklor(PlayerbotAI* botAI)
    {
        return new Aq40WarlockTankAttackVeklorAction(botAI);
    }
    static Action* twin_emperors_avoid_exploding_bug(PlayerbotAI* botAI)
    {
        return new Aq40TwinEmperorsAvoidExplodingBugAction(botAI);
    }
    static Action* ouro_avoid_sand_blast(PlayerbotAI* botAI) { return new Aq40OuroAvoidSandBlastAction(botAI); }
    static Action* ouro_avoid_dirt_mound(PlayerbotAI* botAI) { return new Aq40OuroAvoidDirtMoundAction(botAI); }
    static Action* cthun_avoid_dark_glare(PlayerbotAI* botAI) { return new Aq40CthunAvoidDarkGlareAction(botAI); }
    static Action* cthun_leave_stomach(PlayerbotAI* botAI) { return new Aq40CthunLeaveStomachAction(botAI); }
    static Action* sartura_stun(PlayerbotAI* botAI) { return new Aq40SarturaStunAction(botAI); }
    static Action* huhuran_shed_threat(PlayerbotAI* botAI) { return new Aq40HuhuranShedThreatAction(botAI); }
    static Action* viscidus_avoid_poison_shock(PlayerbotAI* botAI)
    {
        return new Aq40ViscidusAvoidPoisonShockAction(botAI);
    }
    static Action* twin_emperors_tank_station(PlayerbotAI* botAI)
    {
        return new Aq40TwinEmperorsTankStationAction(botAI);
    }
    static Action* twin_emperors_healer_avoid_blizzard(PlayerbotAI* botAI)
    {
        return new Aq40TwinEmperorsHealerAvoidBlizzardAction(botAI);
    }
};

#endif
