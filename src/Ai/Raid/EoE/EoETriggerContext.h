/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_EOETRIGGERCONTEXT_H
#define PLAYERBOTS_EOETRIGGERCONTEXT_H

#include "EoETriggers.h"
#include "NamedObjectContext.h"

class RaidEoETriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidEoETriggerContext()
    {
        creators["malygos"] = &RaidEoETriggerContext::malygos;
        creators["power spark"] = &RaidEoETriggerContext::power_spark;
        creators["malygos power spark near boss"] = &RaidEoETriggerContext::malygos_power_spark_near_boss;
        creators["malygos outside arcane overload"] = &RaidEoETriggerContext::malygos_outside_arcane_overload;
        creators["malygos static field"] = &RaidEoETriggerContext::malygos_static_field;
    }

private:
    static Trigger* power_spark(PlayerbotAI* botAI) { return new PowerSparkTrigger(botAI); }
    static Trigger* malygos(PlayerbotAI* botAI) { return new MalygosTrigger(botAI); }
    static Trigger* malygos_power_spark_near_boss(PlayerbotAI* botAI)
    {
        return new MalygosPowerSparkNearBossTrigger(botAI);
    }
    static Trigger* malygos_outside_arcane_overload(PlayerbotAI* botAI)
    {
        return new MalygosOutsideArcaneOverloadTrigger(botAI);
    }
    static Trigger* malygos_static_field(PlayerbotAI* botAI) { return new MalygosStaticFieldTrigger(botAI); }
};

#endif
