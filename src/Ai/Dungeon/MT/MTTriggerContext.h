/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MTTRIGGERCONTEXT_H
#define PLAYERBOTS_MTTRIGGERCONTEXT_H

#include "MTTriggers.h"
#include "NamedObjectContext.h"

class TbcDungeonManaTombsTriggerContext : public NamedObjectContext<Trigger>
{
public:
    TbcDungeonManaTombsTriggerContext()
    {
        // Pandemonius
        creators["pandemonius dark shell"] = &TbcDungeonManaTombsTriggerContext::pandemonius_dark_shell;

        // Nexus-Prince Shaffar
        creators["shaffar is active"] = &TbcDungeonManaTombsTriggerContext::shaffar_is_active;
    }

private:
    static Trigger* pandemonius_dark_shell(PlayerbotAI* botAI) { return new PandemoniusDarkShellTrigger(botAI); }
    static Trigger* shaffar_is_active(PlayerbotAI* botAI) { return new ShaffarIsActiveTrigger(botAI); }
};

#endif
