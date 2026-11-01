/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SMHELPERS_H
#define PLAYERBOTS_SMHELPERS_H

#include "SMShared.h"
#include "Unit.h"

namespace SMShared
{

inline bool IsDoanDetonating(Unit* doan)
{
    return doan && (doan->HasAura(SPELL_ARCANE_BUBBLE) || doan->FindCurrentSpellBySpellId(SPELL_DETONATION));
}

inline bool IsHerodWhirlwinding(Unit* herod)
{
    return herod && herod->HasAura(SPELL_HEROD_WHIRLWIND);
}

}

#endif
