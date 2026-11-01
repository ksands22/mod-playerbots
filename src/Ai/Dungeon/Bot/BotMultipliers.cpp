/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BotMultipliers.h"
#include "BotActions.h"
#include "BotShared.h"
#include "Playerbots.h"

using namespace BotShared;

// Thorngrin the Tender

// He channels in place, so keep chasing from walking bots back into Hellfire
float ThorngrinHellfireMultiplier::GetValue(Action* action)
{
    if (!dynamic_cast<MovementAction*>(action) || dynamic_cast<ThorngrinAvoidHellfireAction*>(action))
        return 1.0f;

    Unit* thorngrin = AI_VALUE2(Unit*, "find target", "thorngrin the tender");
    if (!thorngrin || !thorngrin->HasAura(SPELL_HELLFIRE))
        return 1.0f;

    return 0.0f;
}
