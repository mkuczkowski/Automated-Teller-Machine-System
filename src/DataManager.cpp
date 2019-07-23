#include "DataManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iterator>

DataManager::DataManager() {
    std::ifstream card("card.json");
    card >> this->currentCardData;
    std::ifstream cards("valid-cards.json");
    nlohmann::json availableCards;
    cards >> availableCards;
    for(int i = 0; i < VALIDATED_CARDS_LENGTH; i++) {
        this->validCards[i].number = availableCards[i]["number"];
        this->validCards[i].cvc = availableCards[i]["CVC"];
        this->validCards[i].pin = availableCards[i]["PIN"];
    }
    setMoneyDetails();
}

DataManager::~DataManager() {}

void DataManager::loadCard() {
    this->insertedCard.number = this->currentCardData["number"].get<std::string>();
    this->insertedCard.cvc = this->currentCardData["CVC"].get<std::string>();
    this->insertedCard.pin = this->currentCardData["PIN"].get<std::string>();
}

Card DataManager::getInsertedCard() {
    return this->insertedCard;
}

bool DataManager::isCardValid() {
    size_t validCardsSize = sizeof(this->validCards) / sizeof(Card);
    Card* end = this->validCards + validCardsSize;
    Card* result = std::find(this->validCards, end, this->insertedCard);
    if (result != end) {
        std::cout << "* CARD VALIDATED SUCCESSFULLY *\n";
        return true;
    } else {
        std::cout << "INVALID CARD!\n";
        return false;
    }
}

void DataManager::setMoneyDetails() {
    std::ifstream file("money-details.txt");
    std::string line;
    if (file.is_open()) {
        while(getline(file,line))
            this->moneyDetails.push_back(line);
    }
    file.close();
}

double DataManager::getBalanceInquiry() {
    for (auto &detail : this->moneyDetails) {
        std::string number = detail.substr(0,19);
        if(number.compare(this->insertedCard.number) == 0) {
            std::string money = detail.substr(23, detail.length() - 23);
            return ::atof(money.c_str());
        }
    }
    return 0.0;
}

void DataManager::withdrawMoney() {
    double availableMoney = this->getBalanceInquiry();
    double amount;
    std::cout << "Type how much money You want to withdraw: ";
    std::cin >> amount;
    if(availableMoney - amount >= 0) {
        this->updateMoneyDetails(availableMoney - amount);
        std::cout << "\nTransaction completed successfully! Thank You for using our service\n";
    } else {
        std::cout << "Not enough money on Your account to do that!\n";
    }
    exit(0);
}

void DataManager::updateMoneyDetails(double valueToUpdate) {
    for (auto &detail : this->moneyDetails) {
        std::string number = detail.substr(0,19);
        if(number.compare(this->insertedCard.number) == 0) {
            detail.replace(23, detail.length() - 23, std::to_string(valueToUpdate));
            std::cout << detail;
        }
    }
    remove("money-details.txt");
    std::ofstream updatedFile("money-details.txt");
    std::ostream_iterator<std::string> fileIterator(updatedFile, "\n");
    std::copy(this->moneyDetails.begin(), this->moneyDetails.end(), fileIterator);
}
