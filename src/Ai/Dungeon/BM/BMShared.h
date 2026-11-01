/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BMSHARED_H
#define PLAYERBOTS_BMSHARED_H

class PlayerbotAI;
class Unit;

namespace BMShared
{

// Rift mobs walk to Medivh and channel Corrupt Medivh at him instead of attacking the group, so
// they never enter the bots' attackers; this finds the nearest one (rift guardians and bosses too)
Unit* FindNearestRiftMob(PlayerbotAI* botAI);

}

#endif
