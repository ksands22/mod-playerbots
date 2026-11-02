/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40TRIGGERS_H
#define PLAYERBOTS_AQ40TRIGGERS_H

#include "Trigger.h"

// Shared

class Aq40NoEncounterInProgressTrigger : public Trigger
{
public:
    Aq40NoEncounterInProgressTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 no encounter in progress") {}
    bool IsActive() override;
};

class Aq40ClassRolesShouldBeAssignedTrigger : public Trigger
{
public:
    Aq40ClassRolesShouldBeAssignedTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 class roles should be assigned") {}
    bool IsActive() override;
};

// Skeram's True Fulfillment and the Qiraji Brainwashers' Cause Insanity.
class Aq40MindControlTrigger : public Trigger
{
public:
    // Scans the group, so it checks once a second rather than every tick.
    Aq40MindControlTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 mind control", 1000) {}
    bool IsActive() override;
};

// Yauj, Anubisath Warders and Qiraji Champions all fear.
class Aq40FearTrigger : public Trigger
{
public:
    Aq40FearTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 fear") {}
    bool IsActive() override;
};

// Trash

class Aq40DefenderExplodeTrigger : public Trigger
{
public:
    Aq40DefenderExplodeTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 defender explode") {}
    bool IsActive() override;
};

class Aq40DefenderPlagueTrigger : public Trigger
{
public:
    Aq40DefenderPlagueTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 defender plague") {}
    bool IsActive() override;
};

class Aq40ThunderclapTrigger : public Trigger
{
public:
    Aq40ThunderclapTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 thunderclap") {}
    bool IsActive() override;
};

class Aq40ObsidianManaTrigger : public Trigger
{
public:
    Aq40ObsidianManaTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 obsidian mana") {}
    bool IsActive() override;
};

// Bug Trio

class Aq40KriPoisonCloudTrigger : public Trigger
{
public:
    Aq40KriPoisonCloudTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 kri poison cloud") {}
    bool IsActive() override;
};

// Battleguard Sartura

class Aq40SarturaWhirlwindTrigger : public Trigger
{
public:
    Aq40SarturaWhirlwindTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 sartura whirlwind") {}
    bool IsActive() override;
};

class Aq40SarturaStunTrigger : public Trigger
{
public:
    Aq40SarturaStunTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 sartura stun") {}
    bool IsActive() override;
};

// Princess Huhuran

class Aq40HuhuranShedThreatTrigger : public Trigger
{
public:
    Aq40HuhuranShedThreatTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 huhuran shed threat") {}
    bool IsActive() override;
};

// Fankriss the Unyielding

class Aq40FankrissTankSwapTrigger : public Trigger
{
public:
    Aq40FankrissTankSwapTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 fankriss tank swap") {}
    bool IsActive() override;
};

// Viscidus

class Aq40ViscidusFrostTrigger : public Trigger
{
public:
    Aq40ViscidusFrostTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 viscidus frost") {}
    bool IsActive() override;
};

class Aq40ViscidusPoisonShockTrigger : public Trigger
{
public:
    Aq40ViscidusPoisonShockTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 viscidus poison shock") {}
    bool IsActive() override;
};

class Aq40ViscidusToxicSlimeTrigger : public Trigger
{
public:
    Aq40ViscidusToxicSlimeTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 viscidus toxic slime") {}
    bool IsActive() override;
};

// Twin Emperors

class Aq40VeklorNeedsWarlockTankTrigger : public Trigger
{
public:
    Aq40VeklorNeedsWarlockTankTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 veklor needs warlock tank") {}
    bool IsActive() override;
};

class Aq40TwinEmperorsTankStationTrigger : public Trigger
{
public:
    Aq40TwinEmperorsTankStationTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 twin emperors tank station") {}
    bool IsActive() override;
};

class Aq40TwinEmperorsHealerBlizzardTrigger : public Trigger
{
public:
    Aq40TwinEmperorsHealerBlizzardTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 twin emperors healer blizzard") {}
    bool IsActive() override;
};

class Aq40TwinEmperorsExplodingBugTrigger : public Trigger
{
public:
    Aq40TwinEmperorsExplodingBugTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 twin emperors exploding bug") {}
    bool IsActive() override;
};

// Ouro

class Aq40OuroSandBlastTrigger : public Trigger
{
public:
    Aq40OuroSandBlastTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 ouro sand blast") {}
    bool IsActive() override;
};

class Aq40OuroDirtMoundTrigger : public Trigger
{
public:
    Aq40OuroDirtMoundTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 ouro dirt mound") {}
    bool IsActive() override;
};

// C'Thun

class Aq40CthunDarkGlareTrigger : public Trigger
{
public:
    Aq40CthunDarkGlareTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 cthun dark glare") {}
    bool IsActive() override;
};

class Aq40CthunStomachExitTrigger : public Trigger
{
public:
    Aq40CthunStomachExitTrigger(PlayerbotAI* botAI) : Trigger(botAI, "aq40 cthun stomach exit") {}
    bool IsActive() override;
};

#endif
