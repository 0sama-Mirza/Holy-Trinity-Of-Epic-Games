#ifndef TTT_H
#define TTT_H

#include "game.h" // Include the base class header

class ttt : public game {
protected:
    char matrix[3][3];
    char player;
    int gameover;

public:
    ttt(); // Constructor declaration
    void reset();
    void display();
    void input();
    void logic();
    bool win();
    void save_score();
    void play();
};

#endif // TTT_H
