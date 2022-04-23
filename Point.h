#ifndef POINT_H
#define POINT_H
#include <GL/glut.h>

//class to set point
class Point
{
private:
	GLint x, y;
public:
	Point* next;
	Point() 				{ x = y = 0; next = NULL; }
	Point(GLint x, GLint y)	{ this->x = x; this->y = y; }
	void setxy(GLint xVal, GLint yVal) {x = xVal;y = yVal;}
	void setx(GLint x)		{ this->x = x; }
	void sety(GLint y)		{ this->y = y; }
	GLint getx() const		{ return x; }
	GLint gety() const		{ return y; }
	void draw(){
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
};

#endif


