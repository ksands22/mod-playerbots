/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SMTRIGGERCONTEXT_H
#define PLAYERBOTS_SMTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "SMTriggers.h"

class VanillaDungeonScarletMonasteryTriggerContext : public NamedObjectContext<Trigger>
{
public:
    VanillaDungeonScarletMonasteryTriggerContext()
    {
        // Arcanist Doan
        creators["doan detonation"] = &VanillaDungeonScarletMonasteryTriggerContext::doan_detonation;

        // Herod
        creators["herod whirlwind"] = &VanillaDungeonScarletMonasteryTriggerContext::herod_whirlwind;

        // High Inquisitor Whitemane
        creators["whitemane is active"] = &VanillaDungeonScarletMonasteryTriggerContext::whitemane_is_active;
    }

private:
    static Trigger* doan_detonation(PlayerbotAI* botAI) { return new DoanDetonationTrigger(botAI); }
    static Trigger* herod_whirlwind(PlayerbotAI* botAI) { return new HerodWhirlwindTrigger(botAI); }
    static Trigger* whitemane_is_active(PlayerbotAI* botAI) { return new WhitemaneIsActiveTrigger(botAI); }
};

#endif
