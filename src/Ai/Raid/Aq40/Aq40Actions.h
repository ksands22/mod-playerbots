/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40ACTIONS_H
#define PLAYERBOTS_AQ40ACTIONS_H

#include "Action.h"
#include "Aq40Helpers.h"
#include "MovementActions.h"

// Mind control: Skeram and Qiraji Brainwashers

// Mages polymorph the mind-controlled player; warlocks fear them.
class Aq40ControlMindControlledAction : public Action
{
public:
    Aq40ControlMindControlledAction(PlayerbotAI* botAI) : Action(botAI, "aq40 control mind controlled") {}
    bool Execute(Event event) override;
};

// Trash

class Aq40DefenderAvoidExplodeAction : public MovementAction
{
public:
    Aq40DefenderAvoidExplodeAction(PlayerbotAI* botAI) : MovementAction(botAI, "aq40 defender avoid explode") {}
    bool Execute(Event event) override;
};

// The plagued player walks away from everyone else until the disease runs out.
class Aq40DefenderPlagueSpreadAction : public MovementAction
{
public:
    Aq40DefenderPlagueSpreadAction(PlayerbotAI* botAI) : MovementAction(botAI, "aq40 defender plague spread") {}
    bool Execute(Event event) override;
};

class Aq40AvoidThunderclapAction : public MovementAction
{
public:
    Aq40AvoidThunderclapAction(PlayerbotAI* botAI) : MovementAction(botAI, "aq40 avoid thunderclap") {}
    bool Execute(Event event) override;
};

class Aq40BurnObsidianManaAction : public Action
{
public:
    Aq40BurnObsidianManaAction(PlayerbotAI* botAI) : Action(botAI, "aq40 burn obsidian mana") {}
    bool Execute(Event event) override;
    bool isPossible() override;
};

// Bug Trio

class Aq40KriAvoidPoisonCloudAction : public MoveAwayFromCreatureAction
{
public:
    Aq40KriAvoidPoisonCloudAction(PlayerbotAI* botAI)
        : MoveAwayFromCreatureAction(botAI, "aq40 kri avoid poison cloud", TempleOfAhnQirajHelpers::NPC_POISON_CLOUD,
                                     TempleOfAhnQirajHelpers::POISON_CLOUD_SAFE_DISTANCE)
    {
    }
};

// Battleguard Sartura

class Aq40SarturaAvoidWhirlwindAction : public MovementAction
{
public:
    Aq40SarturaAvoidWhirlwindAction(PlayerbotAI* botAI) : MovementAction(botAI, "aq40 sartura avoid whirlwind") {}
    bool Execute(Event event) override;
};

class Aq40SarturaStunAction : public Action
{
public:
    Aq40SarturaStunAction(PlayerbotAI* botAI) : Action(botAI, "aq40 sartura stun") {}
    bool Execute(Event event) override;
    bool isPossible() override;
};

// Princess Huhuran

class Aq40HuhuranShedThreatAction : public Action
{
public:
    Aq40HuhuranShedThreatAction(PlayerbotAI* botAI) : Action(botAI, "aq40 huhuran shed threat") {}
    bool Execute(Event event) override;
};

// Fankriss the Unyielding

class Aq40FankrissTauntAction : public Action
{
public:
    Aq40FankrissTauntAction(PlayerbotAI* botAI) : Action(botAI, "aq40 fankriss taunt") {}
    bool Execute(Event event) override;
    bool isPossible() override;
};

// Viscidus

class Aq40ViscidusFrostSpellAction : public Action
{
public:
    Aq40ViscidusFrostSpellAction(PlayerbotAI* botAI) : Action(botAI, "aq40 viscidus frost spell") {}
    bool Execute(Event event) override;
    bool isPossible() override;
};

class Aq40ViscidusAvoidPoisonShockAction : public MovementAction
{
public:
    Aq40ViscidusAvoidPoisonShockAction(PlayerbotAI* botAI) : MovementAction(botAI, "aq40 viscidus avoid poison shock")
    {
    }
    bool Execute(Event event) override;
};

class Aq40ViscidusAvoidToxicSlimeAction : public MoveAwayFromCreatureAction
{
public:
    Aq40ViscidusAvoidToxicSlimeAction(PlayerbotAI* botAI)
        : MoveAwayFromCreatureAction(botAI, "aq40 viscidus avoid toxic slime", TempleOfAhnQirajHelpers::NPC_TOXIC_SLIME,
                                     TempleOfAhnQirajHelpers::TOXIN_SAFE_DISTANCE)
    {
    }
};

// Twin Emperors

class Aq40WarlockTankAttackVeklorAction : public Action
{
public:
    Aq40WarlockTankAttackVeklorAction(PlayerbotAI* botAI) : Action(botAI, "aq40 warlock tank attack veklor") {}
    bool Execute(Event event) override;
    bool isPossible() override;
};

class Aq40TwinEmperorsTankStationAction : public MovementAction
{
public:
    Aq40TwinEmperorsTankStationAction(PlayerbotAI* botAI) : MovementAction(botAI, "aq40 twin emperors tank station") {}
    bool Execute(Event event) override;
};

class Aq40TwinEmperorsHealerAvoidBlizzardAction : public MovementAction
{
public:
    Aq40TwinEmperorsHealerAvoidBlizzardAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "aq40 twin emperors healer avoid blizzard")
    {
    }
    bool Execute(Event event) override;
};

class Aq40TwinEmperorsAvoidExplodingBugAction : public MovementAction
{
public:
    Aq40TwinEmperorsAvoidExplodingBugAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "aq40 twin emperors avoid exploding bug")
    {
    }
    bool Execute(Event event) override;
};

// Ouro

class Aq40OuroAvoidSandBlastAction : public BossRearFlankAction
{
public:
    Aq40OuroAvoidSandBlastAction(PlayerbotAI* botAI)
        : BossRearFlankAction(botAI, "ouro", 0.0f, TempleOfAhnQirajHelpers::SAND_BLAST_AVOID_ANGLE, M_PI)
    {
    }
    bool Execute(Event event) override;
    bool isUseful() override;
};

class Aq40OuroAvoidDirtMoundAction : public MoveAwayFromCreatureAction
{
public:
    Aq40OuroAvoidDirtMoundAction(PlayerbotAI* botAI)
        : MoveAwayFromCreatureAction(botAI, "aq40 ouro avoid dirt mound", TempleOfAhnQirajHelpers::NPC_DIRT_MOUND,
                                     TempleOfAhnQirajHelpers::QUAKE_SAFE_DISTANCE)
    {
    }
};

// C'Thun

class Aq40CthunAvoidDarkGlareAction : public MovementAction
{
public:
    Aq40CthunAvoidDarkGlareAction(PlayerbotAI* botAI) : MovementAction(botAI, "aq40 cthun avoid dark glare") {}
    bool Execute(Event event) override;
};

class Aq40CthunLeaveStomachAction : public MovementAction
{
public:
    Aq40CthunLeaveStomachAction(PlayerbotAI* botAI) : MovementAction(botAI, "aq40 cthun leave stomach") {}
    bool Execute(Event event) override;
};

// Shared

class Aq40AssignClassRolesAction : public Action
{
public:
    Aq40AssignClassRolesAction(PlayerbotAI* botAI) : Action(botAI, "aq40 assign class roles") {}
    bool Execute(Event event) override;
};

class Aq40TwinEmperorsAnnounceClassRolesAction : public Action
{
public:
    Aq40TwinEmperorsAnnounceClassRolesAction(PlayerbotAI* botAI)
        : Action(botAI, "aq40 twin emperors announce class roles")
    {
    }
    bool Execute(Event event) override;
};

#endif
