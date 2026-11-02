/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "RFDTriggers.h"
#include "DungeonHelpers.h"
#include "Playerbots.h"
#include "RFDShared.h"

using namespace DungeonHelpers;
using namespace RFDShared;

// Extinguishing the Idol (Belnistrasz)

bool BelnistraszUnderAttackTrigger::IsActive()
{
    if (PlayerbotAI::IsHeal(bot))
        return false;

    return FindAttackerOfCreature(botAI, NPC_BELNISTRASZ);
}
