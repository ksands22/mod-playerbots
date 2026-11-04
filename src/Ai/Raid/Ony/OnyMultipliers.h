/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ONYMULTIPLIERS_H
#define PLAYERBOTS_ONYMULTIPLIERS_H

#include "Multiplier.h"

// Phase 3: shamans keep Tremor Totem down instead of their other earth totems.
class OnyxiaKeepTremorTotemMultiplier : public Multiplier
{
public:
    OnyxiaKeepTremorTotemMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "ony keep tremor totem") {}
    float GetValue(Action* action) override;
};

#endif
