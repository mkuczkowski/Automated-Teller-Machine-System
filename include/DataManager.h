#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <nlohmann/json.hpp>
#include "Card.h"

#define VALIDATED_CARDS_LENGTH 3
#define AVAILABLE_BILLS_LENGTH 6

class DataManager {
    public:
        DataManager();
        virtual ~DataManager();
        void loadCard();
        Card getInsertedCard();
        bool isCardValid();
        void withdrawMoney();
        void depositMoney();
        void transferMoney();
        double getBalanceInquiry() const;
    private:
        nlohmann::json currentCardData;
        Card insertedCard;
        Card validCards[VALIDATED_CARDS_LENGTH];
        void setMoneyDetails();
        void updateMoneyDetails(double, std::string);
        std::string getCurrentDateTime(bool) const;
        void createReceipt(double, double);
        std::vector<std::string> moneyDetails;
        int getMinNumberOfBills(int);
        int bills[AVAILABLE_BILLS_LENGTH];
        bool isAccountCorrect(std::string);
        std::string convertAccountNumber(const std::string&);
};


#endif // DATAMANAGER_H
