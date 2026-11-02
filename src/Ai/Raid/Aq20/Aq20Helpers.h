/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20HELPERS_H
#define PLAYERBOTS_AQ20HELPERS_H

#include "Define.h"

class Player;
class PlayerbotAI;
class Unit;

namespace Aq20Helpers
{
constexpr uint32 MAP_RUINS_OF_AHNQIRAJ = 509;

enum Aq20NPCs
{
    // General Rajaxx and his wave captains
    NPC_RAJAXX = 15341,
    NPC_CAPTAIN_QEEZ = 15391,
    NPC_CAPTAIN_TUUBID = 15392,
    NPC_CAPTAIN_DRENN = 15389,
    NPC_CAPTAIN_XURREM = 15390,
    NPC_MAJOR_YEGGETH = 15386,
    NPC_MAJOR_PAKKON = 15388,
    NPC_COLONEL_ZERRAN = 15385,

    // Moam
    NPC_MOAM = 15340,
    NPC_MANA_FIEND = 15527,

    // Buru the Gorger
    NPC_BURU = 15370,
    NPC_BURU_EGG = 15514,

    // Ayamiss the Hunter
    NPC_HIVEZARA_LARVA = 15555,
};

enum Aq20Spells
{
    SPELL_MORTAL_WOUND = 25646,    // Kurinnaxx
    SPELL_MOAM_ENERGIZE = 25685,   // Moam's stone phase
    SPELL_BURU_THORNS = 25640,     // Buru's egg phase; gone below 20%
    SPELL_POISON_STINGER = 25748,  // Ayamiss
};

// Warcraft Tavern swaps Kurinnaxx's tank at about 5 Mortal Wound stacks.
constexpr uint32 KURINNAXX_SWAP_STACKS = 5;
// The wiki keeps Poison Stinger below 20 stacks, so the healers don't run dry.
constexpr uint32 AYAMISS_STINGER_HOLD_STACKS = 20;
// A raid-killed egg hurts Buru within 25y; 15y leaves margin for him walking past. Our number.
constexpr float BURU_EGG_KILL_DISTANCE = 15.0f;
// The chased player stands this far beyond the egg, so Buru's path runs over it. Our number.
constexpr float BURU_KITE_BEYOND_EGG = 8.0f;
constexpr float AQ20_ADD_SEARCH_DISTANCE = 60.0f;

// The captain, Mana Fiend or Buru egg the raid should kill next, or null when the skull is already right.
Unit* GetKillOrderMarkTarget(PlayerbotAI* botAI);
// The Mana Fiend to banish with the moon icon, or null when moon is already right.
Unit* GetCcMarkTarget(PlayerbotAI* botAI);
Unit* GetNearestNpc(PlayerbotAI* botAI, uint32 entry, float maxDistance);
bool IsMoamStoned(Unit const* moam);
bool IsBuruEggPhase(Unit const* buru);
uint32 GetAuraStacks(Unit const* unit, uint32 spellId);
}

#endif
