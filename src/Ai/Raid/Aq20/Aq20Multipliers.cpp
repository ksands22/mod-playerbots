/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Multipliers.h"
#include "Aq20Helpers.h"
#include "AttackAction.h"
#include "EncounterHelpers.h"
#include "GenericSpellActions.h"
#include "Playerbots.h"
#include "ReachTargetActions.h"

using namespace Aq20Helpers;
using namespace EncounterHelpers;

float KurinnaxxMortalWoundMultiplier::GetValue(Action* action)
{
    // The stacked tank lets the stacks fall off instead of taunting him straight back.
    if (!IsTauntAction(bot, action) || GetAuraStacks(bot, SPELL_MORTAL_WOUND) < KURINNAXX_SWAP_STACKS)
        return 1.0f;

    return AI_VALUE2(Unit*, "find target", "kurinnaxx") ? 0.0f : 1.0f;
}

float AyamissMultiplier::GetValue(Action* action)
{
    if (PlayerbotAI::IsTank(bot))
        return 1.0f;

    Unit* target = nullptr;
    if (dynamic_cast<CastSpellAction*>(action))
        target = action->GetTarget();
    else if (dynamic_cast<AttackAction*>(action))
        target = AI_VALUE(Unit*, "current target");

    if (!target || target != AI_VALUE2(Unit*, "find target", "ayamiss the hunter"))
        return 1.0f;

    // In the air she stings the top-threat ranged player; at 20 stacks it lets someone else take her.
    if (target->IsFlying())
        return GetAuraStacks(bot, SPELL_POISON_STINGER) >= AYAMISS_STINGER_HOLD_STACKS ? 0.0f : 1.0f;

    // Landing resets her threat and she can't be taunted, so DPS wait until a tank has her.
    Unit* victim = target->GetVictim();
    Player* victimPlayer = victim ? victim->ToPlayer() : nullptr;
    return victimPlayer && PlayerbotAI::IsTank(victimPlayer) ? 1.0f : 0.0f;
}

float BuruChasedMultiplier::GetValue(Action* action)
{
    // The chased player keeps leading Buru to the eggs instead of closing back into melee.
    if (!dynamic_cast<ReachMeleeAction*>(action) && !dynamic_cast<MeleeAction*>(action) &&
        !dynamic_cast<CastReachTargetSpellAction*>(action))
        return 1.0f;

    // The chased player is always on his threat list, so the cached lookup finds him.
    Unit* buru = AI_VALUE2(Unit*, "find target", "buru the gorger");
    return IsBuruEggPhase(buru) && buru->GetVictim() == bot ? 0.0f : 1.0f;
}
