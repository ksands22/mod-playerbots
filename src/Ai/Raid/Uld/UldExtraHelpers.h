/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ULDEXTRAHELPERS_H
#define PLAYERBOTS_ULDEXTRAHELPERS_H

#include "AreaDefines.h"
#include "Define.h"
#include "Position.h"

class Player;
class PlayerbotAI;
class Unit;

// Ignis, XT-002, Auriaya and Algalon, from the WotLK guides and the current core scripts.
namespace UlduarExtraHelpers
{

enum UlduarExtraNPCs
{
    // Ignis the Furnace Master
    NPC_IRON_CONSTRUCT = 33121,
    NPC_SCORCHED_GROUND = 33123,
    NPC_WATER_TRIGGER = 22515,

    // The Iron Council
    NPC_STORMCALLER_BRUNDIR = 32857,
    NPC_STEELBREAKER = 32867,
    NPC_RUNEMASTER_MOLGEIM = 32927,

    // Hodir
    NPC_FLASH_FREEZE_PLAYER = 32926,
    NPC_FLASH_FREEZE_HELPER = 32938,
    NPC_TOASTY_FIRE = 33342,

    // Freya and her Elders
    NPC_IRON_ROOTS = 33088,
    NPC_STRENGTHENED_IRON_ROOTS = 33168,
    NPC_FREYA_SUN_BEAM = 33170,
    NPC_BRIGHTLEAF_SUN_BEAM = 33050,

    // Mimiron
    NPC_MIMIRON_PROXIMITY_MINE = 34362,

    // Yogg-Saron
    NPC_YOGG_OMINOUS_CLOUD = 33292,

    // XT-002 Deconstructor
    NPC_HEART_OF_THE_DECONSTRUCTOR = 33329,
    NPC_XS013_SCRAPBOT = 33343,
    NPC_XM024_PUMMELLER = 33344,
    NPC_XE321_BOOMBOT = 33346,

    // Auriaya
    NPC_SANCTUM_SENTRY = 34014,
    NPC_FERAL_DEFENDER = 34035,

    // Algalon the Observer
    NPC_BLACK_HOLE = 32953,
    NPC_COLLAPSING_STAR = 32955,
    NPC_LIVING_CONSTELLATION = 33052,
};

enum UlduarExtraSpells
{
    // Ignis; the core swaps in the 25-player versions by difficulty.
    SPELL_IGNIS_MOLTEN = 62373,
    SPELL_IGNIS_BRITTLE = 62382,
    SPELL_SCORCHED_GROUND = 62548,
    SPELL_FLAME_JETS = 62680,

    // The Iron Council
    SPELL_BRUNDIR_CHAIN_LIGHTNING = 61879,
    SPELL_BRUNDIR_LIGHTNING_WHIRL = 61915,

    // Kologarn
    SPELL_CRUNCH_ARMOR_10 = 63355,
    SPELL_CRUNCH_ARMOR_25 = 64002,

    // Hodir
    SPELL_BITING_COLD = 62039,
    SPELL_FROZEN_BLOWS = 62478,

    // Freya and her Elders
    SPELL_NATURES_FURY = 62589,
    SPELL_UNSTABLE_ENERGY_FREYA = 62451,
    SPELL_GROUND_TREMOR_FREYA = 62437,
    SPELL_GROUND_TREMOR_STONEBARK = 62325,

    // General Vezax
    SPELL_VEZAX_SEARING_FLAMES = 62661,

    // Yogg-Saron
    SPELL_GUARDIAN_DARK_VOLLEY = 63038,

    // XT-002
    SPELL_SEARING_LIGHT = 63018,
    SPELL_GRAVITY_BOMB = 63024,

    // Auriaya
    SPELL_SENTINEL_BLAST = 64389,

    // Algalon
    SPELL_PHASE_PUNCH = 64412,
    SPELL_BIG_BANG = 64443,
};

// Biting Cold stacks a ranged bot or healer takes before it goes to a Toasty Fire; ours.
constexpr uint32 BITING_COLD_FIRE_STACKS = 2;
// Guides swap Kologarn's tanks after 2 Crunch Armor stacks.
constexpr uint32 CRUNCH_ARMOR_SWAP_STACKS = 2;
// Guides swap Algalon at 4 Phase Punch stacks; the 5th phases the tank out.
constexpr uint32 PHASE_PUNCH_SWAP_STACKS = 4;
// Enter a Black Hole with this much of the 8s Big Bang left, as guides time it near the end.
constexpr int32 BIG_BANG_ENTER_LEAD_MS = 4000;
// XT-002's heart is a burst window, but killing it starts hard mode; this is where DPS stop.
constexpr float XT_HEART_STOP_PCT = 15.0f;
// The core sets a Proximity Mine off when a player comes within 1.9 yd; the margin is ours.
constexpr float MIMIRON_MINE_AVOID_DISTANCE = 1.9f + 2.5f;
// The core has an Ominous Cloud summon a Guardian when a player comes within 6 yd; the margin is ours.
constexpr float YOGG_CLOUD_AVOID_DISTANCE = 6.0f + 3.0f;
constexpr float ULDUAR_EXTRA_SEARCH_DISTANCE = 80.0f;

Unit* GetNearestNpc(PlayerbotAI* botAI, uint32 entry, float maxDistance);
bool HasDifficultyAura(Unit const* unit, uint32 baseSpellId, Unit const* caster);
bool IsCastingDifficultySpell(Unit* caster, uint32 baseSpellId, int32* remainingMs = nullptr);
// Skull: Ignis' Brittle constructs, XT-002's exposed heart, Auriaya's Sanctum Sentries, and the
// Iron Council in the guides' normal-mode order (Steelbreaker, Molgeim, Brundir).
Unit* GetKillOrderMarkTarget(PlayerbotAI* botAI);
// An add the first off-tank should hold: Pummellers, Sentries, Feral Defenders, Constellations, Constructs.
Unit* GetUntankedOffTankAdd(PlayerbotAI* botAI);
// Where Ignis' off-tank takes its constructs: Scorch until Molten, then water until Brittle.
bool GetIgnisConstructDestination(PlayerbotAI* botAI, Position& destination);
// How far XT-002's Searing Light or Gravity Bomb reaches from the bot, or 0 without either.
float GetXtDebuffRadius(Player* bot);
Position GetAuriayaStackSpot(Unit const* auriaya);
// A boss casting what guides interrupt: Auriaya's Sentinel Blast, Brundir's Chain Lightning and
// Lightning Whirl, General Vezax's Searing Flames, and the Guardians of Yogg-Saron's Dark Volley.
Unit* GetInterruptTarget(PlayerbotAI* botAI);
// Iron Council tanks: main tank Steelbreaker, first off-tank Molgeim, second off-tank Brundir. A tank
// whose member is dead takes the next living one, as guides move Steelbreaker's tank to Molgeim.
Unit* GetAssignedCouncilMember(PlayerbotAI* botAI);
uint32 GetCrunchArmorStacks(Unit const* unit);
// Hodir: a Flash Freeze ice block to break, frozen players first, then the frozen helpers.
Unit* GetHodirIceBlock(PlayerbotAI* botAI);
// Freya: the nearest Iron Roots or Strengthened Iron Roots holding a player, within spell range.
Unit* GetFreyaIronRoots(PlayerbotAI* botAI);
// How far Nature's Fury reaches from the bot, or 0 without it.
float GetNaturesFuryRadius(Player* bot);
// Freya's or Elder Brightleaf's Sun Beam the bot stands in, with the distance it must get to.
Unit* GetFreyaSunBeamInRange(PlayerbotAI* botAI, float& safeDistance);
}

#endif
