#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "MyShape.h"
// All available shape modes in this mini paint project:
#define POINT		1	//done
#define FREEPOINT	2	//done
#define LINE		3	//done
#define FREELINE	4	//done
#define CIRCLE		5	//done
#define ECLIPSE		6	//done
#define TRIANGLE	7	//done
#define RTRIANGLE	8	//done
#define RECTANGLE	9	//done
#define DIAMOND		10	//done
#define PENTAGON	11	//done
#define HEXAGON		12	//done
#define RIGHTARROW	13	//done
#define LEFTARROW	14	//done
#define UPARROW		15	//done
#define DOWNARROW	16	//done
#define FOURSTAR	17	//done
#define FIVESTAR	18	//done
#define SIXSTAR		19	//done
#define HEART		20	//doing
using namespace std;

					//----------GLOBAL VARIABLES---------

//set default shape type as FREELINE
short currentShapeType = FREELINE;//FREELINE;

//vector to store drawn shapes and deleted shapes
vector<MyShape> drawnShapes, erasedShapes;
vector<MyShape>::iterator shapeIterator;

//For record information of current drawing shapes
MyShape currentShape;

//window size
GLfloat Xsize = 1200, Ysize = 600;

//Scene Mode
int scene = 0;

//Background color (Erase color)
GLfloat BG_R = 1, BG_G = 1, BG_B = 1;

//Brush color (Shape color)
GLfloat BR_R = 0, BR_G = 0, BR_B = 0;

//Brush size & Erase size
int brushSize = 3.0, eraseSize = 3.0;
const int MaxBrushSize = 20.0;
const int MinBrushSize = 1.0;

//check if user press left button key before entering working space
int startflag = 0;

//check if the pen is up/down
bool isDrawing = false;

//check if the program is in brush/erase mode
bool isErasing = false;

//coordinates of the MOST RECENTLY mouse click point
int mouseX, mouseY;

					//----------FUNCTIONS FOR DISPLAYING INFORMATIONS---------

void DisplayString(int x, int y, char* string, int font){
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		if (font == 1)	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
		if (font == 2)	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
		if (font == 3)	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
		if (font == 4)	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);
	}
}

void FrontPage(void){
	char title[] 	= "Ky thuat do hoa";
	char project[] 	= "De tai nhom: mini bresenham paint app";
	char member[] 	= "Thanh vien:";
	char creator1[]	= "Member 1 msv";
	char creator2[]	= "Member 2 msv";
	char start[] 	= "PRESS SPACE KEY TO START";
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
	DisplayString(Xsize * 3.5 / 10, Ysize * 9 / 10, title, 1);
	DisplayString(Xsize * 3.5 / 10, Ysize * 8 / 10, project, 1);
	DisplayString(Xsize * 3.5 / 10, Ysize * 6 / 10, member, 2);
	DisplayString(Xsize * 3.5 / 10, Ysize * 5 / 10, creator1, 2);
	DisplayString(Xsize * 3.5 / 10, Ysize * 4 / 10, creator2, 2);
	DisplayString(Xsize * 3.5 / 10, Ysize * 2 / 10, start, 1);
	glutPostRedisplay();
	glFlush();

}

void KeyShortcutInfo() {
	glColor3f(0.2, 0.2, 0.2);
	char info1[] = "Left Button: Drawing";
	char info2[] = "Right Button: Menu List";
	char info3[] = "+: Increase Brush Width";
	char info4[] = "-: Decrease Brush Width";
	char info5[] = "]: Increase Erase Width";
	char info6[] = "[: Decrease Erase Width";
	char info7[] = "Z/z: Undo";
	char info8[] = "Y/y: Redo";
	char info9[] = "N/n: New Blank Page";
	char info10[] = "E/e: Turn on/off Erase mode";
	char info11[] = "ESC: Set Window To Original Position";
	DisplayString(Xsize * 2.65 / 10, Ysize * 9.45 / 10, info1, 4);
	DisplayString(Xsize * 2.65 / 10, Ysize * 9.15 / 10, info2, 4);
	DisplayString(Xsize * 3.75 / 10, Ysize * 9.45 / 10, info3, 4);
	DisplayString(Xsize * 3.75 / 10, Ysize * 9.15 / 10, info4, 4);
	DisplayString(Xsize * 4.95 / 10, Ysize * 9.45 / 10, info5, 4);
	DisplayString(Xsize * 4.95 / 10, Ysize * 9.15 / 10, info6, 4);
	DisplayString(Xsize * 6.1 / 10, Ysize * 9.45 / 10, info7, 4);
	DisplayString(Xsize * 6.1 / 10, Ysize * 9.15 / 10, info8, 4);
	DisplayString(Xsize * 6.7 / 10, Ysize * 9.45 / 10, info9, 4);
	DisplayString(Xsize * 6.7 / 10, Ysize * 9.15 / 10, info10, 4);
	DisplayString(Xsize * 8.2 / 10, Ysize * 9.45 / 10, info11, 4);
}

void ValuesInfo() {
	char Color_info[]	= "Color";
	char Size_info[]	= "Size";
	char Brush_info[]	= "Brush";
	char Erase_info[]	= "Erase";
	char Shape[21][21] = {
		"Shape", "Point", "FreeDotted", "Line", "FreeHand",
		"Circle", "Eclipse", "Triangle", "RightTriangle",
		"Rectangle", "Diamond", "Pentagon", "Hexagon",
		"RightArrow", "LeftArrow", "UpArrow", "DownArrow",
		"FourStar", "FiveStar", "SixStar", "Heart"
	};
	
	//background menu
	glColor3f(0.95, 0.95, 0.95);
	glBegin(GL_QUADS);
	glVertex2f(Xsize * 0 / 10, Ysize * 10 / 10);
	glVertex2f(Xsize * 10 / 10, Ysize * 10 / 10);
	glVertex2f(Xsize * 10 / 10, Ysize * 8.75 / 10);
	glVertex2f(Xsize * 0 / 10, Ysize * 8.75 / 10);
	glEnd();
	
	glColor3f(0.85, 0.85, 0.85);
	if(!isErasing) {
		glBegin(GL_QUADS);
		glVertex2f(Xsize * 0.8 / 10, Ysize * 10 / 10);
		glVertex2f(Xsize * 1.82 / 10, Ysize * 10 / 10);
		glVertex2f(Xsize * 1.82 / 10, Ysize * 8.75 / 10);
		glVertex2f(Xsize * 0.8 / 10, Ysize * 8.75 / 10);
		glEnd();
	} else {
		glBegin(GL_QUADS);
		glVertex2f(Xsize * 1.82 / 10, Ysize * 10 / 10);
		glVertex2f(Xsize * 2.42 / 10, Ysize * 10 / 10);
		glVertex2f(Xsize * 2.42 / 10, Ysize * 8.75 / 10);
		glVertex2f(Xsize * 1.82 / 10, Ysize * 8.75 / 10);
		glEnd();
	}
	glBegin(GL_LINES);
	glVertex2f(Xsize * 10 / 10, Ysize * 8.75 / 10);
	glVertex2f(Xsize * 0 / 10, Ysize * 8.75 / 10);
	glVertex2f(Xsize * 0.81 / 10, Ysize * 9.9 / 10);
	glVertex2f(Xsize * 0.81 / 10, Ysize * 8.85 / 10);
	glVertex2f(Xsize * 1.81 / 10, Ysize * 9.9 / 10);
	glVertex2f(Xsize * 1.81 / 10, Ysize * 8.85 / 10);
	glVertex2f(Xsize * 2.41 / 10, Ysize * 9.9 / 10);
	glVertex2f(Xsize * 2.41 / 10, Ysize * 8.85 / 10);
	glEnd();
	
	//text menu
	glColor3f(0.2, 0.2, 0.2);
	switch (currentShapeType) {
		case POINT: 	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[1], 4); break;
		case FREEPOINT:	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[2], 4); break;
		case LINE: 		DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[3], 4); break;
		case FREELINE: 	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[4], 4); break;
		case CIRCLE: 	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[5], 4); break;
		case ECLIPSE: 	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[6], 4); break;
		case TRIANGLE: 	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[7], 4); break;
		case RTRIANGLE:	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[8], 4); break;
		case RECTANGLE:	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[9], 4); break;
		case DIAMOND:	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[10], 4); break;
		case PENTAGON:	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[11], 4); break;
		case HEXAGON:	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[12], 4); break;
		case RIGHTARROW:DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[13], 4); break;
		case LEFTARROW:	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[14], 4); break;
		case UPARROW:	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[15], 4); break;
		case DOWNARROW:	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[16], 4); break;
		case FOURSTAR:	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[17], 4); break;
		case FIVESTAR:	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[18], 4); break;
		case SIXSTAR:	DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[19], 4); break;
		case HEART:		DisplayString(Xsize * 0.25 / 10, Ysize * 9.15 / 10, Shape[20], 4); break;
		default: break;
	}
	DisplayString(Xsize * 0.25 / 10, Ysize * 8.9 / 10, Shape[0], 4);
	DisplayString(Xsize * 1.0 / 10, Ysize * 8.9 / 10, Color_info, 4);
	DisplayString(Xsize * 1.4 / 10, Ysize * 8.9 / 10, Size_info, 4);
	DisplayString(Xsize * 2.0 / 10, Ysize * 8.9 / 10, Size_info, 4);
	DisplayString(Xsize * 2.0 / 10, Ysize * 9.15 / 10, Erase_info, 4);
	DisplayString(Xsize * 1.0 / 10, Ysize * 9.15 / 10, Brush_info, 4);
	DisplayString(Xsize * 1.4 / 10, Ysize * 9.15 / 10, Brush_info, 4);
	
	//content menu
	glColor3f(0.65, 0.65, 0.65);
	glBegin(GL_LINE_LOOP);
	glVertex2f(Xsize * 1.01 / 10, Ysize * 9.44 / 10);
	glVertex2f(Xsize * 1.22 / 10, Ysize * 9.44 / 10);
	glVertex2f(Xsize * 1.22 / 10, Ysize * 9.86 / 10);
	glVertex2f(Xsize * 1.01 / 10, Ysize * 9.86 / 10);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(BR_R, BR_G, BR_B);
	glBegin(GL_QUADS);
	glVertex2f(Xsize * 1.03 / 10, Ysize * 9.475 / 10);
	glVertex2f(Xsize * 1.20 / 10, Ysize * 9.475 / 10);
	glVertex2f(Xsize * 1.20 / 10, Ysize * 9.825 / 10);
	glVertex2f(Xsize * 1.03 / 10, Ysize * 9.825 / 10);
	glEnd();
	if(isErasing){
		glPointSize(brushSize);
		glBegin(GL_QUADS);
		glVertex2f(Xsize * 1.38 / 10, Ysize * 9.65 / 10 - brushSize*1.0/2);
		glVertex2f(Xsize * 1.63 / 10, Ysize * 9.65 / 10 - brushSize*1.0/2);
		glVertex2f(Xsize * 1.63 / 10, Ysize * 9.65 / 10 + brushSize*1.0/2);
		glVertex2f(Xsize * 1.38 / 10, Ysize * 9.65 / 10 + brushSize*1.0/2);
		glEnd();
		glPointSize(eraseSize);
	} else {
		glBegin(GL_QUADS);
		glVertex2f(Xsize * 1.38 / 10, Ysize * 9.65 / 10 - brushSize*1.0/2);
		glVertex2f(Xsize * 1.63 / 10, Ysize * 9.65 / 10 - brushSize*1.0/2);
		glVertex2f(Xsize * 1.63 / 10, Ysize * 9.65 / 10 + brushSize*1.0/2);
		glVertex2f(Xsize * 1.38 / 10, Ysize * 9.65 / 10 + brushSize*1.0/2);
		glEnd();
	}
	glColor3f(BG_R, BG_G, BG_B);
	if(!isErasing){
		glPointSize(eraseSize);
		glBegin(GL_QUADS);
		glVertex2f(Xsize * 1.98 / 10, Ysize * 9.65 / 10 - eraseSize*1.0/2);
		glVertex2f(Xsize * 2.23 / 10, Ysize * 9.65 / 10 - eraseSize*1.0/2);
		glVertex2f(Xsize * 2.23 / 10, Ysize * 9.65 / 10 + eraseSize*1.0/2);
		glVertex2f(Xsize * 1.98 / 10, Ysize * 9.65 / 10 + eraseSize*1.0/2);
		glEnd();
		glPointSize(brushSize);
	} else {
		glBegin(GL_QUADS);
		glVertex2f(Xsize * 1.98 / 10, Ysize * 9.65 / 10 - eraseSize*1.0/2);
		glVertex2f(Xsize * 2.23 / 10, Ysize * 9.65 / 10 - eraseSize*1.0/2);
		glVertex2f(Xsize * 2.23 / 10, Ysize * 9.65 / 10 + eraseSize*1.0/2);
		glVertex2f(Xsize * 1.98 / 10, Ysize * 9.65 / 10 + eraseSize*1.0/2);
		glEnd();
	}
}


					//----------FOR GLUT-DEFINED FUNCTIONS---------
// Mouse callback routine.
void MouseFunc(int button, int state, GLint x, GLint y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){		//left mouse down -> pen down -> get start point
		//a "point" shape needs only the start point, so it must be drawn here immediately
		//...while the others need both start & end point
		if (currentShapeType == POINT && !isErasing) {
			isDrawing = false;
			currentShape.setxy(x, Ysize - y);				//currentShape (which is a point) has been drawn completely
			drawnShapes.push_back(currentShape);				//add currentShape into drawnShapes
			MyShape temp;										//reset the currentShape
			currentShape = temp;
			startflag = 0;
			return;
		}
		startflag = 1;
		isDrawing = true;
		mouseX = x;
		mouseY = y;
	}
	if (startflag == 1)
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){	//left mouse up -> pen up -> get end point
			isDrawing = false;									//currentShape has been drawn completely
			drawnShapes.push_back(currentShape);				//add currentShape into drawnShapes
			MyShape temp;										//reset the currentShape
			currentShape = temp;
			startflag = 0;
		}
}

//Mouse Motion callback for key down
void MotionFunc(int x, int y){
	if (isErasing) {	//an erase is always in freeline mode
		currentShape.InsertFreeLineNode(new LineBres(Point(x, Ysize - y), Point(x, Ysize - y)));
		return;
	}
	if (startflag && isDrawing){
		switch (currentShapeType){
		case POINT:
			//a "point" shape needs only the start point and it had been drawn in the MouseController function above
			break;
		case FREEPOINT:
			currentShape.InsertFreePointNode(new Point(x, Ysize - y));
			break;
		case LINE:
			currentShape.SetStartPoint(Point(mouseX, Ysize - mouseY));
			currentShape.SetEndPoint(Point(x, Ysize - y));
			break;
		case FREELINE:
			currentShape.InsertFreeLineNode(new LineBres(Point(x, Ysize - y), Point(x, Ysize - y)));
			break;
		case CIRCLE:
			//set center of mouse press
			currentShape.setCircleCenter(Point(mouseX, Ysize - mouseY));
			currentShape.setCircleRadius(
				max(
					abs(currentShape.getCircleCenter().getx() - x),
					abs(currentShape.getCircleCenter().gety() + y - (int)Ysize)
				)
			);
			break;
		case ECLIPSE:
			currentShape.setEclipseCenter(Point(mouseX, Ysize - mouseY));
			currentShape.setEclipseRadiusX(abs(currentShape.getEclipseCenter().getx() - x));
			currentShape.setEclipseRadiusY(abs(currentShape.getEclipseCenter().gety() + y - Ysize));
			break;
		default:	//A POLYGON
			//both top line and right line	start at MOST RECENTLY mouse click point
			//	 							end at CURRENT mouse move point
			currentShape.setRectangleTop(LineBres(Point(mouseX, Ysize - mouseY), Point(x, Ysize - mouseY)));
			currentShape.setRectangleRight(LineBres(Point(mouseX, Ysize - mouseY), Point(mouseX, Ysize - y)));

			//the difference between left and right is value of x
			currentShape.setRectangleLeft(
				LineBres(
					Point(x, currentShape.getRectangleRight().getStartPoint().gety()), 
					Point(x, currentShape.getRectangleRight().getEndPoint().gety())
				)
			);

			//the difference between top and bottom is value of y
			currentShape.setRectangleBottom(
				LineBres(
					Point(currentShape.getRectangleTop().getStartPoint().getx(), Ysize - y), 
					Point(currentShape.getRectangleTop().getEndPoint().getx(), Ysize - y)
				)
			);
			break;
		}
	}
}

//drawing function
void DisplayFunc(void) {
	if (scene == 0) {
		FrontPage();
	}
	else {
		glClear(GL_COLOR_BUFFER_BIT);
		//set the color of background 
		//It will be changed when getting an user input(glutPostRedisplay and glutswapbuffers will recall this drawing function)
		glClearColor(BG_R, BG_G, BG_B, 1);
		
		//redraw all drawn shapes
		shapeIterator = drawnShapes.begin();
		while (shapeIterator != drawnShapes.end()) {
			shapeIterator->draw(BG_R, BG_G, BG_B);
			shapeIterator++;
		}

		//config currentShape
		//an erase is always in freeline mode
		currentShape.setShapeType((isErasing) ? FREELINE : currentShapeType);
		//an erase has same color as background color
		currentShape.setShapeColor((isErasing) ? Color(BG_R, BG_G, BG_B) : Color(BR_R, BR_G, BR_B));
		//determine if the current shape is an erase or not
		currentShape.setEraseShape((isErasing) ? true : false);
		//an erase has its eraseSize and a brush has its brushSize
		currentShape.setShapeWidth((isErasing) ? eraseSize : brushSize);
		currentShape.draw(BG_R, BG_G, BG_B);

		//display the main menu
		ValuesInfo();		
		//display all key shortcuts
		KeyShortcutInfo();
		//declare here because we dont want to draw when haven't start(case when user no press space bar to start)
		glutMouseFunc(MouseFunc);
		glutMotionFunc(MotionFunc);

		//To redisplay and swap buffer when key pressed or other user input is detected
		glutPostRedisplay();
		glFlush();
	}
}

//Reshape function
void ReshapeFunc(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set viewing box dimensions equal to window dimensions.
	glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);

	// Pass the size of the OpenGL window to globals.
	Xsize = w;
	Ysize = h;
}

//keyboard function
void KeyboardFunc(GLubyte key, GLint x, GLint y){
	switch (key){
	case 27:
		glutPositionWindow(10, 30);
		glutReshapeWindow(1200, 600);
		break;
	case ' ':
		scene = 1;
		DisplayFunc();
		break;
	case 'Z':
	case 'z':
		if (!drawnShapes.empty()){
			erasedShapes.push_back(drawnShapes[drawnShapes.size()-1]);
			drawnShapes.pop_back();
		}
		break;
	case 'Y':
	case 'y':
		if (!erasedShapes.empty()){
			drawnShapes.push_back(erasedShapes[erasedShapes.size()-1]);
			erasedShapes.pop_back();
		}
		break;
	case 'N':
	case 'n':
		while (!drawnShapes.empty())
			drawnShapes.pop_back();
		break;
	case '+':
	case '=':
		if (brushSize < MaxBrushSize)
			brushSize++;
		break;
	case '-':
	case '_':
		if (brushSize > MinBrushSize)
			brushSize--;
		break;
	case '[':
		if (eraseSize > MinBrushSize)
			eraseSize--;
		break;
	case ']':
		if (eraseSize < MaxBrushSize)
			eraseSize++;
		break;
	case 'E':
	case 'e':
		if(isErasing) isErasing = false;
		else isErasing = true;
		break;
	default: break;
	}
	glutPostRedisplay();
}

					//----------RIGHT-CLICK MENU---------
//Menu Controller
void MainMenuController(int id) {
	if (id == 41)
		exit(0);

	if (id == 42) {
		glutRemoveMenuItem(5);
		glutFullScreen();
		glutAddMenuEntry("Exit Full Screen", 43);
	}
	if (id == 43) {
		glutRemoveMenuItem(5);
		glutPositionWindow(0, 30);
		glutReshapeWindow(1200, 600);
		glutAddMenuEntry("Full Screen", 42);
	}
}

void BgColorMenuController(int id) {
	if (id == 1)	BG_R = 1,	BG_G = 1,	BG_B = 1;	//white
	if (id == 2)	BG_R = 0,	BG_G = 0,	BG_B = 0;	//black
	if (id == 3)	BG_R = 1,	BG_G = 0,	BG_B = 0;	//red
	if (id == 4)	BG_R = 1,	BG_G = 0.5,	BG_B = 0;	//orange
	if (id == 5)	BG_R = 1,	BG_G = 1, 	BG_B = 0;	//yellow
	if (id == 6)	BG_G = 1, 	BG_B = 0,	BG_R = 0;	//green
	if (id == 7)	BG_B = 1, 	BG_R = 0,	BG_G = 0;	//blue
	if (id == 8)	BG_R = 1,	BG_B = 1, 	BG_G = 0;	//purple
	if (id == 9)	BG_R = 0.5, BG_G = 0,	BG_B = 0;	//brown
	if (id == 10)	BG_R = 1,	BG_B = 1,	BG_G = 0.7;	//pink
}

void ShapeMenuController(int id) {
	if (id == 11)	currentShapeType = POINT;
	if (id == 12)	currentShapeType = FREEPOINT;
	if (id == 13)	currentShapeType = LINE;
	if (id == 14)	currentShapeType = FREELINE;
	if (id == 15)	currentShapeType = CIRCLE;
	if (id == 16)	currentShapeType = ECLIPSE;
	if (id == 17)	currentShapeType = TRIANGLE;
	if (id == 18)	currentShapeType = RTRIANGLE;
	if (id == 19)	currentShapeType = RECTANGLE;
	if (id == 20)	currentShapeType = DIAMOND;
	if (id == 21)	currentShapeType = PENTAGON;
	if (id == 22)	currentShapeType = HEXAGON;
	if (id == 23)	currentShapeType = RIGHTARROW;
	if (id == 24)	currentShapeType = LEFTARROW;
	if (id == 25)	currentShapeType = UPARROW;
	if (id == 26)	currentShapeType = DOWNARROW;
	if (id == 27)	currentShapeType = FOURSTAR;
	if (id == 28)	currentShapeType = FIVESTAR;
	if (id == 29)	currentShapeType = SIXSTAR;
	if (id == 30)	currentShapeType = HEART;
}

void ColorMenuController(int id){
	if (id == 31)	BR_R = 1,	BR_G = 1,	BR_B = 1;	//white
	if (id == 32)	BR_R = 0,	BR_G = 0,	BR_B = 0;	//black
	if (id == 33)	BR_R = 1,	BR_G = 0,	BR_B = 0;	//red
	if (id == 34)	BR_R = 1,	BR_G = 0.5,	BR_B = 0;	//orange
	if (id == 35)	BR_R = 1,	BR_G = 1,	BR_B = 0;	//yellow
	if (id == 36)	BR_G = 1,	BR_B = 0,	BR_R = 0;	//green
	if (id == 37)	BR_B = 1,	BR_R = 0,	BR_G = 0;	//blue
	if (id == 38)	BR_R = 1,	BR_B = 1,	BR_G = 0;	//purple
	if (id == 39)	BR_R = 0.5,	BR_G = 0,	BR_B = 0;	//brown
	if (id == 40)	BR_R = 1,	BR_B = 1,	BR_G = 0.7;	//pink
}

//Menu Func
void MenuFunc(){
	int BG_Color_submenu = glutCreateMenu(BgColorMenuController);
	glutAddMenuEntry("White", 1);
	glutAddMenuEntry("Black", 2);
	glutAddMenuEntry("Red", 3);
	glutAddMenuEntry("Orange", 4);
	glutAddMenuEntry("Yellow", 5);
	glutAddMenuEntry("Green", 6);
	glutAddMenuEntry("Blue", 7);
	glutAddMenuEntry("Purple", 8);
	glutAddMenuEntry("Brown", 9);
	glutAddMenuEntry("Pink", 10);

	int Shape_submenu = glutCreateMenu(ShapeMenuController);
	glutAddMenuEntry("Point", 11);
	glutAddMenuEntry("Free dotted hand", 12);
	glutAddMenuEntry("Line", 13);
	glutAddMenuEntry("Free Hand", 14);
	glutAddMenuEntry("Circle", 15);
	glutAddMenuEntry("Eclipse", 16);
	glutAddMenuEntry("Triangle", 17);
	glutAddMenuEntry("RightTriangle", 18);
	glutAddMenuEntry("Rectangle", 19);
	glutAddMenuEntry("Diamond", 20);
	glutAddMenuEntry("Pentagon", 21);
	glutAddMenuEntry("Hexagon", 22);
	glutAddMenuEntry("RightArrow", 23);
	glutAddMenuEntry("LeftArrow", 24);
	glutAddMenuEntry("UpArrow", 25);
	glutAddMenuEntry("DownArrow", 26);
	glutAddMenuEntry("FourStar", 27);
	glutAddMenuEntry("FiveStar", 28);
	glutAddMenuEntry("SixStar", 29);
	glutAddMenuEntry("Heart", 30);

	int Color_submenu = glutCreateMenu(ColorMenuController);
	glutAddMenuEntry("White", 31);
	glutAddMenuEntry("Black", 32);
	glutAddMenuEntry("Red", 33);
	glutAddMenuEntry("Orange", 34);
	glutAddMenuEntry("Yellow", 35);
	glutAddMenuEntry("Green", 36);
	glutAddMenuEntry("Blue", 37);
	glutAddMenuEntry("Purple", 38);
	glutAddMenuEntry("Brown", 39);
	glutAddMenuEntry("Pink", 40);

	glutCreateMenu(MainMenuController);
	glutAddSubMenu("Background Color", BG_Color_submenu);
	glutAddSubMenu("Shape", Shape_submenu);
	glutAddSubMenu("Color", Color_submenu);
	glutAddMenuEntry("Exit", 41);
	glutAddMenuEntry("Full Screen", 42);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowPosition(0, 30);
	glutInitWindowSize(Xsize, Ysize);
	glutCreateWindow("The mini 'code & fix' paint");
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	MenuFunc();
	glutMainLoop();
}


