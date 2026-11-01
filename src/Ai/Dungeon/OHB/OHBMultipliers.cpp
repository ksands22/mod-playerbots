/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "OHBMultipliers.h"
#include "ChooseTargetActions.h"
#include "OHBActions.h"
#include "OHBShared.h"
#include "Playerbots.h"

using namespace OHBShared;

// Lieutenant Drake

float DrakeWhirlwindMultiplier::GetValue(Action* action)
{
    if (PlayerbotAI::IsTank(bot))
        return 1.0f;

    if (!dynamic_cast<MovementAction*>(action) || dynamic_cast<DrakeAvoidWhirlwindAction*>(action))
        return 1.0f;

    Unit* drake = AI_VALUE2(Unit*, "find target", "lieutenant drake");
    if (!drake || !drake->HasAura(SPELL_DRAKE_WHIRLWIND))
        return 1.0f;

    return 0.0f;
}

// Thrall's escort

// Keep the assist actions from pulling a bot off an attacker of Thrall or Taretha
float ThrallDefendMultiplier::GetValue(Action* action)
{
    if (!dynamic_cast<DpsAssistAction*>(action) && !dynamic_cast<TankAssistAction*>(action))
        return 1.0f;

    if (!IsAttackingEscort(AI_VALUE(Unit*, "current target")))
        return 1.0f;

    return 0.0f;
}
