/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_DMACTIONCONTEXT_H
#define PLAYERBOTS_DMACTIONCONTEXT_H

#include "DMActions.h"
#include "NamedObjectContext.h"

class VanillaDungeonDireMaulActionContext : public NamedObjectContext<Action>
{
public:
    VanillaDungeonDireMaulActionContext()
    {
        // Immol'thar
        creators["immolthar mark eye"] = &VanillaDungeonDireMaulActionContext::immolthar_mark_eye;

        // Prince Tortheldrin
        creators["tortheldrin avoid whirlwind"] = &VanillaDungeonDireMaulActionContext::tortheldrin_avoid_whirlwind;
    }

private:
    static Action* immolthar_mark_eye(PlayerbotAI* botAI) { return new ImmoltharMarkEyeAction(botAI); }
    static Action* tortheldrin_avoid_whirlwind(PlayerbotAI* botAI)
    {
        return new TortheldrinAvoidWhirlwindAction(botAI);
    }
};

#endif
