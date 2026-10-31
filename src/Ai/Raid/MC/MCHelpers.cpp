/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "MCHelpers.h"
#include "AiObjectContext.h"
#include "Group.h"
#include "Map.h"
#include "Playerbots.h"
#include "RtiTargetValue.h"
#include "Spell.h"
#include "SpellInfo.h"

namespace MoltenCoreHelpers
{
// Healers mend everything else, so they die first; bosses come after their adds.
static uint8 GetKillPriority(uint32 entry)
{
    switch (entry)
    {
        case NPC_FLAMEWAKER_HEALER:
            return 3;
        case NPC_FLAMEWAKER_PROTECTOR:
        case NPC_FLAMEWAKER:
        case NPC_FLAMEWAKER_PRIEST:
        case NPC_FLAMEWAKER_ELITE:
        case NPC_SON_OF_FLAME:
            return 2;
        case NPC_LUCIFRON:
        case NPC_GEHENNAS:
        case NPC_SULFURON_HARBINGER:
        case NPC_RAGNAROS:
            return 1;
        default:
            return 0;
    }
}

Unit* GetKillOrderMarkTarget(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    Group* group = bot->GetGroup();
    if (!group)
        return nullptr;

    Unit* best = nullptr;
    uint8 bestPriority = 0;
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("attackers")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || !bot->IsValidAttackTarget(unit))
            continue;

        uint8 const priority = GetKillPriority(unit->GetEntry());
        if (!priority)
            continue;

        if (priority > bestPriority || (priority == bestPriority && unit->GetHealthPct() < best->GetHealthPct()))
        {
            best = unit;
            bestPriority = priority;
        }
    }

    if (!best)
        return nullptr;

    // Keep a skull that is still in the top tier, so the raid doesn't split as add health values cross.
    Unit* skull = botAI->GetUnit(group->GetTargetIcon(RtiTargetValue::skullIndex));
    if (skull && skull->IsAlive() && GetKillPriority(skull->GetEntry()) >= bestPriority)
        return nullptr;

    return best;
}

Unit* GetDarkMendingCaster(PlayerbotAI* botAI)
{
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("attackers")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || unit->GetEntry() != NPC_FLAMEWAKER_PRIEST)
            continue;

        Spell* spell = unit->GetCurrentSpell(CURRENT_GENERIC_SPELL);
        if (spell && spell->m_spellInfo->Id == SPELL_DARK_MENDING)
            return unit;
    }
    return nullptr;
}

bool IsReflectingAttacksFrom(Unit* target, Player* bot)
{
    if (PlayerbotAI::IsCaster(bot))
        return target->HasAura(SPELL_MAGIC_REFLECTION);

    if (PlayerbotAI::IsMelee(bot))
        return target->HasAura(SPELL_DAMAGE_REFLECTION);

    return false;
}

Unit* GetReflectedAttackTarget(Player* bot)
{
    if (PlayerbotAI::IsCaster(bot))
    {
        for (CurrentSpellTypes type : { CURRENT_GENERIC_SPELL, CURRENT_CHANNELED_SPELL, CURRENT_AUTOREPEAT_SPELL })
        {
            Spell* spell = bot->GetCurrentSpell(type);
            if (!spell || spell->m_spellInfo->IsPositive())
                continue;

            Unit* target = spell->m_targets.GetUnitTarget();
            if (target && target != bot && IsReflectingAttacksFrom(target, bot))
                return target;
        }
        return nullptr;
    }

    Unit* victim = bot->GetVictim();
    if (victim && IsReflectingAttacksFrom(victim, bot))
        return victim;

    return nullptr;
}

bool IsRagnarosEmerged(Unit* ragnaros)
{
    return ragnaros && ragnaros->IsAlive() && !ragnaros->HasUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
}

bool IsMagmaAt(Player* bot, float x, float y, float z)
{
    LiquidData const liquid =
        bot->GetMap()->GetLiquidData(bot->GetPhaseMask(), x, y, z, bot->GetCollisionHeight(), MAP_ALL_LIQUIDS);
    return (liquid.Flags & MAP_LIQUID_TYPE_MAGMA) &&
           (liquid.Status & (LIQUID_MAP_WATER_WALK | LIQUID_MAP_IN_WATER | LIQUID_MAP_UNDER_WATER));
}
}
