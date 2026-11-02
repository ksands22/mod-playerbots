/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SMStrategy.h"
#include "SMMultipliers.h"

void VanillaDungeonScarletMonasteryStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Arcanist Doan
    triggers.push_back(new TriggerNode("doan detonation",
                                       {NextAction("doan avoid detonation", ACTION_EMERGENCY + 1)}));

    // Herod
    triggers.push_back(new TriggerNode("herod whirlwind",
                                       {NextAction("herod avoid whirlwind", ACTION_EMERGENCY + 1)}));

    // High Inquisitor Whitemane
    triggers.push_back(new TriggerNode("whitemane is active",
                                       {NextAction("whitemane mark boss", ACTION_RAID)}));
}

void VanillaDungeonScarletMonasteryStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new DoanDetonationMultiplier(botAI));

    multipliers.push_back(new HerodWhirlwindMultiplier(botAI));
}
