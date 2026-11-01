/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "OHBShared.h"
#include "DungeonHelpers.h"

namespace OHBShared
{

Unit* FindAttackerOfEscort(PlayerbotAI* botAI)
{
    if (Unit* attacker = DungeonHelpers::FindAttackerOfCreature(botAI, NPC_THRALL))
        return attacker;

    return DungeonHelpers::FindAttackerOfCreature(botAI, NPC_TARETHA);
}

bool IsAttackingEscort(Unit* unit)
{
    return  DungeonHelpers::IsAttackingCreature(unit, NPC_THRALL) ||
            DungeonHelpers::IsAttackingCreature(unit, NPC_TARETHA);
}

}
