/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ARCTRIGGERS_H
#define PLAYERBOTS_ARCTRIGGERS_H

#include "Trigger.h"

// Dalliah the Doomsayer

class DalliahWhirlwindTrigger : public Trigger
{
public:
    DalliahWhirlwindTrigger(PlayerbotAI* botAI) : Trigger(botAI, "dalliah whirlwind") {}

    bool IsActive() override;
};

#endif
