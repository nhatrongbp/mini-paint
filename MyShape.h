#ifndef MYSHAPE_H
#define MYSHAPE_H
#include "FreePoint.h"
#include "FreeLine.h"
#include "CircleBres.h"
#include "Eclipse.h"
#include "Polygon.h"
#include "Color.h"
//class for record every drawn shapes: using multi inherit
class MyShape : public Point, public FreePoint, public LineBres, public FreeLine, public CircleBres, public Eclipse, public Polygon {
protected:
	short 	shapeType;
	Color 	shapeColor;
	int 	shapeWidth;
	bool 	isEraseShape;	//if this shape is an eraser or a brush
public:
	MyShape() {}
	void setShapeType(char st) 		{ shapeType = st; }
	char getShapeType() 			{ return shapeType; }
	void setShapeColor(Color sc) 	{ shapeColor = sc; }
	void setShapeColor(GLfloat BR_R, GLfloat BR_G, GLfloat BR_B) { shapeColor = Color(BR_R, BR_G, BR_B); }
	Color getColor() 				{ return shapeColor; }
	void setShapeWidth(int sw) 		{ shapeWidth = sw; }
	int getBorderWidth() 			{ return shapeWidth; }
	void setEraseShape(bool b) 		{ isEraseShape = b; }
	bool getEraseShape() 			{ return isEraseShape; }
	void draw(GLfloat BG_R, GLfloat BG_G, GLfloat BG_B) {
		glColor3f(shapeColor.getRed(), shapeColor.getGreen(), shapeColor.getBlue());
		if(isEraseShape) glColor3f(BG_R, BG_G, BG_B);
		glPointSize(shapeWidth);
		if(7 <= shapeType && shapeType <= 20) Polygon::balance4Lines();//RECTANGLE
		switch (shapeType){
			case 1:	Point::draw(); 				break;
			case 2:	FreePoint::draw();			break;
			case 3:	LineBres::draw(); 			break;
			case 4:	FreeLine::draw(); 			break;
			case 5:	CircleBres::draw(); 		break;
			case 6:	Eclipse::draw();			break;
			case 7:	Polygon::drawTriangle();	break;
			case 8:	Polygon::drawRTriangle();	break;
			case 9:	Polygon::drawRectangle();	break;
			case 10:Polygon::drawDiamond();		break;
			case 11:Polygon::drawPentagon();	break;
			case 12:Polygon::drawHexagon();		break;
			case 13:Polygon::drawRightArrow();	break;
			case 14:Polygon::drawLeftArrow();	break;
			case 15:Polygon::drawUpArrow();		break;
			case 16:Polygon::drawDownArrow();	break;
			case 17:Polygon::drawFourStar();	break;
			case 18:Polygon::drawFiveStar();	break;
			case 19:Polygon::drawSixStar();		break;
			case 20:Polygon::drawHeart();		break;
			default: 							break;
		}
	}
};

#endif


