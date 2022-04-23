#ifndef ECLIPSE_H
#define ECLIPSE_H
#include <math.h>
#include "Point.h"

//class to draw eclipse
class Eclipse {
protected:
	GLint eclipse_radius_x;
	GLint eclipse_radius_y;
	Point eclipsecenter;
public:
	Eclipse() {
		eclipsecenter.setxy(0, 0); 
		eclipse_radius_x = 0; 
		eclipse_radius_y = 0;
	}
	void setEclipseCenter(Point c) { eclipsecenter = c; }
	void setEclipseRadiusX(GLint rad_x) { eclipse_radius_x = rad_x; }
	void setEclipseRadiusY(GLint rad_y) { eclipse_radius_y = rad_y; }
	Point getEclipseCenter() { return eclipsecenter; }
	GLint getEclipseRadiusX() { return eclipse_radius_x; }
	GLint getEclipseRadiusY() { return eclipse_radius_y; }
	void draw() {
		void ellipsePlotPoints(int, int, int, int);
		int a = eclipse_radius_x, b = eclipse_radius_y;
		int a2 = a*a;	//a^2
		int b2 = b*b;	//b^2
		int x = 0, y = b;
		int fx = 0, fy = 2 * a2 * y;
		ellipsePlotPoints(eclipsecenter.getx(), eclipsecenter.gety(), x, y);
		/* Region 1 */
		int p = round(b2 - (a2*b) + (0.25*a));
		while (fx < fy) {
			x++;
			fx += 2*b2;
			if (p < 0)
				p += b2*(2*x+3);
			else {
				y--;
				p += b2*(2*x +3) + a2*(-2*y +2); 
				fy -= 2*a2;
			}
			ellipsePlotPoints(eclipsecenter.getx(), eclipsecenter.gety(), x, y);
		}
		/* Region 2 */
		p = round(b2*(x+0.5)*(x+0.5) + a2*(y-1)*(y-1) - a2*b2);
		while (y > 0) {
			y--;
			fy -= 2*a2;
			if (p > 0)
				p+=a2*(3 - 2*y); 
			else {
				x++;
				fx += 2*b2; 
				p += b2*(2*x+2) + a2*(-2*y +3);
			}
			ellipsePlotPoints(eclipsecenter.getx(), eclipsecenter.gety(), x, y);
		}
	}
};

void ellipsePlotPoints(int xCenter, int yCenter, int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2d(xCenter + x, yCenter + y);
	glVertex2d(xCenter - x, yCenter + y);
	glVertex2d(xCenter + x, yCenter - y);
	glVertex2d(xCenter - x, yCenter - y);
	glEnd();
}

#endif


