/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "DMMultipliers.h"
#include "DMActions.h"
#include "DMShared.h"
#include "Playerbots.h"

using namespace DMShared;

// Prince Tortheldrin

float TortheldrinWhirlwindMultiplier::GetValue(Action* action)
{
    if (PlayerbotAI::IsTank(bot))
        return 1.0f;

    if (!dynamic_cast<MovementAction*>(action) || dynamic_cast<TortheldrinAvoidWhirlwindAction*>(action))
        return 1.0f;

    Unit* tortheldrin = AI_VALUE2(Unit*, "find target", "prince tortheldrin");
    if (!tortheldrin || !tortheldrin->HasAura(SPELL_TORTHELDRIN_WHIRLWIND))
        return 1.0f;

    return 0.0f;
}
