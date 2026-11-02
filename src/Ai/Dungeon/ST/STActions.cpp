/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "STActions.h"
#include "DungeonHelpers.h"
#include "Playerbots.h"
#include "STShared.h"

using namespace DungeonHelpers;
using namespace STShared;

// Atal'ai defenders (Mijan, Zolo)

bool AtalaiDefendersMarkTotemAction::Execute(Event /*event*/)
{
    return MarkNearestWithSkull(botAI, {NPC_MIJAN_HEALING_WARD, NPC_ATALAI_SKELETON_TOTEM});
}
