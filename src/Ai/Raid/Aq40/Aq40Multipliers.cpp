/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq40Multipliers.h"

#include "Aq40Helpers.h"
#include "AttackAction.h"
#include "EncounterHelpers.h"
#include "GenericSpellActions.h"
#include "Playerbots.h"
#include "ReachTargetActions.h"
#include "SpellAuraEffects.h"
#include "SpellMgr.h"

using namespace TempleOfAhnQirajHelpers;

// Ranged stay in casting range on their own; melee would walk straight back into the danger.
static bool IsMeleeReachAction(Player* bot, Action* action)
{
    return !PlayerbotAI::IsRanged(bot) &&
           (dynamic_cast<ReachMeleeAction*>(action) || dynamic_cast<CastReachTargetSpellAction*>(action));
}

float AnubisathSpellReflectMultiplier::GetValue(Action* action)
{
    // Sentinels and Defenders reflect either fire and arcane or shadow and frost back at the caster.
    CastSpellAction* spellAction = dynamic_cast<CastSpellAction*>(action);
    if (!spellAction)
        return 1.0f;

    Unit* target = spellAction->GetTarget();
    if (!target || !target->HasAuraType(SPELL_AURA_REFLECT_SPELLS_SCHOOL))
        return 1.0f;

    uint32 reflectedSchools = 0;
    for (AuraEffect const* effect : target->GetAuraEffectsByType(SPELL_AURA_REFLECT_SPELLS_SCHOOL))
        reflectedSchools |= effect->GetMiscValue();

    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(AI_VALUE2(uint32, "spell id", spellAction->getSpell()));
    if (spellInfo && (spellInfo->GetSchoolMask() & reflectedSchools))
        return 0.0f;

    return 1.0f;
}

float AnubisathDefenderMultiplier::GetValue(Action* action)
{
    if (!IsMeleeReachAction(bot, action))
        return 1.0f;

    // Melee must not walk back into an exploding Defender, and a plagued player stays apart.
    Unit* target = AI_VALUE(Unit*, "current target");
    if (target && target->HasAura(SPELL_DEFENDER_EXPLODE))
        return 0.0f;

    if (!PlayerbotAI::IsTank(bot) && bot->HasAura(SPELL_DEFENDER_PLAGUE))
        return 0.0f;

    return 1.0f;
}

float AnubisathThunderclapMultiplier::GetValue(Action* action)
{
    // Once a ranged bot stands at the edge of Thunderclap, short-range spells must not pull it back in.
    if (!PlayerbotAI::IsRanged(bot) || PlayerbotAI::IsTank(bot) || !dynamic_cast<ReachSpellAction*>(action))
        return 1.0f;

    Unit* target = AI_VALUE(Unit*, "current target");
    if (CanThunderclap(target) && bot->GetDistance2d(target) <= THUNDERCLAP_SAFE_DISTANCE + 2.0f)
        return 0.0f;

    return 1.0f;
}

float KriPoisonCloudMultiplier::GetValue(Action* action)
{
    if (!IsMeleeReachAction(bot, action) || !IsBossInProgress(bot, BOSS_BUG_TRIO))
        return 1.0f;

    // The bug's tank drags it out of the cloud; wait for that instead of following it in.
    Unit* target = AI_VALUE(Unit*, "current target");
    if (target && target->FindNearestCreature(NPC_POISON_CLOUD, POISON_CLOUD_RADIUS))
        return 0.0f;

    return 1.0f;
}

float SarturaWhirlwindMultiplier::GetValue(Action* action)
{
    if (IsMeleeReachAction(bot, action) && IsWhirlwinding(AI_VALUE(Unit*, "current target")))
        return 0.0f;

    return 1.0f;
}

float FankrissMortalWoundMultiplier::GetValue(Action* action)
{
    // A stacked tank must not taunt the boss back off the fresh one.
    if (!EncounterHelpers::IsTauntAction(bot, action) ||
        GetAuraStacks(bot, SPELL_MORTAL_WOUND) < MORTAL_WOUND_SWAP_STACKS)
        return 1.0f;

    if (AI_VALUE2(Unit*, "find target", "fankriss the unyielding"))
        return 0.0f;

    return 1.0f;
}

float HuhuranAcidSpitMultiplier::GetValue(Action* action)
{
    // While shedding threat, nothing that adds threat or restarts auto-attack runs.
    bool const addsThreat =
        dynamic_cast<AttackAction*>(action) || action->getThreatType() != Action::ActionThreatType::None;
    if (addsThreat && ShouldShedHuhuranThreat(botAI))
        return 0.0f;

    return 1.0f;
}

float ViscidusPoisonShockMultiplier::GetValue(Action* action)
{
    if (!IsMeleeReachAction(bot, action) || PlayerbotAI::IsTank(bot))
        return 1.0f;

    Unit* target = AI_VALUE(Unit*, "current target");
    if (target && target->GetEntry() == NPC_VISCIDUS && IsViscidusFreezable(target))
        return 0.0f;

    return 1.0f;
}

float HuhuranWyvernStingMultiplier::GetValue(Action* action)
{
    // Removing Wyvern Sting deals 3000 nature damage, and it is the only curable poison on this fight.
    CurePartyMemberAction* cure = dynamic_cast<CurePartyMemberAction*>(action);
    bool const curesPoison = cure && cure->GetDispelType() == DISPEL_POISON;
    if (!curesPoison && action->getName() != "cleansing totem")
        return 1.0f;

    if (AI_VALUE2(Unit*, "find target", "princess huhuran"))
        return 0.0f;

    return 1.0f;
}
