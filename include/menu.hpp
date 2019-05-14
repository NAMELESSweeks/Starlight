#pragma once

#include <list>
#include "collector.hpp"
#include "sead/textwriter.h"

 class Menu {
    public:

    virtual void update() = 0;
    virtual void render(sead::TextWriter*) = 0;
};

class MenuEntry {
    public:

    virtual void update() = 0;
    virtual void render(sead::TextWriter*) = 0;
    virtual void selected(Menu*) = 0;
};

class SimpleMenuEntry : public MenuEntry {
    public: 
    void update();
    void render(sead::TextWriter*);
    void selected(Menu*);
};

class SimpleMenu : public Menu {
    public:
    std::list<MenuEntry*> entries;
    signed int selectedIndex;

    void update();
    void render(sead::TextWriter*);
};