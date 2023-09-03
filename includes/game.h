#ifndef GAME_H
#define GAME_H

#include <string>

class game {
protected:
    std::string winname;
    int count;

public:
    int point1;
    int point2;
    game();
    virtual ~game();
    virtual void reset() = 0;
    virtual void display() = 0;
    virtual void logic() = 0;
    virtual bool win() = 0;
    virtual void save_score() = 0;
    virtual void play() = 0;
    friend void setname(std::string& p1_name, std::string& p2_name);
};

#endif // GAME_H