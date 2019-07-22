#ifndef MENU_H
#define MENU_H
#include "Option.h"
#include "DataManager.h"

#define OPTIONS_LENGTH 4

class Menu {
    public:
        Menu();
        virtual ~Menu();
        void showHomeScreen();
        Option* getOptions();
    private:
        Option options[OPTIONS_LENGTH];
        void showTransactions();
        DataManager manager;
};

#endif // MENU_H
