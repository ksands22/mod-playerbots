/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "KaraTriggers.h"
#include "EncounterHelpers.h"
#include "KaraActions.h"
#include "KaraHelpers.h"
#include "Pet.h"
#include "Playerbots.h"

using namespace KaraHelpers;
using namespace EncounterHelpers;

// Shared

bool KarazhanBotIsNotInCombatTrigger::IsActive()
{
    return bot->GetMapId() == KARA_MAP_ID && !AI_VALUE2(bool, "combat", "self target");
}

bool KarazhanEnemiesCastFearTrigger::IsActive()
{
    if (bot->getClass() != CLASS_SHAMAN)
        return false;

    if (AI_VALUE2(bool, "has totem", "tremor totem"))
        return false;

    Unit* nightbane = AI_VALUE2(Unit*, "find target", "nightbane");
    if (nightbane && nightbane->GetPositionZ() <= NIGHTBANE_FLIGHT_Z)
        return true;

    return AI_VALUE2(Unit*, "find target", "spectral charger") ||
        AI_VALUE2(Unit*, "find target", "the big bad wolf") ||
        AI_VALUE2(Unit*, "find target", "roar");
}

// Trash

bool ManaWarpIsAboutToExplodeTrigger::IsActive()
{
    if (bot->getClass() == CLASS_DEATH_KNIGHT || bot->getClass() == CLASS_HUNTER ||
        bot->getClass() == CLASS_MAGE || bot->getClass() == CLASS_PRIEST)
    {
        return false;
    }

    return AI_VALUE2(Unit*, "find target", "mana warp");
}

// Attumen the Huntsman

// Midnight is still present as a separate (invisible) unit after Attumen mounts.
// A Midnight threat list check will capture the entire encounter.
bool AttumenTheHuntsmanPhaseOneActiveTrigger::IsActive()
{
    return AI_VALUE2(Unit*, "find target", "midnight") && !GetAttumenMounted(bot);
}

bool AttumenTheHuntsmanPhaseTwoActiveTrigger::IsActive()
{
    return AI_VALUE2(Unit*, "find target", "midnight") && GetAttumenMounted(bot);
}

bool AttumenTheHuntsmanPhaseTransitionTrigger::IsActive()
{
    if (!IsMechanicTrackerBot(bot, KARA_MAP_ID))
        return false;

    if (!AI_VALUE2(Unit*, "find target", "midnight"))
        return false;

    return GetAttumenMounted(bot);
}

// Moroes

bool MoroesShouldPrioritizeAddsTrigger::IsActive()
{
    return IsMechanicTrackerBot(bot, KARA_MAP_ID) && AI_VALUE2(Unit*, "find target", "moroes");
}

bool MoroesGougedTheTankTrigger::IsActive()
{
    // Guides keep a second tank ready to take Moroes while Gouge incapacitates his tank.
    if (!PlayerbotAI::IsTank(bot))
        return false;

    Unit* moroes = AI_VALUE2(Unit*, "find target", "moroes");
    Unit* victim = moroes ? moroes->GetVictim() : nullptr;
    Player* victimPlayer = victim ? victim->ToPlayer() : nullptr;
    if (!victimPlayer || PlayerbotAI::IsTank(victimPlayer))
        return false;

    return GetTakeoverTank(bot, nullptr, [](Player const* tank)
        { return !tank->IsAlive() || tank->HasAura(Id(KaraSpells::SPELL_GOUGE)); }) == bot;
}

// Maiden of Virtue

bool MaidenOfVirtueBossEngagedByTanksTrigger::IsActive()
{
    return PlayerbotAI::IsTank(bot) && AI_VALUE2(Unit*, "find target", "maiden of virtue");
}

bool MaidenOfVirtueGroundingTotemConsumesHolyFireTrigger::IsActive()
{
    if (bot->getClass() != CLASS_SHAMAN)
        return false;

    if (!AI_VALUE2(Unit*, "find target", "maiden of virtue"))
        return false;

    return !AI_VALUE2(bool, "has totem", "grounding totem");
}

bool MaidenOfVirtueHolyWrathDealsChainDamageTrigger::IsActive()
{
    return PlayerbotAI::IsRanged(bot) && AI_VALUE2(Unit*, "find target", "maiden of virtue");
}

// The Big Bad Wolf

bool BigBadWolfBossEngagedByTankTrigger::IsActive()
{
    if (!PlayerbotAI::IsTank(bot))
        return false;

    if (!AI_VALUE2(Unit*, "find target", "the big bad wolf"))
        return false;

    return !bot->HasAura(Id(KaraSpells::SPELL_LITTLE_RED_RIDING_HOOD));
}

bool BigBadWolfBossIsChasingLittleRedRidingHoodTrigger::IsActive()
{
    return bot->HasAura(Id(KaraSpells::SPELL_LITTLE_RED_RIDING_HOOD));
}

// Romulo and Julianne

bool RomuloAndJulianneBothBossesRevivedTrigger::IsActive()
{
    if (!IsMechanicTrackerBot(bot, KARA_MAP_ID))
        return false;

    return AI_VALUE2(Unit*, "find target", "romulo") && AI_VALUE2(Unit*, "find target", "julianne");
}

bool JulianneCastsEternalAffectionTrigger::IsActive()
{
    // Guides interrupt Eternal Affection, her heal on herself or Romulo.
    switch (bot->getClass())
    {
        case CLASS_WARRIOR:
        case CLASS_ROGUE:
        case CLASS_SHAMAN:
        case CLASS_MAGE:
        case CLASS_HUNTER:
            break;
        default:
            return false;
    }

    Unit* julianne = AI_VALUE2(Unit*, "find target", "julianne");
    return julianne && julianne->FindCurrentSpellBySpellId(Id(KaraSpells::SPELL_ETERNAL_AFFECTION));
}

// The Wizard of Oz

bool WizardOfOzNeedTargetPriorityTrigger::IsActive()
{
    if (!IsMechanicTrackerBot(bot, KARA_MAP_ID))
        return false;

    for (char const* name : OZ_TARGETS)
    {
        if (AI_VALUE2(Unit*, "find target", name))
            return true;
    }

    return false;
}

bool WizardOfOzStrawmanIsVulnerableToFireTrigger::IsActive()
{
    return bot->getClass() == CLASS_MAGE && AI_VALUE2(Unit*, "find target", "strawman");
}

bool WizardOfOzCycloneIsNearbyTrigger::IsActive()
{
    // The Crone's cyclones wander and knock back whoever they touch.
    if (!AI_VALUE2(Unit*, "find target", "the crone"))
        return false;

    // Read from the spell data; the fallback and margin are ours, the margin for their wandering.
    constexpr float fallbackRadius = 5.0f;
    constexpr float margin = 3.0f;
    float const safeDistance =
        GetSpellRadiusOrFallback(Id(KaraSpells::SPELL_CYCLONE_KNOCKBACK), fallbackRadius) + margin;
    return GetNearestNpcOfEntry(botAI, Id(KaraNpcs::NPC_CYCLONE), safeDistance) != nullptr;
}

// The Curator

bool TheCuratorAstralFlareSpawnedTrigger::IsActive()
{
    return IsMechanicTrackerBot(bot, KARA_MAP_ID) &&
        AI_VALUE2(Unit*, "find target", "astral flare");
}

bool TheCuratorBossEngagedByTanksTrigger::IsActive()
{
    return PlayerbotAI::IsTank(bot) && AI_VALUE2(Unit*, "find target", "the curator");
}

bool TheCuratorBossEngagedByRangedTrigger::IsActive()
{
    return PlayerbotAI::IsRanged(bot) && AI_VALUE2(Unit*, "find target", "the curator");
}

// Terestian Illhoof

bool TerestianIllhoofShouldPrioritizeChainsTrigger::IsActive()
{
    return IsMechanicTrackerBot(bot, KARA_MAP_ID) &&
        AI_VALUE2(Unit*, "find target", "terestian illhoof");
}

// Shade of Aran

bool ShadeOfAranArcaneExplosionIsCastingTrigger::IsActive()
{
    Unit* aran = AI_VALUE2(Unit*, "find target", "shade of aran");
    return aran && IsAranCastingArcaneExplosion(aran) && !IsFlameWreathActive(bot);
}

bool ShadeOfAranFlameWreathIsActiveTrigger::IsActive()
{
    return AI_VALUE2(Unit*, "find target", "shade of aran") && IsFlameWreathActive(bot);
}

bool ShadeOfAranConjuredElementalsSummonedTrigger::IsActive()
{
    return IsMechanicTrackerBot(bot, KARA_MAP_ID) &&
        AI_VALUE2(Unit*, "find target", "conjured elemental");
}

bool ShadeOfAranBossCastsCounterspellNearbyTrigger::IsActive()
{
    if (!PlayerbotAI::IsRanged(bot))
        return false;

    Unit* aran = AI_VALUE2(Unit*, "find target", "shade of aran");
    if (!aran)
        return false;

    if (bot->HasAura(Id(KaraSpells::SPELL_BLIZZARD)))
        return false;

    return !IsAranCastingArcaneExplosion(aran) && !IsFlameWreathActive(bot);
}

bool ShadeOfAranBlizzardIsNearbyTrigger::IsActive()
{
    // Guides move out of Aran's Blizzard as it circles the room; never through a Flame Wreath.
    if (!AI_VALUE2(Unit*, "find target", "shade of aran") || IsFlameWreathActive(bot))
        return false;

    // Read from the spell data; the fallback and margin are ours.
    constexpr float fallbackRadius = 8.0f;
    constexpr float margin = 2.0f;
    float const safeDistance = GetSpellRadiusOrFallback(Id(KaraSpells::SPELL_BLIZZARD), fallbackRadius) + margin;
    return GetNearestNpcOfEntry(botAI, Id(KaraNpcs::NPC_ARAN_BLIZZARD), safeDistance) != nullptr;
}

bool ShadeOfAranIsDrinkingTrigger::IsActive()
{
    // Guides leave Aran's drink alone until the raid is back to full health after Mass Polymorph.
    constexpr float healthyPct = 90.0f;
    Unit* aran = AI_VALUE2(Unit*, "find target", "shade of aran");
    if (!aran || !IsAranDrinking(aran) || IsGroupHealthy(bot, healthyPct))
        return false;

    Pet* pet = bot->GetPet();
    return bot->GetVictim() == aran || (pet && pet->GetVictim() == aran);
}

// Netherspite

bool NetherspiteRedBeamIsActiveTrigger::IsActive()
{
    Unit* netherspite = AI_VALUE2(Unit*, "find target", "netherspite");
    if (!netherspite || IsBanishPhase(netherspite))
        return false;

    constexpr float searchRadius = 150.0f;
    return bot->FindNearestCreature(Id(KaraNpcs::NPC_RED_PORTAL), searchRadius);
}

bool NetherspiteBlueBeamIsActiveTrigger::IsActive()
{
    Unit* netherspite = AI_VALUE2(Unit*, "find target", "netherspite");
    if (!netherspite || IsBanishPhase(netherspite))
        return false;

    constexpr float searchRadius = 150.0f;
    return bot->FindNearestCreature(Id(KaraNpcs::NPC_BLUE_PORTAL), searchRadius);
}

bool NetherspiteGreenBeamIsActiveTrigger::IsActive()
{
    Unit* netherspite = AI_VALUE2(Unit*, "find target", "netherspite");
    if (!netherspite || IsBanishPhase(netherspite))
        return false;

    constexpr float searchRadius = 150.0f;
    return bot->FindNearestCreature(Id(KaraNpcs::NPC_GREEN_PORTAL), searchRadius);
}

bool NetherspiteBotIsNotBeamBlockerTrigger::IsActive()
{
    Unit* netherspite = AI_VALUE2(Unit*, "find target", "netherspite");
    if (!netherspite || IsBanishPhase(netherspite))
        return false;

    auto [redBlocker, greenBlocker, blueBlocker] = GetCurrentBeamBlockers(bot);
    return bot != redBlocker && bot != blueBlocker && bot != greenBlocker;
}

bool NetherspiteBossIsBanishedTrigger::IsActive()
{
    Unit* netherspite = AI_VALUE2(Unit*, "find target", "netherspite");
    return netherspite && IsBanishPhase(netherspite);
}

bool NetherspiteShouldManageTimersAndTrackersTrigger::IsActive()
{
    return AI_VALUE2(Unit*, "find target", "netherspite");
}

// Prince Malchezaar

bool PrinceMalchezaarBotIsEnfeebledTrigger::IsActive()
{
    return bot->HasAura(Id(KaraSpells::SPELL_ENFEEBLE));
}

bool PrinceMalchezaarEngagedByNonTanksTrigger::IsActive()
{
    Unit* malchezaar = AI_VALUE2(Unit*, "find target", "prince malchezaar");
    if (!malchezaar)
        return false;

    if (bot->HasAura(Id(KaraSpells::SPELL_ENFEEBLE)))
        return false;

    if ((PlayerbotAI::IsTank(bot) && malchezaar->GetVictim() == bot) ||
        PlayerbotAI::IsMainTank(bot))
    {
        return false;
    }

    return true;
}

bool PrinceMalchezaarBossEngagedByTanksTrigger::IsActive()
{
    Unit* malchezaar = AI_VALUE2(Unit*, "find target", "prince malchezaar");
    if (!malchezaar)
        return false;

    return (PlayerbotAI::IsTank(bot) && malchezaar->GetVictim() == bot) ||
        PlayerbotAI::IsMainTank(bot);
}

// Nightbane

bool NightbaneBossEngagedByTanksTrigger::IsActive()
{
    if (!PlayerbotAI::IsTank(bot))
        return false;

    Unit* nightbane = AI_VALUE2(Unit*, "find target", "nightbane");
    return nightbane && nightbane->GetPositionZ() <= NIGHTBANE_FLIGHT_Z;
}

bool NightbaneGroundPhaseEngagedByRangedTrigger::IsActive()
{
    if (!PlayerbotAI::IsRanged(bot))
        return false;

    Unit* nightbane = AI_VALUE2(Unit*, "find target", "nightbane");
    return nightbane && nightbane->GetPositionZ() <= NIGHTBANE_FLIGHT_Z;
}

bool NightbanePetsIgnoreCollisionToChaseFlyingBossTrigger::IsActive()
{
    if (bot->getClass() != CLASS_HUNTER && bot->getClass() != CLASS_WARLOCK)
        return false;

    if (!AI_VALUE2(Unit*, "find target", "nightbane"))
        return false;

    Pet* pet = bot->GetPet();
    return pet && pet->IsAlive();
}

bool NightbaneBossIsFlyingTrigger::IsActive()
{
    Unit* nightbane = AI_VALUE2(Unit*, "find target", "nightbane");
    if (!nightbane || nightbane->GetPositionZ() <= NIGHTBANE_FLIGHT_Z)
        return false;

    uint32 const instanceId = nightbane->GetMap()->GetInstanceId();
    time_t const now = std::time(nullptr);
    constexpr uint8 flightPhaseDurationSeconds = 35;
    // After 35s, Nightbane goes to land, and bots freely follow their master
    if (nightbaneFlightPhaseStartTimer.find(instanceId) == nightbaneFlightPhaseStartTimer.end())
        return false;

    return now - nightbaneFlightPhaseStartTimer[instanceId] < flightPhaseDurationSeconds;
}

bool NightbaneBotWentOutOfBoundsTrigger::IsActive()
{
    if (!AI_VALUE2(Unit*, "find target", "nightbane"))
        return false;

    constexpr float outOfBoundsLeeway = 5.0f;
    return bot->GetPositionZ() < NIGHTBANE_GROUND_Z - outOfBoundsLeeway;
}

bool NightbaneShouldManageTimersAndTrackersTrigger::IsActive()
{
    return AI_VALUE2(Unit*, "find target", "nightbane");
}
