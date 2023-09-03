#include "../includes/ttt.h"
#include "../includes/globals.h"
#include <iostream>
#include <fstream>
ttt::ttt()
    : player('X'), gameover(0) {
    matrix[0][0] = '1';
    matrix[0][1] = '2';
    matrix[0][2] = '3';
    matrix[1][0] = '4';
    matrix[1][1] = '5';
    matrix[1][2] = '6';
    matrix[2][0] = '7';
    matrix[2][1] = '8';
    matrix[2][2] = '9';
    point1 = 0;
    point2 = 0;
    count = 0;
}
void ttt::reset(){	
			matrix[0][0]='1';
    		matrix[0][1]='2';
			matrix[0][2]='3';
			matrix[1][0]='4';
    		matrix[1][1]='5';
    		matrix[1][2]='6';
    		matrix[2][0]='7';
			matrix[2][1]='8';
    		matrix[2][2]='9';
    		player='X';
    		point1=0;
    		point2=0;
		}
void ttt::display(){
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					std::cout<<matrix[i][j];
           			if(j<2)
               			std::cout<<" | ";
				}
				std::cout<<std::endl;
        		if(i<2)
            		std::cout<<"----------"<<std::endl;
			}	
		}
void ttt::input(){
		char a;
		if(player=='X')
			std::cout<<"Player 1 "<<p1_name<<"'s turn\n";
		else if(player=='O')
			std::cout<<"Player 2 "<<p2_name<<"'s turn\n";
        abc:
		std::cout<<"Select Region To Tick: ";
			std::cin>>a;
			if(a=='1'&&matrix[0][0]=='1')
				matrix[0][0]=player;
			else if(a=='2'&&matrix[0][1]=='2')
				matrix[0][1]=player;
			else if(a=='3'&&matrix[0][2]=='3')
				matrix[0][2]=player;
			else if(a=='4'&&matrix[1][0]=='4')
				matrix[1][0]=player;
			else if(a=='5'&&matrix[1][1]=='5')
				matrix[1][1]=player;
			else if(a=='6'&&matrix[1][2]=='6')
				matrix[1][2]=player;
			else if(a=='7'&&matrix[2][0]=='7')
				matrix[2][0]=player;
			else if(a=='8'&&matrix[2][1]=='8')
				matrix[2][1]=player;
			else if(a=='9'&&matrix[2][2]=='9')
				matrix[2][2]=player;	
            else{
                std::cout<<"You Cannot Mark on the same place twice! Again ";
                goto abc;
            }
		}
void ttt::logic(){
        	if(player=='X')
				player='O';
			else
				player='X';
		}
bool ttt::win(){
        	//first player
			if (matrix[0][0] == 'X' && matrix[0][1] == 'X' && matrix[0][2] == 'X'){
				gameover=1;
				return 1;
			}
			 if (matrix[1][0] == 'X' && matrix[1][1] == 'X' && matrix[1][2] == 'X'){
				gameover=1;
				return 1;
			}
			if (matrix[2][0] == 'X' && matrix[2][1] == 'X' && matrix[2][2] == 'X'){
				gameover=1;
				return 1;
			}
			 if (matrix[0][0] == 'X' && matrix[1][0] == 'X' && matrix[2][0] == 'X'){
			 	gameover=1;
				return 1;
			}
			if (matrix[0][1] == 'X' && matrix[1][1] == 'X' && matrix[2][1] == 'X'){
				gameover=1;
				return 1;
			}
			 if (matrix[0][2] == 'X' && matrix[1][2] == 'X' && matrix[2][2] == 'X'){
			 	gameover=1;
				return 1;
			}
			 if (matrix[0][0] == 'X' && matrix[1][1] == 'X' && matrix[2][2] == 'X'){
			 	gameover=1;
				return 1;
				
			}
			 if (matrix[2][0] == 'X' && matrix[1][1] == 'X' && matrix[0][2] == 'X'){
			 	gameover=1;
				return 1;
			}
			//second player
			 if (matrix[0][0] == 'O' && matrix[0][1] == 'O' && matrix[0][2] == 'O'){
			 	gameover=2;
				return 1;
			}
			 if (matrix[1][0] == 'O' && matrix[1][1] == 'O' && matrix[1][2] == 'O'){
			 	gameover=2;
				return 1;
			}
			 if (matrix[2][0] == 'O' && matrix[2][1] == 'O' && matrix[2][2] == 'O'){
			 	gameover=2;
				return 1;
			}
			 if (matrix[0][0] == 'O' && matrix[1][0] == 'O' && matrix[2][0] == 'O'){
			 	gameover=2;
				return 1;
			}
			 if (matrix[0][1] == 'O' && matrix[1][1] == 'O' && matrix[2][1] == 'O'){
			 	gameover=2;
				return 1;
			}
			 if (matrix[0][2] == 'O' && matrix[1][2] == 'O' && matrix[2][2] == 'O'){
			 	gameover=2;
				return 1;
			}
			 if (matrix[0][0] == 'O' && matrix[1][1] == 'O' && matrix[2][2] == 'O'){
			 	gameover=2;
				return 1;
			}
			 if (matrix[2][0] == 'O' && matrix[1][1] == 'O' && matrix[0][2] == 'O'){
			 	gameover=2;
				return 1;
			}
			else if(matrix[0][0]!='1'&&matrix[0][1]!='2'&&matrix[0][2]!='3'&&matrix[1][0]!='4'&&matrix[1][1]!='5'&&matrix[1][2]!='6'&&matrix[2][0]!='7'&&matrix[2][1]!='8'&&matrix[2][2]!='9'){
				gameover=3;
                return 0;
			}
			else
				gameover=0;
                return 0;
		}
void ttt::save_score(){
			std::fstream myfile;
			if(count<=0){
				myfile.open("TicTacToe.txt",std::ios::out);//overwrite
				if(myfile.is_open()){
					myfile<<"\t\tTick Corss Battle Records!\n";
					myfile<<"Player 1"<<"\t\t"<<"Player 2\n";
					myfile.close();
					count++;
				}
			}
			myfile.open("TicTacToe.txt",std::ios::app);//append
				if(myfile.is_open()){
					myfile<<p1_name<<" Score: "<<point1<<"\t\t"<<p2_name<<" Score: "<<point2<<std::endl;
					myfile<<winname<<" Wins!"<<std::endl<<std::endl;
					myfile.close();	
				}
		}

void ttt::play(){
        	display();
				while (true){
					input();
					display();
					if (win()&&gameover==2){
						std::cout <<"Player 2 "<<p2_name<<" wins!" << std::endl;
						point2++;
						winname=p2_name;
						save_score();
						break;
					}
					else if (win()&&gameover==1){
						std::cout <<"Player 1 "<<p1_name<<" wins!" << std::endl;
						point1++;
						winname=p1_name;
						save_score();
						break;
					}
					else if(gameover==3){
						std::cout<<"Its a Draw!. Proceed to the next game.\n";
                        break;
					}
					logic();
				}	
		}			