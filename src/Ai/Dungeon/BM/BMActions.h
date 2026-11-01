/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BMACTIONS_H
#define PLAYERBOTS_BMACTIONS_H

#include "AttackAction.h"

// Opening of the Dark Portal (Medivh)

class BlackMorassAttackRiftMobAction : public AttackAction
{
public:
    BlackMorassAttackRiftMobAction(PlayerbotAI* botAI) : AttackAction(botAI, "black morass attack rift mob") {}

    bool Execute(Event event) override;
};

#endif
