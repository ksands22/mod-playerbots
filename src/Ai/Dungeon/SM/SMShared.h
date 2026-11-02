/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SMSHARED_H
#define PLAYERBOTS_SMSHARED_H

#include "Common.h"

namespace SMShared
{

inline constexpr uint32 SM_MAP_ID = 189;

// Arcanist Doan: Arcane Bubble (8s) leads into Detonation
inline constexpr uint32 SPELL_ARCANE_BUBBLE = 9438;
inline constexpr uint32 SPELL_DETONATION = 9435;
inline constexpr float DETONATION_SAFE_DISTANCE = 33.0f;  // 30 yd radius

// Herod: 10s aura pulsing an 8 yd Whirlwind every 2s
inline constexpr uint32 SPELL_HEROD_WHIRLWIND = 8989;
inline constexpr float HEROD_WHIRLWIND_SAFE_DISTANCE = 11.0f;  // 8 yd radius

}

#endif
