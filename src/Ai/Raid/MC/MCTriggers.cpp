/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "MCTriggers.h"
#include "EncounterHelpers.h"
#include "MCHelpers.h"
#include "SharedDefines.h"
#include "SpellAuras.h"
#include "Timer.h"

using namespace EncounterHelpers;
using namespace MoltenCoreHelpers;

bool McLivingBombDebuffTrigger::IsActive()
{
    // No check for Baron Geddon, because bots may have the bomb even after Geddon died.
    return bot->HasAura(SPELL_LIVING_BOMB);
}

bool McBaronGeddonInfernoTrigger::IsActive()
{
    if (Unit* boss = AI_VALUE2(Unit*, "find target", "baron geddon"))
        return boss->HasAura(SPELL_INFERNO);
    return false;
}

bool McShazzrahRangedTrigger::IsActive()
{
    // Only fire inside Arcane Explosion range. The move-away action no-ops
    // beyond it, so an unconditional trigger makes every already-safe ranged
    // bot attempt a failing move each tick.
    if (!PlayerbotAI::IsRanged(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "shazzrah");
    return boss && bot->GetDistance2d(boss) < ARCANE_EXPLOSION_DISTANCE;
}

bool McInLavaTrigger::IsActive()
{
    LiquidData const& liquid = bot->GetLiquidData();
    return (liquid.Flags & MAP_LIQUID_TYPE_MAGMA) &&
           (liquid.Status & (LIQUID_MAP_WATER_WALK | LIQUID_MAP_IN_WATER | LIQUID_MAP_UNDER_WATER));
}

bool McGolemaggMagmaSplashTrigger::IsActive()
{
    if (PlayerbotAI::IsTank(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "golemagg the incinerator");
    if (!boss)
        return false;

    // Below 10% the fight is a burn race (Earthquake pulses, Core Ragers
    // converge): stack management stops mattering, melee return to dps.
    if (boss->GetHealthPct() <= 10.0f)
        return false;

    Aura* splash = bot->GetAura(SPELL_MAGMA_SPLASH);
    if (!splash || splash->GetStackAmount() < MAGMA_SPLASH_BACK_OFF_STACKS)
        return false;

    // Only fire while still inside swing range; once the bot has backed off,
    // the multiplier keeps it from re-engaging until the stack expires.
    return bot->GetDistance2d(boss) < MAGMA_SPLASH_BACK_OFF_DISTANCE;
}

bool McGolemaggMarkBossTrigger::IsActive()
{
    // any tank may mark the boss
    return PlayerbotAI::IsTank(bot) && AI_VALUE2(Unit*, "find target", "golemagg the incinerator");
}

bool McGolemaggIsMainTankTrigger::IsActive()
{
    return PlayerbotAI::IsMainTank(bot) && AI_VALUE2(Unit*, "find target", "golemagg the incinerator");
}

bool McGolemaggIsAssistTankTrigger::IsActive()
{
    return PlayerbotAI::IsAssistTank(bot) && AI_VALUE2(Unit*, "find target", "golemagg the incinerator");
}

bool McGolemaggIsHealerTrigger::IsActive()
{
    return PlayerbotAI::IsHeal(bot) && AI_VALUE2(Unit*, "find target", "golemagg the incinerator");
}

bool McCoreHoundMarkTrigger::IsActive()
{
    return PlayerbotAI::IsMainTank(bot) && AI_VALUE2(Unit*, "find target", "core hound");
}

bool McKillOrderMarkTrigger::IsActive()
{
    // One marker per raid; encounter-only, so trash packs with the same adds keep normal targeting.
    return bot->IsInCombat() && IsEncounterInProgress(bot, MAP_MOLTEN_CORE) &&
           IsMechanicTrackerBot(bot, MAP_MOLTEN_CORE) && GetKillOrderMarkTarget(botAI);
}

bool McSulfuronDarkMendingTrigger::IsActive()
{
    return AI_VALUE2(Unit*, "find target", "sulfuron harbinger") && GetDarkMendingCaster(botAI);
}

bool McMajordomoReflectionTrigger::IsActive()
{
    if (PlayerbotAI::IsTank(bot) || !AI_VALUE2(Unit*, "find target", "majordomo executus"))
        return false;

    return GetReflectedAttackTarget(bot) != nullptr;
}

bool McRagnarosRangedTooCloseTrigger::IsActive()
{
    if (!PlayerbotAI::IsRanged(bot) || PlayerbotAI::IsTank(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "ragnaros");
    return IsRagnarosEmerged(boss) && bot->GetExactDist2d(boss) < RAGNAROS_WRATH_SAFE_DISTANCE;
}

bool McRagnarosRangedSpreadTrigger::IsActive()
{
    if (!PlayerbotAI::IsRanged(bot) || PlayerbotAI::IsTank(bot))
        return false;

    if (!IsRagnarosEmerged(AI_VALUE2(Unit*, "find target", "ragnaros")))
        return false;

    return GetNearestPlayerInRadius(bot, RAGNAROS_SPREAD_DISTANCE) != nullptr;
}

bool McRagnarosWrathSoonTrigger::IsActive()
{
    if (!PlayerbotAI::IsMelee(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "ragnaros");
    bool const engaged = IsRagnarosEmerged(boss) && boss->IsInCombat();
    uint32 const now = getMSTime();

    // A gap in evaluation (out of combat, dead) means the old phase start no longer applies.
    constexpr uint32 MAX_EVALUATION_GAP_MS = 5000;
    if (!engaged || (_lastSeenMs && getMSTimeDiff(_lastSeenMs, now) > MAX_EVALUATION_GAP_MS))
        _phaseStartMs = 0;
    _lastSeenMs = now;

    if (!engaged)
        return false;

    if (!_phaseStartMs)
        _phaseStartMs = now;

    // His current target holds him in melee: without it he starts casting Magma Blast at the raid.
    if (boss->GetVictim() == bot || bot->GetExactDist2d(boss) >= RAGNAROS_WRATH_SAFE_DISTANCE)
        return false;

    uint32 const elapsed = getMSTimeDiff(_phaseStartMs, now);
    uint32 const untilWrath = elapsed < RAGNAROS_WRATH_FIRST_MS
        ? RAGNAROS_WRATH_FIRST_MS - elapsed
        : RAGNAROS_WRATH_INTERVAL_MS - (elapsed - RAGNAROS_WRATH_FIRST_MS) % RAGNAROS_WRATH_INTERVAL_MS;
    return untilWrath <= RAGNAROS_WRATH_LEAD_MS;
}
