/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_DMSHARED_H
#define PLAYERBOTS_DMSHARED_H

#include "Common.h"

namespace DMShared
{

inline constexpr uint32 DM_MAP_ID = 429;

// Immol'thar: summons Eyes of Immol'thar
inline constexpr uint32 NPC_EYE_OF_IMMOLTHAR = 14396;

// Prince Tortheldrin: 2s aura, then one 8 yd Whirlwind pulse
inline constexpr uint32 SPELL_TORTHELDRIN_WHIRLWIND = 13736;
inline constexpr float TORTHELDRIN_WHIRLWIND_SAFE_DISTANCE = 11.0f;

}

#endif
