/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_DUNGEONHELPERS_H
#define PLAYERBOTS_DUNGEONHELPERS_H

#include "Common.h"
#include <initializer_list>

class PlayerbotAI;
class Unit;

namespace DungeonHelpers
{

// The nearest living hostile with one of these entries, from the bot's possible targets
Unit* FindNearestOfEntries(PlayerbotAI* botAI, std::initializer_list<uint32> entries);

// Skulls the nearest living hostile with one of these entries, such as a totem or a priority add.
// Keeps an existing skull on any living unit of these entries, so DPS doesn't swap between them.
bool MarkNearestWithSkull(PlayerbotAI* botAI, std::initializer_list<uint32> entries);

// The nearest hostile whose victim is a creature with this entry, such as an escorted or channeling
// NPC. Bots don't count it as an attacker, since it is on no group member's threat list.
Unit* FindAttackerOfCreature(PlayerbotAI* botAI, uint32 creatureEntry);

bool IsAttackingCreature(Unit* unit, uint32 creatureEntry);

// The nearest hostile within range of the bot that is casting one of these spells
Unit* FindNearbyCaster(PlayerbotAI* botAI, std::initializer_list<uint32> spells, float range);

}

#endif
