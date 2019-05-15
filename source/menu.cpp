#include "menu.hpp"

void SimpleMenu::update() {
    // handle inputs
    if(Collector::Control.isPressed(Controller::Buttons::UpDpad))
        selectedIndex++;
    if(Collector::Control.isPressed(Controller::Buttons::UpDpad))
        selectedIndex--;

    // handle under/overflow
    if(selectedIndex < 0)
        selectedIndex = entries.size()-1;
    if((unsigned int)selectedIndex > entries.size())
        selectedIndex = 0;

    // update entries
    std::list<MenuEntry*>::iterator it;
    int i = 0;
    for (it = entries.begin(); it != entries.end(); ++it){
        MenuEntry* entry = *it;
        entry->update();
        if(Collector::Control.isPressed(Controller::Buttons::LStick))
            if(i == selectedIndex)
                entry->selected(this);
        i++;
    }
}

void SimpleMenu::render(sead::TextWriter* textWriter){
    int i = 0;
    std::list<MenuEntry*>::iterator it;
    for (it = entries.begin(); it != entries.end(); ++it){
        MenuEntry* entry = *it;
        const char* prefix = "   ";
        if(i == selectedIndex){
            prefix = " > ";
        }
        
        textWriter->printf(prefix);
        entry->render(textWriter);

        i++;
    }
}

void SimpleMenuEntry::update() {

}

void SimpleMenuEntry::render(sead::TextWriter* textWriter){
    textWriter->printf("bruh\n");
}

void SimpleMenuEntry::selected(Menu* menu){

}