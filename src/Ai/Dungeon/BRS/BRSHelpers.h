/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BRSHELPERS_H
#define PLAYERBOTS_BRSHELPERS_H

class Player;

namespace BRSShared
{

// The nearest other group member with Conflagration within its safe distance of the bot
Player* GetNearbyConflagratedMember(Player* bot);

}

#endif
