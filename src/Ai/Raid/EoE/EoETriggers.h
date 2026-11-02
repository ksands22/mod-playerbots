/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_EOETRIGGERS_H
#define PLAYERBOTS_EOETRIGGERS_H

#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "Trigger.h"

enum EyeOfEternityIDs
{
    NPC_MALYGOS                         = 28859,
    NPC_POWER_SPARK                     = 30084,
    NPC_NEXUS_LORD                      = 30245,
    NPC_SCION_OF_ETERNITY               = 30249,
    NPC_WYRMREST_SKYTALON               = 30161,
    NPC_ARCANE_OVERLOAD                 = 30282,
    NPC_STATIC_FIELD                    = 30592,

    SPELL_POWER_SPARK_VISUAL            = 55845,
    SPELL_POWER_SPARK_GROUND_BUFF       = 55852,
    SPELL_POWER_SPARK_MALYGOS_BUFF      = 56152,

    SPELL_TELEPORT_VISUAL               = 52096,

    SPELL_STATIC_FIELD_DAMAGE           = 57429,

    SPELL_SCION_ARCANE_BARRAGE          = 56397,
    SPELL_ARCANE_SHOCK_N                = 57058,
    SPELL_ARCANE_SHOCK_H                = 60073,
    SPELL_HASTE                         = 57060,

    SPELL_ALEXSTRASZA_GIFT              = 61028,

    // Drake Abilities:
    // DPS
    SPELL_FLAME_SPIKE                   = 56091,
    SPELL_ENGULF_IN_FLAMES              = 56092,
    // Healing
    SPELL_REVIVIFY                      = 57090,
    SPELL_LIFE_BURST                    = 57143,
    // Utility
    SPELL_FLAME_SHIELD                  = 57108,
    SPELL_BLAZING_SPEED                 = 57092,
};

const uint32 EOE_MAP_ID = 616;

// Phase 1: a Power Spark close to Malygos. Guides kill them there, so the raid gets the damage buff the
// spark leaves on the ground, before it reaches him and buffs him.
Unit* GetPowerSparkNearMalygos(PlayerbotAI* botAI, Unit* malygos);
// Phase 2: the newest Arcane Overload bubble, which halves magic damage inside and shrinks with age.
Unit* GetNewestArcaneOverload(PlayerbotAI* botAI);
// Phase 2: a Static Field the bot stands in, with the distance it must get to.
Unit* GetStaticFieldInRange(PlayerbotAI* botAI, float& safeDistance);

class MalygosTrigger : public Trigger
{
public:
    MalygosTrigger(PlayerbotAI* botAI) : Trigger(botAI, "malygos") {}
    bool IsActive() override;
    uint8 static getPhase(Player* bot, Unit* boss);
};

class PowerSparkTrigger : public Trigger
{
public:
    PowerSparkTrigger(PlayerbotAI* botAI) : Trigger(botAI, "power spark") {}
    bool IsActive() override;
};

class MalygosPowerSparkNearBossTrigger : public Trigger
{
public:
    MalygosPowerSparkNearBossTrigger(PlayerbotAI* botAI) : Trigger(botAI, "malygos power spark near boss") {}
    bool IsActive() override;
};

class MalygosOutsideArcaneOverloadTrigger : public Trigger
{
public:
    MalygosOutsideArcaneOverloadTrigger(PlayerbotAI* botAI) : Trigger(botAI, "malygos outside arcane overload") {}
    bool IsActive() override;
};

class MalygosStaticFieldTrigger : public Trigger
{
public:
    MalygosStaticFieldTrigger(PlayerbotAI* botAI) : Trigger(botAI, "malygos static field") {}
    bool IsActive() override;
};

#endif
