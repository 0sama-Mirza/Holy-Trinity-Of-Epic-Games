#include "../includes/snake.h"
#include <iostream>
#include<fstream>
#include <unistd.h> // For usleep (Linux)
// #include <windows.h> // For Sleep (Windows)
#include "../includes/kbhit.h"
snake::snake(int w,int h)
            : gameOver(false), 
              width(w), 
              height(h), 
              fruitX(0), 
              fruitY(0), 
              score1(0), 
              score2(0), 
              dir(STOP), 
              dir2(STOP), 
              TailX1(static_cast<size_t>(w * h), 0),
              TailY1(static_cast<size_t>(w * h), 0),
              TailX2(static_cast<size_t>(w * h), 0),
              TailY2(static_cast<size_t>(w * h), 0) {
            count=0;
            point1=0;
            point2=0;
            x1=(width-10)/4;
            y1=(height-10)/4;
            x2=(width-10)/2;
            y2=(height-10)/2;
            fruitX=1+(rand()%(width-1));
            fruitY=1+(rand()%(height-2));
        }
void snake::reset(){
            gameOver=false;
            point1=0;
            point2=0;
            for(size_t i=0;i<static_cast<size_t>(width*height);i++){
                TailX1[i]=0;
                TailX2[i]=0;
                TailY1[i]=0;
                TailY2[i]=0;
            }
            dir= STOP;
            dir2= STOP;
            x1=(width-10)/4;
            y1=(height-10)/4;
            x2=(width-10)/2;
            y2=(height-10)/2;
            fruitX=1+(rand()%(width-1));
            fruitY=1+(rand()%(height-2));
            score1=0;
            score2=0;   
        }
void snake::logic(){
            for(size_t i=static_cast<size_t>(score1);i>0;i--){
                TailX1[i] = TailX1[i - 1];
                TailY1[i] = TailY1[i - 1];
            }
            TailX1[0]=x1;
            TailY1[0]=y1;
            for(size_t i=static_cast<size_t>(score2);i>0;i--){
                TailX2[i]=TailX2[i - 1];
                TailY2[i]=TailY2[i - 1];
            }
            TailX2[0]=x2;
            TailY2[0]=y2;
            switch (dir){
        //#####################Player 1's Logic#######################
                case LEFT:
                    x1--;
                    break;
                case RIGHT:
                    x1++;
                    break;
                case UP:
                    y1--;
                    break;
                case DOWN:
                    y1++;
                    break;
                case STOP:
                    break;
                default:
                    break;
            }
        //#############Player 2's Logic################################
            switch(dir2){
                case LEFTT:
                    x2--;
                    break;
                case RIGHTT:
                    x2++;
                    break;
                case UPP:
                    y2--;
                    break;
                case DOWNN:
                    y2++;
                    break;
                case STOP:
                    break;
                default:
                    break;
            }
            win();
            if(x1==fruitX&&y1==fruitY){
                score1++;
                fruitX=1+(rand()%(width-1));
        		fruitY=1+(rand()%(height-2));
            }
            else if(x2==fruitX&&y2==fruitY){
                score2++;
                fruitX=1+(rand()%(width-1));
        		fruitY=1+(rand()%(height-2));
            }
        }
void snake::Input(){
            if(kbhit()){//just kbhit for Linux
            //###Only For Linux
            
                char op;
                std::cin>>op;
                switch (op){
            
            //##End Of Linux
            
            //###Only For Windows
            //switch(_getch()){
            //###End Of Windows
        //##########################Player 1's Controls####################
                    case 'a':
                        dir=LEFT;
                        break;
                    case 's':
                        dir=DOWN;
                        break;
                    case 'd':
                        dir=RIGHT;
                        break;
                    case 'w':
                        dir=UP;
                        break;
        //##########################Player 2's Controls##############
                    case 'j':
                        dir2=LEFTT;
                        break;
                    case 'k':
                        dir2=DOWNN;
                        break;
                    case 'l':
                        dir2=RIGHTT;
                        break;
                    case 'i':
                        dir2=UPP;
                        break;
                    case 'x':
                        gameOver= true;
                        break;
                }
            }
        }
bool snake::win(){
            if(x1>=width||x1<=0||y1>height-2||y1<=0){
                gameOver=true;
                return 1;
            }
            else if(x2>=width||x2<=0||y2>height-2||y2<=0){
                gameOver=true;
                return 0;
            }
            if(x1==x2&&y1==y2){
		gameOver=true;
                if(score1>score2)
                    return 0;
                else
                    return 1;
            }
            for(size_t i=static_cast<size_t>(score1);i>0;i--){
		gameOver=true;
                if(x1==TailX2[i]&&y1==TailY2[i])
                    return 1;
                else if(x2==TailX1[i]&&y2==TailY1[i])
                    return 0;
            }
            gameOver=false;
            return 0;
        }
void snake::display(){
            system("clear");//For Linux
			//system("cls"); //For Windows
            std::cout<<"\nFruit's Coordinates: ("<<fruitX<<","<<fruitY<<")\n";
            for(int i=0;i<height;i++){
                if(i==0||i==height-1){
                    for(int j=0;j<width+1;j++)
                        std::cout<<"#";
                }
                else{
                    std::cout<<"#";
                        int spaces=1;
                        while(spaces!=width){
                            if(i==y1&&spaces==x1){
                                std::cout<<"1";
                            }
                            else if(i==y2&&spaces==x2){
                                std::cout<<"2";
                            }
                            else if(i==fruitY&&spaces==fruitX){
                                std::cout<<"F";
                            }
                            else{
                                bool print=false;
                                for(size_t k=0;k<static_cast<size_t>(score1);k++){
                                    if(TailX1[k]==spaces&&TailY1[k]==i){
                                        std::cout<<"o";
                                        print=true;
                                    }
                                }
                                for(size_t k=0;k<static_cast<size_t>(score2);k++){
                                    if(TailX2[k]==spaces&&TailY2[k]==i){
                                        std::cout<<"*";
                                        print=true;
                                    }
                                }
                                if(!print)
                                    std::cout<<" ";
                            }
                            spaces++;
                        }
                        std::cout<<"#";
                }
                std::cout<<std::endl;
            }
            std::cout<<"\nSnake 1's Size: "<<score1<<std::endl;
            std::cout<<"\nSnake 1's Head Coordinates: ("<<x1<<","<<y1<<")"<<std::endl;
            std::cout<<"Snake 2's Size: "<<score2<<std::endl;
            std::cout<<"\nSnake 2's Head Coordinates: ("<<x2<<","<<y2<<")"<<std::endl;
        }
void snake::save_score(){
			std::fstream myfile;
			if(count<=0){
				myfile.open("Snake.txt",std::ios::out);//write
				if(myfile.is_open()){
					myfile<<"\t\tSnake Battle Records!\n";
					myfile<<"Player 1"<<"\t\t"<<"Player 2\n";
					myfile.close();
					count++;
				}
			}
			myfile.open("Snake.txt",std::ios::app);//append
				if(myfile.is_open()){
					myfile<<p1_name<<" Score: "<<point1<<"\t\t"<<p2_name<<" Score: "<<point2<<std::endl;
					myfile<<winname<<" Wins!"<<std::endl<<std::endl;
					myfile.close();	
				}
			}
void snake::play(){
            std::cout<<std::endl<<"\t\tSnake Game:\n\t\tPlayer1 Controls: 'w' 'a' 's' 'd'\n\t\tPlayer2 Controls: 'i' 'j' 'k' 'l'\n\t\t5"<<std::endl;
            sleep(1);
            std::cout<<"\t\t4"<<std::endl;
            sleep(1);
            std::cout<<"\t\t3"<<std::endl;
            sleep(1);
            std::cout<<"\t\t2"<<std::endl;
            sleep(1);
            std::cout<<"\t\t1"<<std::endl;
            sleep(1);
            while(!gameOver){
                Input();
                logic();
                display();
                usleep(100000);//For Linux
				//Sleep(10); //for Windows
            }
            if(gameOver){
            	if(win()){
                    std::cout<<"\nGame Over.\nPlayer 2 "<<p2_name<< " Wins!\n";
                	point2++;
                	winname=p2_name;
                	save_score();
				}
                else{
                    std::cout<<"\nGame Over.\nPlayer 1 "<<p1_name<<" Wins!\n";
                	point1++;
                	winname=p1_name;
                	save_score();
				}
			}
        }
