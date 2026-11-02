/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "MaraMultipliers.h"
#include "MaraActions.h"
#include "MaraShared.h"
#include "Playerbots.h"

using namespace MaraShared;

// Princess Theradras

// She is rooted during Dust Field, so keep chasing from walking bots back in until it ends
float TheradrasDustFieldMultiplier::GetValue(Action* action)
{
    if (!dynamic_cast<MovementAction*>(action) || dynamic_cast<TheradrasAvoidDustFieldAction*>(action))
        return 1.0f;

    Unit* theradras = AI_VALUE2(Unit*, "find target", "princess theradras");
    if (!theradras || !theradras->HasAura(SPELL_DUST_FIELD))
        return 1.0f;

    return 0.0f;
}
