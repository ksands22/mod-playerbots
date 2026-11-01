/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ZGStrategy.h"
#include "Playerbots.h"
#include "ZGHelpers.h"
#include "ZGMultipliers.h"

using namespace ZulGurubHelpers;

void RaidZulGurubStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Venoxis, Mar'li, Thekal's council, Jin'do: adds and totems die in the guides' order
    triggers.push_back(
        new TriggerNode("zg kill order mark",
                        { NextAction("zg kill order mark", ACTION_RAID) }));
    // Venoxis' cobras and Thekal's tigers: moon on the one the skull reaches last, for the bots' cc
    triggers.push_back(
        new TriggerNode("zg cc mark",
                        { NextAction("zg cc mark", ACTION_RAID) }));

    // Jeklik's and Lor'Khan's Great Heal, Mar'li's Drain Life, Jeklik's Mind Flay
    triggers.push_back(
        new TriggerNode("zg interrupt",
                        { NextAction("zg interrupt", ACTION_RAID) }));

    // High Priestess Jeklik
    triggers.push_back(
        new TriggerNode("zg jeklik spread",
                        { NextAction("zg jeklik spread", ACTION_RAID) }));

    // High Priest Venoxis
    triggers.push_back(
        new TriggerNode("zg venoxis snake form too close",
                        { NextAction("zg venoxis move away", ACTION_RAID) }));

    // High Priest Thekal
    triggers.push_back(
        new TriggerNode("zg thekal tiger",
                        { NextAction("zg thekal attack tiger", ACTION_RAID) }));

    // Bloodlord Mandokir
    triggers.push_back(
        new TriggerNode("zg mandokir gaze",
                        { NextAction("zg mandokir stop attacking", ACTION_RAID + 1) }));
    triggers.push_back(
        new TriggerNode("zg ohgan not tanked",
                        { NextAction("zg ohgan tank", ACTION_RAID) }));

    // Jin'do the Hexxer
    triggers.push_back(
        new TriggerNode("zg jindo shade",
                        { NextAction("zg jindo attack shade", ACTION_RAID) }));

    // Hakkar
    triggers.push_back(
        new TriggerNode("zg hakkar poisonous cloud",
                        { NextAction("zg hakkar stand in cloud", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("zg hakkar son pull",
                        { NextAction("zg hakkar pull son", ACTION_RAID) }));

    // Gahz'ranka
    triggers.push_back(
        new TriggerNode("zg gahzranka not tanked",
                        { NextAction("zg gahzranka tank", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("zg gahzranka not victim",
                        { NextAction("zg gahzranka avoid breath", ACTION_MOVE + 4) }));

    // Edge of Madness: Gri'lek, Wushoolay, Hazza'rah
    triggers.push_back(
        new TriggerNode("zg grilek pursued",
                        { NextAction("zg grilek kite", ACTION_RAID + 1) }));
    triggers.push_back(
        new TriggerNode("zg caster spread",
                        { NextAction("zg caster spread", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("zg hazzarah illusion",
                        { NextAction("zg hazzarah attack illusion", ACTION_RAID) }));
}

void RaidZulGurubStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new VenoxisSnakeFormMultiplier(botAI));
    multipliers.push_back(new MandokirGazeMultiplier(botAI));
    multipliers.push_back(new JindoMultiplier(botAI));
    multipliers.push_back(new HakkarPoisonousBloodMultiplier(botAI));
    multipliers.push_back(new GrilekPursuitMultiplier(botAI));
}

void RaidZulGurubStrategy::AppendTargetExclusions(GuidSet& exclusions, TargetValueExclusionType type)
{
    if (type == TargetValueExclusionType::TankTarget ||
        (type == TargetValueExclusionType::Aoe && PlayerbotAI::IsTank(botAI->GetBot())))
        return;

    // Arlokk's panthers respawn endlessly and Ohgan's death enrages Mandokir: tanks hold them,
    // the rest of the raid leaves them alone.
    AiObjectContext* context = botAI->GetAiObjectContext();
    for (ObjectGuid const guid : AI_VALUE(GuidVector, "attackers"))
    {
        Unit* unit = botAI->GetUnit(guid);
        if (unit && (unit->GetEntry() == NPC_ZULIAN_PROWLER || unit->GetEntry() == NPC_OHGAN))
            exclusions.insert(guid);
    }
}
