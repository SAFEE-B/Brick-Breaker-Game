#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include <fstream>
#include <fstream>
#include<string>
#include<ctime>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...


void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


class paddle{
	protected:
		int x1,y1,x2,y2;
		int width1;
		int width2;
		int speed;
		int color;

	public:
		paddle(int level){
			if(level==1){
				x1=500;
				y1=40;
				width1=120;
				width2=120;
				x2=400;
				y2=800;
			}
		}
		int getX1(){
			return x1;
		}
		int getY1(){
			return y1;
		}
		int getX2(){
			return x2;
		}
		int getY2(){
			return y2;
		}
		int getWidth1(){
			return width1;
		}
		int getWidth2(){
			return width2;
		}

		void setX1(int num){
			if(!(num<=30||num>=(990-width1)))
				x1=num;
		}
		void setWidth1(int num){
			if(num==1)
			width1=width1*1.5;
			if(num==2)
			width1=width1/1.5;

		}
		void setX2(int num){
			if(!(num<=30||num>=(990-width1)))
				x2=num;
			if(x2<30)
				x2=31;
			if(x2>990-width2)
				x2=990-width2-1;
		}
		void setWidth2(int num){
			if(num==1)
			width2=width2*1.5;
			if(num==2)
			width2=width2/1.5;

		}
		
};

class Score{
protected:
    int score;
	int lives;
public:
    Score(){
        score=0;
		lives=0;
    }
    void addScore(){
        score+=10;
    }
    int getScore(){
        return score;
    }
	void lifeLost(){
		lives-=1;
	}
	int getLives(){
		return lives;
	}
	void resetAll(){
		score=0;
		lives=2;
	}
	
    void writeScoreToFile(){
        ofstream outfile("score.txt");
        if(outfile.is_open()){
            outfile << score;
            outfile.close();
        }
        else{
            cerr << "Error: Unable to open file for writing!" << endl;
        }
    }
    int readHighestScoreFromFile(){
        ifstream infile("score.txt");
        int highestScore = 0;
        if(infile.is_open()){
            infile >> highestScore;
            infile.close();
        }
        else{
            cerr << "Error: Unable to open file for reading!" << endl;
        }
        return highestScore;
    }
};


class blocks{
	protected:
	int arrBloc[121];
	int x;
	public:
	int getLevel(){
		return x;
	}

	void print(int num, char key,int count){
    if(num>0){
        if(key=='*'){
			arrBloc[count+num-1]=rand()%3;
			cout<<"*";
		}
		else{
		arrBloc[count+num-1]=4;
		cout<<" ";
		}
    print(num-1,key,count);
    }
    

}

	void func(int lines,int total,bool bool1,int count){
    
    if(lines>0){
        if(lines<=total){
            if(lines==total&&bool1==false){
                print(lines+1,'*',count);
                count+=lines+1;
                print(lines,'*',count);
                count+=lines;
                cout<<endl;
            }
        	print(lines,'*',count);
        	count+=lines;
        	print((total-lines)*2+1,' ',count);
        	count+=(total-lines)*2+1;
        	print(lines,'*',count);
        	count+=lines;
        	cout<<endl;
        	if(lines==total&&bool1==true){
            	print(lines+1,'*',count);
            	count+=lines+1;
            	print(lines,'*',count);
            	count+=lines;
            	cout<<endl;
        	}

        	if(bool1==false)
        		func(lines-1,total,bool1,count);
        	else
        		func(lines+1,total,bool1,count);

    	}

    }
	else{
        func(lines+2,total,true,count);
    }
}


	blocks(int level){
		if(level==1){
			x=1;
		for(int a=0;a<121;a++){
			if(a<40)
			arrBloc[a]=rand()%3;
			else 
			arrBloc[a]=4;
		}
		}
		else if(level==2){
			x=2;
			func(5,5,false,0);

		}
	}
	

	void changeLevel(int level){
		if(level==1){
			x=1;
		for(int a=0;a<121;a++){
			if(a<40)
			arrBloc[a]=rand()%3;
			else 
			arrBloc[a]=4;


		}

		}
		else if(level==2){
			x=2;
			func(5,5,false,0);
		}
	}
	
	bool checkExist(int num){
		return(!(arrBloc[num]==4));
	}
	void blockHit(int num){
		arrBloc[num]+=1;
	}
	int getBlockVal(int num){
		return arrBloc[num];
	}
	
	
};
class Ball{
	double x;
	double y;
	double dirX;
	double dirY;
	public:
	Ball(){
		x=500;
		y=200;
		dirX=2;
		dirY=2;
	}
	double getx(){
		return x;
	}
	double gety(){
		return y;
	}
	double getdirX(){
		return dirX;
	}
	double getdirY(){
		return dirY;
	}
	void setx(double xval){
		x=xval;
	}
	void sety(double yval){
		y=yval;

	}
	void setdirX(double xval){
		dirX=xval;
	}
	void setdirY(double yval){
		dirY=yval;
	}
	
};
class Food{
	protected:
	int x;
	int y;
	int type;
	int count;
	public:
	Food(){
		x=0;
		y=0;
		type=0;

	}
	void setCount(int num){
		count=num;
	}
	
	void setx(int num){
		x=num;
	}
	void sety(int num){
		y=num;
	}
	void setType(int num){
		type=num;
	}
	int getx(){
		return x;
	}
	int gety(){
		return y;
	}
	int getType(){
		return type;
	}
	void generate(int x1,int y1,int type1){
		x=x1;
		y=y1;
		type=type1;
	}
	bool isLive(){
		return(x!=0);
	}
};

class sendDisplay{
	paddle *px;
	blocks *bx;
	Ball *bl;
	Score *sc;
	Food *fd;
	public:
	sendDisplay(){
		px=nullptr;
		bx=nullptr;
	}
	sendDisplay(paddle &p1,blocks &b1,Ball &b2,Score &s2,Food &f1) {
		px=&p1;
		bx=&b1;
		bl=&b2;
		sc=&s2;
		fd=&f1;
	}
	bool gameStop(){
		return ((*sc).getLives()==0);
	}
	void paddle1Pos(int xval){
		(*px).setX1(xval);

	}
	int getPaddleX2(){
		return (*px).getX2();
	}
	void setPaddleX2(int num){
		if(num==1)
		(*px).setX2((*px).getX2()+5);
		else if(num==2)
		(*px).setX2((*px).getX2()-5);
	}
	int ResetCount(){
		return (*px).getX1();
	}
	void ResetGame(){
		(*px).setX1(500);	
		(*bl).setx(500);
		(*bl).sety(200);
		(*bl).setdirX(1.0);
		(*bl).setdirY(1.0);
		(*px).setX1(500);
		(*px).setWidth1(120);
	}
	void Continue(int level){
		(*sc).resetAll();
		((*bx).changeLevel(level));

	}
	void send(){
		//FOR DRAWING BORDERS
		DrawLine( 30 , 820 ,  990 , 820 , 1 , colors[WHITE] );
		DrawLine( 30 , 30 ,  30 , 820 , 1 , colors[WHITE] );		
		DrawLine( 990 , 30 ,  990 , 820 , 1 , colors[WHITE] );		
		

		//FOR DRAWING BLOCKS
		
		if((*bx).getLevel()==1){
		int starty=700;
		int startx=110;
		for(int a=0;a<40;a++){
			switch((*bx).getBlockVal(a)){
			case 0:
			DrawRoundRect(startx,starty,80,30,colors[GRAY],0);
			break;
			case 1:
			DrawRoundRect(startx,starty,80,30,colors[GOLD],0);
			break;
			case 2:
			DrawRoundRect(startx,starty,80,30,colors[BLUE],0);
			break;
			case 3:
			DrawRoundRect(startx,starty,80,30,colors[YELLOW],0);
			break;
			case 4:
			break;
			}
			
			startx+=80;
			if(((a+1)%10)==0){
				starty-=30;
				startx=110;
			}
		}
		}
		else
		{
			int starty=600;
		int startx=42;
		for(int a=0;a<121;a++){
			switch((*bx).getBlockVal(a)){
			case 0:
			DrawRoundRect(startx,starty,85,20,colors[GRAY],0);
			break;
			case 1:
			DrawRoundRect(startx,starty,85,20,colors[GOLD],0);
			break;
			case 2:
			DrawRoundRect(startx,starty,85,20,colors[BLUE],0);
			break;
			case 3:
			DrawRoundRect(startx,starty,85,20,colors[YELLOW],0);
			break;
			case 4:
			break;
			}
			
			startx+=85;
			if(((a+1)%11)==0){
				starty-=20;
				startx=42;
			}
		}

		}
		if((*bx).getLevel()==2)
		DrawRoundRect((*px).getX2(),(*px).getY2(),(*px).getWidth2(),20,colors[DARK_SEA_GREEN],0);
		//FOR PADDLE LOWER
		DrawRoundRect((*px).getX1(),(*px).getY1(),(*px).getWidth1(),20,colors[DARK_SEA_GREEN],0);

		//FOR BALL
		DrawCircle((*bl).getx(),(*bl).gety(),10,colors[RED]);
		
		
		//FOR DRAWING SCORE
		DrawString(800,820,"SCORE:",colors[WHITE]);
		DrawString(900,820,to_string((*sc).getScore()),colors[WHITE]);
		DrawString(10,820,"LIFE:",colors[WHITE]);
		DrawString(100,820,to_string((*sc).getLives()),colors[GREEN]);
		DrawString(300,820,"HIGHEST SCORE:",colors[WHITE]);
		DrawString(550,820,to_string((*sc).readHighestScoreFromFile()),colors[GREEN]);



		//FOR DRAWING FOOD
		if((*fd).isLive()){
			if((*fd).getType()==1){
				DrawSquare((*fd).getx(),(*fd).gety(),20,colors[GREEN]);
			}
			if((*fd).getType()==2){
				DrawSquare((*fd).getx(),(*fd).gety(),20,colors[PURPLE]);
			}
			if((*fd).getType()==3){
				DrawCircle((*fd).getx(),(*fd).gety(),7,colors[RED]);
			}
			if((*fd).getType()==0){
				DrawCircle((*fd).getx(),(*fd).gety(),7,colors[YELLOW]);
			}
		}

	}
	void TimerLogic(){
		
		
		//FOR RUNNING THE BALL
		(*bl).setx((*bl).getx()+(*bl).getdirX());
		(*bl).sety((*bl).gety()+(*bl).getdirY());
		if(int((*bl).gety())%4==0){
			if((*fd).isLive()){
			(*fd).sety((*fd).gety()-1);
			}
		}

	}


	void CheckCollision() {


	// Check collision with borders
    	if ((*bl).getx() <= 40 || (*bl).getx() >= 980) {
    	    // Reverse horizontal direction
    	    (*bl).setdirX(-(*bl).getdirX());
    	}
    	if ((*bl).gety() >= 810) {
    	    // Reverse vertical direction
    	    (*bl).setdirY(-(*bl).getdirY());
    	}



    // Check collision with paddle
    if ((*bl).gety() <= ((*px).getY1() + 20) && (*bl).gety() >= (*px).getY1()) {
        if ((*bl).getx() >= (*px).getX1() && (*bl).getx() <= ((*px).getX1() + (*px).getWidth1())) {
            // Collision detected with paddle
            // Reverse vertical direction

            // Calculate relative intersection point
            double relativeIntersectX = (*bl).getx() - ((*px).getX1() + (*px).getWidth1() / 2);
            double normalizedRelativeIntersectionX = relativeIntersectX / ((*px).getWidth1() / 2);

            // Calculate bounce angle
            double maxBounceAngle = M_PI / 6; // Maximum bounce angle (60 degrees)
            double bounceAngle = maxBounceAngle * normalizedRelativeIntersectionX;

            // Adjust horizontal direction
            (*bl).setdirX(2.0 * sin(bounceAngle));
			// Adjust vertical direction
			(*bl).setdirY(-(*bl).getdirY());

        }
    }


	// Check collision with block
		if((*bx).getLevel()==1){
		int blockWidth = 80;
    	int blockHeight = 30;
    	for (int i = 0; i < 40; i++) {
        	if (bx->checkExist(i)) {
            	int blockX = 110 + (i % 10) * 80; // Calculate block X position
            	int blockY = 700 - (i / 10) * 35; // Calculate block Y position

            
				if((*bl).gety()+5>=blockY-1&&(*bl).gety()+5<=blockY+1&&(*bl).getx()>=blockX&&(*bl).getx()<=blockX+blockWidth){
					bl->setdirY(-bl->getdirY());
					(*bx).blockHit(i);
					if((*bx).getBlockVal(i)==4)
						(*sc).addScore();
					if((*sc).getScore()%20==0&&(*fd).isLive()==false){
						(*fd).generate((*bl).getx(),(*bl).gety(),rand()%3);
					}
				}
				if((*bl).gety()-5>=blockY+blockHeight-1&&(*bl).gety()-5<=blockY+blockHeight+1&&(*bl).getx()>=blockX&&(*bl).getx()<=blockX+blockWidth){
					bl->setdirY(-bl->getdirY());
					(*bx).blockHit(i);
					if((*bx).getBlockVal(i)==4)
						(*sc).addScore();
					if((*sc).getScore()%20==0&&(*fd).isLive()==false){
						(*fd).generate((*bl).getx(),(*bl).gety(),rand()%3);
					}
				}
				if(int((*bl).getx())+5<=blockX+1&&int((*bl).getx())+5>=blockX-1&&(*bl).gety()>=blockY&&(*bl).gety()<=blockY+blockHeight){
					bl->setdirX(-bl->getdirX());
					(*bx).blockHit(i);
					if((*bx).getBlockVal(i)==4)
						(*sc).addScore();
					if((*sc).getScore()%20==0&&(*fd).isLive()==false){
						(*fd).generate((*bl).getx(),(*bl).gety(),rand()%3);
					}
				}
				if(int((*bl).getx())-5<=blockX+blockWidth+1&&int((*bl).getx())-5>=blockX+blockWidth-1&&(*bl).gety()>=blockY&&(*bl).gety()<=blockY+blockHeight){
					bl->setdirX(-bl->getdirX());
					(*bx).blockHit(i);
					if((*bx).getBlockVal(i)==4)
						(*sc).addScore();
					if((*sc).getScore()%20==0&&(*fd).isLive()==false){
						(*fd).generate((*bl).getx(),(*bl).gety(),rand()%3);
					}
				}
			}
		}
		}
		else{
			int blockWidth = 85;
    	int blockHeight = 20;
    	for (int i = 0; i < 121; i++) {
        	if (bx->checkExist(i)) {
            	int blockX = 42 + (i % 11) * 85; // Calculate block X position
            	int blockY = 600 - (i / 11) * 20; // Calculate block Y position

            
				if((*bl).gety()+5>=blockY-1&&(*bl).gety()+5<=blockY+1&&(*bl).getx()>=blockX&&(*bl).getx()<=blockX+blockWidth){
					bl->setdirY(-bl->getdirY());
					(*bx).blockHit(i);
					if((*bx).getBlockVal(i)==4)
						(*sc).addScore();
					if((*sc).getScore()%20==0&&(*fd).isLive()==false){
						(*fd).generate((*bl).getx(),(*bl).gety(),rand()%3);
					}
				}
				if((*bl).gety()-5>=blockY+blockHeight-1&&(*bl).gety()-5<=blockY+blockHeight+1&&(*bl).getx()>=blockX&&(*bl).getx()<=blockX+blockWidth){
					bl->setdirY(-bl->getdirY());
					(*bx).blockHit(i);
					if((*bx).getBlockVal(i)==4)
						(*sc).addScore();
					if((*sc).getScore()%20==0&&(*fd).isLive()==false){
						(*fd).generate((*bl).getx(),(*bl).gety(),rand()%3);
					}
				}
				if(int((*bl).getx())+5<=blockX+1&&int((*bl).getx())+5>=blockX-1&&(*bl).gety()>=blockY&&(*bl).gety()<=blockY+blockHeight){
					bl->setdirX(-bl->getdirX());
					(*bx).blockHit(i);
					if((*bx).getBlockVal(i)==4)
						(*sc).addScore();
					if((*sc).getScore()%20==0&&(*fd).isLive()==false){
						(*fd).generate((*bl).getx(),(*bl).gety(),rand()%3);
					}
				}
				if(int((*bl).getx())-5<=blockX+blockWidth+1&&int((*bl).getx())-5>=blockX+blockWidth-1&&(*bl).gety()>=blockY&&(*bl).gety()<=blockY+blockHeight){
					bl->setdirX(-bl->getdirX());
					(*bx).blockHit(i);
					if((*bx).getBlockVal(i)==4)
						(*sc).addScore();
					if((*sc).getScore()%20==0&&(*fd).isLive()==false){
						(*fd).generate((*bl).getx(),(*bl).gety(),rand()%3);
					}
				}
			}
		}
		}



			//COLLISION OF FOOD WITH PADDLE
			if ((*fd).gety() <= ((*px).getY1() + 20) && (*fd).gety() >= (*px).getY1()) {
        		if ((*fd).getx() >= (*px).getX1()-2 && (*fd).getx() <= ((*px).getX1() + (*px).getWidth1()+2)) {
					(*fd).setx(0);
					if((*fd).getType()==1){
					(*px).setWidth1(1);
					}
					if((*fd).getType()==2){
						(*px).setWidth1(2);
					}
					if((*fd).getType()==3){
					}
					if((*fd).getType()==0){
					}
				}
			}
			if((*fd).gety()<10&&(*fd).isLive()==true){
				(*fd).setx(0);

			}

			if((*bl).gety()<10){
				if((*sc).getLives()==0){
					(*sc).writeScoreToFile();
				}
				if((*sc).getLives()!=0){
				(*sc).lifeLost();
				(*bl).setx(500);
				(*bl).sety(200);
				(*bl).setdirX(1.0);
				(*bl).setdirY(1.0);
				}
			}

	}
			
        
    

	void setPx(paddle *p1){
		px=p1;
	}
	void setBx(blocks *b1){
		bx=b1;
	}
	void setBl(Ball *b1){
		bl=b1;
	}
	void setSc(Score *s1){
		sc=s1;
	}
	void setFd(Food *f1){
		fd=f1;
	}
	int getLevel(){
		return (*bx).getLevel();
	}
};


sendDisplay s1;

/*
 * Main Canvas drawing function.
 * */
int dx=400;

void GameDisplay(){

	
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.


	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//Fire Gun
	if ((s1).gameStop()&&s1.ResetCount()!=500){
        // Display game over message
        // Display menu options
        // Example:
        DrawString(400, 400, "Game Over", colors[RED]);
        DrawString(400, 380, "Press 'L' to choose a new level", colors[WHITE]);
        DrawString(400, 360, "Press 'Q' to quit", colors[WHITE]);
    }else if((s1).gameStop()){
		DrawString(400, 400, "PRESS 1 for: LEVEL 1", colors[WHITE]);
		DrawString(400, 350, "PRESS 2 for: LEVEL 2", colors[WHITE]);

		DrawString(400, 300, "PRESS 3 for: LEVEL 3", colors[WHITE]);
        DrawString(400, 250, "Press 'Q' to quit", colors[RED]);

	}
	
	else {
	
	
	
	for(int a=0;a<2;a++){
	s1.send();
	s1.CheckCollision();
		s1.TimerLogic();
	}
	}
	

	glutSwapBuffers(); // do not modify this line..



}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
	dx++;

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}
void PrintableKeys(unsigned char key, int x, int y) {
    if (s1.gameStop()&&s1.ResetCount()!=500) {
        if (key == 'l'||key == 'L' ) {
			s1.ResetGame();
			

        } else if (key == 'q' || key == 'Q') {
            exit(0); 
        }
	}
	else if(s1.gameStop()){
		if (key == '2' ) {
			s1.Continue(2);
            
        }
		else if (key == '3' ) {
			s1.Continue(3);
		}
		else if (key == '1' ) {
			s1.Continue(1);
		}
	
            
        }
     else {
		if(s1.getLevel()==2){
			if(key=='a'){
				s1.setPaddleX2(2);
			}
			if(key=='d'){
				s1.setPaddleX2(1);
			}
		}
        
        if (key == 27) {
            exit(1); // exit the program when escape key is pressed.
        }
    }
    glutPostRedisplay();
}





/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

		if(!(s1.gameStop())){
		s1.CheckCollision();
		s1.TimerLogic();
		}
		glutPostRedisplay();

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 * */
void MousePressedAndMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	if(!s1.gameStop()){
	s1.paddle1Pos(x);
	}
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}





int main(int argc, char*argv[]) {
	srand(time(0));
	int width = 1020, height = 840; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Project"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...




	paddle p1(1);
	blocks b1(1);
	Ball b2;
	Score s2;
	Food f1;
	s1.setPx(&p1);
	s1.setBx(&b1);
	s1.setBl(&b2);
	s1.setSc(&s2);
	s1.setFd(&f1);

	
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
