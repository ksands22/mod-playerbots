/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_DUNGEONMULTIPLIERS_H
#define PLAYERBOTS_DUNGEONMULTIPLIERS_H

#include "Multiplier.h"
#include <utility>
#include <vector>

// Casters hold spells on their current target while it has one of these spell-reflect auras
class ReflectingTargetMultiplier : public Multiplier
{
public:
    ReflectingTargetMultiplier(PlayerbotAI* botAI, std::string const name, std::vector<uint32> reflectSpells)
        : Multiplier(botAI, name), _reflectSpells(std::move(reflectSpells))
    {
    }

    float GetValue(Action* action) override;

private:
    std::vector<uint32> _reflectSpells;
};

#endif
