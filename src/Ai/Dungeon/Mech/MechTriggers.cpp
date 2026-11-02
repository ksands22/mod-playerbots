/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "MechTriggers.h"
#include "AiObject.h"
#include "MechShared.h"
#include "Playerbots.h"

bool SepethreaKiteFlameTrigger::IsActive()
{
    if (!MechanarFlames::GetSepethrea(bot))
        return false;

    if (!MechanarFlames::GetFixatingFlame(bot))
        return false;

    return !MechanarFlames::TankMustGrabBoss(bot);
}

bool SepethreaAvoidFlameTrigger::IsActive()
{
    if (!MechanarFlames::GetSepethrea(bot))
        return false;

    if (MechanarFlames::GetFixatingFlame(bot))
        return false;

    if (!MechanarFlames::IsFlameNearCached(bot))
        return false;

    return !MechanarFlames::HealerHoldsFire(bot);
}

bool SepethreaTrailTrigger::IsActive()
{
    if (!MechanarFlames::GetSepethrea(bot))
        return false;

    if (!MechanarFlames::InTrailDangerCached(bot))
        return false;

    return !MechanarFlames::HealerHoldsFire(bot);
}

bool SepethreaFocusBossTrigger::IsActive()
{
    return MechanarFlames::GetSepethrea(bot) != nullptr;
}

bool IronhandJackhammerTrigger::IsActive()
{
    Unit* ironhand = AI_VALUE2(Unit*, "find target", "gatewatcher iron-hand");
    // A channel may carry its aura on the targets rather than the caster, so check the channel too
    if (!ironhand || (!ironhand->HasAura(MechanarIronhand::SPELL_JACKHAMMER) &&
                      !ironhand->FindCurrentSpellBySpellId(MechanarIronhand::SPELL_JACKHAMMER)))
        return false;

    return bot->GetExactDist2d(ironhand) < MechanarIronhand::JACKHAMMER_SAFE_DISTANCE;
}
