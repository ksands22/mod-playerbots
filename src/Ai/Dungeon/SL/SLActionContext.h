/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SLACTIONCONTEXT_H
#define PLAYERBOTS_SLACTIONCONTEXT_H

#include "NamedObjectContext.h"
#include "SLActions.h"

class TbcDungeonShadowLabyrinthActionContext : public NamedObjectContext<Action>
{
public:
    TbcDungeonShadowLabyrinthActionContext()
    {
        // Grandmaster Vorpil
        creators["vorpil mark void traveler"] = &TbcDungeonShadowLabyrinthActionContext::vorpil_mark_void_traveler;

        // Murmur
        creators["murmur avoid sonic boom"] = &TbcDungeonShadowLabyrinthActionContext::murmur_avoid_sonic_boom;
        creators["murmurs touch move from group"] =
            &TbcDungeonShadowLabyrinthActionContext::murmurs_touch_move_from_group;
    }

private:
    static Action* vorpil_mark_void_traveler(PlayerbotAI* botAI) { return new VorpilMarkVoidTravelerAction(botAI); }
    static Action* murmur_avoid_sonic_boom(PlayerbotAI* botAI) { return new MurmurAvoidSonicBoomAction(botAI); }
    static Action* murmurs_touch_move_from_group(PlayerbotAI* botAI)
    {
        return new MurmursTouchMoveFromGroupAction(botAI);
    }
};

#endif
