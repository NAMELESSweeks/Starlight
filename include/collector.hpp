
#pragma once

#include "input.hpp"

#include "Game/MainMgr.h"
#include "Game/PlayerMgr.h"
#include "Game/Player/Player.h"
#include "Cmn/PlayerCtrl.h"
#include "Cmn/StaticMem.h"
#include "Lp/Utl.h"

class Collector {
    public:
    static Controller Control;

    static Game::MainMgr* MainMgrInstance;
    static Cmn::StaticMem* StaticMemInstance;
    static Game::PlayerMgr* PlayerMgrInstance;
    static Cmn::PlayerCtrl* PlayerCtrlInstance;
    static Cmn::PlayerInfoAry* PlayerInfoAry;
    static Cmn::PlayerInfo* Collector::FirstPlayer;
    static Game::Player* Collector::ControlledPlayer;

    static void init();
    static void collect();
};