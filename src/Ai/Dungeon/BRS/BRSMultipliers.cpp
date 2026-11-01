/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BRSMultipliers.h"
#include "BRSActions.h"
#include "BRSShared.h"
#include "Playerbots.h"

using namespace BRSShared;

// Warchief Rend Blackhand

float RendWhirlwindMultiplier::GetValue(Action* action)
{
    if (PlayerbotAI::IsTank(bot))
        return 1.0f;

    if (!dynamic_cast<MovementAction*>(action) || dynamic_cast<RendAvoidWhirlwindAction*>(action))
        return 1.0f;

    Unit* rend = AI_VALUE2(Unit*, "find target", "warchief rend blackhand");
    if (!rend || !rend->HasAura(SPELL_REND_WHIRLWIND))
        return 1.0f;

    return 0.0f;
}
