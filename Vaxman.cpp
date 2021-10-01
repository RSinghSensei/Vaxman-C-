// Vaxman Author : Ritvik Singh
// Pacman Author: Patricia Terol



//EA Virtual Intership TASK 2
//Hey! If you're checking my code, Please check the blocks of code which are commented betweeen ---->PLEASE REFER HERE and -------->MORE CODE CHANGES BELOW, as they are the ones with the code changes
//Thank you for taking the time to check my "Modded" Pacman, aka, Vaxman!
//ALSO, I will be iterating over this and adding new features. I believe iterating over work is better than just doing it all at once. So, I suppose this isn't the final product, but of course, the mechanics which have been asked for are present here!
//Once again, Thank you for this opportunity, and I hope you have a fabulous day
//Cheers! :)



#include <stdlib.h>
#include <vector>
#include <deque>
#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

static bool replay = false; //check if starts a new game
static bool over = true; //check for the game to be over
static float squareSize = 50.0; //size of one square on the game
static float xIncrement = 0; // x movement on pacman
static float yIncrement = 0; // y movement on pacman
static int rotation = 0; // orientation of pacman
//float* monster1 = new float[3] {10.5, 8.5, 1.0}; //coordinates and direction of first monster
//float* monster2 = new float[3] {13.5, 1.5, 2.0}; //coordinates and direction of second monster
//float* monster3 = new float[3] {4.5, 6.5, 3.0}; //coordinates and direction of third monster
//float* monster4 = new float[3] {2.5, 13.5, 4.0}; //coordinates and direction of fourth monster

float monster1[3]{ 10.5, 8.5, 1.0 }; //coordinates and direction of first monster
float monster2[3]{ 13.5, 1.5, 2.0 }; //coordinates and direction of second monster
float monster3[3]{ 4.5, 6.5, 3.0 }; //coordinates and direction of third monster
float monster4[3]{ 2.5, 13.5, 4.0 }; //coordinates and direction of fourth monster


//Modified Code for Vaxman ---------------------------------------------------------------------------------------------------------------------> PLEASE REFER HERE

//Created a Vector of float pointers, initialized at 4 for the first 4 monsters, could have just had an array[128] but a vector seems to be more intuitive in this case
//Created a Vector which is 1:1 to every entry in the enemies vector, so we can have an individual 30 second timer for every monster, also allows for ease of access and deletion when required
//Another Vector which acts like a bool value, but allows us to only regenerate monsters once when we hit the 30 second timer
vector<float*>v1{ monster1,monster2, monster3, monster4 };
vector<int>d_timer(4,1);
vector<int>v2;

//t value is used to track how many of the monsters are drawn, and is incremented when we hit the 30 second timer, and reset upon game reset
//This is better than allocating new float arrays on the go, as there are performance issues you end up hitting, especially when it comes to having multiple elements on the screen
static int t = 4;

//The function that runs before we enter the game loop, to already have memory allocated for the enemy rather than creating them when needed
void Adder() {
	for (int i = 0; i < 124; i++) {
		v1.push_back(new float[3]{ 10.5, 8.5, 1.0 });
		d_timer.push_back(0);
	}
}

//This Function checks for when our enemy has been alive for 30 seconds, and increments the t variable, allowing us to draw the already allocated enemy
//The v2 acts like a bool, as stated previously, and uses the bitwise & to keep initializing to 0 when the set bit is 1
void Double_time(){
	for (int i = 0; i < t; i++) {
		int j = (clock() - d_timer[i]) / CLOCKS_PER_SEC, temp = t;		
		if (j % 30 == 0 && v2.size() == 0) {
			v2.push_back(0); 
			cout << "Enemies: " << t << " Size of v1: " << v1.size() << endl;
			if (t + temp >= 128) { cout << "Next Stage Loss\n"; over = true; }
			else { t += temp; }
		}
		if (j & 1) { v2 = {}; }
		//cout << d_timer[i] << " ";
		
	}
	
}

// ---------------------------------------------------------------------------------------------------------------------------------------------> MORE CODE CHANGES BELOW

static vector<int> border = { 0, 0, 15, 1, 15, 15, 14, 1, 0, 14, 15, 15, 1, 14, 0, 0 }; //coordinates of the border walls

//coordinates of the obstacles (divided into 3 for clarity)
static vector<int> obstaclesTop = { 2, 2, 3, 6, 3, 6, 4, 5, 4, 2, 5, 4, 5, 3, 6, 5, 6, 1, 9, 2, 7, 2, 8, 5, 9, 5, 10, 3, 10, 4, 11, 2, 11, 5, 12, 6, 12, 6, 13, 2 };
static vector<int> obstaclesMiddle = { 2, 9, 3, 7, 3, 7, 4, 8, 4, 9, 5, 11, 5, 6, 6, 10, 6, 10, 7, 8, 7, 8, 8, 9, 6, 7, 7, 6, 8, 6, 9, 7, 10, 6, 9, 10, 9, 10, 8, 8, 11, 9, 10, 11, 11, 8, 12, 7, 12, 7, 13, 9 };
static vector<int> obstaclesBottom = { 2, 10, 3, 13, 3, 13, 4, 12, 5, 12, 6, 13, 6, 13, 7, 11, 8, 11, 9, 13, 9, 13, 10, 12, 11, 12, 12, 13, 12, 13, 13, 10 };
static deque<float> food = { 1.5, 1.5, 1.5, 2.5, 1.5, 3.5, 1.5, 4.5, 1.5, 5.5, 1.5, 6.5, 1.5, 7.5, 1.5, 8.5, 1.5, 9.5, 1.5, 10.5, 1.5, 11.5, 1.5, 12.5, 1.5, 13.5, 2.5, 1.5, 2.5, 6.5, 2.5, 9.5, 2.5, 13.5, 3.5, 1.5, 3.5, 2.5, 3.5, 3.5, 3.5, 4.5, 3.5, 6.5, 3.5, 8.5, 3.5, 9.5, 3.5, 10.5, 3.5, 11.5, 3.5, 13.5, 4.5, 1.5, 4.5, 4.5, 4.5, 5.5, 4.5, 6.5, 4.5, 7.5, 4.5, 8.5, 4.5, 11.5, 4.5, 12.5, 4.5, 13.5, 5.5, 1.5, 5.5, 2.5, 5.5, 5.5, 5.5, 10.5, 5.5, 11.5, 5.5, 13.5, 6.5, 2.5, 6.5, 3.5, 6.5, 4.5, 6.5, 5.5, 6.5, 7.5, 6.5, 10.5, 6.5, 13.5, 7.5, 5.5, 7.5, 6.5, 7.5, 7.5, 7.5, 9.5, 7.5, 10.5, 7.5, 11.5, 7.5, 12.5, 7.5, 13.5, 8.5, 2.5, 8.5, 3.5, 8.5, 4.5, 8.5, 5.5, 8.5, 7.5, 8.5, 10.5, 8.5, 13.5, 9.5, 1.5, 9.5, 2.5, 9.5, 5.5, 9.5, 10.5, 9.5, 11.5, 9.5, 13.5, 10.5, 1.5, 10.5, 4.5, 10.5, 5.5, 10.5, 6.5, 10.5, 7.5, 10.5, 8.5, 10.5, 11.5, 10.5, 12.5, 10.5, 13.5, 11.5, 1.5, 11.5, 2.5, 11.5, 3.5, 11.5, 4.5, 11.5, 5.5, 11.5, 6.5, 11.5, 8.5, 11.5, 9.5, 11.5, 10.5, 11.5, 11.5, 11.5, 13.5, 12.5, 1.5, 12.5, 6.5, 12.5, 9.5, 12.5, 13.5, 13.5, 1.5, 13.5, 2.5, 13.5, 3.5, 13.5, 4.5, 13.5, 5.5, 13.5, 6.5, 13.5, 7.5, 13.5, 8.5, 13.5, 9.5, 13.5, 10.5, 13.5, 11.5, 13.5, 12.5, 13.5, 13.5 };
static vector<vector<bool>> bitmap; // 2d image of which squares are blocked and which are clear for pacman to move in 
bool* keyStates = new bool[256]; // record of all keys pressed 
int points = 0; // total points collected

//Initializes the game with the appropiate information 
void init(void){
	//clear screen
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	//reset all keys
	for (int i = 0; i < 256; i++){
		keyStates[i] = false;
	}
	//fill the bitmap with the obstacles
	bitmap.push_back({ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false, false, false, true });
	bitmap.push_back({ true, false, true, true, true, true, false, true, true, false, true, true, true, false, true });
	bitmap.push_back({ true, false, false, false, false, true, false, true, false, false, false, false, true, false, true});
	bitmap.push_back({ true, false, true, true, false, false, false, false, false, true, true, false, false, false, true});
	bitmap.push_back({ true, false, false, true, true, false, true, true, true, true, false, false, true, false, true});
	bitmap.push_back({ true, true, false, false, false, false, true, false, true, true, false, true, true, false, true});
	bitmap.push_back({ true, true, true, true, true, false, false, false, true, false, false, false, false, false, true});
	bitmap.push_back({ true, true, false, false, false, false, true, false, true, true, false, true, true, false, true });
	bitmap.push_back({ true, false, false, true, true, false, true, true, true, true, false, false, true, false, true });
	bitmap.push_back({ true, false, true, true, false, false, false, false, false, true, true, false, false, false, true });
	bitmap.push_back({ true, false, false, false, false, true, false, true, false, false, false, false, true, false, true });
	bitmap.push_back({ true, false, true, true, true, true, false, true, true, false, true, true, true, false, true });
	bitmap.push_back({ true, false, false, false, false, false, false, false, false, false, false, false, false, false, true });
	bitmap.push_back({ true, true, true, true, true, true, true, true, true, true, true, true, true, true, true });
}

//Method to draw the obstacle course and the walls
void drawLaberynth(){
	glColor3f(1.0, 1.0, 1.0);
	//Border
	for (int i = 0; i < border.size(); i = i + 4){
		glRectf(border.at(i) * squareSize, border.at(i + 1)*squareSize, border.at(i + 2)*squareSize, border.at(i + 3)*squareSize);
	}

	//Obstacles
	for (int j = 0; j < obstaclesBottom.size(); j = j + 4){
		glRectf(obstaclesBottom.at(j) * squareSize, obstaclesBottom.at(j + 1)*squareSize, obstaclesBottom.at(j + 2)*squareSize, obstaclesBottom.at(j + 3)*squareSize);
	}
	for (int k = 0; k < obstaclesMiddle.size(); k = k + 4){
		glRectf(obstaclesMiddle.at(k) * squareSize, obstaclesMiddle.at(k + 1)*squareSize, obstaclesMiddle.at(k + 2)*squareSize, obstaclesMiddle.at(k + 3)*squareSize);
	}
	for (int p = 0; p < obstaclesTop.size(); p = p + 4){
		glRectf(obstaclesTop.at(p) * squareSize, obstaclesTop.at(p + 1)*squareSize, obstaclesTop.at(p + 2)*squareSize, obstaclesTop.at(p + 3)*squareSize);
	}
}

//Method to check if the food has been eaten
bool foodEaten(int x, int y, float pacmanX, float pacmanY){
	if (x >= pacmanX - 16.0 *cos(359 * M_PI / 180.0) && x <= pacmanX + 16.0*cos(359 * M_PI / 180.0)){
		if (y >= pacmanY - 16.0*cos(359 * M_PI / 180.0) && y <= pacmanY + 16.0*cos(359 * M_PI / 180.0)){
			return true;
		}
	}
	return false;
}

//Method to draw all the food left and delete the ate one
void drawFood(float pacmanX, float pacmanY){
	deque<float> temp;
	//check if the food has not been eaten
	for (int i = 0; i < food.size(); i = i + 2){
		if (!foodEaten(food.at(i)*squareSize, food.at(i + 1)*squareSize, pacmanX, pacmanY)){
			temp.push_back(food.at(i));
			temp.push_back(food.at(i + 1));
		}
		else {
			points++;
		}
	}
	food.swap(temp);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 1.0);
	//draw all the food avilable
	for (int j = 0; j < food.size(); j = j + 2){
		glVertex2f(food.at(j)*squareSize, food.at(j + 1)*squareSize);
	}
	glEnd();
}

//Method to draw the pacman character through consicutive circle algorithm
void drawPacman(float positionX, float positionY, float rotation){
	int x, y;
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);
	for (int k = 0; k < 32; k++){
		x = (float)k / 2.0 * cos((30 + 90*rotation) * M_PI / 180.0) + (positionX*squareSize);
		y = (float)k / 2.0* sin((30 + 90 * rotation) * M_PI / 180.0) + (positionY*squareSize);
		for (int i = 30; i < 330; i++){
			glVertex2f(x, y);
			x = (float)k / 2.0 * cos((i + 90 * rotation) * M_PI / 180.0) + (positionX*squareSize);
			y = (float)k / 2.0* sin((i + 90 * rotation) * M_PI / 180.0) + (positionY*squareSize);
			glVertex2f(x, y);
		}
	}
	glEnd();
}

//Method to draw the monster character through consecutive circles algorithm
//void drawMonster(float positionX, float positionY, float r, float g, float b){
//	int x, y;
//	glBegin(GL_LINES);
//	glColor3f(r, g, b);
//	//draw the head
//	for (int k = 0; k < 32; k++){
//		x = (float)k / 2.0 * cos(360 * M_PI / 180.0) + (positionX*squareSize);
//		y = (float)k / 2.0* sin(360 * M_PI / 180.0) + (positionY*squareSize);
//		for (int i = 180; i <= 360; i++){
//			glVertex2f(x, y);
//			x = (float)k / 2.0 * cos(i * M_PI / 180.0) + (positionX*squareSize);
//			y = (float)k / 2.0* sin(i * M_PI / 180.0) + (positionY*squareSize);
//			glVertex2f(x, y);
//		}
//	}
//	glEnd();	
//	//draw body
//	glRectf((positionX*squareSize) - 17, positionY*squareSize, (positionX*squareSize) + 15, (positionY*squareSize) + 15);
//	glBegin(GL_POINTS);
//	glColor3f(0, 0.2, 0.4);
//	//draw eyes and legs
//	glVertex2f((positionX*squareSize) - 11, (positionY*squareSize) + 14); //legs
//	glVertex2f((positionX*squareSize) - 1, (positionY*squareSize) + 14); //legs
//	glVertex2f((positionX*squareSize) + 8, (positionY*squareSize) + 14); //legs
//	glVertex2f((positionX*squareSize) + 4, (positionY*squareSize) - 3); //eyes
//	glVertex2f((positionX*squareSize) - 7, (positionY*squareSize) - 3); //eyes 
//	glEnd();
//}


//Modified Code for Vaxman ---------------------------------------------------------------------------------------------------------------------> PLEASE REFER HERE

//This function had too many draw calls, leading to performance issues when having more than 8 elements on screen, therefore I reduced the number of circles drawn for the head, which fixed most of the performance
void drawMonster() {
	if (t < 128) {
		for (int i = 0; i < t; i++) {
			float positionX = v1[i][0], positionY = v1[i][1];
			int x, y;
			glBegin(GL_LINES);
			glColor3f(0.1, 1.0, 1.0);
			//draw the head
			for (int k = 0; k < 32; k += 2) {
				x = (float)k / 2.0 * cos(360 * M_PI / 180.0) + (positionX * squareSize);
				y = (float)k / 2.0 * sin(360 * M_PI / 180.0) + (positionY * squareSize);
				for (int i = 180; i <= 360; i += 20) {
					glVertex2f(x, y);
					x = (float)k / 2.0 * cos(i * M_PI / 180.0) + (positionX * squareSize);
					y = (float)k / 2.0 * sin(i * M_PI / 180.0) + (positionY * squareSize);
					glVertex2f(x, y);
				}
			}
			glEnd();
			//draw body
			glRectf((positionX * squareSize) - 17, positionY * squareSize, (positionX * squareSize) + 15, (positionY * squareSize) + 15);
			glBegin(GL_POINTS);
			/*glColor3f(0, 0.2, 0.4);*/
			glColor3f(1.0, 0, 0);
			//draw eyes and legs
			glVertex2f((positionX * squareSize) - 11, (positionY * squareSize) + 14); //legs
			glVertex2f((positionX * squareSize) - 1, (positionY * squareSize) + 14); //legs
			glVertex2f((positionX * squareSize) + 8, (positionY * squareSize) + 14); //legs
			glVertex2f((positionX * squareSize) + 4, (positionY * squareSize) - 3); //eyes
			glVertex2f((positionX * squareSize) - 7, (positionY * squareSize) - 3); //eyes 
			glEnd();
		}
	}
}

// ---------------------------------------------------------------------------------------------------------------------------------------------> MORE CODE CHANGES BELOW

//Method to update the position of the monsters randomly
//void updateMonster(float* monster, int id){
//		//find the current position of the monster
//		int x1Quadrant = (int)((monster[0] - (2/squareSize)) - (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
//		int x2Quadrant = (int)((monster[0] + (2/squareSize)) + (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
//		int y1Quadrant = (int)((monster[1] - (2/squareSize)) - (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
//		int y2Quadrant = (int)((monster[1] + (2/squareSize)) + (16.0 *cos(360 * M_PI / 180.0)) / squareSize);
//		//move him acording to its direction until he hits an obstacle
//		switch ((int)monster[2]){
//		case 1:
//			if (!bitmap.at(x1Quadrant).at((int)monster[1])){ 
//				monster[0] -= 2 / squareSize;
//			}else {
//				int current = monster[2];
//				do{
//					monster[2] =  (rand() % 4) + 1;
//				} while (current == (int) monster[2]);
//			}
//			break;
//		case 2:
//			if (!bitmap.at(x2Quadrant).at((int)monster[1])){
//				monster[0] += 2 / squareSize;
//			}
//			else {
//				int current = monster[2];
//				do{
//					monster[2] = (rand() % 4) + 1;
//				} while (current == (int)monster[2]);
//			}
//			break;
//		case 3:
//			if (!bitmap.at((int)monster[0]).at(y1Quadrant)){
//				monster[1] -= 2 / squareSize;
//			}
//			else {
//				int current = monster[2];
//				do{
//					monster[2] = (rand() % 4) + 1;
//				} while (current == (int)monster[2]);
//			}
//			break;
//		case 4:
//			if (!bitmap.at((int)monster[0]).at(y2Quadrant)){
//				monster[1] += 2 / squareSize;
//			}
//			else {
//				int current = monster[2];
//				do{
//					monster[2] = (rand() % 4) + 1;
//				} while (current == (int)monster[2]);
//			}
//			break;
//		default:
//			break;
//		}
//}

//Modified Code for Vaxman ---------------------------------------------------------------------------------------------------------------------> PLEASE REFER HERE
//The game originally was only meant for 4 monsters, as it should have, but it had no scope for increasing enemies or different stages, therefore this part was changed to iterate over all enemies
//All enemies as defined by our global t variable
void updateMonster() {
	//find the current position of the monster
	if (t < 128) {
		for (int i = 0; i < t; i++) {
			int x1Quadrant = (int)((v1[i][0] - (2 / squareSize)) - (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
			int x2Quadrant = (int)((v1[i][0] + (2 / squareSize)) + (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
			int y1Quadrant = (int)((v1[i][1] - (2 / squareSize)) - (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
			int y2Quadrant = (int)((v1[i][1] + (2 / squareSize)) + (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
			//move him acording to its direction until he hits an obstacle
			switch ((int)v1[i][2]) {
			case 1:
				if (!bitmap.at(x1Quadrant).at((int)v1[i][1])) {
					v1[i][0] -= 2 / squareSize;
				}
				else {
					int current = v1[i][2];
					do {
						v1[i][2] = (rand() % 4) + 1;
					} while (current == (int)v1[i][2]);
				}
				break;
			case 2:
				if (!bitmap.at(x2Quadrant).at((int)v1[i][1])) {
					v1[i][0] += 2 / squareSize;
				}
				else {
					int current = v1[i][2];
					do {
						v1[i][2] = (rand() % 4) + 1;
					} while (current == (int)v1[i][2]);
				}
				break;
			case 3:
				if (!bitmap.at((int)v1[i][0]).at(y1Quadrant)) {
					v1[i][1] -= 2 / squareSize;
				}
				else {
					int current = v1[i][2];
					do {
						v1[i][2] = (rand() % 4) + 1;
					} while (current == (int)v1[i][2]);
				}
				break;
			case 4:
				if (!bitmap.at((int)v1[i][0]).at(y2Quadrant)) {
					v1[i][1] += 2 / squareSize;
				}
				else {
					int current = v1[i][2];
					do {
						v1[i][2] = (rand() % 4) + 1;
					} while (current == (int)v1[i][2]);
				}
				break;
			default:
				break;
			}
		}
	}
}
// ---------------------------------------------------------------------------------------------------------------------------------------------> MORE CODE CHANGES BELOW



//Method to set the pressed key
void keyPressed(unsigned char key, int x, int y){
	keyStates[key] = true;
}

//Method to unset the released key
void keyUp(unsigned char key, int x, int y){
	keyStates[key] = false;
}

//Method to reset all the variable necessaries to start the game again
//Modified Code for Vaxman ---------------------------------------------------------------------------------------------------------------------> PLEASE REFER HERE
//Resets t value to 4, reinitializes our enemy list v1 to including the 4 orignal monsters and going through our Adder() function again
void resetGame(){
	over = false;
	xIncrement = 0;
	yIncrement = 0; 
	rotation = 0;
	/*monster1 = new float[3] {10.5, 8.5, 1.0};
	monster2 = new float[3] {13.5, 1.5, 2.0};
	monster3 = new float[3] {4.5, 6.5, 3.0};
	monster4 = new float[3] {2.5, 13.5, 4.0};*/
	points = 0;
	t = 4;
	v1.clear();
	v1.push_back(monster1);	v1.push_back(monster2);	v1.push_back(monster3);	v1.push_back(monster4);
	Adder();
	for (int i = 0; i < 256; i++){
		keyStates[i] = false;
	}
	food = { 1.5, 1.5, 1.5, 2.5, 1.5, 3.5, 1.5, 4.5, 1.5, 5.5, 1.5, 6.5, 1.5, 7.5, 1.5, 8.5, 1.5, 9.5, 1.5, 10.5, 1.5, 11.5, 1.5, 12.5, 1.5, 13.5, 2.5, 1.5, 2.5, 6.5, 2.5, 9.5, 2.5, 13.5, 3.5, 1.5, 3.5, 2.5, 3.5, 3.5, 3.5, 4.5, 3.5, 6.5, 3.5, 8.5, 3.5, 9.5, 3.5, 10.5, 3.5, 11.5, 3.5, 13.5, 4.5, 1.5, 4.5, 4.5, 4.5, 5.5, 4.5, 6.5, 4.5, 7.5, 4.5, 8.5, 4.5, 11.5, 4.5, 12.5, 4.5, 13.5, 5.5, 1.5, 5.5, 2.5, 5.5, 5.5, 5.5, 10.5, 5.5, 11.5, 5.5, 13.5, 6.5, 2.5, 6.5, 3.5, 6.5, 4.5, 6.5, 5.5, 6.5, 7.5, 6.5, 10.5, 6.5, 13.5, 7.5, 5.5, 7.5, 6.5, 7.5, 7.5, 7.5, 9.5, 7.5, 10.5, 7.5, 11.5, 7.5, 12.5, 7.5, 13.5, 8.5, 2.5, 8.5, 3.5, 8.5, 4.5, 8.5, 5.5, 8.5, 7.5, 8.5, 10.5, 8.5, 13.5, 9.5, 1.5, 9.5, 2.5, 9.5, 5.5, 9.5, 10.5, 9.5, 11.5, 9.5, 13.5, 10.5, 1.5, 10.5, 4.5, 10.5, 5.5, 10.5, 6.5, 10.5, 7.5, 10.5, 8.5, 10.5, 11.5, 10.5, 12.5, 10.5, 13.5, 11.5, 1.5, 11.5, 2.5, 11.5, 3.5, 11.5, 4.5, 11.5, 5.5, 11.5, 6.5, 11.5, 8.5, 11.5, 9.5, 11.5, 10.5, 11.5, 11.5, 11.5, 13.5, 12.5, 1.5, 12.5, 6.5, 12.5, 9.5, 12.5, 13.5, 13.5, 1.5, 13.5, 2.5, 13.5, 3.5, 13.5, 4.5, 13.5, 5.5, 13.5, 6.5, 13.5, 7.5, 13.5, 8.5, 13.5, 9.5, 13.5, 10.5, 13.5, 11.5, 13.5, 12.5, 13.5, 13.5 };
}
// ---------------------------------------------------------------------------------------------------------------------------------------------> MORE CODE CHANGES BELOW


//Method to update the movement of the pacman according to the movement keys pressed
void keyOperations(){
	//get current position
	float  x = (1.5 + xIncrement) * squareSize;
	float y = (1.5 + yIncrement) * squareSize;
	//update according to keys pressed
	if (keyStates['a']){
		x -= 2;
		int x1Quadrant = (int)((x - 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at(x1Quadrant).at((int)y/squareSize)){
			xIncrement -= 2 / squareSize;
			rotation = 2;
		}
	}
	if (keyStates['d']){
		x += 2;
		int x2Quadrant = (int)((x + 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at(x2Quadrant).at((int)y / squareSize)){
			xIncrement += 2 / squareSize;
			rotation = 0;
		}
	}
	if (keyStates['w']){
		y -= 2;
		int y1Quadrant = (int)((y - 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at((int)x/squareSize).at(y1Quadrant)){
			yIncrement -= 2 / squareSize;
			rotation = 3;
		}
	}
	if (keyStates['s']){
		y += 2;
		int y2Quadrant = (int)((y + 16.0 *cos(360 * M_PI / 180.0)) / squareSize);
		if (!bitmap.at((int)x / squareSize).at(y2Quadrant)){
			yIncrement += 2 / squareSize;
			rotation = 1;
		}
	}
	if (keyStates[' ']){
		if (!replay && over){
			resetGame();
			replay = true;
		}
		else if (replay && over){
			replay = false;
		}
	}
}

//Method to check if the game is over
//void gameOver(){
//	int pacmanX = (int)(1.5 + xIncrement);
//	int pacmanY = (int)(1.5 + yIncrement);
//	int monster1X = (int)(monster1[0]);
//	int monster1Y = (int)(monster1[1]);
//	int monster2X = (int)(monster2[0]);
//	int monster2Y = (int)(monster2[1]);
//	int monster3X = (int)(monster3[0]);
//	int monster3Y = (int)(monster3[1]);
//	int monster4X = (int)(monster4[0]);
//	int monster4Y = (int)(monster4[1]);
//	if (pacmanX == monster1X && pacmanY == monster1Y){
//		cout << "HIT!" << endl;
//	}
//	/*if (pacmanX == monster2X && pacmanY == monster2Y){
//		float* newMonster = new float[3]{ 6.5, 6.5, 1.0 };
//		v1.push_back(newMonster);
//	}
//	if (pacmanX == monster3X && pacmanY == monster3Y){
//		float* newMonster = new float[3]{ 1.5, 6.5, 1.0 };
//		v1.push_back(newMonster);
//	}
//	if (pacmanX == monster4X && pacmanY == monster4Y){
//		float* newMonster = new float[3]{ 8.5, 6.5, 1.0 };
//		v1.push_back(newMonster);
//	}*/
//	if (points == 106){
//		over = true;
//	}
//}


//Modified Code for Vaxman ---------------------------------------------------------------------------------------------------------------------> PLEASE REFER HERE
//Again, since we were dealing with only 4 in the original game, to iterate over all enemies as defined by t, we only need one check, and of course, the points check
//The game mechanic that changes here is that vaxman doesn't die but the enmey does, and its specific timer and float array[] is deleted as defined by vector.erase
//The 1:1 ratio of enemy tracker to timer was really helpful here
void gameOver() {
	if (t < 128){
		for (int i = 0; i < t; i++) {
			int pacmanX = (int)(1.5 + xIncrement);
			int pacmanY = (int)(1.5 + yIncrement);
			/*int monster1X = (int)(monster1[0]);
			int monster1Y = (int)(monster1[1]);
			int monster2X = (int)(monster2[0]);
			int monster2Y = (int)(monster2[1]);
			int monster3X = (int)(monster3[0]);
			int monster3Y = (int)(monster3[1]);
			int monster4X = (int)(monster4[0]);
			int monster4Y = (int)(monster4[1]);*/
			if (pacmanX == (int)v1[i][0] && pacmanY == (int)v1[i][1]) {
				v1.erase(v1.begin() + i);
				d_timer.erase(d_timer.begin() + i);
				t -= 1;
			}
			/*if (pacmanX == (int)v1[i][0] && pacmanY == (int)v1[i][1]){
				cout << "HIT!" << endl;
			}
			if (pacmanX == (int)v1[i][0] && pacmanY == (int)v1[i][1]){
				cout << "HIT!" << endl;
			}
			if (pacmanX == (int)v1[i][0] && pacmanY == (int)v1[i][1]){
				cout << "HIT!" << endl;
			}*/
		}
		

	}
	if (points == 106) {
		over = true;
	}
	/*if (t >= 128) {
		over = true;
	}*/
}
// ---------------------------------------------------------------------------------------------------------------------------------------------> MORE CODE CHANGES BELOW


//Method to display the results of the game at the ends
void resultsDisplay(){
	if (points == 106){
		//Won
		char* message = "*************************************";
		glRasterPos2f(170, 250);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "CONGRATULATIONS, YOU WON! ";
		glColor3f(1, 1, 1);
		glRasterPos2f(200, 300);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "*************************************";
		glRasterPos2f(170, 350);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "To start or restart the game, press the space key.";
		glRasterPos2f(170, 550);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
	}else {
		//Lost
		char* message = "*************************";
		glRasterPos2f(210, 250);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "SORRY, YOU LOST ... ";
		glColor3f(1, 1, 1);
		glRasterPos2f(250, 300);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "*************************";
		glRasterPos2f(210, 350);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "You got: ";
		glRasterPos2f(260, 400);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		string result = to_string(points);
		message = (char*)result.c_str();
		glRasterPos2f(350, 400);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = " points!";
		glRasterPos2f(385, 400);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
		message = "To start or restart the game, press the space key.";
		glRasterPos2f(170, 550);
		while (*message)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
	}
}

//Method to display the starting instructions
void welcomeScreen(){
	glClearColor(0, 0.2, 0.4, 1.0);
	char* message = "*************************************";
	glRasterPos2f(150, 200);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "Vaxman - by Ritvik Singh";
	glColor3f(1, 1, 1);
	glRasterPos2f(225, 250);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "*************************************";
	glRasterPos2f(150, 300);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *message++);
	message = "To control VAX-MAN use A to go right, D to go left, W to go up and S to go down.";
	glRasterPos2f(50, 400);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
	message = "To start or restart the game, press the space key.";
	glRasterPos2f(170, 450);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
	message = "Credit to Patricia Terol (Patriciateroltolsa)";
	glRasterPos2f(205, 500);
	while (*message)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);
}

//Method to display the screen and its elements
//Modified Code for Vaxman ---------------------------------------------------------------------------------------------------------------------> PLEASE REFER HERE


//Only require one call for update monster and draw monster since we're iterating over all every frame
void display(){
	if (points == 1){
		over = false;
	}
	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT);
	gameOver();



	if (replay){
		if (!over){

			int TimeChecker = glutGet(GLUT_ELAPSED_TIME)/1000;
			int t1 = v1.size();			
			//float temp[3]{ 10.5, 8.5, 1.0 };
			/*cout << TimeChecker << endl;*/
			/*if (TimeChecker % 10 == 0 && v2.size() == 0){	
				cout << "Size: " << t1 << endl;
				v2.push_back(1);
			}
			if (TimeChecker % 11 == 0) {
				v2 = {};
			}*/
			
			Double_time();
						
			drawLaberynth();
			drawFood((1.5 + xIncrement) * squareSize, (1.5 + yIncrement) * squareSize);
			drawPacman(1.5 + xIncrement, 1.5 + yIncrement, rotation);
			/*updateMonster(monster1, 1);
			updateMonster(monster2, 2);
			updateMonster(monster3, 3);
			updateMonster(monster4, 4);*/
			updateMonster();
			drawMonster();
			//drawMonster(monster1[0], monster1[1], 0.0, 1.0, 1.0); //cyan
			//drawMonster(monster2[0], monster2[1], 1.0, 0.0, 0.0); //red
			//drawMonster(monster3[0], monster3[1], 1.0, 0.0, 0.6); //magenta
			//drawMonster(monster4[0], monster4[1], 1.0, 0.3, 0.0); //orange
		}
		else {
			resultsDisplay();
		}
	}
	else {
		welcomeScreen();
	}
	glutSwapBuffers();
}
// ---------------------------------------------------------------------------------------------------------------------------------------------> END OF SIGNIFICANT CODE CHANGES



//Methdo to reshape the game is the screen size changes
void reshape(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glOrtho(0, 750, 750, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//Main functions that controls the running of the game
int main(int argc, char** argv){
	//initialize and create the screen
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(500, 50);
	glutCreateWindow("Vaxman - by Ritvik Singh");

	//define all the control functions


	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);

	//run the game
	Adder();
	cout << v1.size() << endl;

	init();

	

	glutMainLoop();
	return 0;
}

