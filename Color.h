#ifndef COLOR_H
#define COLOR_H
#include <GL/glut.h>

//class color
class Color {
protected:
	float red, green, blue;
public:
	Color() { 
		red = 0; green = 0; blue = 0;
		glColor3f(red, green, blue); 
	}
	Color(GLfloat r, GLfloat g, GLfloat b) {
		red = r;
		green = g;
		blue = b;
		glColor3f(red, green, blue);
	}
	void setRed(GLfloat r) { red = r; }
	void setGreen(GLfloat g) { green = g; }
	void setBlue(GLfloat b) { blue = b; }
	GLfloat getRed() { return red; }
	GLfloat getGreen() { return green; }
	GLfloat getBlue() { return blue; }
};
#endif


