/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "EoEStrategy.h"
#include "EoEMultipliers.h"
#include "Strategy.h"

void RaidEoEStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("malygos",
        { NextAction("malygos position", ACTION_MOVE) }));
    triggers.push_back(new TriggerNode("malygos",
        { NextAction("malygos target", ACTION_RAID + 1) }));
    triggers.push_back(new TriggerNode("malygos power spark near boss",
        { NextAction("malygos kill power spark", ACTION_RAID + 2) }));
    triggers.push_back(new TriggerNode("malygos static field",
        { NextAction("malygos avoid static field", ACTION_MOVE + 6) }));
    triggers.push_back(new TriggerNode("malygos outside arcane overload",
        { NextAction("malygos move into arcane overload", ACTION_MOVE + 5) }));

    triggers.push_back(new TriggerNode("group flying",
        { NextAction("eoe fly drake", ACTION_NORMAL + 1) }));
    triggers.push_back(new TriggerNode("drake combat",
        { NextAction("eoe drake attack", ACTION_NORMAL + 5) }));
}

void RaidEoEStrategy::InitMultipliers(std::vector<Multiplier*> &multipliers)
{
    multipliers.push_back(new MalygosMultiplier(botAI));
}
