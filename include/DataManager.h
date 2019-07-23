#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <nlohmann/json.hpp>
#include "Card.h"

#define VALIDATED_CARDS_LENGTH 3

class DataManager {
    public:
        DataManager();
        virtual ~DataManager();
        void loadCard();
        Card getInsertedCard();
        bool isCardValid();
        std::vector<std::string> moneyDetails;
        void withdrawMoney();
        double getBalanceInquiry();
    private:
        nlohmann::json currentCardData;
        Card insertedCard;
        Card validCards[VALIDATED_CARDS_LENGTH];
        void setMoneyDetails();
};


#endif // DATAMANAGER_H