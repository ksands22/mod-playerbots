/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Actions.h"
#include "Aq20Helpers.h"
#include "Aq20Utils.h"
#include "EncounterHelpers.h"
#include <cmath>

using namespace Aq20Helpers;
using namespace EncounterHelpers;

bool Aq20UseCrystalAction::Execute(Event /*event*/)
{
    if (Unit* boss = AI_VALUE2(Unit*, "find target", "ossirian the unscarred"))
    {
        if (GameObject* crystal = RaidAq20Utils::GetNearestCrystal(boss))
        {
            float botDist = bot->GetDistance(crystal);
            if (botDist > INTERACTION_DISTANCE)
                return MoveTo(bot->GetMapId(),
                    crystal->GetPositionX() + frand(-3.5f, 3.5f),
                    crystal->GetPositionY() + frand(-3.5f, 3.5f),
                    crystal->GetPositionZ());

            // if we're already in range just wait here until it's time to activate crystal
            SetNextMovementDelay(500);

            // don't activate crystal if boss too far or its already been activated
            if (boss->GetDistance(crystal) > 25.0f ||
                crystal->HasGameObjectFlag(GO_FLAG_IN_USE))
                return false;

            // don't activate crystal if boss doesn't have buff yet AND isn't going to have it soon
            // (though ideally bot should activate it ~5 seconds early due to time it takes for
            // crystal to activate and remove buff)
            if (!RaidAq20Utils::IsOssirianBuffActive(boss) &&
                RaidAq20Utils::GetOssirianDebuffTimeRemaining(boss) > 5000)
                return false;

            // this makes crystal do its animation (then disappear after)
            WorldPacket data1(CMSG_GAMEOBJ_USE);
            data1 << crystal->GetGUID();
            bot->GetSession()->HandleGameObjectUseOpcode(data1);

            // this makes crystal actually remove the buff and put on debuff (took a while to figure that out)
            WorldPacket data2(CMSG_GAMEOBJ_USE);
            data2 << crystal->GetGUID();
            bot->GetSession()->HandleGameobjectReportUse(data2);

            return true;
        }
    }
    return false;
}

bool Aq20KillOrderMarkAction::Execute(Event /*event*/)
{
    return MarkTargetWithSkull(bot, GetKillOrderMarkTarget(botAI));
}

bool Aq20CcMarkAction::Execute(Event /*event*/)
{
    return MarkTargetWithMoon(bot, GetCcMarkTarget(botAI));
}

bool Aq20KurinnaxxTauntAction::Execute(Event event)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "kurinnaxx");
    if (!boss)
        return false;

    if (bot->GetVictim() != boss)
        return Attack(boss);

    return botAI->DoSpecificAction("taunt spell", event, true);
}

bool Aq20MoamDrainManaAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "moam");
    if (!boss)
        return false;

    // Each class's own mana drain from the guides: Drain Mana, Mana Burn, Viper Sting.
    char const* spell = nullptr;
    switch (bot->getClass())
    {
        case CLASS_WARLOCK:
            spell = "drain mana";
            break;
        case CLASS_PRIEST:
            spell = "mana burn";
            break;
        case CLASS_HUNTER:
            spell = "viper sting";
            break;
        default:
            return false;
    }

    return botAI->CanCastSpell(spell, boss) && botAI->CastSpell(spell, boss);
}

bool Aq20AyamissAttackLarvaAction::Execute(Event /*event*/)
{
    Unit* larva = GetNearestNpc(botAI, NPC_HIVEZARA_LARVA, AQ20_ADD_SEARCH_DISTANCE);
    return larva && Attack(larva);
}

bool Aq20BuruKiteToEggAction::Execute(Event /*event*/)
{
    Unit* buru = GetNearestNpc(botAI, NPC_BURU, AQ20_ADD_SEARCH_DISTANCE);
    Unit* egg = GetNearestNpc(botAI, NPC_BURU_EGG, AQ20_ADD_SEARCH_DISTANCE);
    if (!buru || !egg)
        return false;

    // Stand on the far side of the egg so Buru's path runs over it; the raid breaks it as he passes.
    float const eggToBuruX = egg->GetPositionX() - buru->GetPositionX();
    float const eggToBuruY = egg->GetPositionY() - buru->GetPositionY();
    float const length = std::hypot(eggToBuruX, eggToBuruY);
    if (length < 0.1f)
        return false;

    float const x = egg->GetPositionX() + eggToBuruX / length * BURU_KITE_BEYOND_EGG;
    float const y = egg->GetPositionY() + eggToBuruY / length * BURU_KITE_BEYOND_EGG;
    constexpr float ARRIVAL_DISTANCE = 2.0f;
    if (bot->GetExactDist2d(x, y) <= ARRIVAL_DISTANCE)
        return false;

    return MoveTo(bot->GetMapId(), x, y, egg->GetPositionZ(), false, false, false, false,
                  MovementPriority::MOVEMENT_COMBAT, true, false);
}
