/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MCHELPERS_H
#define PLAYERBOTS_MCHELPERS_H

#include "Define.h"

class Player;
class PlayerbotAI;
class Unit;

namespace MoltenCoreHelpers
{
constexpr uint32 MAP_MOLTEN_CORE = 409;

enum MoltenCoreNPCs
{
    // Lucifron
    NPC_LUCIFRON = 12118,
    NPC_FLAMEWAKER_PROTECTOR = 12119,

    // Gehennas
    NPC_GEHENNAS = 12259,
    NPC_FLAMEWAKER = 11661,

    // Sulfuron Harbinger
    NPC_SULFURON_HARBINGER = 12098,
    NPC_FLAMEWAKER_PRIEST = 11662,

    // Golemagg
    NPC_CORE_RAGER = 11672,

    // Majordomo Executus
    NPC_MAJORDOMO_EXECUTUS = 12018,
    NPC_FLAMEWAKER_HEALER = 11663,
    NPC_FLAMEWAKER_ELITE = 11664,

    // Ragnaros
    NPC_RAGNAROS = 11502,
    NPC_SON_OF_FLAME = 12143,

    // Core Hound (trash)
    NPC_CORE_HOUND = 11671,
};
enum MoltenCoreSpells
{
    // Baron Geddon
    SPELL_INFERNO = 19695,
    SPELL_LIVING_BOMB = 20475,

    // Sulfuron Harbinger
    SPELL_DARK_MENDING = 19775,

    // Golemagg
    SPELL_GOLEMAGGS_TRUST = 20553,
    SPELL_MAGMA_SPLASH = 13880,

    // Majordomo Executus
    SPELL_MAGIC_REFLECTION = 20619,
    SPELL_DAMAGE_REFLECTION = 21075,
};

constexpr uint32 MAGMA_SPLASH_BACK_OFF_STACKS = 20;
constexpr float MAGMA_SPLASH_BACK_OFF_DISTANCE = 12.0f;

// Shazzrah's Arcane Explosion radius
constexpr float ARCANE_EXPLOSION_DISTANCE = 26.0f;

// Wrath of Ragnaros knocks back everything within 25y of his center
constexpr float RAGNAROS_WRATH_SAFE_DISTANCE = 28.0f;
// Might of Ragnaros explodes for 20y around a random mana user; the full radius
// cannot be kept on the shore, so this only limits how many get caught.
constexpr float RAGNAROS_SPREAD_DISTANCE = 10.0f;

// Wrath of Ragnaros is instant, so melee step out on the core script's schedule:
// first cast 30s after he engages or emerges, then every 25s.
constexpr uint32 RAGNAROS_WRATH_FIRST_MS = 30000;
constexpr uint32 RAGNAROS_WRATH_INTERVAL_MS = 25000;
// Melee start at his hitbox edge and need ~2-3s at run speed to clear 28y.
constexpr uint32 RAGNAROS_WRATH_LEAD_MS = 3000;
// Covers the lead plus a second after the cast, so a late prediction still clears the knockback.
constexpr uint32 RAGNAROS_WRATH_HOLD_MS = RAGNAROS_WRATH_LEAD_MS + 1000;

// The add the raid should kill next in an add encounter, or null when the skull is already right.
Unit* GetKillOrderMarkTarget(PlayerbotAI* botAI);
Unit* GetDarkMendingCaster(PlayerbotAI* botAI);
// True when Majordomo's shield on the target punishes the way this bot attacks.
bool IsReflectingAttacksFrom(Unit* target, Player* bot);
Unit* GetReflectedAttackTarget(Player* bot);
// Ragnaros is unattackable during the intro and while submerged.
bool IsRagnarosEmerged(Unit* ragnaros);
bool IsMagmaAt(Player* bot, float x, float y, float z);
}

#endif
