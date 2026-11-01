/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ULDAMANSTRATEGY_H
#define PLAYERBOTS_ULDAMANSTRATEGY_H

#include "Strategy.h"

class VanillaDungeonUldamanStrategy : public Strategy
{
public:
    VanillaDungeonUldamanStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    std::string const getName() override { return "vanilla-uldaman"; }

    void InitMultipliers(std::vector<Multiplier*>& multipliers) override;
};

#endif
