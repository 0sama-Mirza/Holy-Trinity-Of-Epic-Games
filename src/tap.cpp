#include "../includes/tap.h"
#include "../includes/globals.h"
#include <iostream>
#include <conio.h> 

tap::tap() : count1(0), count2(0), con1('C'), con2('C'), move('M') {
    x1 = 5;
    x2 = 5;
}

void tap::reset() {
    count1 = 0;
    count2 = 0;
    x1 = 5;
    x2 = 5;
    point1 = 0;
    point2 = 0;
}

void tap::select_controls() {
    std::cout << "---------------------------------";
    std::cout << "\nPlayer 1! Select Your Key: ";
    std::cin >> con1;
    std::cout << "Player 2! Select Your Key: ";
    std::cin >> con2;
    std::cout << "As soon as someone presses a key the game will begin\n";
    std::cout << "---------------------------------\n";
}

void tap::logic() {
    display();
    while (x1 < 10 && x2 < 10) {
       if(_kbhit()){
            int rawInput = _getch();
            move = static_cast<char>(rawInput);
            if (move == con1) {
                count1++;
                x1++;
                x2--;
                display();
            }
            if (move == con2) {
                count2++;
                x2++;
                x1--;
                display();
            }
        }
    }
}

bool tap::win() {
    return count1 > count2;
}

void tap::display() {
    std::cout << "#              #\n#";
    for (int j = 0; j <= (x1 - 1); j++) {
        std::cout << " ";
    }
    std::cout << "-><-";
    for (int k = 0; k <= (x2 - 1); k++) {
        std::cout << " ";
    }
    std::cout << "#\n#              #\n";
}

void tap::play() {
    std::cout << "\tWelcome to Tap! Tap! Tap! Tap! Tap! Tap!!!!\n\t\t\tTHE GAME!\n\n";
    std::cout << "\nThe Rule is Simple. You gotta push the other player to the boundary.\nSimple Right? Now go out there and start TAPPING!\n";
    std::cout << "---------------------------------------------------------------------\n\n\n";
    select_controls();
    logic();
    std::cout << "-------------------------------------------------\n";
    if (win()) {
        std::cout << "Player 2 " << p2_name << " Wins!";
        point2++;
        winname = p2_name;
        save_score();
    } else {
        std::cout << "Player 1 " << p1_name << " Wins!" << std::endl;
        point1++;
        winname = p1_name;
        save_score();
    }
    std::cout << "\nPlayer 1 " << p1_name << "'s Total Taps: " << count1;
    std::cout << "\nPlayer 2 " << p2_name << "'s Total Taps: " << count2 << std::endl;
}

void tap::save_score() {
    std::fstream myfile;
    if (count <= 0) {
        myfile.open("TapTap.txt", std::ios::out); // write
        if (myfile.is_open()) {
            myfile << "\t\tTap Tap Battle Records!\n";
            myfile << "Player 1" << "\t\t" << "Player 2\n";
            myfile.close();
            count++;
        }
    }
    myfile.open("TapTap.txt", std::ios::app); // append
    if (myfile.is_open()) {
        myfile << p1_name << " Score: " << point1 << "\t\t" << p2_name << " Score: " << point2 << std::endl;
        myfile << winname << " Wins!" << std::endl << std::endl;
        myfile.close();
    }
}
