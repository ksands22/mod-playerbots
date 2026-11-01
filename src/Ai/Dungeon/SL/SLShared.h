/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SLSHARED_H
#define PLAYERBOTS_SLSHARED_H

#include "Common.h"
#include "Unit.h"

namespace SLShared
{

inline constexpr uint32 SL_MAP_ID = 555;

// Grandmaster Vorpil: travelers walk to him and empower him
inline constexpr uint32 NPC_VOID_TRAVELER = 19226;

// Murmur: Sonic Boom cast, then a 34 yd blast around him; he is rooted
inline constexpr uint32 SPELL_SONIC_BOOM_CAST_N = 33923;
inline constexpr uint32 SPELL_SONIC_BOOM_CAST_H = 38796;
inline constexpr float SONIC_BOOM_SAFE_DISTANCE = 37.0f;

// Murmur's Touch: explodes on its target when it expires and hits players nearby
inline constexpr uint32 SPELL_MURMURS_TOUCH_N = 33711;
inline constexpr uint32 SPELL_MURMURS_TOUCH_H = 38794;
inline constexpr float MURMURS_TOUCH_SAFE_DISTANCE = 15.0f;

inline bool IsCastingSonicBoom(Unit* murmur)
{
    return  murmur && (murmur->FindCurrentSpellBySpellId(SPELL_SONIC_BOOM_CAST_N) ||
                       murmur->FindCurrentSpellBySpellId(SPELL_SONIC_BOOM_CAST_H));
}

inline bool HasMurmursTouch(Unit* unit)
{
    return unit->HasAura(SPELL_MURMURS_TOUCH_N) || unit->HasAura(SPELL_MURMURS_TOUCH_H);
}

}

#endif
