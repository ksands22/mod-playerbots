/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "RFDActions.h"
#include "DungeonHelpers.h"
#include "Playerbots.h"
#include "RFDShared.h"

using namespace DungeonHelpers;
using namespace RFDShared;

// Extinguishing the Idol (Belnistrasz)

bool BelnistraszDefendAction::Execute(Event /*event*/)
{
    // Don't swap between attackers while already on one
    if (IsAttackingCreature(AI_VALUE(Unit*, "current target"), NPC_BELNISTRASZ))
        return false;

    Unit* attacker = FindAttackerOfCreature(botAI, NPC_BELNISTRASZ);
    if (!attacker)
        return false;

    return Attack(attacker);
}
