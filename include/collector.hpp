
#pragma once

#include "input.hpp"

#include "Game/MainMgr.h"
#include "Game/PlayerMgr.h"
#include "Game/Player/Player.h"
#include "Cmn/PlayerCtrl.h"
#include "Cmn/StaticMem.h"
#include "Cmn/Mush/MushDataHolder.h"
#include "Cmn/Mush/MushWeaponInfo.h"
#include "Cmn/Mush/MushMapInfo.h"
#include "Lp/Utl.h"

class Collector {
    public:
    static Controller Control;

    // Managers
    static Game::MainMgr* MainMgrInstance;
    static Game::PlayerMgr* PlayerMgrInstance;

    // Utils
    static Cmn::StaticMem* StaticMemInstance;

    // Player Information
    static Game::Player* ControlledPlayer;
    static Cmn::PlayerInfo* FirstPlayer;
    static Cmn::PlayerCtrl* PlayerCtrlInstance;
    static Cmn::PlayerInfoAry* PlayerInfoAry;

    // Mush
    static Cmn::MushDataHolder* MushDataHolder;
    static Cmn::MushWeaponInfo* MushWeaponInfo;
    static Cmn::MushMapInfo* MushMapInfo;

    static void init();
    static void collect();
};