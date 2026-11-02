/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ZGActions.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "ZGHelpers.h"
#include <array>

using namespace EncounterHelpers;
using namespace ZulGurubHelpers;

static constexpr std::array<char const*, 7> INTERRUPT_SPELLS = {
    "kick", "pummel", "shield bash", "wind shear", "counterspell", "mind freeze", "silencing shot"};

bool ZgKillOrderMarkAction::Execute(Event /*event*/)
{
    return MarkTargetWithSkull(bot, GetKillOrderMarkTarget(botAI));
}

bool ZgInterruptAction::Execute(Event /*event*/)
{
    Unit* caster = GetInterruptTarget(botAI);
    if (!caster)
        return false;

    for (char const* name : INTERRUPT_SPELLS)
    {
        uint32 const spellId = AI_VALUE2(uint32, "spell id", name);
        SpellInfo const* spellInfo = spellId ? sSpellMgr->GetSpellInfo(spellId) : nullptr;
        if (!spellInfo || !bot->IsWithinCombatRange(caster, spellInfo->GetMaxRange(false)))
            continue;

        if (botAI->CanCastSpell(name, caster) && botAI->CastSpell(name, caster))
            return true;
    }
    return false;
}

bool ZgJeklikSpreadAction::Execute(Event /*event*/)
{
    return MoveFromGroup(JEKLIK_SPREAD_DISTANCE);
}

bool ZgVenoxisMoveAwayAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "high priest venoxis");
    if (!boss)
        return false;

    float const distToTravel = VENOXIS_SNAKE_SAFE_DISTANCE - bot->GetDistance2d(boss);
    if (distToTravel <= 0.0f)
        return false;

    return MoveAway(boss, distToTravel);
}

bool ZgThekalAttackTigerAction::Execute(Event /*event*/)
{
    // Lowest health first, so melee finish one tiger before starting the next.
    Unit* tiger = nullptr;
    for (ObjectGuid const guid : AI_VALUE(GuidVector, "attackers"))
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || unit->GetEntry() != NPC_ZULIAN_TIGER)
            continue;

        if (!tiger || unit->GetHealthPct() < tiger->GetHealthPct())
            tiger = unit;
    }

    return tiger && Attack(tiger);
}

bool ZgMandokirStopAttackingAction::Execute(Event /*event*/)
{
    bot->AttackStop();
    bot->CastStop();
    return true;
}

bool ZgTankUnitAction::Execute(Event event)
{
    Unit* unit = AI_VALUE2(Unit*, "find target", _unitName);
    if (!unit)
        return false;

    if (bot->GetVictim() != unit)
        return Attack(unit);

    return botAI->DoSpecificAction("taunt spell", event, true);
}

bool ZgGahzrankaAvoidBreathAction::isUseful()
{
    Unit const* boss = GetTarget();
    return boss && boss->HasInArc(2.0f * minAngle, bot);
}

bool ZgGrilekKiteAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "gri'lek");
    if (!boss)
        return false;

    float const distToTravel = GRILEK_KITE_DISTANCE - bot->GetDistance2d(boss);
    if (distToTravel <= 0.0f)
        return false;

    return MoveAway(boss, distToTravel);
}

bool ZgCasterSpreadAction::Execute(Event /*event*/)
{
    return MoveFromGroup(CASTER_SPREAD_DISTANCE);
}

bool ZgHazzarahAttackIllusionAction::Execute(Event /*event*/)
{
    Unit* illusion = GetNearestNpc(botAI, NPC_NIGHTMARE_ILLUSION, botAI->GetRange("spell"));
    return illusion && Attack(illusion);
}

bool ZgJindoAttackShadeAction::Execute(Event /*event*/)
{
    Unit* shade = GetNearestNpc(botAI, NPC_SHADE_OF_JINDO, sPlayerbotAIConfig.SightDistance);
    return shade && Attack(shade);
}

bool ZgHakkarStandInCloudAction::Execute(Event /*event*/)
{
    Unit* cloud = GetNearestNpc(botAI, NPC_POISONOUS_CLOUD, POISONOUS_CLOUD_SEARCH_DISTANCE);
    if (!cloud || bot->GetExactDist2d(cloud) <= POISONOUS_CLOUD_STAND_DISTANCE)
        return false;

    return MoveTo(cloud->GetMapId(), cloud->GetPositionX(), cloud->GetPositionY(), cloud->GetPositionZ(), false,
                  false, false, false, MovementPriority::MOVEMENT_COMBAT, true, false);
}

bool ZgCcMarkAction::Execute(Event /*event*/)
{
    return MarkTargetWithMoon(bot, GetCcMarkTarget(botAI));
}

bool ZgHakkarPullSonAction::Execute(Event event)
{
    Unit* pulled = nullptr;
    Unit* idle = nullptr;
    float idleDistance = HAKKAR_SON_SEARCH_DISTANCE;
    for (ObjectGuid const guid : AI_VALUE(GuidVector, "nearest npcs"))
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit || !unit->IsAlive() || unit->GetEntry() != NPC_SON_OF_HAKKAR)
            continue;

        if (unit->IsInCombat())
        {
            pulled = unit;
            break;
        }

        float const distance = bot->GetExactDist2d(unit);
        if (distance < idleDistance)
        {
            idle = unit;
            idleDistance = distance;
        }
    }

    if (!pulled)
        return idle && Attack(idle);

    if (pulled->GetVictim() != bot)
    {
        if (bot->GetVictim() != pulled)
            return Attack(pulled);
        return botAI->DoSpecificAction("taunt spell", event, true);
    }

    // Walk it back to the raid so its Poisonous Cloud lands where the raid can stand in it.
    Player* mainTank = GetGroupMainTank(bot);
    if (!mainTank || mainTank == bot || bot->GetExactDist2d(mainTank) <= HAKKAR_SON_RETURN_DISTANCE)
        return false;

    return MoveTo(mainTank->GetMapId(), mainTank->GetPositionX(), mainTank->GetPositionY(),
                  mainTank->GetPositionZ(), false, false, false, false, MovementPriority::MOVEMENT_COMBAT, true,
                  false);
}
