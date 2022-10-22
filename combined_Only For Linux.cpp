#include<iostream>
#include<vector>
#include<unistd.h>//Sleep Function
#include<fstream>

//###Only For Linux###
#include<ncurses.h>

#include <sys/ioctl.h>
#include <termios.h>
bool kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}

//###END OF Only For Linux###

//###Only For Windows
/*
#include<conio.h> //Get _kbhit wala 
#include<time.h>//Random wala
#include<windows.h> //Windows APIS
*/
//##End Of Windows
using namespace std;
string p1_name;
string p2_name;
void setname(){
    cout<<"Enter Player 1's Name: ";
    cin>>p1_name;
    cout<<"\nEnter Player 2's Name: ";
    cin>>p2_name;
}
class game{
    protected:
        string winname;
        int count;
    public:
    	int point1;
        int point2;
        friend void setname();
        virtual void reset()=0;
        virtual void display()=0;  
        virtual void logic()=0;
        virtual bool win()=0;   
        virtual void save_score()=0;
        virtual void play()=0;
};
class position:public game{
    protected:
        int x1;
        int x2;
        int y1;
        int y2;
    public:
        position(){x1=0;x2=0;y1=0;y2=0;}
        ~position(){}
};


//#####Tap Tap Game$$$$$$$$$$$$
class tap:public position{
    protected:
        int count1;
        int count2;
        char con1;
        char con2;
        char move;
    public:
        void save_score(){
			fstream myfile;
			if(count<=0){
				myfile.open("TapTap.txt",ios::out);//write
				if(myfile.is_open()){
					myfile<<"\t\tTap Tap Battle Records!\n";
					myfile<<"Player 1"<<"\t\t"<<"Player 2\n";
					myfile.close();
					count++;
				}
			}
			myfile.open("TapTap.txt",ios::app);//append
				if(myfile.is_open()){
					myfile<<p1_name<<" Score: "<<point1<<"\t\t"<<p2_name<<" Score: "<<point2<<endl;
					myfile<<winname<<" Wins!"<<endl<<endl;
					myfile.close();	
				}
		}
        tap(){count1=0;count2=0;x1=5;x2=5;point1=0;point2=0;count=0;}
        void reset(){count1=0;count2=0;x1=5;x2=5;point1=0;point2=0;}
        void select_controls(){
            cout<<"---------------------------------";
            cout<<"\nPlayer 1! Select Your Key: ";
            cin>>con1;
            cout<<"Player 2! Select Your Key: ";
            cin>>con2;
            cout<<"As soon as someone presses a key the game will begin\n";
            cout<<"---------------------------------\n";
        }
        void logic(){
            display();
            while(x1<10&&x2<10){
                move=cin.get();
                if(move==con1){
                    count1++;
                    x1++;
                    x2--;
                    display();
                }
                if(move==con2){
                    count2++;
                    x2++;
                    x1--;
                    display();
                }
            }
        }
        bool win(){
            if(count1>count2)
                return 0;
                //cout<<"Player 1 "<<p1_name<<" Wins!";
            else
                return 1;
                //cout<<"Player 2 "<<p2_name<<" Wins!";
        }
        void display(){
            cout<<"#              #\n#";
            for(int j=0;j<=(x1-1);j++){
                cout<<" ";
            }
            cout<<"-><-";
            for(int k=0;k<=(x2-1);k++){
                cout<<" ";
            }
            cout<<"#\n#              #\n";   
        }
        void play(){
            cout<<"\tWelcome to Tap! Tap! Tap! Tap! Tap! Tap!!!!\n\t\t\tTHE GAME!\n\n";
            cout<<"\nThe Rule is Simple. You gotta push the other player to the boundry.\nSimple Right? Now go out there and start TAPPING!\n";
            cout<<"---------------------------------------------------------------------\n\n\n";
            select_controls();
            logic();
            cout<<"-------------------------------------------------\n";
            if(win()){
                cout<<"Player 2 "<<p2_name<<" Wins!";
                point2++;
                winname=p2_name;
                save_score();
            }
            else{
                cout<<"Player 1 "<<p1_name<<" Wins!"<<endl;
        		point1++;
        		winname=p2_name;
        		save_score();
			}
			cout<<"\nPlayer 1 "<<p1_name<<"'s Total Taps: "<<count1;
            cout<<"\nPlayer 2 "<<p2_name<<"'s Total Taps: "<<count2<<endl;
        }
};

//#############################Snake and Other Stuff###########################
class snake:public position{
    protected:
        bool gameOver;
        int width;
        int height;
        int fruitX,fruitY,score1,score2;
        enum eDirection {STOP=0,LEFT,RIGHT,UP,DOWN,LEFTT,RIGHTT,UPP,DOWNN};
        eDirection dir,dir2;
        vector<int>TailX1,TailY1,TailX2,TailY2;
    public:
        snake(int w,int h){
            count=0;
        	gameOver=false;
            width=w;
            height=h;
            point1=0;
            point2=0;
            for(int i=0;i<width*height;i++){
                TailX1.push_back(0);
                TailY1.push_back(0);
                TailX2.push_back(0);
                TailY2.push_back(0);
            }
                dir= STOP;
                x1=(width-10)/4;
                y1=(height-10)/4;
                x2=(width-10)/2;
                y2=(height-10)/2;
                fruitX=1+(rand()%(width-1));
                fruitY=1+(rand()%(height-2));
                score1=0;
                score2=0;    
        }
        void reset(){
            gameOver=false;
            point1=0;
            point2=0;
            for(int i=0;i<width*height;i++){
                TailX1[i]=0;
                TailX2[i]=0;
                TailY1[i]=0;
                TailY2[i]=0;
            }
            dir= STOP;
            x1=(width-10)/4;
            y1=(height-10)/4;
            x2=(width-10)/2;
            y2=(height-10)/2;
            fruitX=1+(rand()%(width-1));
            fruitY=1+(rand()%(height-2));
            score1=0;
            score2=0;   
        }
        void logic(){
            for(int i=score1;i>0;i--){
                TailX1[i] = TailX1[i - 1];
                TailY1[i] = TailY1[i - 1];
            }
            TailX1[0]=x1;
            TailY1[0]=y1;
            for(int i=score2;i>0;i--){
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
        void Input(){
            if(kbhit()){//just kbhit for Linux
            //###Only For Linux
            
                char op;
                cin>>op;
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
        bool win(){
            if(x1>=width||x1<=0||y1>height-2||y1<=0){
                gameOver=true;
                return 1;
            }
            else if(x2>=width||x2<=0||y2>height-2||y2<=0){
                gameOver=true;
                return 0;
            }
            if(x1==x2&&y1==y2){
                if(score1>score2){
                    gameOver=true;
                    return 0;
                }
                else{
                    gameOver=true;
                    return 1;
                }
            }
            for(int i=score1;i>0;i--){
                if(x1==TailX2[i]&&y1==TailY2[i]){
                    gameOver=true;
                    return 1;
                }
                else if(x2==TailX1[i]&&y2==TailY1[i]){
                    gameOver=true;
                    return 0;
                }
            }
        }
        void display(){
            system("clear");//For Linux
			//system("cls"); //For Windows
            cout<<"\nFruit's Coordinates: ("<<fruitX<<","<<fruitY<<")\n";
            for(int i=0;i<height;i++){
                if(i==0||i==height-1){
                    for(int j=0;j<width+1;j++)
                        cout<<"#";
                }
                else{
                    cout<<"#";
                        int spaces=1;
                        while(spaces!=width){
                            if(i==y1&&spaces==x1){
                                cout<<"1";
                            }
                            else if(i==y2&&spaces==x2){
                                cout<<"2";
                            }
                            else if(i==fruitY&&spaces==fruitX){
                                cout<<"F";
                            }
                            else{
                                bool print=false;
                                for(int k=0;k<score1;k++){
                                    if(TailX1[k]==spaces&&TailY1[k]==i){
                                        cout<<"o";
                                        print=true;
                                    }
                                }
                                for(int k=0;k<score2;k++){
                                    if(TailX2[k]==spaces&&TailY2[k]==i){
                                        cout<<"*";
                                        print=true;
                                    }
                                }
                                if(!print)
                                    cout<<" ";
                            }
                            spaces++;
                        }
                        cout<<"#";
                }
                cout<<endl;
            }
            cout<<"\nSnake 1's Size: "<<score1<<endl;
            cout<<"\nSnake 1's Head Coordinates: ("<<x1<<","<<y1<<")"<<endl;
            cout<<"Snake 2's Size: "<<score2<<endl;
            cout<<"\nSnake 2's Head Coordinates: ("<<x2<<","<<y2<<")"<<endl;
        }
        void save_score(){
			fstream myfile;
			if(count<=0){
				myfile.open("Snake.txt",ios::out);//write
				if(myfile.is_open()){
					myfile<<"\t\tSnake Battle Records!\n";
					myfile<<"Player 1"<<"\t\t"<<"Player 2\n";
					myfile.close();
					count++;
				}
			}
			myfile.open("Snake.txt",ios::app);//append
				if(myfile.is_open()){
					myfile<<p1_name<<" Score: "<<point1<<"\t\t"<<p2_name<<" Score: "<<point2<<endl;
					myfile<<winname<<" Wins!"<<endl<<endl;
					myfile.close();	
				}
			}
        void play(){
            while(!gameOver){
                Input();
                logic();
                display();
                usleep(100000);//For Linux
				//Sleep(10); //for Windows
            }
            if(gameOver){
            	if(win()){
                    cout<<"\nGame Over.\nPlayer 2 "<<p2_name<< " Wins!\n";
                	point2++;
                	winname=p2_name;
                	save_score();
				}
                else{
                    cout<<"\nGame Over.\nPlayer 1 "<<p1_name<<" Wins!\n";
                	point1++;
                	winname=p1_name;
                	save_score();
				}
			}
        }
};



//######Tick Cross#######################################
class ttt:public game{
    protected:
    	char matrix[3][3];
    	char player;
    	int gameover;
    public:
    	void reset(){	
			matrix[0][0]={'1'};
    		matrix[0][1]={'2'};
			matrix[0][2]={'3'};
			matrix[1][0]={'4'};
    		matrix[1][1]={'5'};
    		matrix[1][2]={'6'};
    		matrix[2][0]={'7'};
			matrix[2][1]={'8'};
    		matrix[2][2]={'9'};
    		player='X';
    		point1=0;
    		point2=0;
		}
    	ttt(){
    		matrix[0][0]={'1'};
    		matrix[0][1]={'2'};
			matrix[0][2]={'3'};
			matrix[1][0]={'4'};
    		matrix[1][1]={'5'};
    		matrix[1][2]={'6'};
    		matrix[2][0]={'7'};
			matrix[2][1]={'8'};
    		matrix[2][2]={'9'};
    		player='X';
    		point1=0;
    		point2=0;
            count=0;
		}
		void display(){
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					cout<<matrix[i][j];
           			if(j<2)
               			cout<<" | ";
				}
				cout<<endl;
        		if(i<2)
            		cout<<"----------"<<endl;
			}	
		} 
		void input(){
		int a;
		if(player=='X')
			cout<<"Player 1 "<<p1_name<<"'s turn\n";
		else if(player=='O')
			cout<<"Player 2 "<<p2_name<<"'s turn\n";
		cout<<"Select Region To Tick: ";
			cin>>a;
			if(a==1)
				matrix[0][0]=player;
			else if(a==2)
				matrix[0][1]=player;
			else if(a==3)
				matrix[0][2]=player;
			else if(a==4)
				matrix[1][0]=player;
			else if(a==5)
				matrix[1][1]=player;
			else if(a==6)
				matrix[1][2]=player;
			else if(a==7)
				matrix[2][0]=player;
			else if(a==8)
				matrix[2][1]=player;
			else if(a==9)
				matrix[2][2]=player;	
		}
        void logic(){
        	if(player=='X')
				player='O';
			else
				player='X';
		}	
        bool win(){
        	//first player
			if (matrix[0][0] == 'X' && matrix[0][1] == 'X' && matrix[0][2] == 'X'){
				gameover=1;
				return 0;
			}
			 if (matrix[1][0] == 'X' && matrix[1][1] == 'X' && matrix[1][2] == 'X'){
				gameover=1;
				return 0;
			}
			if (matrix[2][0] == 'X' && matrix[2][1] == 'X' && matrix[2][2] == 'X'){
				gameover=1;
				return 0;
			}
			 if (matrix[0][0] == 'X' && matrix[1][0] == 'X' && matrix[2][0] == 'X'){
			 	gameover=1;
				return 0;
			}
			if (matrix[0][1] == 'X' && matrix[1][1] == 'X' && matrix[2][1] == 'X'){
				gameover=1;
				return 0;
			}
			 if (matrix[0][2] == 'X' && matrix[1][2] == 'X' && matrix[2][2] == 'X'){
			 	gameover=1;
				return 0;
			}
			 if (matrix[0][0] == 'X' && matrix[1][1] == 'X' && matrix[2][2] == 'X'){
			 	gameover=1;
				return 0;
				
			}
			 if (matrix[2][0] == 'X' && matrix[1][1] == 'X' && matrix[0][2] == 'X'){
			 	gameover=1;
				return 0;
			}
			//second player
			 if (matrix[0][0] == 'O' && matrix[0][1] == 'O' && matrix[0][2] == 'O'){
			 	gameover=1;
				return 1;
			}
			 if (matrix[1][0] == 'O' && matrix[1][1] == 'O' && matrix[1][2] == 'O'){
			 	gameover=1;
				return 1;
			}
			 if (matrix[2][0] == 'O' && matrix[2][1] == 'O' && matrix[2][2] == 'O'){
			 	gameover=1;
				return 1;
			}
			 if (matrix[0][0] == 'O' && matrix[1][0] == 'O' && matrix[2][0] == 'O'){
			 	gameover=1;
				return 1;
			}
			 if (matrix[0][1] == 'O' && matrix[1][1] == 'O' && matrix[2][1] == 'O'){
			 	gameover=1;
				return 1;
			}
			 if (matrix[0][2] == 'O' && matrix[1][2] == 'O' && matrix[2][2] == 'O'){
			 	gameover=1;
				return 1;
			}
			 if (matrix[0][0] == 'O' && matrix[1][1] == 'O' && matrix[2][2] == 'O'){
			 	gameover=1;
				return 1;
			}
			 if (matrix[2][0] == 'O' && matrix[1][1] == 'O' && matrix[0][2] == 'O'){
			 	gameover=1;
				return 1;
			}
			else if(matrix[0][0]!='1'&&matrix[0][1]!='2'&&matrix[0][2]!='3'&&matrix[1][0]!='4'&&matrix[1][1]!='5'&&matrix[1][2]!='6'&&matrix[2][0]!='7'&&matrix[2][1]!='8'&&matrix[2][2]!='9'){
				gameover=2;
			}
			else
				gameover=0;
		}  
        void save_score(){
			fstream myfile;
			if(count<=0){
				myfile.open("TicTacToe.txt",ios::out);//overwrite
				if(myfile.is_open()){
					myfile<<"\t\tTick Corss Battle Records!\n";
					myfile<<"Player 1"<<"\t\t"<<"Player 2\n";
					myfile.close();
					count++;
				}
			}
			myfile.open("TicTacToe.txt",ios::app);//append
				if(myfile.is_open()){
					myfile<<p1_name<<" Score: "<<point1<<"\t\t"<<p2_name<<" Score: "<<point2<<endl;
					myfile<<winname<<" Wins!"<<endl<<endl;
					myfile.close();	
				}
		}
        void play(){
        	display();
				while (true){
					input();
					display();
					if (win()&&gameover==1){
						cout <<"Player 2 "<<p2_name<<" wins!" << endl;
						point2++;
						winname=p2_name;
						save_score();
						break;
					}
					else if (!win()&&gameover==1){
						cout <<"Player 1 "<<p1_name<<" wins!" << endl;
						point1++;
						winname=p1_name;
						save_score();
						break;
					}
					else if(gameover==2){
						cout<<"Its a Draw!. Proceed to the next game.\n";
					}
					logic();
				}	
		}				
};


int main(){
	int match=0;
	int totalscore1=0;
	int totalscore2=0;
    char op='y';
	ttt t;
	tap a;
	snake s(30,20);
	setname();
    do{
	    cout<<"\n\n\nThis match will have 3 different games. You will begin by a small game of tick cross.\n";
	    do{
	    	cout<<"This match will not be over unless one of you wins more then 2 games then the other.\n";
	    	cout<<"\nPlayer 1 "<<p1_name<<" Total Score: "<<totalscore1<<endl;
	    	cout<<"Player 2 "<<p2_name<<" Total Score: "<<totalscore2<<endl;
	    	cout<<"\t\t\t\tRound Number: "<<++match<<endl<<endl;
	    t.play();
	    string stop;
        a.play();
        cout<<"-------------------------------------------------";
            while(stop!="0"){
                cout<<"\nEnough!! To stop press the number 0: ";
                cin>>stop;
            }
        srand(time(NULL));
        s.play();
        totalscore1=t.point1+a.point1+s.point1+totalscore1;
        totalscore2=t.point2+a.point2+s.point2+totalscore2;
        s.reset();
        a.reset();
        t.reset();
	    }
	    while(totalscore1>totalscore2+2||totalscore2>totalscore1+2);
	    if(totalscore1>totalscore2){
	    	cout<<"Congrats!! Player 1 "<<p1_name<<" Wins The Match!!\nHere is your Reward"<<endl;
	    	sleep(1);
	    	cout<<"Absolutly Nothing :) You just wasted your time. Have a Nice Day.";
	    }
	    else{
	    	cout<<"Congrats!! Player 2 "<<p2_name<<" Wins THe Match!!\nHere is your Reward"<<endl;
	    	sleep(1);
	    	cout<<"Absolutly Nothing :) You just wasted your time. Have a Nice Day.";
        }
        cout<<"\nDo you want to Play Again?(Y/N): ";
        cin>>op;
    }while(op=='y'||op=='Y');
    return 0;
}