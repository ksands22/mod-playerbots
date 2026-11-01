/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_OHBSHARED_H
#define PLAYERBOTS_OHBSHARED_H

#include "Common.h"

class PlayerbotAI;
class Unit;

namespace OHBShared
{

// Lieutenant Drake: 4s aura pulsing an 8 yd Whirlwind every 2s
inline constexpr uint32 SPELL_DRAKE_WHIRLWIND = 31909;
inline constexpr float DRAKE_WHIRLWIND_SAFE_DISTANCE = 11.0f;

// Escorted NPCs; ambushes attack them rather than the group
inline constexpr uint32 NPC_THRALL = 17876;
inline constexpr uint32 NPC_TARETHA = 18887;

Unit* FindAttackerOfEscort(PlayerbotAI* botAI);
bool IsAttackingEscort(Unit* unit);

}

#endif
