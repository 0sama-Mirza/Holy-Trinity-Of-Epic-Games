#include <iostream>
#include "/home/baymax/Git-Projects/Holy-Trinity-Of-Epic-Games/headers/game.h" // Include game.h
#include "/home/baymax/Git-Projects/Holy-Trinity-Of-Epic-Games/headers/ttt.h"  // Include ttt.h
#include "/home/baymax/Git-Projects/Holy-Trinity-Of-Epic-Games/headers/snake.h" // Include snake.h
#include "/home/baymax/Git-Projects/Holy-Trinity-Of-Epic-Games/headers/tap.h" // Include tap.h
#include<unistd.h>//Sleep Function
std::string p1_name = "Player1";
std::string p2_name = "Player2";
int main(){
	int match=0;
	int totalscore1=0;
	int totalscore2=0;
    int roundscore1=0,roundscore2=0;
    char op='y';
	ttt TickCross;
	tap TapTapGame;
	snake s(40,20);
	setname();
    do{
	    std::cout<<"\n\n\nThis match will have 3 different games. You will begin by a small game of tick cross.\n";
	    do{
	    	std::cout<<"This match will not be over unless one of you wins more then 2 games then the other.\n";
	    	std::cout<<"\nPlayer 1 "<<p1_name<<" Total Score: "<<roundscore1<<std::endl;
	    	std::cout<<"Player 2 "<<p2_name<<" Total Score: "<<roundscore2<<std::endl;
	    	std::cout<<"\t\t\t\tRound Number: "<<++match<<std::endl<<std::endl;
        TickCross.play();
	    std::string stop;
        TapTapGame.play();
        std::cout<<"-------------------------------------------------";
            while(stop!="0"){
                std::cout<<"\nEnough!! To stop press the number 0: ";
                std::cin>>stop;
            }
        srand(static_cast<unsigned int>(time(NULL)));
        s.play();
        totalscore1=TickCross.point1+TapTapGame.point1+s.point1+totalscore1;
        totalscore2=TickCross.point2+TapTapGame.point2+s.point2+totalscore2;
        if(totalscore1>totalscore2)
            roundscore1++;
        else
            roundscore2++;
        totalscore1=0;
        totalscore2=0;
        s.reset();
        TapTapGame.reset();
        TickCross.reset();
	    }while(roundscore1!=3&&roundscore2!=3);
	    if(roundscore1>roundscore2){
	    	std::cout<<"Congrats!! Player 1 "<<p1_name<<" Wins The Match!!\nHere is your Reward"<<std::endl;
	    	sleep(1);
	    	std::cout<<"Absolutly Nothing :) You just wasted your time. Have a Nice Day.";
	    }
	    else{
	    	std::cout<<"Congrats!! Player 2 "<<p2_name<<" Wins THe Match!!\nHere is your Reward"<<std::endl;
	    	sleep(1);
	    	std::cout<<"Absolutly Nothing :) You just wasted your time. Have a Nice Day.";
        }
        std::cout<<"\nDo you want to Play Again?(Y/N): ";
        std::cin>>op;
    }while(op=='y'||op=='Y');
    return 0;
}
