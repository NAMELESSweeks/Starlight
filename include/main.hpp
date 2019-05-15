#pragma once

#include "svc.h"
#include "types.h"
#include "agl/lyr/renderinfo.h"
#include "agl/utl/devtools.h"
#include "sead/textwriter.h"
#include "sead/string.h"
#include "sead/heap.h"
#include "sead/matrix.h"
#include "Cmn/StaticMem.h"
#include "Cmn/PlayerInfoUtil.h"
#include "Cmn/PlayerCtrl.h"
#include "Cmn/Mush/MushDataHolder.h"
#include "Cmn/Def/util.h"
#include "Lp/Utl.h"
#include "Lp/Sys/ctrl.h"
#include "Game/Utl.h"
#include "Game/PlayerGamePadData/FrameInput.h"
#include "Game/Player/PlayerMotion.h"
#include "Game/Player/Player.h"
#include "Game/PaintUtl.h"
#include "Game/PlayerMgr.h"
#include "Game/MainMgr.h"
#include "ModuleObject.hpp"
#include "collector.hpp"
#include "menu.hpp"
#include "alloc.h"

enum Modes {
    NONE, FLY, EVENT_VIEWER, INPUT_VIEWER,  PLAYER_SWITCHER, END
};

void render(agl::DrawContext *drawContext, sead::TextWriter *textWriter);
bool isTriggered(Lp::Sys::Ctrl *controller, unsigned long id);

void drawBackground();
void handleMainMgr(Game::MainMgr* mainMgr);
void handleStaticMem(Cmn::StaticMem *staticMem);
void handlePlayerMgr(Game::PlayerMgr* playerMgr);
void handlePlayerControl(Cmn::PlayerCtrl* playerCtrl);
void handleMushDataHolder(Cmn::MushDataHolder* mushDataHolder);
void handleMainMgr(Game::MainMgr* mainMgr);

char const* modeToText(Modes);



