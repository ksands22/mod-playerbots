/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "OnyTriggers.h"
#include "EncounterHelpers.h"
#include "GenericTriggers.h"
#include "NearestNpcsValue.h"
#include "ObjectAccessor.h"
#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "SpellMgr.h"

using namespace OnyxiaHelpers;

namespace OnyxiaHelpers
{
bool IsOnyxianWhelp(Unit const* unit)
{
    return unit && (unit->GetEntry() == NPC_ONYXIAN_WHELP || unit->GetEntry() == NPC_ONYXIAN_WHELP_40);
}

bool IsOnyxiaPhase3(Unit* onyxia)
{
    constexpr float PHASE_3_HEALTH_PCT = 40.0f;
    return onyxia && onyxia->IsInCombat() && !onyxia->IsFlying() && onyxia->GetHealthPct() <= PHASE_3_HEALTH_PCT;
}

bool IsCastingDifficultySpell(Unit* caster, uint32 baseSpellId)
{
    if (!caster)
        return false;

    uint32 const difficultyId = sSpellMgr->GetSpellIdForDifficulty(baseSpellId, caster);
    for (CurrentSpellTypes const type : { CURRENT_GENERIC_SPELL, CURRENT_CHANNELED_SPELL })
    {
        Spell* spell = caster->GetCurrentSpell(type);
        if (spell && (spell->m_spellInfo->Id == baseSpellId || spell->m_spellInfo->Id == difficultyId))
            return true;
    }
    return false;
}

Unit* GetOnyxianWhelp(PlayerbotAI* botAI)
{
    for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("possible targets")->Get())
    {
        Unit* unit = botAI->GetUnit(guid);
        if (unit && unit->IsAlive() && IsOnyxianWhelp(unit))
            return unit;
    }
    return nullptr;
}
}

OnyxiaDeepBreathTrigger::OnyxiaDeepBreathTrigger(PlayerbotAI* botAI) : Trigger(botAI, "ony deep breath warning") {}

bool OnyxiaDeepBreathTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "onyxia");
    if (!boss || !boss->HasUnitState(UNIT_STATE_CASTING))
        return false;

    // Check if Onyxia is casting
    Spell* currentSpell = boss->GetCurrentSpell(CURRENT_GENERIC_SPELL);

    if (!currentSpell || !currentSpell->m_spellInfo)
        return false;

    uint32 spellId = currentSpell->m_spellInfo->Id;

    if (spellId == 17086 ||  // North to South
        spellId == 18351 ||  // South to North
        spellId == 18576 ||  // East to West
        spellId == 18609 ||  // West to East
        spellId == 18564 ||  // Southeast to Northwest
        spellId == 18584 ||  // Northwest to Southeast
        spellId == 18596 ||  // Southwest to Northeast
        spellId == 18617     // Northeast to Southwest
    )
    {
        return true;
    }

    return false;
}

OnyxiaNearTailTrigger::OnyxiaNearTailTrigger(PlayerbotAI* botAI) : Trigger(botAI, "ony near tail") {}

bool OnyxiaNearTailTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "onyxia");
    if (!boss || PlayerbotAI::IsTank(bot))
        return false;

    // Skip if Onyxia is in air or transitioning
    if (!boss->IsInCombat() || boss->IsFlying() || !boss->GetVictim())
        return false;

    return true;
}
RaidOnyxiaFireballSplashTrigger::RaidOnyxiaFireballSplashTrigger(PlayerbotAI* botAI)
    : Trigger(botAI, "ony fireball splash incoming")
{
}

bool RaidOnyxiaFireballSplashTrigger::IsActive()
{
    // Fireball's 25-player and vanilla-raid versions are swapped in by difficulty.
    Unit* boss = AI_VALUE2(Unit*, "find target", "onyxia");
    if (!IsCastingDifficultySpell(boss, SPELL_FIREBALL))
        return false;

    GuidVector nearbyUnits = AI_VALUE(GuidVector, "nearest friendly players");

    for (ObjectGuid guid : nearbyUnits)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || unit == bot || !unit->IsAlive())
            continue;

        if (bot->GetDistance(unit) < 8.0f)
            return true;
    }

    return false;
}

RaidOnyxiaWhelpsSpawnTrigger::RaidOnyxiaWhelpsSpawnTrigger(PlayerbotAI* botAI) : Trigger(botAI, "ony whelps spawn") {}

bool RaidOnyxiaWhelpsSpawnTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "onyxia");
    if (!boss || PlayerbotAI::IsHeal(bot))
        return false;

    // Phase 2: dps and tanks take the whelps while she flies.
    if (boss->IsFlying())
        return true;

    // Phase 3: guides keep the dps on Onyxia; the off-tanks pick up the whelps that keep coming.
    return IsOnyxiaPhase3(boss) && PlayerbotAI::IsAssistTank(bot) && GetOnyxianWhelp(botAI);
}

OnyxiaAvoidEggsTrigger::OnyxiaAvoidEggsTrigger(PlayerbotAI* botAI) : Trigger(botAI, "ony avoid eggs") {}

bool OnyxiaAvoidEggsTrigger::IsActive()
{
    Position botPos = Position(bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ());

    if (botPos.GetExactDist2d(-35.0f, -165.0f) <= 5.0f)
        return true;

    if (botPos.GetExactDist2d(-35.0f, -260.0f) <= 5.0f)
        return true;

    return false;
}

// Phase 3: guides put Fear Ward on the tank and Tremor Totem down against Bellowing Roar, and warriors
// break it with Berserker Rage.

OnyxiaPhase3TremorTotemTrigger::OnyxiaPhase3TremorTotemTrigger(PlayerbotAI* botAI)
    : Trigger(botAI, "ony phase 3 tremor totem")
{
}

bool OnyxiaPhase3TremorTotemTrigger::IsActive()
{
    if (bot->getClass() != CLASS_SHAMAN || AI_VALUE2(bool, "has totem", "tremor totem"))
        return false;

    return IsOnyxiaPhase3(AI_VALUE2(Unit*, "find target", "onyxia"));
}

OnyxiaMainTankNeedsFearWardTrigger::OnyxiaMainTankNeedsFearWardTrigger(PlayerbotAI* botAI)
    : Trigger(botAI, "ony main tank needs fear ward")
{
}

bool OnyxiaMainTankNeedsFearWardTrigger::IsActive()
{
    if (bot->getClass() != CLASS_PRIEST || !IsOnyxiaPhase3(AI_VALUE2(Unit*, "find target", "onyxia")))
        return false;

    Player* mainTank = EncounterHelpers::GetGroupMainTank(bot);
    return mainTank && mainTank->IsAlive() && !mainTank->HasAura(SPELL_FEAR_WARD) &&
           botAI->CanCastSpell(SPELL_FEAR_WARD, mainTank);
}

OnyxiaBellowingRoarTrigger::OnyxiaBellowingRoarTrigger(PlayerbotAI* botAI) : Trigger(botAI, "ony bellowing roar") {}

bool OnyxiaBellowingRoarTrigger::IsActive()
{
    if (bot->getClass() != CLASS_WARRIOR)
        return false;

    return IsCastingDifficultySpell(AI_VALUE2(Unit*, "find target", "onyxia"), SPELL_BELLOWING_ROAR) &&
           botAI->CanCastSpell("berserker rage", bot);
}
