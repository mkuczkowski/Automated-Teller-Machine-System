#ifndef OPTION_H
#define OPTION_H
#include <string>

class Option {
    public:
        Option();
        Option(std::string);
        virtual ~Option();
        std::string getInformation();
        int getChoiceValue();
        void setInformation(std::string);
        void setChoiceValue(int);
        void assignOption(std::string);
    private:
        std::string information;
        int choiceValue;
};

#endif // OPTION_H
