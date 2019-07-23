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

    private:
        nlohmann::json currentCardData;
        Card insertedCard;
        Card validCards[VALIDATED_CARDS_LENGTH];

};


#endif // DATAMANAGER_H
