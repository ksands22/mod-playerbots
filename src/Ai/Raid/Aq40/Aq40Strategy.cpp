/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq40Strategy.h"

#include "Aq40Helpers.h"
#include "Aq40Multipliers.h"
#include "Playerbots.h"

using namespace TempleOfAhnQirajHelpers;

void RaidAq40Strategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Shared
    triggers.push_back(new TriggerNode("aq40 no encounter in progress",
                                       {NextAction("aq40 twin emperors announce class roles", ACTION_EMERGENCY + 8)}));
    triggers.push_back(new TriggerNode("aq40 class roles should be assigned",
                                       {NextAction("aq40 assign class roles", ACTION_EMERGENCY + 9)}));

    // Skeram and Brainwasher mind control; Yauj, Warder and Champion fears
    triggers.push_back(new TriggerNode("aq40 mind control", {NextAction("aq40 control mind controlled", ACTION_RAID)}));
    triggers.push_back(new TriggerNode("aq40 fear", {NextAction("tremor totem", ACTION_RAID)}));

    // Trash
    triggers.push_back(
        new TriggerNode("aq40 defender explode", {NextAction("aq40 defender avoid explode", ACTION_RAID + 5)}));
    triggers.push_back(
        new TriggerNode("aq40 defender plague", {NextAction("aq40 defender plague spread", ACTION_RAID + 1)}));
    triggers.push_back(new TriggerNode("aq40 thunderclap", {NextAction("aq40 avoid thunderclap", ACTION_RAID)}));
    triggers.push_back(new TriggerNode("aq40 obsidian mana", {NextAction("aq40 burn obsidian mana", ACTION_RAID + 1)}));

    // Bug Trio
    triggers.push_back(
        new TriggerNode("aq40 kri poison cloud", {NextAction("aq40 kri avoid poison cloud", ACTION_RAID + 1)}));

    // Battleguard Sartura
    triggers.push_back(
        new TriggerNode("aq40 sartura whirlwind", {NextAction("aq40 sartura avoid whirlwind", ACTION_RAID)}));
    triggers.push_back(new TriggerNode("aq40 sartura stun", {NextAction("aq40 sartura stun", ACTION_RAID)}));

    // Princess Huhuran
    triggers.push_back(
        new TriggerNode("aq40 huhuran shed threat", {NextAction("aq40 huhuran shed threat", ACTION_RAID + 2)}));

    // Fankriss the Unyielding
    triggers.push_back(
        new TriggerNode("aq40 fankriss tank swap", {NextAction("aq40 fankriss taunt", ACTION_RAID + 2)}));

    // Viscidus
    triggers.push_back(new TriggerNode("aq40 viscidus frost", {NextAction("aq40 viscidus frost spell", ACTION_RAID)}));
    triggers.push_back(new TriggerNode("aq40 viscidus poison shock",
                                       {NextAction("aq40 viscidus avoid poison shock", ACTION_RAID + 1)}));
    triggers.push_back(
        new TriggerNode("aq40 viscidus toxic slime", {NextAction("aq40 viscidus avoid toxic slime", ACTION_RAID + 1)}));

    // Twin Emperors
    triggers.push_back(new TriggerNode("aq40 veklor needs warlock tank",
                                       {NextAction("aq40 warlock tank attack veklor", ACTION_RAID + 1)}));
    triggers.push_back(new TriggerNode("aq40 twin emperors tank station",
                                       {NextAction("aq40 twin emperors tank station", ACTION_RAID)}));
    triggers.push_back(new TriggerNode("aq40 twin emperors healer blizzard",
                                       {NextAction("aq40 twin emperors healer avoid blizzard", ACTION_RAID)}));
    triggers.push_back(new TriggerNode("aq40 twin emperors exploding bug",
                                       {NextAction("aq40 twin emperors avoid exploding bug", ACTION_RAID + 1)}));

    // Ouro
    triggers.push_back(
        new TriggerNode("aq40 ouro sand blast", {NextAction("aq40 ouro avoid sand blast", ACTION_RAID)}));
    triggers.push_back(
        new TriggerNode("aq40 ouro dirt mound", {NextAction("aq40 ouro avoid dirt mound", ACTION_RAID + 1)}));

    // C'Thun
    triggers.push_back(
        new TriggerNode("aq40 cthun dark glare", {NextAction("aq40 cthun avoid dark glare", ACTION_RAID + 5)}));
    triggers.push_back(
        new TriggerNode("aq40 cthun stomach exit", {NextAction("aq40 cthun leave stomach", ACTION_RAID + 1)}));
}

void RaidAq40Strategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new AnubisathSpellReflectMultiplier(botAI));
    multipliers.push_back(new AnubisathDefenderMultiplier(botAI));
    multipliers.push_back(new AnubisathThunderclapMultiplier(botAI));
    multipliers.push_back(new KriPoisonCloudMultiplier(botAI));
    multipliers.push_back(new SarturaWhirlwindMultiplier(botAI));
    multipliers.push_back(new FankrissMortalWoundMultiplier(botAI));
    multipliers.push_back(new HuhuranWyvernStingMultiplier(botAI));
    multipliers.push_back(new HuhuranAcidSpitMultiplier(botAI));
    multipliers.push_back(new ViscidusPoisonShockMultiplier(botAI));
}

void RaidAq40Strategy::AppendTargetExclusions(GuidSet& exclusions, TargetValueExclusionType type)
{
    Player* bot = botAI->GetBot();
    if (type == TargetValueExclusionType::Aoe && PlayerbotAI::IsTank(bot))
        return;

    AiObjectContext* context = botAI->GetAiObjectContext();
    GuidVector const attackers = AI_VALUE(GuidVector, "attackers");
    bool const tankTarget = type == TargetValueExclusionType::TankTarget;
    bool const isMainTank = PlayerbotAI::IsMainTank(bot);
    bool const inStomach = IsInCthunStomach(bot);
    std::optional<TwinEmperorsSide> const twinSide = GetTwinEmperorsTankSide(bot);

    Unit* bugKillTarget = nullptr;
    Unit* sentinelKillTarget = nullptr;
    bool royalGuardAlive = false;
    bool spawnOfFankrissAlive = false;
    bool cthunTentacleAlive = false;
    bool cthunWeakened = false;
    std::optional<uint8> topTentaclePriority;
    if (!tankTarget)
    {
        bugKillTarget = FindBugTrioKillTarget(botAI, attackers);
        sentinelKillTarget = FindSentinelKillTarget(botAI, attackers);
        for (ObjectGuid const guid : attackers)
        {
            Unit* unit = botAI->GetUnit(guid);
            if (!unit || !unit->IsAlive())
                continue;

            royalGuardAlive |= unit->GetEntry() == NPC_SARTURA_ROYAL_GUARD;
            spawnOfFankrissAlive |= unit->GetEntry() == NPC_SPAWN_OF_FANKRISS;
            cthunTentacleAlive |= IsCthunTentacleAdd(unit);
            cthunWeakened |= unit->GetEntry() == NPC_CTHUN && !unit->HasAura(SPELL_CARAPACE_CTHUN);

            std::optional<uint8> const priority = GetCthunTentaclePriority(unit);
            if (priority && (!topTentaclePriority || *priority < *topTentaclePriority))
                topTentaclePriority = priority;
        }
    }

    for (ObjectGuid const guid : attackers)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit)
            continue;

        uint32 const entry = unit->GetEntry();

        // Each twin is immune to one kind of damage, and twin tanks hold their own side of the room.
        // Flesh Tentacles only exist inside the stomach, and whoever is in there fights nothing else.
        bool exclude = IsTwinImmuneToBot(unit, bot) ||
                       (twinSide && IsTwinEmperor(unit) && GetTwinEmperorsSide(unit) != *twinSide) ||
                       (entry == NPC_FLESH_TENTACLE) != inStomach;

        if (tankTarget)
        {
            // The main tank holds the real Prophet; assist tanks pick up the images.
            exclude |= isMainTank && IsSkeramImage(unit);
        }
        else
        {
            // Skeram's images despawn with him. A dying bug ignores damage until it is devoured.
            // Sentinels die one at a time, since each death heals and empowers the rest. Sartura's guards, Fankriss's
            // worms and the Eye's tentacles die before their boss, and C'Thun's body is immune while its carapace
            // holds. Outside the weakened window the phase 2 tentacles die in priority order; inside it everything goes
            // into C'Thun.
            std::optional<uint8> const tentaclePriority = GetCthunTentaclePriority(unit);
            exclude |= IsSkeramImage(unit) || IsBugTrioMemberDying(unit) ||
                       (bugKillTarget && IsBugTrioMember(unit) && unit != bugKillTarget) ||
                       (sentinelKillTarget && entry == NPC_ANUBISATH_SENTINEL && unit != sentinelKillTarget) ||
                       (royalGuardAlive && entry == NPC_SARTURA) || (spawnOfFankrissAlive && entry == NPC_FANKRISS) ||
                       (cthunTentacleAlive && entry == NPC_EYE_OF_CTHUN) ||
                       (entry == NPC_CTHUN && unit->HasAura(SPELL_CARAPACE_CTHUN)) ||
                       (tentaclePriority &&
                        (cthunWeakened || (topTentaclePriority && *tentaclePriority > *topTentaclePriority)));
        }

        if (exclude)
            exclusions.insert(guid);
    }
}
