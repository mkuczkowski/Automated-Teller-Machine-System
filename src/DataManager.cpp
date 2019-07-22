#include "DataManager.h"
#include <fstream>

DataManager::DataManager() {
    std::ifstream card("card.json");
    card >> this->currentCardData;
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
