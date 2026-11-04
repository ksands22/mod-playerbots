/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

// OnyxiaTriggers.h
#ifndef PLAYERBOTS_ONYTRIGGERS_H
#define PLAYERBOTS_ONYTRIGGERS_H

#include "PlayerbotAI.h"
#include "Trigger.h"

// Onyxia, from the classic guides, the core's boss_onyxia.cpp and mod-individual-progression's vanilla
// version, which uses its own Onyxia (301000) and whelps (301001) and has no Lair Guards.
namespace OnyxiaHelpers
{
enum OnyxiaIds : uint32
{
    NPC_ONYXIAN_WHELP = 11262,
    NPC_ONYXIAN_WHELP_40 = 301001,

    SPELL_FIREBALL = 18392,
    SPELL_BELLOWING_ROAR = 18431,

    SPELL_FEAR_WARD = 6346,
    SPELL_TREMOR_TOTEM = 8143,
};

bool IsOnyxianWhelp(Unit const* unit);
// Onyxia back on the ground below 40%, where Bellowing Roar fears the raid.
bool IsOnyxiaPhase3(Unit* onyxia);
// The caster is casting the spell or the version the core swapped in for this difficulty.
bool IsCastingDifficultySpell(Unit* caster, uint32 baseSpellId);
Unit* GetOnyxianWhelp(PlayerbotAI* botAI);
}

// Mechanics
class OnyxiaDeepBreathTrigger : public Trigger
{
public:
    OnyxiaDeepBreathTrigger(PlayerbotAI* botAI);
    bool IsActive() override;
};

class OnyxiaNearTailTrigger : public Trigger
{
public:
    OnyxiaNearTailTrigger(PlayerbotAI* botAI);
    bool IsActive() override;
};

class RaidOnyxiaFireballSplashTrigger : public Trigger
{
public:
    RaidOnyxiaFireballSplashTrigger(PlayerbotAI* botAI);
    bool IsActive() override;
};

class RaidOnyxiaWhelpsSpawnTrigger : public Trigger
{
public:
    RaidOnyxiaWhelpsSpawnTrigger(PlayerbotAI* botAI);
    bool IsActive() override;
};

class OnyxiaAvoidEggsTrigger : public Trigger
{
public:
    OnyxiaAvoidEggsTrigger(PlayerbotAI* botAI);
    bool IsActive() override;
};

// Phase 3 (40% - 0%)
class OnyxiaPhase3TremorTotemTrigger : public Trigger
{
public:
    OnyxiaPhase3TremorTotemTrigger(PlayerbotAI* botAI);
    bool IsActive() override;
};

class OnyxiaMainTankNeedsFearWardTrigger : public Trigger
{
public:
    OnyxiaMainTankNeedsFearWardTrigger(PlayerbotAI* botAI);
    bool IsActive() override;
};

class OnyxiaBellowingRoarTrigger : public Trigger
{
public:
    OnyxiaBellowingRoarTrigger(PlayerbotAI* botAI);
    bool IsActive() override;
};

#endif
