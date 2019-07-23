#include "Menu.h"
#include <iostream>
#include <chrono>
#include <thread>

Menu::Menu() {
    this->options[0].assignOption("1. Cash withdrawal\n");
    this->options[1].assignOption("2. Deposit\n");
    this->options[2].assignOption("3. Balance Inquiry\n");
    this->options[3].assignOption("\n9. Exit\n");
}

Menu::~Menu() {}

void Menu::showTransactions() {
    std::cout << "*** Automated-Teller-Machine ***\n";
    std::cout << "Select transaction: \n\n";
    for(Option &option : this->options)
        std::cout << option.getInformation();
}

Option* Menu::getOptions() {
    return this->options;
}

void Menu::showHomeScreen() {
    std::cout << "*** Automated-Teller-Machine ***\n";
    std::cout << "Please insert credit/debit card\n";
    std::cout << "\n1. Insert (card.json)\n";
    std::cout << "\n9. Exit\n";
    int choice;
    while(choice != 1 || choice != 9) {
        std::cin >>  choice;
        switch(choice) {
        case 1:
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            this->manager.loadCard();
            std::cout << "Loading...";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            system("cls");
            this->manager.isCardValid() ? this->showTransactions() : exit(0);
            return;
        case 9:
            exit(0);
            break;
        default:
            std::cout << "Incorrect option! Please try again:\n";
            break;
        }
    }
}
