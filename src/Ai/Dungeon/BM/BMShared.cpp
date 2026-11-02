/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BMShared.h"
#include "DungeonHelpers.h"

namespace BMShared
{

namespace
{

enum BlackMorassNpcs : uint32
{
    NPC_TIME_KEEPER             = 17918,
    NPC_RIFT_KEEPER_WARLOCK     = 21104,
    NPC_RIFT_KEEPER_MAGE        = 21148,
    NPC_RIFT_LORD               = 17839,
    NPC_RIFT_LORD_2             = 21140,
    NPC_CHRONO_LORD_DEJA        = 17879,
    NPC_INFINITE_CHRONO_LORD    = 21697,
    NPC_TEMPORUS                = 17880,
    NPC_INFINITE_TIMEREAVER     = 21698,
    NPC_AEONUS                  = 17881,
    NPC_INFINITE_ASSASSIN       = 17835,
    NPC_INFINITE_WHELP          = 21818,
    NPC_INFINITE_CHRONOMANCER   = 17892,
    NPC_INFINITE_EXECUTIONER    = 18994,
    NPC_INFINITE_VANQUISHER     = 18995,
    NPC_INFINITE_ASSASSIN_2     = 21137,
    NPC_INFINITE_CHRONOMANCER_2 = 21136,
    NPC_INFINITE_EXECUTIONER_2  = 21138,
    NPC_INFINITE_VANQUISHER_2   = 21139,
};

}

Unit* FindNearestRiftMob(PlayerbotAI* botAI)
{
    return DungeonHelpers::FindNearestOfEntries(
        botAI, {NPC_TIME_KEEPER, NPC_RIFT_KEEPER_WARLOCK, NPC_RIFT_KEEPER_MAGE, NPC_RIFT_LORD, NPC_RIFT_LORD_2,
                NPC_CHRONO_LORD_DEJA, NPC_INFINITE_CHRONO_LORD, NPC_TEMPORUS, NPC_INFINITE_TIMEREAVER, NPC_AEONUS,
                NPC_INFINITE_ASSASSIN, NPC_INFINITE_WHELP, NPC_INFINITE_CHRONOMANCER, NPC_INFINITE_EXECUTIONER,
                NPC_INFINITE_VANQUISHER, NPC_INFINITE_ASSASSIN_2, NPC_INFINITE_CHRONOMANCER_2,
                NPC_INFINITE_EXECUTIONER_2, NPC_INFINITE_VANQUISHER_2});
}

}
