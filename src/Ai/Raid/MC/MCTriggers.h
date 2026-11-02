/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MCTRIGGERS_H
#define PLAYERBOTS_MCTRIGGERS_H

#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "Trigger.h"

class McLivingBombDebuffTrigger : public Trigger
{
public:
    McLivingBombDebuffTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc living bomb debuff") {}
    bool IsActive() override;
};

class McBaronGeddonInfernoTrigger : public Trigger
{
public:
    McBaronGeddonInfernoTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc baron geddon inferno") {}
    bool IsActive() override;
};

class McShazzrahRangedTrigger : public Trigger
{
public:
    McShazzrahRangedTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc shazzrah ranged") {}
    bool IsActive() override;
};

class McGolemaggMarkBossTrigger : public Trigger
{
public:
    McGolemaggMarkBossTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc golemagg mark boss") {}
    bool IsActive() override;
};

class McGolemaggIsMainTankTrigger : public Trigger
{
public:
    McGolemaggIsMainTankTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc golemagg is main tank") {}
    bool IsActive() override;
};

class McGolemaggIsAssistTankTrigger : public Trigger
{
public:
    McGolemaggIsAssistTankTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc golemagg is assist tank") {}
    bool IsActive() override;
};

class McGolemaggIsHealerTrigger : public Trigger
{
public:
    McGolemaggIsHealerTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc golemagg is healer") {}
    bool IsActive() override;
};

class McCoreHoundMarkTrigger : public Trigger
{
public:
    McCoreHoundMarkTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc core hound mark") {}
    bool IsActive() override;
};

// Standing/swimming in magma (knocked into a lava pool by Ragnaros' Wrath or an Eruption)
class McInLavaTrigger : public Trigger
{
public:
    McInLavaTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc in lava") {}
    bool IsActive() override;
};

class McGolemaggMagmaSplashTrigger : public Trigger
{
public:
    McGolemaggMagmaSplashTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc golemagg magma splash") {}
    bool IsActive() override;
};

class McKillOrderMarkTrigger : public Trigger
{
public:
    McKillOrderMarkTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc kill order mark") {}
    bool IsActive() override;
};

class McSulfuronDarkMendingTrigger : public Trigger
{
public:
    McSulfuronDarkMendingTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc sulfuron dark mending") {}
    bool IsActive() override;
};

class McMajordomoReflectionTrigger : public Trigger
{
public:
    McMajordomoReflectionTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc majordomo reflection") {}
    bool IsActive() override;
};

class McRagnarosRangedTooCloseTrigger : public Trigger
{
public:
    McRagnarosRangedTooCloseTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc ragnaros ranged too close") {}
    bool IsActive() override;
};

// Checked every 2s: finding the nearest raid member walks the whole group.
class McRagnarosRangedSpreadTrigger : public Trigger
{
public:
    McRagnarosRangedSpreadTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc ragnaros ranged spread", 2) {}
    bool IsActive() override;
};

// Each bot times Wrath of Ragnaros from the moment it sees him engage or emerge. A bot that joins
// mid-phase (late arrival, battle rez) starts its clock late and may be knocked back that phase.
class McRagnarosWrathSoonTrigger : public Trigger
{
public:
    McRagnarosWrathSoonTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc ragnaros wrath soon") {}
    bool IsActive() override;

private:
    uint32 _phaseStartMs = 0;
    uint32 _lastSeenMs = 0;
};

#endif
