/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_HORSHARED_H
#define PLAYERBOTS_HORSHARED_H

#include "Common.h"

namespace HoRShared
{

inline constexpr uint32 HOR_MAP_ID = 668;

// Spirit waves: priests heal and DoT, mages burst
inline constexpr uint32 NPC_WAVE_PRIEST = 38175;
inline constexpr uint32 NPC_WAVE_MAGE = 38172;

// Lich King escape: witch doctors cast from behind each wall's ghouls
inline constexpr uint32 NPC_RISEN_WITCH_DOCTOR = 36941;

}

#endif
