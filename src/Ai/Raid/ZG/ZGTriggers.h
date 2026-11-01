/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGTRIGGERS_H
#define PLAYERBOTS_ZGTRIGGERS_H

#include "Trigger.h"

class ZgKillOrderMarkTrigger : public Trigger
{
public:
    ZgKillOrderMarkTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg kill order mark") {}
    bool IsActive() override;
};

class ZgCcMarkTrigger : public Trigger
{
public:
    ZgCcMarkTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg cc mark") {}
    bool IsActive() override;
};

class ZgInterruptTrigger : public Trigger
{
public:
    ZgInterruptTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg interrupt") {}
    bool IsActive() override;
};

// Checked every 2s: finding the nearest raid member walks the whole group.
class ZgJeklikSpreadTrigger : public Trigger
{
public:
    ZgJeklikSpreadTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg jeklik spread", 2) {}
    bool IsActive() override;
};

class ZgVenoxisSnakeFormTooCloseTrigger : public Trigger
{
public:
    ZgVenoxisSnakeFormTooCloseTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg venoxis snake form too close") {}
    bool IsActive() override;
};

class ZgThekalTigerTrigger : public Trigger
{
public:
    ZgThekalTigerTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg thekal tiger") {}
    bool IsActive() override;
};

class ZgMandokirGazeTrigger : public Trigger
{
public:
    ZgMandokirGazeTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg mandokir gaze") {}
    bool IsActive() override;
};

class ZgOhganNotTankedTrigger : public Trigger
{
public:
    ZgOhganNotTankedTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg ohgan not tanked") {}
    bool IsActive() override;
};

class ZgJindoShadeTrigger : public Trigger
{
public:
    ZgJindoShadeTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg jindo shade") {}
    bool IsActive() override;
};

class ZgHakkarPoisonousCloudTrigger : public Trigger
{
public:
    ZgHakkarPoisonousCloudTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg hakkar poisonous cloud") {}
    bool IsActive() override;
};

class ZgGahzrankaNotTankedTrigger : public Trigger
{
public:
    ZgGahzrankaNotTankedTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg gahzranka not tanked") {}
    bool IsActive() override;
};

class ZgGahzrankaNotVictimTrigger : public Trigger
{
public:
    ZgGahzrankaNotVictimTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg gahzranka not victim") {}
    bool IsActive() override;
};

class ZgGrilekPursuedTrigger : public Trigger
{
public:
    ZgGrilekPursuedTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg grilek pursued") {}
    bool IsActive() override;
};

// Checked every 2s: finding the nearest raid member walks the whole group.
class ZgCasterSpreadTrigger : public Trigger
{
public:
    ZgCasterSpreadTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg caster spread", 2) {}
    bool IsActive() override;
};

class ZgHazzarahIllusionTrigger : public Trigger
{
public:
    ZgHazzarahIllusionTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg hazzarah illusion") {}
    bool IsActive() override;
};

// The first assist tank times Blood Siphon from the moment it sees Hakkar engage. A tank that joins
// mid-fight (late arrival, battle rez) starts its clock late and pulls off-schedule.
class ZgHakkarSonPullTrigger : public Trigger
{
public:
    ZgHakkarSonPullTrigger(PlayerbotAI* botAI) : Trigger(botAI, "zg hakkar son pull") {}
    bool IsActive() override;

private:
    uint32 _engagedMs = 0;
    uint32 _lastSeenMs = 0;
};

#endif
