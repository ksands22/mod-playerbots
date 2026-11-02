/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BWLMultipliers.h"
#include "BWLActions.h"
#include "BWLHelpers.h"
#include "ChooseTargetActions.h"
#include "EncounterHelpers.h"
#include "GenericSpellActions.h"
#include "HunterActions.h"
#include "Playerbots.h"
#include "ReachTargetActions.h"

using namespace BlackwingLairHelpers;
using namespace EncounterHelpers;

static constexpr float VAELASTRASZ_BA_SAFE_DISTANCE = 20.0f;
static constexpr float VAELASTRASZ_BA_BOSS_DISTANCE = 30.0f;

float RazorgoreTankMultiplier::GetValue(Action* action)
{
    if (!PlayerbotAI::IsTank(bot))
        return 1.0f;

    Unit* boss = AI_VALUE2(Unit*, "find target", "razorgore the untamed");
    if (!boss)
        return 1.0f;

    if (AreRazorgoreEggsAlive(botAI))
    {
        // Off-tank picks up boss, blocks TankAssistAction to avoid changing targets
        if (IsRazorgoreOffTank(bot) && bot->GetVictim() != nullptr && dynamic_cast<TankAssistAction*>(action))
            return 0.0f;
        return 1.0f;
    }

    // All eggs destroyed. Tanks not targeted by the boss don't run into the Cleave.
    if (boss->GetVictim() != bot && dynamic_cast<TankFaceAction*>(action))
        return 0.0f;
    return 1.0f;
}

float VaelastraszTankMultiplier::GetValue(Action* action)
{
    if (!PlayerbotAI::IsTank(bot))
        return 1.0f;

    Unit* boss = AI_VALUE2(Unit*, "find target", "vaelastrasz the corrupt");
    if (!boss)
        return 1.0f;

    // Stay at rear flank position and don't move in front of the boss.
    if (dynamic_cast<TankFaceAction*>(action))
    {
        Unit* victim = boss->GetVictim();
        Player* victimPlayer = victim ? victim->ToPlayer() : nullptr;
        if (victim != bot && victimPlayer && PlayerbotAI::IsTank(victimPlayer))
            return 0.0f;
    }

    return 1.0f;
}

float VaelastraszBurningAdrenalineMultiplier::GetValue(Action* action)
{
    if (bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_BURNING_ADRENALINE)))
    {
        if (dynamic_cast<MovementAction*>(action))
        {
            if (dynamic_cast<BwlVaelastraszMoveAwayAction*>(action))
            {
                // Allow movement when boss is dead or bot was knocked away
                Unit* boss = AI_VALUE2(Unit*, "find target", "vaelastrasz the corrupt");
                if (!boss || !boss->IsAlive() || bot->GetDistance2d(boss) > VAELASTRASZ_BA_BOSS_DISTANCE)
                    return 1.0f;
            }

            // Block ALL other movement once bot is far enough from non-BA bots
            if (!IsNonBABotNearPosition(bot, bot->GetPosition(), VAELASTRASZ_BA_SAFE_DISTANCE) ||
                !dynamic_cast<BwlVaelastraszMoveAwayAction*>(action))
                return 0.0f;
        }
        // Also block charge actions
        if (dynamic_cast<CastReachTargetSpellAction*>(action))
            return 0.0f;
    }

    return 1.0f;
}

float FiremawFlameBuffetMultiplier::GetValue(Action* action)
{
    if (!PlayerbotAI::IsDps(bot) || PlayerbotAI::IsTank(bot) || !HasFlameBuffetHideStacks(bot))
        return 1.0f;

    if (!AI_VALUE2(Unit*, "find target", "firemaw"))
        return 1.0f;

    // A hidden bot holds its spot until the whole stack expires, instead of walking back into sight.
    if (dynamic_cast<MovementAction*>(action) && !dynamic_cast<BwlFiremawHideFromFlameBuffetAction*>(action) &&
        !dynamic_cast<AvoidAoeAction*>(action))
        return 0.0f;

    if (dynamic_cast<CastReachTargetSpellAction*>(action))
        return 0.0f;

    return 1.0f;
}

float FiremawHealerPositionMultiplier::GetValue(Action* action)
{
    if (!PlayerbotAI::IsHeal(bot) || PlayerbotAI::IsTank(bot) || !dynamic_cast<ReachPartyMemberToHealAction*>(action))
        return 1.0f;

    // A hidden healer heals whoever it can reach from cover rather than walking back into Firemaw's sight.
    Unit* boss = AI_VALUE2(Unit*, "find target", "firemaw");
    if (boss && !IsSpotInSightOf(boss, bot, bot->GetPosition()))
        return 0.0f;

    return 1.0f;
}

float EbonrocShadowTankMultiplier::GetValue(Action* action)
{
    // Ebonroc heals each time he hits the tank wearing his Shadow, so that tank must not taunt him back.
    if (!bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_SHADOW_OF_EBONROC)))
        return 1.0f;

    if (IsTauntAction(bot, action) && AI_VALUE2(Unit*, "find target", "ebonroc"))
        return 0.0f;

    return 1.0f;
}

float NefarianCorruptedHealingMultiplier::GetValue(Action* action)
{
    if (!bot->IsClass(CLASS_PRIEST) ||
        !bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_CORRUPTED_HEALING)))
        return 1.0f;

    CastSpellAction* spellAction = dynamic_cast<CastSpellAction*>(action);
    if (spellAction && IsCorruptedHealingSpell(spellAction->getSpell()))
        return 0.0f;

    return 1.0f;
}
