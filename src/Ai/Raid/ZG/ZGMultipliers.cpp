/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ZGMultipliers.h"
#include "AttackAction.h"
#include "GenericSpellActions.h"
#include "Playerbots.h"
#include "ReachTargetActions.h"
#include "ZGActions.h"
#include "ZGHelpers.h"

using namespace ZulGurubHelpers;

float VenoxisSnakeFormMultiplier::GetValue(Action* action)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "high priest venoxis");
    if (!IsVenoxisSnakeForm(boss) || boss->GetVictim() == bot)
        return 1.0f;

    // Everyone but his target stays out of melee range in snake form.
    if (dynamic_cast<ReachMeleeAction*>(action) || dynamic_cast<MeleeAction*>(action) ||
        dynamic_cast<CastReachTargetSpellAction*>(action))
        return 0.0f;

    return 1.0f;
}

float MandokirGazeMultiplier::GetValue(Action* action)
{
    if (!bot->HasAura(SPELL_THREATENING_GAZE))
        return 1.0f;

    if (dynamic_cast<CastSpellAction*>(action) || dynamic_cast<AttackAction*>(action))
        return 0.0f;

    return 1.0f;
}

float JindoMultiplier::GetValue(Action* action)
{
    if (auto* spellAction = dynamic_cast<CastSpellAction*>(action))
    {
        // Delusions of Jin'do is what lets a player hit the Shades, so it must stay on.
        if (IsCurseRemovalSpell(spellAction->getSpell()))
        {
            Unit* target = action->GetTarget();
            if (target && target->HasAura(SPELL_DELUSIONS_OF_JINDO))
                return 0.0f;
        }
        return 1.0f;
    }

    // A cursed bot already on a Shade stays on it instead of following the raid's target.
    if (dynamic_cast<AttackAction*>(action) && !dynamic_cast<MeleeAction*>(action) &&
        bot->HasAura(SPELL_DELUSIONS_OF_JINDO))
    {
        Unit* victim = bot->GetVictim();
        if (victim && victim->GetEntry() == NPC_SHADE_OF_JINDO && victim->IsAlive())
            return 0.0f;
    }

    return 1.0f;
}

float HakkarPoisonousBloodMultiplier::GetValue(Action* action)
{
    auto* spellAction = dynamic_cast<CastSpellAction*>(action);
    if (!spellAction)
        return 1.0f;

    std::string const spell = spellAction->getSpell();

    // Poisonous Blood turns Blood Siphon against Hakkar, so nobody cures it.
    if (IsPoisonCureSpell(spell))
    {
        Unit* target = action->GetTarget();
        if (target && target->HasAura(SPELL_POISONOUS_BLOOD))
            return 0.0f;
    }
    else if (spell == "cleansing totem" && AI_VALUE2(Unit*, "find target", "hakkar"))
        return 0.0f;

    return 1.0f;
}

float GrilekPursuitMultiplier::GetValue(Action* action)
{
    // The chased player keeps running instead of closing back into melee for his 5000+ hits.
    if (!dynamic_cast<ReachMeleeAction*>(action) && !dynamic_cast<MeleeAction*>(action) &&
        !dynamic_cast<CastReachTargetSpellAction*>(action))
        return 1.0f;

    Unit* boss = AI_VALUE2(Unit*, "find target", "gri'lek");
    if (boss && boss->HasAura(SPELL_GRILEK_AVATAR) && boss->GetVictim() == bot)
        return 0.0f;

    return 1.0f;
}
