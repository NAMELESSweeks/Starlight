#include "main.hpp"

// rtld working object
__attribute__((section(".bss"))) rtld::ModuleObject __nx_module_runtime;

// Needed on old versions of rtld that doesn't check for DT_INIT existance.
extern "C" void __custom_init(void) {}

// DT_FINI here for completeness.
extern "C" void __custom_fini(void) {}

static agl::DrawContext *mDrawContext;
static sead::TextWriter *mTextWriter;
static SimpleMenu menu;
static int mode;
static bool showMenu;
static bool init = false;

// hook for gsys::SystemTask::invokeDrawTV_
void renderEntrypoint(agl::DrawContext *drawContext, sead::TextWriter *textWriter)
{
    mDrawContext = drawContext;
    mTextWriter = textWriter;

    if(!init){
        Collector::init();

        SimpleMenuEntry *entry1 = (SimpleMenuEntry*) malloc(sizeof(SimpleMenuEntry));
        SimpleMenuEntry *entry2 = (SimpleMenuEntry*) malloc(sizeof(SimpleMenuEntry));
        menu.entries.push_front(entry1);
        menu.entries.push_front(entry2);
    }
    Collector::collect();
    init = true;

    if(Collector::Control.isPressed(Controller::Buttons::Minus1))
        showMenu = !showMenu;

    textWriter->printf("showMenu: 0x%x", showMenu);

    if(showMenu){
        drawBackground();
        textWriter->setScaleFromFontHeight(20);
        sead::TextWriter::setupGraphics(drawContext); // re-setup context
        textWriter->printf("Starlight\n");
        
        menu.update();
        //menu.render(mTextWriter);
        /*drawBackground();
        
        textWriter->setScaleFromFontHeight(20);
        sead::TextWriter::setupGraphics(drawContext); // re-setup context

        textWriter->printf("Welcome to Starlight!\n");
        textWriter->printf("This is a demonstration of C/C++ code running in the context of a Switch game!\n");
        textWriter->printf("Credit to shibboleet, Khangaroo, Thog, Retr0id, and the libnx maintainers!\n");

        if(Collector::Control.isPressed(Controller::Buttons::RStick))
            mode++;
        if(mode > Modes::END)
            mode = 0;
        textWriter->printf("Current mode: %s\n", modeToText((Modes)mode));

        Game::MainMgr* mainMgr = Game::MainMgr::sInstance;
        if(mainMgr != NULL)
            handleMainMgr(mainMgr);

        Cmn::StaticMem *staticMem = Cmn::StaticMem::sInstance;
        if(staticMem != NULL)
            handleStaticMem(staticMem);

        Game::PlayerMgr *playerMgr = Game::PlayerMgr::sInstance;
        if(playerMgr != NULL)
            handlePlayerMgr(playerMgr);
            
        Cmn::PlayerCtrl *playerCtrl = Cmn::PlayerCtrl::sInstance;
        if(playerCtrl != NULL)
            handlePlayerControl(playerCtrl);
        else if(mode == Modes::INPUT_VIEWER){
            mTextWriter->printf("Information not available.\n");
        }

        Cmn::MushDataHolder* mushData = Cmn::MushDataHolder::sInstance;
        if(mushData != NULL)
            handleMushDataHolder(mushData);
            */
    }
    
    Collector::Control.update();
}

void drawBackground(){
    sead::Vector3<float> p1; // top left
    p1.mX = -1.0;
    p1.mY = 1.0;
    p1.mZ = 0.0;
    sead::Vector3<float> p2; // top right
    p2.mX = 0.0;
    p2.mY = 1.0;
    p2.mZ = 0.0;
    sead::Vector3<float> p3; // bottom left
    p3.mX = -1.0;
    p3.mY = -1.0;
    p3.mZ = 0.0;
    sead::Vector3<float> p4; // bottom right
    p4.mX = 0.0;
    p4.mY = -1.0;
    p4.mZ = 0.0;

    sead::Color4f c;
    c.r = 1.0;
    c.g = 1.0;
    c.b = 1.0;
    c.a = 0.5;

    agl::utl::DevTools::beginDrawImm(mDrawContext, sead::Matrix34<float>::ident, sead::Matrix44<float>::ident);
    agl::utl::DevTools::drawTriangleImm(mDrawContext, p1, p2, p3, c);
    agl::utl::DevTools::drawTriangleImm(mDrawContext, p3, p4, p2, c);
}

void handleMainMgr(Game::MainMgr* mainMgr){
    unsigned int paintGameFrame = mainMgr->getPaintGameFrame();
    Game::PaintUtl::requestAllPaintFloor(paintGameFrame, Cmn::Def::Team::Alpha);
}

void handleStaticMem(Cmn::StaticMem *staticMem){
    mTextWriter->printf("StaticMem ptr: 0x%x\n", staticMem);
    sead::BufferedSafeStringBase<char> *stageName = &staticMem->mMapFileName1;
    if(stageName->mCharPtr != NULL){
        mTextWriter->printf("Loaded stage: %s\n", stageName->mCharPtr);
    }
    
    Cmn::PlayerInfo* playerInfo = Collector::ControlledPlayerInfo;
    if(playerInfo != NULL){
        mTextWriter->printf("PlayerInfo[0] ptr: 0x%x\n", playerInfo);
        mTextWriter->printf("PlayerInfo[0] unk FC: 0x%x\n", playerInfo->dwordFC);
    }
}

void handlePlayerMgr(Game::PlayerMgr* playerMgr){
    if(Collector::ControlledPlayer != NULL)
    {
        mTextWriter->printf("Controlled player ptr: 0x%x\n", Collector::ControlledPlayer);
        Game::PlayerMotion *playerMotion = Collector::ControlledPlayer->motion;

        mTextWriter->printf("PlayerMotion ptr: 0x%x\n", playerMotion);

        if(mode == Modes::EVENT_VIEWER) {
            static long scroll = 0;

            if(Collector::Control.isPressed(Controller::Buttons::UpDpad))
                scroll++;
            if(Collector::Control.isPressed(Controller::Buttons::DownDpad))
                scroll--;

            if(Collector::Control.isPressed(Controller::Buttons::LeftDpad))
                scroll-=0x10;
            if(Collector::Control.isPressed(Controller::Buttons::RightDpad))
                scroll+=0x10;

            if(scroll < 0)
                scroll = 0;

            mTextWriter->printf("Event ID: 0x%x\n", scroll);

            if(Collector::Control.isPressed(Controller::Buttons::LStick))
                playerMotion->startEventAnim((Game::PlayerMotion::AnimID) scroll, 0, 1.0);

        } else if(mode == Modes::PLAYER_SWITCHER){

            //playerMgr->validAmountOfPlayers = 0xA;
            //playerMgr->validInfoNum = 0xA;

            signed int currentPlayer = playerMgr->currentPlayerIndex;
            mTextWriter->printf("Current player: %i\n", currentPlayer);

            if(Collector::Control.isPressed(Controller::Buttons::UpDpad))
                currentPlayer++;
            if(Collector::Control.isPressed(Controller::Buttons::DownDpad))
                currentPlayer--;
            if(currentPlayer < 0)
                currentPlayer = playerMgr->validAmountOfPlayers;
            if(playerMgr->validAmountOfPlayers <= currentPlayer)
                currentPlayer = 0;
            
            playerMgr->currentPlayerIndex = currentPlayer;
            playerMgr->onChangeControlledPlayer();
        }
    }
}

void handlePlayerControl(Cmn::PlayerCtrl* playerCtrl){
    Game::PlayerGamePadData::FrameInput input;
    input.record(); // grab input data

    if(mode == Modes::INPUT_VIEWER){
        mTextWriter->printf("Left stick | x: %f | y: %f\n", input.leftStick.mX, input.leftStick.mY);
        mTextWriter->printf("Right stick | x: %f | y: %f\n", input.rightStick.mX, input.rightStick.mY);
        mTextWriter->printf("Angle vel | x: %f | y: %f | z: %f\n", input.angleVel.mX, input.angleVel.mY, input.angleVel.mZ);
        mTextWriter->printf("Posture x | x: %f | y: %f | z: %f\n", input.postureX.mX, input.postureX.mY, input.postureX.mZ);
        mTextWriter->printf("Posture y | x: %f | y: %f | z: %f\n", input.postureY.mX, input.postureY.mY, input.postureY.mZ);
        mTextWriter->printf("Posture z | x: %f | y: %f | z: %f\n", input.postureZ.mX, input.postureZ.mY, input.postureZ.mZ);
    }

    static bool entered = false;
    if(mode == 1 && Collector::ControlledPlayer != NULL){
        static float x, y, z;
        sead::Vector3<float> *playerPos = &Collector::ControlledPlayer->position;
        if(!entered){
            x = playerPos->mX;
            y = playerPos->mY;
            z = playerPos->mZ;
        }

        int speed = 10;

        if(Collector::Control.isHeld(Controller::Buttons::UpDpad))
            y+=speed;
        if(Collector::Control.isHeld(Controller::Buttons::DownDpad))
            y-=speed;
        if(Collector::Control.isHeld(Controller::Buttons::LeftDpad))
            x+=speed;
        if(Collector::Control.isHeld(Controller::Buttons::RightDpad))
            x-=speed;
        if(Collector::Control.isHeld(Controller::Buttons::RightRStickOrdinal))
            z+=speed;
        if(Collector::Control.isHeld(Controller::Buttons::LeftRStickOrdinal))
            z-=speed;

        playerPos->mX = x;
        playerPos->mY = y;
        playerPos->mZ = z;
        entered = true;
    } else {
        entered = false;
    }
}

void handleMushDataHolder(Cmn::MushDataHolder* mushDataHolder){
    static bool entered = false;
    if(!entered){
        for(int i = 0; i < 29001; i++){
            Cmn::WeaponData* data = Collector::MushWeaponInfo->getById(Cmn::Def::WeaponKind::cMain, i);
            if(data != NULL){
                data->mPrice = 0;
                data->mRank = 0;
                data->mSpecialCost = 0;
                data->mLockType = Cmn::WeaponData::LockType::NotForSale;
            }
        }

        for(int i = 0; i < 230; i++){
            Cmn::MushMapInfo::Data* mapData = Collector::MushMapInfo->getByMushOrder(i);
            if(mapData != NULL){
                mapData->mEnvHour = 2;
            }
        }

        entered = true;
    }

}

char const* modeToText(Modes mode){
    switch(mode){
        case Modes::NONE:
            return "None";
        case Modes::FLY:
            return "Fly";
        case Modes::EVENT_VIEWER:
            return "Event viewer";
        case Modes::INPUT_VIEWER:
            return "Gyro/stick input viewer";
        case Modes::PLAYER_SWITCHER:
            return "Player switcher";
        default:
            return "None";
    }
}

int main(int arg, char **argv){

}