/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGHELPERS_H
#define PLAYERBOTS_ZGHELPERS_H

#include "Define.h"
#include <string>

class Player;
class PlayerbotAI;
class Unit;

namespace ZulGurubHelpers
{
constexpr uint32 MAP_ZUL_GURUB = 309;

enum ZulGurubNPCs
{
    // High Priest Venoxis
    NPC_VENOXIS = 14507,
    NPC_RAZZASHI_COBRA = 11373,

    // High Priestess Mar'li
    NPC_MARLI = 14510,
    NPC_SPAWN_OF_MARLI = 15041,

    // High Priest Thekal
    NPC_THEKAL = 14509,
    NPC_ZEALOT_LORKHAN = 11347,
    NPC_ZEALOT_ZATH = 11348,
    NPC_ZULIAN_TIGER = 11361,

    // Bloodlord Mandokir
    NPC_OHGAN = 14988,

    // High Priestess Arlokk
    NPC_ZULIAN_PROWLER = 15101,

    // Jin'do the Hexxer
    NPC_JINDO = 11380,
    NPC_SHADE_OF_JINDO = 14986,
    NPC_POWERFUL_HEALING_WARD = 14987,
    NPC_BRAIN_WASH_TOTEM = 15112,

    // Edge of Madness
    NPC_NIGHTMARE_ILLUSION = 15163,  // Hazza'rah

    // Hakkar
    NPC_SON_OF_HAKKAR = 11357,
    NPC_POISONOUS_CLOUD = 14989,  // left by a dying Son of Hakkar
};

enum ZulGurubSpells
{
    // High Priestess Jeklik
    SPELL_JEKLIK_BAT_FORM = 23966,
    SPELL_JEKLIK_MIND_FLAY = 23953,
    SPELL_JEKLIK_GREATER_HEAL = 23954,

    // High Priest Venoxis
    SPELL_VENOXIS_TRANSFORM = 23849,

    // High Priestess Mar'li
    SPELL_MARLI_DRAIN_LIFE = 24300,

    // High Priest Thekal
    SPELL_THEKAL_TIGER_FORM = 24169,
    SPELL_LORKHAN_GREATER_HEAL = 24208,

    // Bloodlord Mandokir
    SPELL_THREATENING_GAZE = 24314,

    // Jin'do the Hexxer
    SPELL_DELUSIONS_OF_JINDO = 24306,

    // Gri'lek
    SPELL_GRILEK_AVATAR = 24646,

    // Hakkar
    SPELL_POISONOUS_BLOOD = 24321,
};

// Jeklik's priest phase: no one within 5y of anyone else
constexpr float JEKLIK_SPREAD_DISTANCE = 5.0f;
// Venoxis' snake form: everyone but his target stays 25y away
constexpr float VENOXIS_SNAKE_SAFE_DISTANCE = 25.0f;
// Gri'lek's Avatar target stays out of reach; 20y is also outside his Ground Tremor stun.
constexpr float GRILEK_KITE_DISTANCE = 20.0f;
// Gri'lek and Wushoolay: guides spread casters and healers but give no distance; this is ours.
constexpr float CASTER_SPREAD_DISTANCE = 10.0f;
// The Poisonous Cloud applies Poisonous Blood within 8y
constexpr float POISONOUS_CLOUD_STAND_DISTANCE = 4.0f;
constexpr float POISONOUS_CLOUD_SEARCH_DISTANCE = 40.0f;

// Blood Siphon follows the core script's schedule: 90s after the pull, then every 90s. The wiki
// pulls a Son "a few seconds before the Siphon" and kills it on arrival. Its cloud lasts only 10s,
// so 25s leaves ~10s to fetch it from the steps and ~5s to kill it, with the cloud covering the cast.
constexpr uint32 HAKKAR_BLOOD_SIPHON_INTERVAL_MS = 90000;
constexpr uint32 HAKKAR_SON_PULL_LEAD_MS = 25000;
// The Sons stand on the steps 20-30y below Hakkar's platform.
constexpr float HAKKAR_SON_SEARCH_DISTANCE = 60.0f;
constexpr float HAKKAR_SON_RETURN_DISTANCE = 8.0f;
// The Son only gets skull once the tank has it this close to the raid, so its cloud lands there.
constexpr float HAKKAR_SON_ARRIVED_DISTANCE = 15.0f;

// The add or council member the raid should kill next, or null when the skull is already right.
Unit* GetKillOrderMarkTarget(PlayerbotAI* botAI);
// The cobra or tiger to crowd-control with the moon icon, or null when moon is already right.
Unit* GetCcMarkTarget(PlayerbotAI* botAI);
// An enemy casting a heal or drain the guides say to interrupt; heals first.
Unit* GetInterruptTarget(PlayerbotAI* botAI);
bool IsJeklikPriestPhase(Unit const* jeklik);
bool IsVenoxisSnakeForm(Unit const* venoxis);
bool IsThekalCouncilPhase(Unit const* thekal);
Unit* GetNearestNpc(PlayerbotAI* botAI, uint32 entry, float maxDistance);
// Cures that would strip Poisonous Blood before Blood Siphon
bool IsPoisonCureSpell(std::string const& spell);
bool IsCurseRemovalSpell(std::string const& spell);
}

#endif
