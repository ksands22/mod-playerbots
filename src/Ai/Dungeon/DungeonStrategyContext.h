/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_DUNGEONSTRATEGYCONTEXT_H
#define PLAYERBOTS_DUNGEONSTRATEGYCONTEXT_H

#include "ACStrategy.h"
#include "AKStrategy.h"
#include "ANStrategy.h"
#include "ArcStrategy.h"
#include "BFStrategy.h"
#include "BMStrategy.h"
#include "BotStrategy.h"
#include "BRDStrategy.h"
#include "BRSStrategy.h"
#include "CoSStrategy.h"
#include "DMStrategy.h"
#include "DTKStrategy.h"
#include "FoSStrategy.h"
#include "GDStrategy.h"
#include "GnomerStrategy.h"
#include "HoLStrategy.h"
#include "HoRStrategy.h"
#include "HoSStrategy.h"
#include "MaraStrategy.h"
#include "MechStrategy.h"
#include "MgTStrategy.h"
#include "MTStrategy.h"
#include "NexStrategy.h"
#include "OCStrategy.h"
#include "OHBStrategy.h"
#include "PoSStrategy.h"
#include "RampStrategy.h"
#include "RFDStrategy.h"
#include "SethStrategy.h"
#include "SLStrategy.h"
#include "SMStrategy.h"
#include "SPStrategy.h"
#include "Strategy.h"
#include "STStrategy.h"
#include "SVStrategy.h"
#include "TOCStrategy.h"
#include "UBStrategy.h"
#include "UKStrategy.h"
#include "UldamanStrategy.h"
#include "UPStrategy.h"
#include "VHStrategy.h"
#include "ZFStrategy.h"

class DungeonStrategyContext : public NamedObjectContext<Strategy>
{
public:
    DungeonStrategyContext() : NamedObjectContext<Strategy>(false, true)
    {
        // Vanilla
        creators["vanilla-gnomer"] = &DungeonStrategyContext::vanilla_gnomer;   // Gnomeregan
        creators["vanilla-sm"] = &DungeonStrategyContext::vanilla_sm;           // Scarlet Monastery
        creators["vanilla-rfd"] = &DungeonStrategyContext::vanilla_rfd;         // Razorfen Downs
        creators["vanilla-uldaman"] = &DungeonStrategyContext::vanilla_uldaman; // Uldaman
        creators["vanilla-zf"] = &DungeonStrategyContext::vanilla_zf;           // Zul'Farrak
        creators["vanilla-mara"] = &DungeonStrategyContext::vanilla_mara;       // Maraudon
        creators["vanilla-st"] = &DungeonStrategyContext::vanilla_st;           // Sunken Temple
        creators["vanilla-brd"] = &DungeonStrategyContext::vanilla_brd;         // Blackrock Depths
        creators["vanilla-brs"] = &DungeonStrategyContext::vanilla_brs;         // Blackrock Spire
        creators["vanilla-dm"] = &DungeonStrategyContext::vanilla_dm;           // Dire Maul

        // Burning Crusade
        creators["tbc-ac"] = &DungeonStrategyContext::tbc_ac;           // Auchindoun: Auchenai Crypts
        creators["tbc-seth"] = &DungeonStrategyContext::tbc_seth;       // Auchindoun: Sethekk Halls
        creators["tbc-mech"] = &DungeonStrategyContext::tbc_mech;       // Tempest Keep: The Mechanar
        creators["tbc-ub"] = &DungeonStrategyContext::tbc_ub;           // Coilfang Reservoir: The Underbog
        creators["tbc-mgt"] = &DungeonStrategyContext::tbc_mgt;         // Magisters' Terrace
        creators["tbc-ramp"] = &DungeonStrategyContext::tbc_ramp;       // Hellfire Citadel: Hellfire Ramparts
        creators["tbc-bf"] = &DungeonStrategyContext::tbc_bf;                   // Hellfire Citadel: The Blood Furnace
        creators["tbc-sp"] = &DungeonStrategyContext::tbc_sp;                   // Coilfang Reservoir: The Slave Pens
        creators["tbc-mt"] = &DungeonStrategyContext::tbc_mt;                   // Auchindoun: Mana-Tombs
        creators["tbc-ohb"] = &DungeonStrategyContext::tbc_ohb;                 // Caverns of Time: Old Hillsbrad Foothills
        creators["tbc-sv"] = &DungeonStrategyContext::tbc_sv;                   // Coilfang Reservoir: The Steamvault
        creators["tbc-sl"] = &DungeonStrategyContext::tbc_sl;                   // Auchindoun: Shadow Labyrinth
        creators["tbc-bm"] = &DungeonStrategyContext::tbc_bm;                   // Caverns of Time: The Black Morass
        creators["tbc-bot"] = &DungeonStrategyContext::tbc_bot;                 // Tempest Keep: The Botanica
        creators["tbc-arc"] = &DungeonStrategyContext::tbc_arc;                 // Tempest Keep: The Arcatraz

        // Wrath of the Lich King
        creators["wotlk-uk"] = &DungeonStrategyContext::wotlk_uk;       // Utgarde Keep
        creators["wotlk-nex"] = &DungeonStrategyContext::wotlk_nex;     // The Nexus
        creators["wotlk-an"] = &DungeonStrategyContext::wotlk_an;       // Azjol-Nerub
        creators["wotlk-ok"] = &DungeonStrategyContext::wotlk_ok;       // Ahn'kahet: The Old Kingdom
        creators["wotlk-dtk"] = &DungeonStrategyContext::wotlk_dtk;     // Drak'Tharon Keep
        creators["wotlk-vh"] = &DungeonStrategyContext::wotlk_vh;       // The Violet Hold
        creators["wotlk-gd"] = &DungeonStrategyContext::wotlk_gd;       // Gundrak
        creators["wotlk-hos"] = &DungeonStrategyContext::wotlk_hos;     // Halls of Stone
        creators["wotlk-hol"] = &DungeonStrategyContext::wotlk_hol;     // Halls of Lightning
        creators["wotlk-occ"] = &DungeonStrategyContext::wotlk_occ;     // The Oculus
        creators["wotlk-up"] = &DungeonStrategyContext::wotlk_up;       // Utgarde Pinnacle
        creators["wotlk-cos"] = &DungeonStrategyContext::wotlk_cos;     // The Culling of Stratholme
        creators["wotlk-toc"] = &DungeonStrategyContext::wotlk_toc;     // Trial of the Champion
        creators["wotlk-pos"] = &DungeonStrategyContext::wotlk_pos;     // Pit of Saron
        creators["wotlk-fos"] = &DungeonStrategyContext::wotlk_fos;     // The Forge of Souls
        creators["wotlk-hor"] = &DungeonStrategyContext::wotlk_hor;             // Halls of Reflection
    }

private:
    static Strategy* vanilla_gnomer(PlayerbotAI* botAI) { return new VanillaDungeonGnomereganStrategy(botAI); }
    static Strategy* vanilla_sm(PlayerbotAI* botAI) { return new VanillaDungeonScarletMonasteryStrategy(botAI); }
    static Strategy* vanilla_rfd(PlayerbotAI* botAI) { return new VanillaDungeonRazorfenDownsStrategy(botAI); }
    static Strategy* vanilla_uldaman(PlayerbotAI* botAI) { return new VanillaDungeonUldamanStrategy(botAI); }
    static Strategy* vanilla_zf(PlayerbotAI* botAI) { return new VanillaDungeonZulFarrakStrategy(botAI); }
    static Strategy* vanilla_mara(PlayerbotAI* botAI) { return new VanillaDungeonMaraudonStrategy(botAI); }
    static Strategy* vanilla_st(PlayerbotAI* botAI) { return new VanillaDungeonSunkenTempleStrategy(botAI); }
    static Strategy* vanilla_brd(PlayerbotAI* botAI) { return new VanillaDungeonBlackrockDepthsStrategy(botAI); }
    static Strategy* vanilla_brs(PlayerbotAI* botAI) { return new VanillaDungeonBlackrockSpireStrategy(botAI); }
    static Strategy* vanilla_dm(PlayerbotAI* botAI) { return new VanillaDungeonDireMaulStrategy(botAI); }
    static Strategy* tbc_ac(PlayerbotAI* botAI) { return new TbcDungeonAuchenaiCryptsStrategy(botAI); }
    static Strategy* tbc_seth(PlayerbotAI* botAI) { return new TbcDungeonSethekkHallsStrategy(botAI); }
    static Strategy* tbc_mech(PlayerbotAI* botAI) { return new TbcDungeonMechanarStrategy(botAI); }
    static Strategy* tbc_ub(PlayerbotAI* botAI) { return new TbcDungeonUnderbogStrategy(botAI); }
    static Strategy* tbc_mgt(PlayerbotAI* botAI) { return new TbcDungeonMagistersTerraceStrategy(botAI); }
    static Strategy* tbc_ramp(PlayerbotAI* botAI) { return new TbcDungeonHellfireRampartsStrategy(botAI); }
    static Strategy* tbc_bf(PlayerbotAI* botAI) { return new TbcDungeonBloodFurnaceStrategy(botAI); }
    static Strategy* tbc_sp(PlayerbotAI* botAI) { return new TbcDungeonSlavePensStrategy(botAI); }
    static Strategy* tbc_mt(PlayerbotAI* botAI) { return new TbcDungeonManaTombsStrategy(botAI); }
    static Strategy* tbc_ohb(PlayerbotAI* botAI) { return new TbcDungeonOldHillsbradStrategy(botAI); }
    static Strategy* tbc_sv(PlayerbotAI* botAI) { return new TbcDungeonSteamvaultStrategy(botAI); }
    static Strategy* tbc_sl(PlayerbotAI* botAI) { return new TbcDungeonShadowLabyrinthStrategy(botAI); }
    static Strategy* tbc_bm(PlayerbotAI* botAI) { return new TbcDungeonBlackMorassStrategy(botAI); }
    static Strategy* tbc_bot(PlayerbotAI* botAI) { return new TbcDungeonBotanicaStrategy(botAI); }
    static Strategy* tbc_arc(PlayerbotAI* botAI) { return new TbcDungeonArcatrazStrategy(botAI); }
    static Strategy* wotlk_uk(PlayerbotAI* botAI) { return new WotlkDungeonUKStrategy(botAI); }
    static Strategy* wotlk_nex(PlayerbotAI* botAI) { return new WotlkDungeonNexStrategy(botAI); }
    static Strategy* wotlk_an(PlayerbotAI* botAI) { return new WotlkDungeonANStrategy(botAI); }
    static Strategy* wotlk_ok(PlayerbotAI* botAI) { return new WotlkDungeonOKStrategy(botAI); }
    static Strategy* wotlk_dtk(PlayerbotAI* botAI) { return new WotlkDungeonDTKStrategy(botAI); }
    static Strategy* wotlk_vh(PlayerbotAI* botAI) { return new WotlkDungeonVHStrategy(botAI); }
    static Strategy* wotlk_gd(PlayerbotAI* botAI) { return new WotlkDungeonGDStrategy(botAI); }
    static Strategy* wotlk_hos(PlayerbotAI* botAI) { return new WotlkDungeonHoSStrategy(botAI); }
    static Strategy* wotlk_hol(PlayerbotAI* botAI) { return new WotlkDungeonHoLStrategy(botAI); }
    static Strategy* wotlk_occ(PlayerbotAI* botAI) { return new WotlkDungeonOccStrategy(botAI); }
    static Strategy* wotlk_up(PlayerbotAI* botAI) { return new WotlkDungeonUPStrategy(botAI); }
    static Strategy* wotlk_cos(PlayerbotAI* botAI) { return new WotlkDungeonCoSStrategy(botAI); }
    static Strategy* wotlk_fos(PlayerbotAI* botAI) { return new WotlkDungeonFoSStrategy(botAI); }
    static Strategy* wotlk_pos(PlayerbotAI* botAI) { return new WotlkDungeonPoSStrategy(botAI); }
    static Strategy* wotlk_toc(PlayerbotAI* botAI) { return new WotlkDungeonToCStrategy(botAI); }
    static Strategy* wotlk_hor(PlayerbotAI* botAI) { return new WotlkDungeonHallsOfReflectionStrategy(botAI); }
};

#endif
