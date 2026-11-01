/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "RFDMultipliers.h"
#include "ChooseTargetActions.h"
#include "DungeonHelpers.h"
#include "Playerbots.h"
#include "RFDShared.h"

using namespace DungeonHelpers;
using namespace RFDShared;

// Extinguishing the Idol (Belnistrasz)

// Keep the assist actions from pulling a bot off an attacker of Belnistrasz
float BelnistraszDefendMultiplier::GetValue(Action* action)
{
    if (!dynamic_cast<DpsAssistAction*>(action) && !dynamic_cast<TankAssistAction*>(action))
        return 1.0f;

    if (!IsAttackingCreature(AI_VALUE(Unit*, "current target"), NPC_BELNISTRASZ))
        return 1.0f;

    return 0.0f;
}
