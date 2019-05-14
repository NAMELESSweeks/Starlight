
#include "collector.hpp"

Controller Collector::Control;

Game::MainMgr* Collector::MainMgrInstance;
Cmn::StaticMem* Collector::StaticMemInstance;
Game::PlayerMgr* Collector::PlayerMgrInstance;
Cmn::PlayerCtrl* Collector::PlayerCtrlInstance;
Cmn::PlayerInfoAry* Collector::PlayerInfoAry;
Cmn::PlayerInfo* Collector::FirstPlayer;
Game::Player* Collector::ControlledPlayer;

void Collector::init() {
    Control.mController = Lp::Utl::getCtrl(0);
}

void Collector::collect(){
    MainMgrInstance = Game::MainMgr::sInstance;
    StaticMemInstance = Cmn::StaticMem::sInstance;
    PlayerMgrInstance = Game::PlayerMgr::sInstance;
    PlayerCtrlInstance = Cmn::PlayerCtrl::sInstance;

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
    
    
}