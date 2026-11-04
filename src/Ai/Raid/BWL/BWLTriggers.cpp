/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BWLTriggers.h"
#include "BWLHelpers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SpellAuras.h"

using namespace BlackwingLairHelpers;
using namespace EncounterHelpers;

// General

bool BwlSuppressionDeviceTrigger::IsActive()
{
    // Until MoP, only rogues could disarm suppression devices.
    // If raid cheats are enabled, any bot can disarm the devices.
    if (botAI->HasCheat(BotCheatMask::raid) || bot->IsClass(CLASS_ROGUE))
    {
        GuidVector gos = AI_VALUE(GuidVector, "nearest game objects");
        for (auto i = gos.begin(); i != gos.end(); ++i)
        {
            GameObject const* go = botAI->GetGameObject(*i);
            if (IsActiveSuppressionDeviceInRange(go, bot))
                return true;
        }
    }
    return false;
}

// Razorgore the Untamed

bool BwlRazorgoreNotMindControlledTrigger::IsActive()
{
    if (Unit* boss = AI_VALUE2(Unit*, "find target", "razorgore the untamed"))
        return !boss->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_MINDCONTROL));
    return false;
}

// Vaelastrasz the Corrupt

bool BwlVaelastraszPositioningTrigger::IsActive()
{
    // Prevent non-tanks from rotating the boss while the tanks gain threat.
    if (Unit* boss = AI_VALUE2(Unit*, "find target", "vaelastrasz the corrupt"))
        return boss->GetVictim() != bot;
    return false;
}

bool BwlVaelastraszBurningAdrenalineTrigger::IsActive()
{
    // No check for Vaelastrasz, because bots may still have burning adrenaline even after Vaelastrasz died.
    return bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_BURNING_ADRENALINE));
}

// Broodlord Lashlayer

bool BwlBroodlordRangedTooCloseTrigger::IsActive()
{
    if (!PlayerbotAI::IsRanged(bot))
        return false;

    if (Unit* boss = AI_VALUE2(Unit*, "find target", "broodlord lashlayer"))
    {
        // In case the bot pulled aggro, prevent it from kiting the boss through the room.
        if (boss->GetVictim() != bot)
            return bot->GetDistance2d(boss) < BROODLORD_SAFE_DISTANCE;
    }
    return false;
}

// Firemaw / Ebonroc / Flamegor

bool BwlBlackDrakeNotVictimTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", bossName);
    if (!boss)
        return false;

    // The tank holding the boss stays where it is to avoid rotating the boss.
    return boss->GetVictim() != bot;
}

bool BwlFiremawFlameBuffetTrigger::IsActive()
{
    // Non-tank DPS only; healers have their own placement.
    if (!PlayerbotAI::IsDps(bot) || PlayerbotAI::IsTank(bot) || !HasFlameBuffetHideStacks(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "firemaw");
    return boss && IsSpotInSightOf(boss, bot, bot->GetPosition());
}

bool BwlFiremawHealerPositionTrigger::IsActive()
{
    if (!PlayerbotAI::IsHeal(bot) || PlayerbotAI::IsTank(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "firemaw");
    Unit* tank = boss ? boss->GetVictim() : nullptr;
    if (!tank || tank == bot)
        return false;

    Position const here = bot->GetPosition();
    return IsSpotInSightOf(boss, bot, here) || !IsFiremawHealerSpot(bot, tank, here, botAI->GetRange("heal"));
}

bool BwlEbonrocShadowOnOtherTankTrigger::IsActive()
{
    if (!PlayerbotAI::IsTank(bot))
        return false;

    uint32 const shadow = static_cast<uint32>(BlackwingLairSpells::SPELL_SHADOW_OF_EBONROC);
    if (bot->HasAura(shadow))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", "ebonroc");
    Unit* victim = boss ? boss->GetVictim() : nullptr;
    Aura const* curse = victim && victim != bot ? victim->GetAura(shadow) : nullptr;
    if (!curse)
        return false;

    // One designated taunter: the first uncursed of the main tank and both off-tanks. The next one
    // joins only if Ebonroc is still on the cursed tank after a moment (the guide's backup for a
    // resisted taunt), so the backup taunt isn't spent on every swap.
    uint32 const cursedForMs = curse->GetMaxDuration() - curse->GetDuration();
    uint8 const takers = cursedForMs >= EBONROC_BACKUP_TAUNT_DELAY_MS ? 2 : 1;

    uint8 rank = 0;
    for (Player* tank : { GetGroupMainTank(bot), GetGroupAssistTank(bot, 0), GetGroupAssistTank(bot, 1) })
    {
        if (!tank || tank == victim || tank->HasAura(shadow))
            continue;

        if (tank == bot)
            return true;

        if (++rank >= takers)
            return false;
    }
    return false;
}

// Chromaggus

bool BwlAfflictionBronzeTrigger::IsActive()
{
    return bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_BROOD_AFFLICTION_BRONZE));
}

bool BwlChromaggusOffTankTrigger::IsActive()
{
    // mod-individual-progression restores vanilla Time Lapse, which drops its target's threat for 8s, so
    // Chromaggus turns to the next on his threat list; a tank without Time Lapse takes him back.
    if (!PlayerbotAI::IsTank(bot))
        return false;

    Unit* chromaggus = AI_VALUE2(Unit*, "find target", "chromaggus");
    Unit* victim = chromaggus ? chromaggus->GetVictim() : nullptr;
    Player* victimPlayer = victim ? victim->ToPlayer() : nullptr;
    if (!victimPlayer || PlayerbotAI::IsTank(victimPlayer))
        return false;

    return GetTakeoverTank(bot, nullptr, [](Player const* tank)
        { return !tank->IsAlive() || tank->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_TIME_LAPSE)); }) ==
           bot;
}

// Nefarian

bool BwlNefarianPositioningTrigger::IsActive()
{
    // Prevent non-tanks from rotating the boss while the tanks gain threat.
    if (Unit* boss = AI_VALUE2(Unit*, "find target", "nefarian"))
        return boss->GetVictim() != bot;
    return false;
}

bool BwlNefarianWildMagicTrigger::IsActive()
{
    return bot->getClass() == CLASS_MAGE &&
        bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_WILD_MAGIC));
}

bool BwlNefarianCorruptedHealingTrigger::IsActive()
{
    return bot->IsClass(CLASS_PRIEST) &&
        bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_CORRUPTED_HEALING)) &&
        IsCastingCorruptedHealingSpell(botAI);
}

bool BwlNefarianCorruptedTotemTrigger::IsActive()
{
    return bot->IsInCombat() && IsMechanicTrackerBot(bot, bot->GetMapId()) && GetCorruptedTotemMarkTarget(botAI);
}

// Trash

bool BwlDeathTalonWyrmguardTankTrigger::IsActive()
{
    return PlayerbotAI::IsTank(bot) && AI_VALUE2(Unit*, "find target", "death talon wyrmguard");
}

bool BwlDeathTalonWyrmguardRangedTrigger::IsActive()
{
    return PlayerbotAI::IsRanged(bot) && AI_VALUE2(Unit*, "find target", "death talon wyrmguard");
}
