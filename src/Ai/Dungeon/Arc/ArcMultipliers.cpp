/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ArcMultipliers.h"
#include "ArcActions.h"
#include "ArcShared.h"
#include "Playerbots.h"

using namespace ArcShared;

// Dalliah the Doomsayer

float DalliahWhirlwindMultiplier::GetValue(Action* action)
{
    if (PlayerbotAI::IsTank(bot))
        return 1.0f;

    if (!dynamic_cast<MovementAction*>(action) || dynamic_cast<DalliahAvoidWhirlwindAction*>(action))
        return 1.0f;

    Unit* dalliah = AI_VALUE2(Unit*, "find target", "dalliah the doomsayer");
    if (!dalliah || !dalliah->HasAura(SPELL_DALLIAH_WHIRLWIND))
        return 1.0f;

    return 0.0f;
}
