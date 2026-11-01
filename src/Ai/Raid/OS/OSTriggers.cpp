/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "OSTriggers.h"
#include "SharedDefines.h"

bool SartharionTankTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "sartharion");
    if (!boss) { return false; }

    return PlayerbotAI::IsTank(bot);
}

bool FlameTsunamiTrigger::IsActive()
{
    if (PlayerbotAI::IsTank(bot)) { return false; }

    Unit* boss = AI_VALUE2(Unit*, "find target", "sartharion");
    if (!boss) { return false; }

    GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");
    for (auto& npc : npcs)
    {
        Unit* unit = botAI->GetUnit(npc);
        if (unit)
        {
            if (unit->GetEntry() == NPC_FLAME_TSUNAMI)
            {
                return true;
            }
        }
    }

    return false;
}

bool TwilightFissureTrigger::IsActive()
{
    // Shadow Fissure comes from the drakes, with or without Sartharion.
    if (!AI_VALUE2(Unit*, "find target", "sartharion") && !AI_VALUE2(Unit*, "find target", "tenebron") &&
        !AI_VALUE2(Unit*, "find target", "shadron") && !AI_VALUE2(Unit*, "find target", "vesperon"))
        return false;

    GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");
    for (auto& npc : npcs)
    {
        Unit* unit = botAI->GetUnit(npc);
        if (unit)
        {
            if (unit->GetEntry() == NPC_TWILIGHT_FISSURE)
            {
                return true;
            }
        }
    }

    return false;
}

bool SartharionDpsTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "sartharion");
    if (!boss) { return false; }

    return PlayerbotAI::IsDps(bot);
}

bool SartharionMeleePositioningTrigger::IsActive()
{
    if (!PlayerbotAI::IsMelee(bot) || !PlayerbotAI::IsDps(bot)) { return false; }

    Unit* boss = AI_VALUE2(Unit*, "find target", "sartharion");
    if (!boss) { return false; }

    Unit* shadron = AI_VALUE2(Unit*, "find target", "shadron");
    Unit* tenebron = AI_VALUE2(Unit*, "find target", "tenebron");
    Unit* vesperon = AI_VALUE2(Unit*, "find target", "vesperon");

    return !(shadron || tenebron || vesperon);
}

bool TwilightPortalEnterTrigger::IsActive()
{
    // Tanks hold Sartharion and the drakes outside, with one healer on them.
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsAssistHealOfIndex(bot, 0) || IsInTwilightRealm(bot))
        return false;

    if (!bot->FindNearestGameObject(GO_TWILIGHT_PORTAL, 100.0f))
        return false;

    // Fought alone, Shadron is immune while his Disciple lives, and Vesperon's Twilight Torment hurts
    // whoever attacks while his Disciple or Acolyte lives; guides go in and kill them. Tenebron's
    // portal is ignored: his whelps are killed outside.
    constexpr float DRAKE_SEARCH_DISTANCE = 150.0f;
    Creature* shadron = bot->FindNearestCreature(NPC_SHADRON, DRAKE_SEARCH_DISTANCE);
    Creature* vesperon = bot->FindNearestCreature(NPC_VESPERON, DRAKE_SEARCH_DISTANCE);
    if ((shadron && shadron->HasAura(SPELL_GIFT_OF_TWILIGHT_SHADOW)) ||
        (vesperon && vesperon->HasAura(SPELL_TWILIGHT_TORMENT_VESPERON)) ||
        bot->HasAura(SPELL_TWILIGHT_TORMENT_VESPERON) || bot->HasAura(SPELL_TWILIGHT_TORMENT_SARTHARION))
        return true;

    // In 25-man, take two healers in. Otherwise just take one
    // if (bot->GetRaidDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL)
    // {
    //     if (PlayerbotAI::IsAssistHealOfIndex(bot, 0) || PlayerbotAI::IsAssistHealOfIndex(bot, 1))
    //     {
    //         return false;
    //     }
    // }
    // else
    // {
    //     if (PlayerbotAI::IsAssistHealOfIndex(bot, 0))
    //     {
    //         return false;
    //     }
    // }

    // Don't enter portal until drakes are dead
    if (bot->HasAura(SPELL_POWER_OF_SHADRON) ||
        bot->HasAura(SPELL_POWER_OF_TENEBRON) ||
        bot->HasAura(SPELL_POWER_OF_VESPERON))
    {
        return false;
    }

    Unit* boss = AI_VALUE2(Unit*, "find target", "sartharion");
    if (!boss) { return false; }

    // With drakes up, Shadron's Acolyte shields Sartharion; this is the leftover Acolyte.
    return boss->HasAura(SPELL_GIFT_OF_TWILIGHT_FIRE);
}

bool TwilightPortalExitTrigger::IsActive()
{
    // Leave once the Acolytes and Disciples inside are dead.
    return IsInTwilightRealm(bot) && !GetTwilightSummon(bot);
}

bool DrakeMeleePositioningTrigger::IsActive()
{
    // A drake fought on its own breathes in front: melee stand behind it.
    if (!PlayerbotAI::IsMelee(bot) || PlayerbotAI::IsTank(bot) || AI_VALUE2(Unit*, "find target", "sartharion"))
        return false;

    Unit* target = AI_VALUE(Unit*, "current target");
    return target &&
           (target->GetEntry() == NPC_TENEBRON || target->GetEntry() == NPC_SHADRON ||
            target->GetEntry() == NPC_VESPERON) &&
           target->GetVictim() != bot;
}

bool LavaBlazeTrigger::IsActive()
{
    // Sartharion's Lava Blazes go to the off-tank.
    return PlayerbotAI::IsAssistTankOfIndex(bot, 0, true) && GetUntankedLavaBlaze(botAI);
}

bool IsInTwilightRealm(Player const* bot)
{
    return bot->HasAura(SPELL_TWILIGHT_SHIFT_PHASE) || bot->HasAura(SPELL_TWILIGHT_SHIFT);
}

Unit* GetTwilightSummon(Player* bot)
{
    constexpr float REALM_SEARCH_DISTANCE = 100.0f;
    for (uint32 entry : { NPC_ACOLYTE_OF_SHADRON, NPC_ACOLYTE_OF_VESPERON, NPC_DISCIPLE_OF_SHADRON,
                          NPC_DISCIPLE_OF_VESPERON })
        if (Creature* summon = bot->FindNearestCreature(entry, REALM_SEARCH_DISTANCE))
            return summon;
    return nullptr;
}

Unit* GetUntankedLavaBlaze(PlayerbotAI* botAI)
{
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("nearest hostile npcs")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || unit->GetEntry() != NPC_LAVA_BLAZE)
            continue;

        Unit* victim = unit->GetVictim();
        Player* victimPlayer = victim ? victim->ToPlayer() : nullptr;
        if (!victimPlayer || !PlayerbotAI::IsTank(victimPlayer))
            return unit;
    }
    return nullptr;
}
