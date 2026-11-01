/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Strategy.h"
#include "Aq20Multipliers.h"
#include "Strategy.h"

void RaidAq20Strategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Rajaxx's captains, Moam's Mana Fiends, and Buru's egg while he stands beside it
    triggers.push_back(
        new TriggerNode("aq20 kill order mark",
            { NextAction("aq20 kill order mark", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("aq20 cc mark",
            { NextAction("aq20 cc mark", ACTION_RAID) }));

    // Kurinnaxx
    triggers.push_back(
        new TriggerNode("aq20 kurinnaxx tank swap",
            { NextAction("aq20 kurinnaxx taunt", ACTION_RAID) }));

    // Moam
    triggers.push_back(
        new TriggerNode("aq20 moam drain mana",
            { NextAction("aq20 moam drain mana", ACTION_RAID) }));

    // Buru the Gorger
    triggers.push_back(
        new TriggerNode("aq20 buru chased",
            { NextAction("aq20 buru kite to egg", ACTION_RAID + 1) }));

    // Ayamiss the Hunter
    triggers.push_back(
        new TriggerNode("aq20 ayamiss larva",
            { NextAction("aq20 ayamiss attack larva", ACTION_RAID) }));

    // Ossirian the Unscarred
    triggers.push_back(
        new TriggerNode("aq20 move to crystal",
            { NextAction("aq20 use crystal", ACTION_RAID) }));
}

void RaidAq20Strategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new KurinnaxxMortalWoundMultiplier(botAI));
    multipliers.push_back(new AyamissMultiplier(botAI));
    multipliers.push_back(new BuruChasedMultiplier(botAI));
}
