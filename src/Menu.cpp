#include "Menu.h"
#include <iostream>

Menu::Menu() {
    options[0].assignOption("1. Cash withdrawal\n");
    options[1].assignOption("2. Deposit\n");
    options[2].assignOption("3. Balance Inquiry\n");
    options[3].assignOption("\n9. Exit\n");
}

Menu::~Menu() {}

void Menu::display() {
    std::cout << "*** Automated-Teller-Machine ***\n";
    std::cout << "Select transaction: \n\n";
    for(Option &option : this->options)
        std::cout << option.getInformation();
}

Option* Menu::getOptions() {
    return this->options;
}
