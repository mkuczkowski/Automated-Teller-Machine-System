#include "Option.h"

Option::Option() {}

Option::Option(std::string information) {
    this->information = information;
    this->choiceValue = (uint8_t) information[0];
}

Option::~Option() {}

std::string Option::getInformation() {
    return this->information;
}

uint8_t Option::getChoiceValue() {
    return this->choiceValue;
}

void Option::setInformation(std::string information) {
    this->information = information;
}

void Option::setChoiceValue(uint8_t choiceValue) {
    this->choiceValue = choiceValue;
}

void Option::assignOption(std::string information) {
    this->information = information;
    this->choiceValue = (uint8_t) this->information[0];
}
