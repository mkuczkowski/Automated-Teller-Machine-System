#include "Option.h"

Option::Option() {}

Option::Option(std::string information) {
    this->information = information;
    this->choiceValue = (int) information[0];
}

Option::~Option() {}

std::string Option::getInformation() {
    return this->information;
}

int Option::getChoiceValue() {
    return this->choiceValue;
}

void Option::setInformation(std::string information) {
    this->information = information;
}

void Option::setChoiceValue(int choiceValue) {
    this->choiceValue = choiceValue;
}

void Option::assignOption(std::string information) {
    this->information = information;
    this->choiceValue = (int) this->information[0];
}
