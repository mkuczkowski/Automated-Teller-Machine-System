#ifndef DISPLAYPANEL_H
#define DISPLAYPANEL_H

class DisplayPanel {
    public:
        virtual ~DisplayPanel() {};
        virtual void display() = 0;
};

#endif // DISPLAYPANEL_H
