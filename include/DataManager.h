#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <nlohmann/json.hpp>
#include "Card.h"

class DataManager {
    public:
        DataManager();
        virtual ~DataManager();
        void loadCard();
        Card getInsertedCard();
    private:
        nlohmann::json currentCardData;
        Card insertedCard;
};

#endif // DATAMANAGER_H
