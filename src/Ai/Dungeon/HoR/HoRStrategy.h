/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_HORSTRATEGY_H
#define PLAYERBOTS_HORSTRATEGY_H

#include "Strategy.h"

class WotlkDungeonHallsOfReflectionStrategy : public Strategy
{
public:
    WotlkDungeonHallsOfReflectionStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}

    std::string const getName() override { return "wotlk-hor"; }

    void InitTriggers(std::vector<TriggerNode*>& triggers) override;
};

#endif
