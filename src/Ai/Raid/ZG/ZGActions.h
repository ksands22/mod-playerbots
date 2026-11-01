/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGACTIONS_H
#define PLAYERBOTS_ZGACTIONS_H

#include "AttackAction.h"
#include "MovementActions.h"

class ZgKillOrderMarkAction : public Action
{
public:
    ZgKillOrderMarkAction(PlayerbotAI* botAI) : Action(botAI, "zg kill order mark") {}
    bool Execute(Event event) override;
};

class ZgCcMarkAction : public Action
{
public:
    ZgCcMarkAction(PlayerbotAI* botAI) : Action(botAI, "zg cc mark") {}
    bool Execute(Event event) override;
};

class ZgInterruptAction : public Action
{
public:
    ZgInterruptAction(PlayerbotAI* botAI) : Action(botAI, "zg interrupt") {}
    bool Execute(Event event) override;
};

class ZgJeklikSpreadAction : public MovementAction
{
public:
    ZgJeklikSpreadAction(PlayerbotAI* botAI) : MovementAction(botAI, "zg jeklik spread") {}
    bool Execute(Event event) override;
};

class ZgVenoxisMoveAwayAction : public MovementAction
{
public:
    ZgVenoxisMoveAwayAction(PlayerbotAI* botAI) : MovementAction(botAI, "zg venoxis move away") {}
    bool Execute(Event event) override;
};

class ZgThekalAttackTigerAction : public AttackAction
{
public:
    ZgThekalAttackTigerAction(PlayerbotAI* botAI) : AttackAction(botAI, "zg thekal attack tiger") {}
    bool Execute(Event event) override;
};

class ZgMandokirStopAttackingAction : public Action
{
public:
    ZgMandokirStopAttackingAction(PlayerbotAI* botAI) : Action(botAI, "zg mandokir stop attacking") {}
    bool Execute(Event event) override;
};

// Attacks, then taunts, a named unit: the off-tank's Ohgan and the tanks' Gahz'ranka pickup.
class ZgTankUnitAction : public AttackAction
{
public:
    ZgTankUnitAction(PlayerbotAI* botAI, std::string const& name, std::string unitName)
        : AttackAction(botAI, name), _unitName(std::move(unitName)) {}
    bool Execute(Event event) override;

private:
    std::string const _unitName;
};

// Steps out of the frontal Frost Breath cone; no tail danger, so any non-frontal spot is fine.
class ZgGahzrankaAvoidBreathAction : public BossRearFlankAction
{
public:
    ZgGahzrankaAvoidBreathAction(PlayerbotAI* botAI)
        : BossRearFlankAction(botAI, "gahz'ranka", 0.0f, ANGLE_45_DEG, M_PI) {}
    bool isUseful() override;
};

class ZgGrilekKiteAction : public MovementAction
{
public:
    ZgGrilekKiteAction(PlayerbotAI* botAI) : MovementAction(botAI, "zg grilek kite") {}
    bool Execute(Event event) override;
};

class ZgCasterSpreadAction : public MovementAction
{
public:
    ZgCasterSpreadAction(PlayerbotAI* botAI) : MovementAction(botAI, "zg caster spread") {}
    bool Execute(Event event) override;
};

class ZgHazzarahAttackIllusionAction : public AttackAction
{
public:
    ZgHazzarahAttackIllusionAction(PlayerbotAI* botAI) : AttackAction(botAI, "zg hazzarah attack illusion") {}
    bool Execute(Event event) override;
};

class ZgJindoAttackShadeAction : public AttackAction
{
public:
    ZgJindoAttackShadeAction(PlayerbotAI* botAI) : AttackAction(botAI, "zg jindo attack shade") {}
    bool Execute(Event event) override;
};

class ZgHakkarStandInCloudAction : public MovementAction
{
public:
    ZgHakkarStandInCloudAction(PlayerbotAI* botAI) : MovementAction(botAI, "zg hakkar stand in cloud") {}
    bool Execute(Event event) override;
};

class ZgHakkarPullSonAction : public AttackAction
{
public:
    ZgHakkarPullSonAction(PlayerbotAI* botAI) : AttackAction(botAI, "zg hakkar pull son") {}
    bool Execute(Event event) override;
};

#endif
