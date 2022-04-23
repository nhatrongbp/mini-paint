#ifndef CIRCLEBRES_H
#define CIRCLEBRES_H
#include "Point.h"

//class to draw circle
class CircleBres {
protected:
	Point circlecenter;
	GLint circleradius;
public:
	CircleBres() { circlecenter.setx(0); circlecenter.sety(0); circleradius = 0; }
	CircleBres(int x, int y, int r) {
		circlecenter.setx(x);
		circlecenter.sety(y);
		circleradius = r;
	}
	void setCircleCenter(int x, int y) {
		circlecenter.setx(x);
		circlecenter.sety(y);
	}
	void setCircleCenter(Point c)	{ circlecenter = c; }
	Point getCircleCenter()			{ return circlecenter; }
	void setCircleRadius(GLint r)	{ circleradius = r; }
	GLint getCircleRadius()			{ return circleradius; }
	void draw() {
		void circlePlotPoints(GLint xc, GLint yc, GLint x, GLint y);
		GLint x = 0, y = circleradius, p = 3 - 2 * circleradius;
		circlePlotPoints(circlecenter.getx(), circlecenter.gety(), y, x);
		while (x < y) {
			if (p < 0) 
				p += 4 * x + 6;
			else {
				p += 4 * (x-y) + 10;
				y--;
			}
			x++;
			circlePlotPoints(circlecenter.getx(), circlecenter.gety(), x, y);
			circlePlotPoints(circlecenter.getx(), circlecenter.gety(), y, x);
		}
		circlePlotPoints(circlecenter.getx(), circlecenter.gety(), x, x);
	}
};

void circlePlotPoints(GLint xc, GLint yc, GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2d(xc + x, yc + y);
	glVertex2d(xc - x, yc - y);
	glVertex2d(xc - y, yc + x);
	glVertex2d(xc + y, yc - x);
	glEnd();
}

#endif


