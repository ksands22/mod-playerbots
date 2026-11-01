/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MTSHARED_H
#define PLAYERBOTS_MTSHARED_H

#include "Common.h"
#include "Unit.h"

namespace MTShared
{

inline constexpr uint32 MT_MAP_ID = 557;

// Pandemonius: for 6s, damages melee attackers and reflects spells
inline constexpr uint32 SPELL_DARK_SHELL_N = 32358;
inline constexpr uint32 SPELL_DARK_SHELL_H = 38759;

// Nexus-Prince Shaffar: beacons turn into Ethereal Apprentices
inline constexpr uint32 NPC_ETHEREAL_BEACON = 18431;

inline bool HasDarkShell(Unit* unit)
{
    return unit && (unit->HasAura(SPELL_DARK_SHELL_N) || unit->HasAura(SPELL_DARK_SHELL_H));
}

}

#endif
