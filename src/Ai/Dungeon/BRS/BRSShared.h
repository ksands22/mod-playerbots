/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BRSSHARED_H
#define PLAYERBOTS_BRSSHARED_H

#include "Common.h"

namespace BRSShared
{

// Warchief Rend Blackhand: 2s aura, then one 8 yd Whirlwind pulse
inline constexpr uint32 SPELL_REND_WHIRLWIND = 13736;
inline constexpr float REND_WHIRLWIND_SAFE_DISTANCE = 11.0f;

// General Drakkisath: disorients his victim for 10s and burns their allies within 5 yd every second
inline constexpr uint32 SPELL_CONFLAGRATION = 16805;
inline constexpr float CONFLAGRATION_SAFE_DISTANCE = 8.0f;

}

#endif
