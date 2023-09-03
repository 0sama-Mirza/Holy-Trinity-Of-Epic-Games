#ifndef POSITION_H
#define POSITION_H

#include "game.h"

class position : public game {
protected:
    int x1;
    int x2;
    int y1;
    int y2;

public:
    position();
    ~position();
};

#endif // POSITION_H
