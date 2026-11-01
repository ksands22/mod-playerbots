/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "DungeonHelpers.h"
#include "EncounterHelpers.h"
#include "Group.h"
#include "Playerbots.h"
#include "RtiTargetValue.h"
#include <algorithm>

namespace DungeonHelpers
{

namespace
{

bool IsOneOf(Unit* unit, std::initializer_list<uint32> entries)
{
    return std::find(entries.begin(), entries.end(), unit->GetEntry()) != entries.end();
}

}

Unit* FindNearestOfEntries(PlayerbotAI* botAI, std::initializer_list<uint32> entries)
{
    Player* bot = botAI->GetBot();
    GuidVector const targets =
        botAI->GetAiObjectContext()->GetValue<GuidVector>("possible targets no los")->Get();

    Unit* nearest = nullptr;
    float nearestDistance = 0.0f;
    for (ObjectGuid const& guid : targets)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || !IsOneOf(unit, entries))
            continue;

        float const distance = bot->GetDistance(unit);
        if (!nearest || distance < nearestDistance)
        {
            nearest = unit;
            nearestDistance = distance;
        }
    }

    return nearest;
}

bool MarkNearestWithSkull(PlayerbotAI* botAI, std::initializer_list<uint32> entries)
{
    Player* bot = botAI->GetBot();
    Group* group = bot->GetGroup();
    if (!group)
        return false;

    Unit* marked = botAI->GetUnit(group->GetTargetIcon(RtiTargetValue::skullIndex));
    if (marked && marked->IsAlive() && IsOneOf(marked, entries))
        return false;

    return EncounterHelpers::MarkTargetWithSkull(bot, FindNearestOfEntries(botAI, entries));
}

Unit* FindAttackerOfCreature(PlayerbotAI* botAI, uint32 creatureEntry)
{
    Player* bot = botAI->GetBot();
    GuidVector const targets =
        botAI->GetAiObjectContext()->GetValue<GuidVector>("possible targets no los")->Get();

    Unit* nearest = nullptr;
    float nearestDistance = 0.0f;
    for (ObjectGuid const& guid : targets)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || !IsAttackingCreature(unit, creatureEntry))
            continue;

        float const distance = bot->GetDistance(unit);
        if (!nearest || distance < nearestDistance)
        {
            nearest = unit;
            nearestDistance = distance;
        }
    }

    return nearest;
}

bool IsAttackingCreature(Unit* unit, uint32 creatureEntry)
{
    if (!unit)
        return false;

    Unit* victim = unit->GetVictim();
    return victim && victim->IsCreature() && victim->GetEntry() == creatureEntry;
}

Unit* FindNearbyCaster(PlayerbotAI* botAI, std::initializer_list<uint32> spells, float range)
{
    Player* bot = botAI->GetBot();
    GuidVector const targets =
        botAI->GetAiObjectContext()->GetValue<GuidVector>("possible targets no los")->Get();

    Unit* nearest = nullptr;
    float nearestDistance = range;
    for (ObjectGuid const& guid : targets)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || !unit->HasUnitState(UNIT_STATE_CASTING))
            continue;

        float const distance = bot->GetExactDist2d(unit);
        if (distance >= nearestDistance)
            continue;

        for (uint32 const spellId : spells)
        {
            if (unit->FindCurrentSpellBySpellId(spellId))
            {
                nearest = unit;
                nearestDistance = distance;
                break;
            }
        }
    }

    return nearest;
}

}
