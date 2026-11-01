/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BRSHelpers.h"
#include "BRSShared.h"
#include "Group.h"
#include "Player.h"

namespace BRSShared
{

Player* GetNearbyConflagratedMember(Player* bot)
{
    Group* group = bot->GetGroup();
    if (!group)
        return nullptr;

    Player* nearest = nullptr;
    float nearestDistance = CONFLAGRATION_SAFE_DISTANCE;
    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        Player* member = ref->GetSource();
        if (!member || member == bot || !member->IsAlive() || !member->HasAura(SPELL_CONFLAGRATION))
            continue;

        float const distance = bot->GetExactDist2d(member);
        if (distance < nearestDistance)
        {
            nearest = member;
            nearestDistance = distance;
        }
    }

    return nearest;
}

}
