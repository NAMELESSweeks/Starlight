
#include "collector.hpp"

Controller Collector::Control;

// Managers
Game::MainMgr* Collector::MainMgrInstance;
Game::PlayerMgr* Collector::PlayerMgrInstance;

// Utils
Cmn::StaticMem* Collector::StaticMemInstance;

// Player Information
Game::Player* Collector::ControlledPlayer;
Cmn::PlayerInfo* Collector::FirstPlayer;
Cmn::PlayerCtrl* Collector::PlayerCtrlInstance;
Cmn::PlayerInfoAry* Collector::PlayerInfoAry;

// Mush
Cmn::MushDataHolder* Collector::MushDataHolder;
Cmn::MushWeaponInfo* Collector::MushWeaponInfo;
Cmn::MushMapInfo* Collector::MushMapInfo;

void Collector::init() {
    Control.mController = Lp::Utl::getCtrl(0);
}

void Collector::collect(){
    MainMgrInstance = Game::MainMgr::sInstance;
    StaticMemInstance = Cmn::StaticMem::sInstance;
    PlayerMgrInstance = Game::PlayerMgr::sInstance;
    PlayerCtrlInstance = Cmn::PlayerCtrl::sInstance;
    MushDataHolder = Cmn::MushDataHolder::sInstance;

    if(StaticMemInstance){
        PlayerInfoAry = StaticMemInstance->playerInfoArray;
        FirstPlayer = PlayerInfoAry->infos[0];
    } else {
        PlayerInfoAry = NULL;
    }

    if(PlayerMgrInstance){
        ControlledPlayer = PlayerMgrInstance->getControlledPerformer();
    } else {
        ControlledPlayer = NULL;
    }
    
    if(MushDataHolder){
        MushWeaponInfo = MushDataHolder->mushWeaponInfo;
        MushMapInfo = MushDataHolder->mushMapInfo;
    } else {
        MushWeaponInfo = NULL;
        MushMapInfo = NULL;
    }
}