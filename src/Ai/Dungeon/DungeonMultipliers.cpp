/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "DungeonMultipliers.h"
#include "GenericSpellActions.h"
#include "Playerbots.h"

float ReflectingTargetMultiplier::GetValue(Action* action)
{
    if (!PlayerbotAI::IsCaster(bot))
        return 1.0f;

    if (!dynamic_cast<CastSpellAction*>(action) || action->GetTargetName() != "current target")
        return 1.0f;

    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target)
        return 1.0f;

    for (uint32 const spellId : _reflectSpells)
    {
        if (target->HasAura(spellId))
            return 0.0f;
    }

    return 1.0f;
}
