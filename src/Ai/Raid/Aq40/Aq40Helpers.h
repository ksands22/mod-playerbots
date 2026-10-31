/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40HELPERS_H
#define PLAYERBOTS_AQ40HELPERS_H

#include <optional>

#include "EncounterHelpers.h"
#include "ObjectGuid.h"
#include "Position.h"
#include "SharedDefines.h"

class Player;
class PlayerbotAI;
class Unit;
class WorldObject;

namespace TempleOfAhnQirajHelpers
{
inline constexpr uint32 AQ40_MAP_ID = 531;

// Mirrors DataTypes in the core's temple_of_ahnqiraj.h.
enum TempleOfAhnQirajBosses : uint32
{
    BOSS_SKERAM = 1,
    BOSS_BUG_TRIO = 2,
    BOSS_SARTURA = 3,
    BOSS_FANKRISS = 4,
    BOSS_VISCIDUS = 5,
    BOSS_HUHURAN = 6,
    BOSS_TWIN_EMPERORS = 7,
    BOSS_OURO = 8,
    BOSS_CTHUN = 9,
};

enum TempleOfAhnQirajNPCs : uint32
{
    // The Prophet Skeram
    NPC_SKERAM = 15263,

    // Bug Trio
    NPC_KRI = 15511,
    NPC_VEM = 15544,
    NPC_YAUJ = 15543,
    NPC_POISON_CLOUD = 15933,

    // Battleguard Sartura
    NPC_SARTURA = 15516,
    NPC_SARTURA_ROYAL_GUARD = 15984,

    // Fankriss the Unyielding
    NPC_FANKRISS = 15510,
    NPC_SPAWN_OF_FANKRISS = 15630,

    // Viscidus
    NPC_VISCIDUS = 15299,
    NPC_TOXIC_SLIME = 15925,

    // Twin Emperors
    NPC_VEKNILASH = 15275,
    NPC_VEKLOR = 15276,

    // Ouro
    NPC_DIRT_MOUND = 15712,

    // C'Thun
    NPC_EYE_OF_CTHUN = 15589,
    NPC_CTHUN = 15727,
    NPC_CLAW_TENTACLE = 15725,
    NPC_EYE_TENTACLE = 15726,
    NPC_FLESH_TENTACLE = 15802,
    NPC_GIANT_CLAW_TENTACLE = 15728,
    NPC_GIANT_EYE_TENTACLE = 15334,

    // Trash
    NPC_ANUBISATH_SENTINEL = 15264,
    NPC_ANUBISATH_DEFENDER = 15277,
};

enum TempleOfAhnQirajSpells : uint32
{
    // The Prophet Skeram
    SPELL_TRUE_FULFILLMENT = 785,

    // Battleguard Sartura
    SPELL_SARTURA_WHIRLWIND = 26083,
    SPELL_ROYAL_GUARD_WHIRLWIND = 26038,

    // Fankriss the Unyielding
    SPELL_MORTAL_WOUND = 25646,

    // Princess Huhuran
    SPELL_ACID_SPIT = 26050,

    // Viscidus
    SPELL_VISCIDUS_FREEZE = 25937,
    SPELL_VISCIDUS_INVISIBLE = 25905,

    // Twin Emperors
    SPELL_EXPLODE_BUG = 804,

    // C'Thun
    SPELL_DARK_GLARE_COLORATION = 22518,
    SPELL_CARAPACE_CTHUN = 26156,
    SPELL_DIGESTIVE_ACID = 26476,

    // Trash
    SPELL_CAUSE_INSANITY = 26079,
    SPELL_DEFENDER_EXPLODE = 25698,
    SPELL_DEFENDER_PLAGUE = 26556,
    // Anubisath Sentinel abilities, each a periodic aura on the Sentinel holding it.
    SPELL_SENTINEL_MANA_BURN = 812,
    SPELL_SENTINEL_SHADOW_STORM = 2148,
    SPELL_SENTINEL_THUNDERCLAP = 2834,
};

// Radii from spell data: Whirlwind damage (26084, 26686), the cloud's Toxic Vapors (25786), the
// slime's Toxin pools (25989), an exploding bug (26059), a dirt mound's Quake (26093) and
// Viscidus's Poison Shock (25993).
constexpr float WHIRLWIND_RADIUS = 10.0f;
constexpr float POISON_CLOUD_RADIUS = 8.0f;
constexpr float TOXIN_RADIUS = 5.0f;
constexpr float EXPLODE_BUG_RADIUS = 15.0f;
constexpr float QUAKE_RADIUS = 8.0f;
constexpr float POISON_SHOCK_RADIUS = 15.0f;
constexpr float AVOID_SAFETY_MARGIN = 3.0f;
constexpr float WHIRLWIND_SAFE_DISTANCE = WHIRLWIND_RADIUS + AVOID_SAFETY_MARGIN;
constexpr float POISON_CLOUD_SAFE_DISTANCE = POISON_CLOUD_RADIUS + AVOID_SAFETY_MARGIN;
constexpr float TOXIN_SAFE_DISTANCE = TOXIN_RADIUS + AVOID_SAFETY_MARGIN;
constexpr float EXPLODE_BUG_SAFE_DISTANCE = EXPLODE_BUG_RADIUS + AVOID_SAFETY_MARGIN;
constexpr float QUAKE_SAFE_DISTANCE = QUAKE_RADIUS + AVOID_SAFETY_MARGIN;
constexpr float POISON_SHOCK_SAFE_DISTANCE = POISON_SHOCK_RADIUS + AVOID_SAFETY_MARGIN;

// An Anubisath Defender that does not enrage at 10% health roots itself and explodes six seconds
// later (25699, 20 yards). Plague (26557) splashes allies within 5 yards of its victim.
constexpr float DEFENDER_EXPLODE_RADIUS = 20.0f;
constexpr float DEFENDER_PLAGUE_RADIUS = 5.0f;
constexpr float DEFENDER_EXPLODE_SAFE_DISTANCE = DEFENDER_EXPLODE_RADIUS + AVOID_SAFETY_MARGIN;
constexpr float DEFENDER_PLAGUE_SAFE_DISTANCE = DEFENDER_PLAGUE_RADIUS + AVOID_SAFETY_MARGIN;
// Defender and Sentinel Thunderclap (26554, 8732). A Defender rolls Thunderclap or Shadow Storm
// without a visible aura, so ranged treat every Defender as a Thunderclap one.
constexpr float THUNDERCLAP_RADIUS = 25.0f;
constexpr float THUNDERCLAP_SAFE_DISTANCE = THUNDERCLAP_RADIUS + AVOID_SAFETY_MARGIN;

// Each Mortal Wound stack cuts healing taken by 10%.
constexpr uint8 MORTAL_WOUND_SWAP_STACKS = 5;
// Acid Spit stacks without limit and Huhuran ignores taunts, so the stacked tank sheds threat instead.
constexpr uint8 ACID_SPIT_SWAP_STACKS = 8;

// Ouro's Sand Blast is a frontal cone; everyone but his tanks stays out of his front half.
constexpr float SAND_BLAST_AVOID_ANGLE = static_cast<float>(M_PI) / 2.0f;
constexpr float OURO_RANGED_FLANK_DISTANCE = 20.0f;

// Dark Glare sweeps half a circle at one tick (M_PI / 35) per second and hits a 5-yard-wide line.
// 35 degrees gives about seven seconds' warning before the beam arrives.
constexpr float DARK_GLARE_DANGER_ANGLE = 35.0f * static_cast<float>(M_PI) / 180.0f;
constexpr float DARK_GLARE_ESCAPE_ANGLE = 50.0f * static_cast<float>(M_PI) / 180.0f;
// Stomach residents leave once acid stacks this high, even with Flesh Tentacles still alive.
// Raids leave at four or five; each stack adds 150 damage every five seconds.
constexpr uint8 DIGESTIVE_ACID_EXIT_STACKS = 5;
// Covers the whole stomach chamber.
constexpr float CTHUN_STOMACH_SEARCH_RANGE = 100.0f;
// Area trigger 4033, which throws a player out of the stomach.
inline Position const CTHUN_STOMACH_EXIT_POSITION = {-8546.23f, 1987.65f, -96.52f};

// The twins swap places on each teleport and neither can be taunted; each takes the nearest player
// as its target. So each side of the room keeps its own tanks, named after the twin that starts
// there: a physical tank for Vek'nilash and a warlock for Vek'lor.
enum class TwinEmperorsSide : uint8
{
    Veknilash,
    Veklor,
};

inline Position const VEKNILASH_SPAWN_POSITION = {-9023.67f, 1176.24f, -104.23f};
inline Position const VEKLOR_SPAWN_POSITION = {-8868.31f, 1205.97f, -104.23f};
// The Twin Emperors' room spans about 160 yards between the two thrones.
inline constexpr float TWIN_EMPERORS_CLASS_ROLE_ANNOUNCE_DISTANCE = 100.0f;
inline constexpr float TWIN_EMPERORS_CLASS_ROLE_REARM_DISTANCE = 200.0f;
// A side's physical tank waits this close to Vek'lor so it is nearest when Vek'nilash teleports in,
// but outside the 5 yards that trigger Arcane Burst.
constexpr float TWIN_TANK_STATION_MIN_DISTANCE = 7.0f;
constexpr float TWIN_TANK_STATION_MAX_DISTANCE = 12.0f;
// Vek'lor casts Blizzard on a random player within 45 yards.
constexpr float VEKLOR_BLIZZARD_SAFE_DISTANCE = 45.0f + AVOID_SAFETY_MARGIN;

// Vek'lor is immune to physical damage, so a warlock on each side holds him with Searing Pain.
inline constexpr EncounterHelpers::ClassRole VEKNILASH_SIDE_WARLOCK_TANK_ROLE = {
    .playerClass = CLASS_WARLOCK,
    .role = {"class_role_twin_emperors_veknilash_side_warlock_tank", "Twin Emperors warlock tank, Vek'nilash's side"},
    .candidate = {"class_role_class_warlock", "Warlock"},
};
inline constexpr EncounterHelpers::ClassRole VEKLOR_SIDE_WARLOCK_TANK_ROLE = {
    .playerClass = CLASS_WARLOCK,
    .role = {"class_role_twin_emperors_veklor_side_warlock_tank", "Twin Emperors warlock tank, Vek'lor's side"},
    .candidate = {"class_role_class_warlock", "Warlock"},
};

bool IsBossInProgress(Player* bot, TempleOfAhnQirajBosses boss);

bool HasLivingGroupMemberOfClass(Player* bot, uint8 playerClass);

// Images share the boss's entry and name; only the real Prophet is not a summon.
bool IsSkeramImage(Unit const* unit);
// A raid member under True Fulfillment or Cause Insanity who is neither polymorphed nor feared yet.
Player* FindMindControlledMemberToControl(Player* bot);

// Nearest Anubisath Defender about to explode within DEFENDER_EXPLODE_SAFE_DISTANCE of the bot.
Unit* FindNearbyExplodingDefender(PlayerbotAI* botAI);
// Nearest other player within DEFENDER_PLAGUE_SAFE_DISTANCE of the bot.
Unit* FindNearbyPlagueVictim(PlayerbotAI* botAI);
// Any Defender, or a Sentinel holding Thunderclap.
bool CanThunderclap(Unit const* unit);
// Nearest attacker that can Thunderclap within THUNDERCLAP_SAFE_DISTANCE of the bot.
Unit* FindNearbyThunderclapper(PlayerbotAI* botAI);
// The Sentinel the whole raid kills next: raid-wide abilities last, then lowest health.
Unit* FindSentinelKillTarget(PlayerbotAI* botAI, GuidVector const& attackers);
// Eradicators and Nullifiers fill their mana by draining the raid and blast it once full.
// The first one the bot fights that still has mana to burn.
Unit* FindObsidianWithMana(PlayerbotAI* botAI);

bool IsBugTrioMember(Unit const* unit);
// A bug at zero health is kept alive (and immune to the raid) until the others devour it.
bool IsBugTrioMemberDying(Unit const* unit);
// Kill order Kri (Toxic Volley), Yauj (heals, fear), then Vem: Vem's death buffs any bug still alive.
Unit* FindBugTrioKillTarget(PlayerbotAI* botAI, GuidVector const& attackers);

bool IsWhirlwinding(Unit const* unit);
// Nearest whirlwinding attacker within WHIRLWIND_SAFE_DISTANCE of the bot.
Unit* FindNearbyWhirlwind(PlayerbotAI* botAI);

uint8 GetAuraStacks(Unit const* unit, uint32 spellId);
// The main tank and the first assist tank trade Fankriss and Huhuran back and forth.
bool IsSwapTank(Player* bot);
// The other swap tank, while it is alive.
Player* GetSwapTankPartner(Player* bot);
// The bot tanks Huhuran with too many Acid Spit stacks and a fresh partner can take over.
bool ShouldShedHuhuranThreat(PlayerbotAI* botAI);

// Viscidus can be frozen while he is neither frozen already nor shattered into globs.
bool IsViscidusFreezable(Unit const* viscidus);

bool IsTwinEmperor(Unit const* unit);
// Vek'nilash shrugs off magic and Vek'lor physical damage; casters count as magic, the rest physical.
bool IsTwinImmuneToBot(Unit const* twin, Player* bot);
// Nearest bug Vek'lor has marked to explode within EXPLODE_BUG_SAFE_DISTANCE of the bot.
Unit* FindNearbyExplodingBug(PlayerbotAI* botAI);
TwinEmperorsSide GetTwinEmperorsSide(WorldObject const* object);
// The side the bot holds as a twin tank (main tank, first assist tank or a warlock tank), if any.
std::optional<TwinEmperorsSide> GetTwinEmperorsTankSide(Player* bot);
// The twin currently standing on the given side.
Unit* FindTwinOnSide(PlayerbotAI* botAI, TwinEmperorsSide side);

bool IsInCthunStomach(Player* bot);
bool IsCthunTentacleAdd(Unit const* unit);
// Phase 2 kill priority outside the stomach, lower first: the Giant Eye can be stunned and dies
// fastest, Eye Tentacles must not channel Mind Flay, and the Giant Claw needs a tank anyway.
std::optional<uint8> GetCthunTentaclePriority(Unit const* unit);
// The Eye of C'Thun while it sweeps Dark Glare, otherwise null.
Unit* FindDarkGlaringEye(PlayerbotAI* botAI);
// Signed angle in [-pi, pi] from the eye's facing (the beam) to the unit.
float GetAngleFromDarkGlare(Unit const* eye, Unit const* unit);

// Shared encounter state
struct Aq40InstanceState
{
    EncounterHelpers::ClassRoleAssignment veknilashSideWarlockTank;
    EncounterHelpers::ClassRoleAssignment veklorSideWarlockTank;
};

Aq40InstanceState& Aq40State(uint32 instanceId);
Aq40InstanceState* FindAq40State(uint32 instanceId);

bool UpdateAq40ClassRoles(PlayerbotAI* botAI);
bool UpdateTwinEmperorsClassRoleAnnouncement(PlayerbotAI* botAI);
// The side the bot holds as a warlock tank, if it holds one.
std::optional<TwinEmperorsSide> GetTwinEmperorsWarlockTankSide(Player* bot);
}  // namespace TempleOfAhnQirajHelpers

#endif
