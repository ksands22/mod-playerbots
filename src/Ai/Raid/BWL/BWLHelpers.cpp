/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BWLHelpers.h"
#include "AiObjectContext.h"
#include "Group.h"
#include "Map.h"
#include "RtiTargetValue.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include <algorithm>
#include <array>

namespace BlackwingLairHelpers
{
    bool IsActiveSuppressionDeviceInRange(GameObject const* go, Player const* bot)
    {
        constexpr float suppressionDeviceInteractionDistance = 15.0f;
        return go &&
               go->GetEntry() == static_cast<uint32>(BlackwingLairGameObjects::GO_SUPPRESSION_DEVICE) &&
               go->GetDistance(bot) < suppressionDeviceInteractionDistance &&
               go->GetGoState() == GO_STATE_READY;
    }

    bool AreRazorgoreEggsAlive(PlayerbotAI* botAI)
    {
        GuidVector gos = botAI->GetAiObjectContext()->GetValue<GuidVector>("nearest game objects")->Get();
        for (auto const& guid : gos)
        {
            GameObject const* go = botAI->GetGameObject(guid);
            if (go && go->GetEntry() == static_cast<uint32>(BlackwingLairGameObjects::GO_BLACK_DRAGON_EGG))
                return true;
        }
        return false;
    }

    bool IsRazorgoreOffTank(Player* bot)
    {
        return PlayerbotAI::IsAssistTankOfIndex(bot, 0, true);
    }

    bool IsNonBABotNearPosition(Player const* bot, Position const& position, float distance)
    {
        Group const* group = bot->GetGroup();
        if (!group)
            return false;

        for (GroupReference const* gref = group->GetFirstMember(); gref; gref = gref->next())
        {
            Player const* p = gref->GetSource();
            if (!p || p == bot || !p->IsAlive() || p->GetMapId() != bot->GetMapId())
                continue;

            if (p->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_BURNING_ADRENALINE)))
                continue;

            if (p->GetDistance2d(position.GetPositionX(), position.GetPositionY()) < distance)
                return true;
        }

        return false;
    }

    bool IsCorruptedWhelp(Unit const* unit)
    {
        if (!unit)
            return false;

        const uint32 entry = unit->GetEntry();
        return entry == static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_RED_WHELP) ||
            entry == static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_GREEN_WHELP) ||
            entry == static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_BLUE_WHELP) ||
            entry == static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_BRONZE_WHELP);
    }

    bool HasFlameBuffetHideStacks(Player const* bot)
    {
        Aura const* buffet = bot->GetAura(static_cast<uint32>(BlackwingLairSpells::SPELL_FLAME_BUFFET));
        return buffet && buffet->GetStackAmount() >= FIREMAW_FLAME_BUFFET_HIDE_STACKS;
    }

    bool IsSpotInSightOf(Unit const* viewer, Player const* bot, Position const& spot)
    {
        return bot->GetMap()->isInLineOfSight(viewer->GetPositionX(), viewer->GetPositionY(),
            viewer->GetPositionZ() + viewer->GetCollisionHeight(), spot.GetPositionX(), spot.GetPositionY(),
            spot.GetPositionZ() + bot->GetCollisionHeight(), bot->GetPhaseMask(), LINEOFSIGHT_ALL_CHECKS,
            VMAP::ModelIgnoreFlags::Nothing);
    }

    bool IsFiremawHealerSpot(Player const* bot, Unit const* tank, Position const& spot, float healRange)
    {
        return tank->GetExactDist(&spot) <= healRange && IsSpotInSightOf(tank, bot, spot);
    }

    // Healing keeps Nefarian topped up and Fire Nova hits the raid; the other two only buff him.
    static uint8 GetCorruptedTotemPriority(uint32 entry)
    {
        switch (entry)
        {
            case static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_HEALING_TOTEM):
                return 4;
            case static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_FIRE_NOVA_TOTEM):
                return 3;
            case static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_WINDFURY_TOTEM):
                return 2;
            case static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_STONESKIN_TOTEM):
                return 1;
            default:
                return 0;
        }
    }

    Unit* GetCorruptedTotemMarkTarget(PlayerbotAI* botAI)
    {
        Player* bot = botAI->GetBot();
        Group* group = bot->GetGroup();
        if (!group)
            return nullptr;

        AiObjectContext* context = botAI->GetAiObjectContext();
        Unit* nefarian = context->GetValue<Unit*>("find target", "nefarian")->Get();
        if (!nefarian || !nefarian->IsAlive())
            return nullptr;

        Unit* best = nullptr;
        uint8 bestPriority = 0;
        for (ObjectGuid const guid : context->GetValue<GuidVector>("possible targets")->Get())
        {
            Unit* unit = botAI->GetUnit(guid);
            if (!unit || !unit->IsAlive() || !bot->IsValidAttackTarget(unit))
                continue;

            uint8 const priority = GetCorruptedTotemPriority(unit->GetEntry());
            if (priority > bestPriority)
            {
                best = unit;
                bestPriority = priority;
            }
        }

        Unit* skull = botAI->GetUnit(group->GetTargetIcon(RtiTargetValue::skullIndex));
        bool const skullAlive = skull && skull->IsAlive();
        if (best)
        {
            if (skullAlive && GetCorruptedTotemPriority(skull->GetEntry()) >= bestPriority)
                return nullptr;
            return best;
        }

        // Totems gone: hand the skull back to Nefarian once he can be attacked.
        if (!skullAlive && bot->IsValidAttackTarget(nefarian))
            return nefarian;

        return nullptr;
    }

    static constexpr std::array<char const*, 5> CORRUPTED_HEALING_SPELLS = {
        "flash heal", "heal", "greater heal", "lesser heal", "prayer of healing"};

    bool IsCorruptedHealingSpell(std::string const& spell)
    {
        return std::find(CORRUPTED_HEALING_SPELLS.begin(), CORRUPTED_HEALING_SPELLS.end(), spell) !=
            CORRUPTED_HEALING_SPELLS.end();
    }

    bool IsCastingCorruptedHealingSpell(PlayerbotAI* botAI)
    {
        Spell const* spell = botAI->GetBot()->GetCurrentSpell(CURRENT_GENERIC_SPELL);
        if (!spell)
            return false;

        // Compare first ranks: bots may cast a lower rank than the one "spell id" resolves to.
        uint32 const castFirstRank = sSpellMgr->GetFirstSpellInChain(spell->m_spellInfo->Id);
        AiObjectContext* context = botAI->GetAiObjectContext();
        for (char const* name : CORRUPTED_HEALING_SPELLS)
        {
            uint32 const spellId = context->GetValue<uint32>("spell id", name)->Get();
            if (spellId && sSpellMgr->GetFirstSpellInChain(spellId) == castFirstRank)
                return true;
        }
        return false;
    }
}
