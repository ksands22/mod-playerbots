/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BFSHARED_H
#define PLAYERBOTS_BFSHARED_H

#include "Common.h"

namespace BFShared
{

// Keli'dan the Breaker: 5s aura (Vortex pulls everyone in on heroic), then a 15 yd Fire Nova
inline constexpr uint32 SPELL_BURNING_NOVA = 30940;
inline constexpr float BURNING_NOVA_SAFE_DISTANCE = 18.0f;

}

#endif
