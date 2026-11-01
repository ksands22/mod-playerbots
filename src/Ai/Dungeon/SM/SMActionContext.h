/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SMACTIONCONTEXT_H
#define PLAYERBOTS_SMACTIONCONTEXT_H

#include "NamedObjectContext.h"
#include "SMActions.h"

class VanillaDungeonScarletMonasteryActionContext : public NamedObjectContext<Action>
{
public:
    VanillaDungeonScarletMonasteryActionContext()
    {
        // Arcanist Doan
        creators["doan avoid detonation"] = &VanillaDungeonScarletMonasteryActionContext::doan_avoid_detonation;

        // Herod
        creators["herod avoid whirlwind"] = &VanillaDungeonScarletMonasteryActionContext::herod_avoid_whirlwind;

        // High Inquisitor Whitemane
        creators["whitemane mark boss"] = &VanillaDungeonScarletMonasteryActionContext::whitemane_mark_boss;
    }

private:
    static Action* doan_avoid_detonation(PlayerbotAI* botAI) { return new DoanAvoidDetonationAction(botAI); }
    static Action* herod_avoid_whirlwind(PlayerbotAI* botAI) { return new HerodAvoidWhirlwindAction(botAI); }
    static Action* whitemane_mark_boss(PlayerbotAI* botAI) { return new WhitemaneMarkBossAction(botAI); }
};

#endif
