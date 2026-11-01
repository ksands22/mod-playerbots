/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Helpers.h"
#include "AiObjectContext.h"
#include "Group.h"
#include "Playerbots.h"
#include "RtiTargetValue.h"
#include "SpellAuras.h"

namespace Aq20Helpers
{
// Guide order: each wave's captain before its adds, then Rajaxx; Mana Fiends one at a time.
static uint8 GetKillPriority(uint32 entry)
{
    switch (entry)
    {
        case NPC_CAPTAIN_QEEZ:
        case NPC_CAPTAIN_TUUBID:
        case NPC_CAPTAIN_DRENN:
        case NPC_CAPTAIN_XURREM:
        case NPC_MAJOR_YEGGETH:
        case NPC_MAJOR_PAKKON:
        case NPC_COLONEL_ZERRAN:
        case NPC_MANA_FIEND:
            return 2;
        case NPC_RAJAXX:
            return 1;
        default:
            return 0;
    }
}

// The egg to break while Buru is beside it: a raid kill is what makes it hurt him.
static Unit* GetBuruEggToKill(PlayerbotAI* botAI)
{
    // By entry, not "find target": Buru wipes his threat list every time he picks a new player.
    Unit* buru = GetNearestNpc(botAI, NPC_BURU, AQ20_ADD_SEARCH_DISTANCE);
    if (!IsBuruEggPhase(buru))
        return nullptr;

    Unit* nearest = nullptr;
    float nearestDistance = BURU_EGG_KILL_DISTANCE;
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("nearest npcs")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || unit->GetEntry() != NPC_BURU_EGG)
            continue;

        float const distance = buru->GetExactDist2d(unit);
        if (distance < nearestDistance)
        {
            nearest = unit;
            nearestDistance = distance;
        }
    }
    return nearest;
}

Unit* GetKillOrderMarkTarget(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    Group* group = bot->GetGroup();
    if (!group)
        return nullptr;

    Unit* skull = botAI->GetUnit(group->GetTargetIcon(RtiTargetValue::skullIndex));

    if (Unit* egg = GetBuruEggToKill(botAI))
        return skull == egg ? nullptr : egg;

    Unit* best = nullptr;
    uint8 bestPriority = 0;
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("possible targets")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || !bot->IsValidAttackTarget(unit))
            continue;

        uint8 const priority = GetKillPriority(unit->GetEntry());
        if (!priority || !unit->IsInCombat())
            continue;

        if (priority > bestPriority || (priority == bestPriority && unit->GetHealthPct() < best->GetHealthPct()))
        {
            best = unit;
            bestPriority = priority;
        }
    }

    if (!best)
        return nullptr;

    // Keep a skull that is still in the top tier, so the raid doesn't split as health values cross.
    if (skull && skull->IsAlive() && GetKillPriority(skull->GetEntry()) >= bestPriority)
        return nullptr;

    return best;
}

Unit* GetCcMarkTarget(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    Group* group = bot->GetGroup();
    if (!group)
        return nullptr;

    ObjectGuid const skullGuid = group->GetTargetIcon(RtiTargetValue::skullIndex);
    Unit* moon = botAI->GetUnit(group->GetTargetIcon(RtiTargetValue::moonIndex));
    if (moon && moon->IsAlive() && moon->GetGUID() != skullGuid)
        return nullptr;

    // Guides banish two of the three Fiends. Moon goes on the healthiest, the one the skull reaches
    // last; the bots' own cc picks up another.
    Unit* best = nullptr;
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("attackers")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || unit->GetGUID() == skullGuid || unit->GetEntry() != NPC_MANA_FIEND)
            continue;

        if (!best || unit->GetHealthPct() > best->GetHealthPct())
            best = unit;
    }
    return best;
}

Unit* GetNearestNpc(PlayerbotAI* botAI, uint32 entry, float maxDistance)
{
    Player* bot = botAI->GetBot();
    Unit* nearest = nullptr;
    float nearestDistance = maxDistance;
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("nearest npcs")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || unit->GetEntry() != entry)
            continue;

        float const distance = bot->GetExactDist2d(unit);
        if (distance < nearestDistance)
        {
            nearest = unit;
            nearestDistance = distance;
        }
    }
    return nearest;
}

bool IsMoamStoned(Unit const* moam)
{
    return moam && moam->HasAura(SPELL_MOAM_ENERGIZE);
}

bool IsBuruEggPhase(Unit const* buru)
{
    return buru && buru->IsAlive() && buru->HasAura(SPELL_BURU_THORNS);
}

uint32 GetAuraStacks(Unit const* unit, uint32 spellId)
{
    Aura const* aura = unit ? unit->GetAura(spellId) : nullptr;
    return aura ? aura->GetStackAmount() : 0;
}
}
