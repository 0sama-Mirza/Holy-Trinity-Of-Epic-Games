#include "/home/baymax/Git-Projects/Holy-Trinity-Of-Epic-Games/headers/game.h"
#include "/home/baymax/Git-Projects/Holy-Trinity-Of-Epic-Games/headers/globals.h" // Include the globals.h header
#include<iostream>
game::game() : winname("Default"), count(0), point1(0), point2(0) {}

game::~game() {}

void setname() {
    std::cout << "Enter Player 1's Name: ";
    std::cin >> p1_name;
    std::cout << "\nEnter Player 2's Name: ";
    std::cin >> p2_name;
}
