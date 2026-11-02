/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "MTMultipliers.h"
#include "AttackAction.h"
#include "GenericSpellActions.h"
#include "MTShared.h"
#include "Playerbots.h"

using namespace MTShared;

// Pandemonius

// Nothing hits him while Dark Shell is up: melee takes its damage and spells reflect
float PandemoniusDarkShellMultiplier::GetValue(Action* action)
{
    bool const attacksTarget = dynamic_cast<AttackAction*>(action) ||
                               (dynamic_cast<CastSpellAction*>(action) &&
                                action->GetTargetName() == "current target");
    if (!attacksTarget)
        return 1.0f;

    if (!HasDarkShell(AI_VALUE(Unit*, "current target")))
        return 1.0f;

    return 0.0f;
}
