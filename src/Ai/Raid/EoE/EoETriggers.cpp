/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "EoETriggers.h"
#include "SharedDefines.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include <algorithm>

uint8 MalygosTrigger::getPhase(Player* bot, Unit* boss)
{
    uint8 phase = 0;
    Unit* vehicle = bot->GetVehicleBase();
    if (bot->GetMapId() != EOE_MAP_ID) { return phase; }

    if (vehicle && vehicle->GetEntry() == NPC_WYRMREST_SKYTALON)
    {
        phase = 3;
    }
    else if (boss && boss->HealthAbovePct(50))
    {
        phase = 1;
    }
    else if (boss)
    {
        phase = 2;
    }

    return phase;
}

bool MalygosTrigger::IsActive()
{
    return bool(AI_VALUE2(Unit*, "find target", "malygos"));
}

bool PowerSparkTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "malygos");
    if (!boss) { return false; }

    if (bot->getClass() != CLASS_DEATH_KNIGHT)
    {
        return false;
    }

    GuidVector targets = AI_VALUE(GuidVector, "possible targets no los");
    for (auto& target : targets)
    {
        Unit* unit = botAI->GetUnit(target);
        if (unit && unit->GetEntry() == NPC_POWER_SPARK)
        {
            return true;
        }
    }

    return false;
}

// Arcane Overload bubbles shrink as they age; staying this close to the center keeps a bot inside. Ours.
static constexpr float ARCANE_OVERLOAD_STAND_DISTANCE = 3.0f;

Unit* GetPowerSparkNearMalygos(PlayerbotAI* botAI, Unit* malygos)
{
    // How close to Malygos a spark gets before it is killed; ours.
    constexpr float SPARK_KILL_DISTANCE = 20.0f;
    if (!malygos)
        return nullptr;

    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("possible targets no los")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (unit && unit->IsAlive() && unit->GetEntry() == NPC_POWER_SPARK &&
            !unit->HasUnitFlag(UNIT_FLAG_NON_ATTACKABLE) && unit->GetExactDist2d(malygos) < SPARK_KILL_DISTANCE)
        {
            return unit;
        }
    }
    return nullptr;
}

Unit* GetNewestArcaneOverload(PlayerbotAI* botAI)
{
    Unit* newest = nullptr;
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("nearest npcs")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (unit && unit->IsAlive() && unit->GetEntry() == NPC_ARCANE_OVERLOAD &&
            (!newest || unit->GetGUID().GetCounter() > newest->GetGUID().GetCounter()))
        {
            newest = unit;
        }
    }
    return newest;
}

Unit* GetStaticFieldInRange(PlayerbotAI* botAI, float& safeDistance)
{
    // Read from the spell data; the fallback and margin are ours.
    constexpr float FALLBACK_STATIC_FIELD_RADIUS = 10.0f;
    constexpr float STATIC_FIELD_MARGIN = 2.0f;
    float radius = 0.0f;
    if (SpellInfo const* info = sSpellMgr->GetSpellInfo(SPELL_STATIC_FIELD_DAMAGE))
        for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
            radius = std::max(radius, info->Effects[i].CalcRadius());
    safeDistance = (radius > 0.0f ? radius : FALLBACK_STATIC_FIELD_RADIUS) + STATIC_FIELD_MARGIN;

    Player* bot = botAI->GetBot();
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("nearest npcs")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (unit && unit->IsAlive() && unit->GetEntry() == NPC_STATIC_FIELD && bot->GetExactDist2d(unit) < safeDistance)
            return unit;
    }
    return nullptr;
}

bool MalygosPowerSparkNearBossTrigger::IsActive()
{
    if (!PlayerbotAI::IsDps(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "malygos");
    if (MalygosTrigger::getPhase(bot, boss) != 1)
        return false;

    Unit* target = AI_VALUE(Unit*, "current target");
    if (target && target->GetEntry() == NPC_POWER_SPARK)
        return false;

    return GetPowerSparkNearMalygos(botAI, boss) != nullptr;
}

bool MalygosOutsideArcaneOverloadTrigger::IsActive()
{
    // Guides stand in the purple bubbles in phase 2; bots riding hover disks are safe already.
    if (bot->GetVehicleBase())
        return false;

    if (MalygosTrigger::getPhase(bot, AI_VALUE2(Unit*, "find target", "malygos")) != 2)
        return false;

    Unit* bubble = GetNewestArcaneOverload(botAI);
    return bubble && bot->GetExactDist2d(bubble) > ARCANE_OVERLOAD_STAND_DISTANCE;
}

bool MalygosStaticFieldTrigger::IsActive()
{
    // Guides move out of Static Field at once.
    if (bot->GetVehicleBase() || MalygosTrigger::getPhase(bot, AI_VALUE2(Unit*, "find target", "malygos")) != 2)
        return false;

    float safeDistance = 0.0f;
    return GetStaticFieldInRange(botAI, safeDistance) != nullptr;
}
