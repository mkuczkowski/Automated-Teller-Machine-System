#ifndef MENU_H
#define MENU_H
#include "DisplayPanel.h"
#include "Option.h"

#define OPTIONS_LENGTH 4

class Menu : public DisplayPanel {
    public:
        Menu();
        virtual ~Menu();
        virtual void display();
        Option* getOptions();
    protected:

    private:
        Option options[OPTIONS_LENGTH];
};

#endif // MENU_H
