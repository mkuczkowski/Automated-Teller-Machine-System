#ifndef OPTION_H
#define OPTION_H
#include <string>

class Option {
    public:
        Option();
        Option(std::string);
        virtual ~Option();
        std::string getInformation();
        uint8_t getChoiceValue();
        void setInformation(std::string);
        void setChoiceValue(uint8_t);
        void assignOption(std::string);

    protected:

    private:
        std::string information;
        uint8_t choiceValue;
};

#endif // OPTION_H
