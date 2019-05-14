#include "input.hpp"


Controller::Controller() {}

Controller::Controller(Lp::Sys::Ctrl *controller){
    mController = controller;
}

void Controller::update(){
    mLastPoll = mController->data;
}

bool Controller::isHeld(Buttons inputs) {
    return mController->data & inputs;
}

bool Controller::isPressed(Buttons inputs) {
    bool buttonHeld = mController->data & inputs;
    return buttonHeld & !(mController->data & mLastPoll & inputs);
}