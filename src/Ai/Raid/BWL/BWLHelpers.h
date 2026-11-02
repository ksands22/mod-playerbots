/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_BWLHELPERS_H
#define PLAYERBOTS_BWLHELPERS_H

#include "Player.h"
#include "PlayerbotAI.h"

namespace BlackwingLairHelpers
{
    enum class BlackwingLairSpells : uint32
    {
        // General
        SPELL_ONYXIA_SCALE_CLOAK = 22683,

        // Razorgore the Untamed
        SPELL_MINDCONTROL = 19832,

        // Vaelastrasz the Corrupt
        SPELL_BURNING_ADRENALINE = 18173,

        // Firemaw
        SPELL_FLAME_BUFFET = 23341,

        // Ebonroc
        SPELL_SHADOW_OF_EBONROC = 23340,

        // Chromaggus
        SPELL_BROOD_AFFLICTION_BRONZE = 23170,
        SPELL_HOURGLASS_SAND = 23645,

        // Nefarian
        SPELL_WILD_MAGIC = 23410,
        SPELL_CORRUPTED_HEALING = 23401
    };

    enum class BlackwingLairGameObjects : uint32
    {
        // General
        GO_SUPPRESSION_DEVICE = 179784,

        // Razorgore the Untamed
        GO_BLACK_DRAGON_EGG = 177807
    };

    enum class BlackwingLairNPCs : uint32
    {
        // Broodlord Lashlayer
        NPC_CORRUPTED_RED_WHELP = 14022,
        NPC_CORRUPTED_GREEN_WHELP = 14023,
        NPC_CORRUPTED_BLUE_WHELP = 14024,
        NPC_CORRUPTED_BRONZE_WHELP = 14025,

        // Nefarian (shaman class call)
        NPC_CORRUPTED_FIRE_NOVA_TOTEM = 14662,
        NPC_CORRUPTED_STONESKIN_TOTEM = 14663,
        NPC_CORRUPTED_HEALING_TOTEM = 14664,
        NPC_CORRUPTED_WINDFURY_TOTEM = 14666,

        // Trash
        NPC_DEATH_TALON_WYRMGUARD = 12460
    };

    constexpr float BROODLORD_SAFE_DISTANCE = 18.0f;

    // Guides break line of sight at 5-6 stacks; out of Firemaw's sight the stack expires instead of refreshing.
    constexpr uint32 FIREMAW_FLAME_BUFFET_HIDE_STACKS = 6;

    // Ebonroc still on the cursed tank this long after the curse means the first taunt was resisted
    // or out of range, so the next tank in line taunts too. Our number; the guide gives none.
    constexpr uint32 EBONROC_BACKUP_TAUNT_DELAY_MS = 1500;

    bool IsActiveSuppressionDeviceInRange(GameObject const* go, Player const* bot);
    bool AreRazorgoreEggsAlive(PlayerbotAI* botAI);
    bool IsRazorgoreOffTank(Player* bot);
    bool IsNonBABotNearPosition(Player const* bot, Position const& position, float distance);
    bool IsCorruptedWhelp(Unit const* unit);
    bool HasFlameBuffetHideStacks(Player const* bot);
    // Whether the viewer can see the bot if it stood at spot. Shared by the Firemaw triggers and the spot
    // search, so a bot never settles where one check calls it hidden and the other doesn't.
    bool IsSpotInSightOf(Unit const* viewer, Player const* bot, Position const& spot);
    // Guide healer placement: out of Firemaw's sight, with the tank in view and in heal range.
    bool IsFiremawHealerSpot(Player const* bot, Unit const* tank, Position const& spot, float healRange);
    // The corrupted totem to kill next, or Nefarian once they are gone; null when the skull is already right.
    Unit* GetCorruptedTotemMarkTarget(PlayerbotAI* botAI);
    // Corrupted Healing turns these priest heals into damage on their target.
    bool IsCorruptedHealingSpell(std::string const& spell);
    bool IsCastingCorruptedHealingSpell(PlayerbotAI* botAI);
}

#endif
