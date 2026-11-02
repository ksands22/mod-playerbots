/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BOTSHARED_H
#define PLAYERBOTS_BOTSHARED_H

#include "Common.h"

namespace BotShared
{

inline constexpr uint32 BOT_MAP_ID = 553;

// High Botanist Freywinn: the Frayers keep him in Tree Form, channelling Tranquility
inline constexpr uint32 NPC_FRAYER = 19953;

// Thorngrin the Tender: 6s channel pulsing a 15 yd Hellfire every second
inline constexpr uint32 SPELL_HELLFIRE = 34659;
inline constexpr float HELLFIRE_SAFE_DISTANCE = 18.0f;

// Warp Splinter: saplings walk to him and heal him
inline constexpr uint32 NPC_SAPLING = 19949;

}

#endif
