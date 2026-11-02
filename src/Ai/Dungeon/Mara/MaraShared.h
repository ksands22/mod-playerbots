/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MARASHARED_H
#define PLAYERBOTS_MARASHARED_H

#include "Common.h"

namespace MaraShared
{

// Tinkerer Gizlock: 8s channel of a 10 yd frontal cone
inline constexpr uint32 SPELL_GOBLIN_DRAGON_GUN = 21833;
inline constexpr float GOBLIN_DRAGON_GUN_SAFE_DISTANCE = 13.0f;
inline constexpr float GOBLIN_DRAGON_GUN_ARC = 1.5708f;  // 90 degrees, centred on his facing

// Princess Theradras: roots herself for 8s and pulses a 20 yd AoE with knockback every second
inline constexpr uint32 SPELL_DUST_FIELD = 21909;
inline constexpr float DUST_FIELD_SAFE_DISTANCE = 23.0f;

}

#endif
