#include "DataManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <time.h>

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
    this->setMoneyDetails();
    int availableBills[] = {500, 200, 100, 50, 20, 10};
    for(int i = 0; i < AVAILABLE_BILLS_LENGTH; i++)
        this->bills[i] = availableBills[i];
}

DataManager::~DataManager() {
    this->insertedCard.number.clear();
    this->insertedCard.cvc.clear();
    this->insertedCard.pin.clear();
    this->currentCardData = nullptr;
}

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
    if(file.is_open()) {
        while(getline(file,line))
            this->moneyDetails.push_back(line);
    }
    file.close();
}

double DataManager::getBalanceInquiry() const {
    for(auto &detail : this->moneyDetails) {
        std::string number = detail.substr(0,19);
        if(number.compare(this->insertedCard.number) == 0) {
            std::string money = detail.substr(23, detail.length() - 23);
            return ::atof(money.c_str());
        }
    }
    return 0.0;
}

void DataManager::withdrawMoney() {
    auto availableMoney = this->getBalanceInquiry();
    int amount;
    std::cout << "Type how much money You want to withdraw: ";
    std::cin >> amount;
    while(amount % 10 != 0) {
        std::cout << "Incorrect amount! Available bills in ATM: : ";
        for(auto &bill : this->bills)
            std::cout << bill << " ";

        std::cout << "\nPlease type a correct amount: ";
        std::cin >> amount;
    }
    if(availableMoney - amount >= 0) {
        this->updateMoneyDetails(double(availableMoney - amount));
        std::cout << "\nBills printed: " << this->getMinNumberOfBills(amount);
        std::cout << "\nTransaction completed successfully! Thank You for using our service\n";
        this->createReceipt(availableMoney, double (availableMoney - amount));
    } else {
        std::cout << "Not enough money on Your account to do that!\n";
    }
    exit(0);
}

void DataManager::depositMoney() {
    auto currentAmount = this->getBalanceInquiry();
    double amountToDeposit;
    std::cout << "Type how much money You want to deposit: ";
    std::cin >> amountToDeposit;
    this->updateMoneyDetails(amountToDeposit + currentAmount);
    std::cout << "\nMoney has been transfered to your account\n";
    this->createReceipt(currentAmount, amountToDeposit + currentAmount);
    exit(0);
}

void DataManager::updateMoneyDetails(double valueToUpdate) {
    for(auto &detail : this->moneyDetails) {
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
    updatedFile.close();
}

std::string DataManager::getCurrentDateTime(bool isFileName) const {
    time_t now = time(0);
    struct tm tstruct;
    char buffer[80];
    tstruct = *localtime(&now);
    std::string format = isFileName ? "%Y%m%d%X" : "%Y-%m-%d %X";
    strftime(buffer, sizeof(buffer), format.c_str(), &tstruct);
    return buffer;
}

void DataManager::createReceipt(double balanceBefore, double balanceAfter) {
    std::string fileName = "Receipt ";
    fileName.append(this->getCurrentDateTime(true));
    fileName.erase(std::remove(fileName.begin(), fileName.end(), ':'), fileName.end());
    fileName.append(".txt");
    std::ofstream receipt;
    receipt.open(fileName.c_str(), std::ios::app);
    if(!receipt.is_open()) {
        std::cerr << "Cannot create receipt: " << strerror(errno);
    } else {
        receipt << "Transaction date: " << this->getCurrentDateTime(false) << std::endl;
        receipt << "Account no. : " << this->insertedCard.number << std::endl;
        receipt << "Balance before transaction: " << std::to_string(balanceBefore) << std::endl;
        receipt << "Current account balance: " << std::to_string(balanceAfter) << std::endl;
        std::cout << "Receipt created: " << fileName << std::endl;
    }
    receipt.close();
}

int DataManager::getMinNumberOfBills(int requiredMoney) {
    if(requiredMoney == 0) return 0;
    int result = INT_MAX;
    for(auto &bill : this->bills) {
        if(bill <= requiredMoney) {
            int subResult = getMinNumberOfBills(requiredMoney - bill);
            if(subResult != INT_MAX && subResult + 1 < result)
                result = subResult + 1;
        }
    }
    return result;
}
