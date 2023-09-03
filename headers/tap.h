#ifndef TAP_H
#define TAP_H

#include "position.h"
#include <fstream>

class tap : public position {
protected:
    int count1;
    int count2;
    char con1;
    char con2;
    char move;

public:
    tap();
    void reset();
    void select_controls();
    void logic();
    bool win();
    void display();
    void play();
    void save_score();
};

#endif // TAP_H
