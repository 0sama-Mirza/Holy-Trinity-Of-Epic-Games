#ifndef SNAKE_H
#define SNAKE_H
#include "globals.h"
#include "position.h" // Include the base class header
#include <vector>

class snake : public position {
protected:
    bool gameOver;
    int width;
    int height;
    int fruitX, fruitY, score1, score2;
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN, LEFTT, RIGHTT, UPP, DOWNN };
    eDirection dir, dir2;
    std::vector<int> TailX1, TailY1, TailX2, TailY2;

public:
    snake(int w, int h); // Constructor declaration
    void reset();
    void logic();
    void Input();
    bool win();
    void display();
    void save_score();
    void play();
};

#endif // SNAKE_H
