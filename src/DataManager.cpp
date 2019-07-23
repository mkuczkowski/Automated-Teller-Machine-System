#include "DataManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>

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
