#ifndef CARD_H
#define CARD_H

struct Card {
    std::string number;
    std::string cvc;
    std::string pin;
    bool operator == (const Card &cardToCompare) const {
        if(cardToCompare.cvc == this->cvc &&
           cardToCompare.number == this->number &&
           cardToCompare.pin == this->pin)
            return true;
        else
            return false;
    }
};

#endif // CARD_H
