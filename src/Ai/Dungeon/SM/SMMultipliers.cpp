/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SMMultipliers.h"
#include "Playerbots.h"
#include "SMActions.h"
#include "SMHelpers.h"

using namespace SMShared;

// Arcanist Doan

// Keep other movement (chasing, following) from walking bots back into Detonation range
float DoanDetonationMultiplier::GetValue(Action* action)
{
    if (!dynamic_cast<MovementAction*>(action) || dynamic_cast<DoanAvoidDetonationAction*>(action))
        return 1.0f;

    if (!IsDoanDetonating(AI_VALUE2(Unit*, "find target", "arcanist doan")))
        return 1.0f;

    return 0.0f;
}

// Herod

float HerodWhirlwindMultiplier::GetValue(Action* action)
{
    if (PlayerbotAI::IsTank(bot))
        return 1.0f;

    if (!dynamic_cast<MovementAction*>(action) || dynamic_cast<HerodAvoidWhirlwindAction*>(action))
        return 1.0f;

    if (!IsHerodWhirlwinding(AI_VALUE2(Unit*, "find target", "herod")))
        return 1.0f;

    return 0.0f;
}
