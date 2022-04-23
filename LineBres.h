#ifndef LINEBRES_H
#define LINEBRES_H
#include <iostream>
#include <string.h>
#include <math.h>
#include "Point.h"
using namespace std;
//class to draw line
class LineBres {
protected:
	Point LineStartPoint;
	Point LineEndPoint;
public:
	LineBres* next;
	LineBres() {
		LineStartPoint.setxy(0, 0);
		LineEndPoint.setxy(0, 0);
		next = NULL;
	}
	LineBres(Point s, Point e)	{ LineStartPoint = s; LineEndPoint = e; }
	void SetStartPoint(Point s)	{ LineStartPoint = s; }
	void SetEndPoint(Point e)	{ LineEndPoint = e; }
	Point getStartPoint()		{ return LineStartPoint; }
	Point getEndPoint()			{ return LineEndPoint; }

	void draw() {
		int x1 = LineStartPoint.getx(), y1 = LineStartPoint.gety();
		int x2 = LineEndPoint.getx(), y2 = LineEndPoint.gety();
		int Dx = x2-x1, Dy = y2-y1;
		double k = 1.0*Dy/Dx;
		if(-1 <= k && k <= 1){
			if(x1 > x2){
				swap(x1, x2);
				swap(y1, y2);
			}
		} else {
			if(y1 > y2){
				swap(x1, x2);
				swap(y1, y2);
			}
		}
		glBegin(GL_POINTS);
		Dx = x2-x1; Dy = y2-y1;
		k = 1.0*Dy/Dx;
		int x = x1, y = y1;
	   	if(0 <= k && k <= 1){
	   		int p = 2*Dy-Dx;
			glVertex2i(x, y);
			while (x < x2) {
				if (p < 0) p += 2*Dy;
				else {
		            p += 2*(Dy-Dx);
				    y++;
				}
				x++;
		        glVertex2i(x, y);
			}
		} else if(k > 1){
			int p = Dy-2*Dx;
			glVertex2i(x, y);
			while (y < y2) {
				if (p > 0) p -= 2*Dx;
				else {
		            p += 2*(Dy-Dx);
				    x++;
				}
				y++;
		        glVertex2i(x, y);
			}
		} else if(k < -1){
			int p = 0-Dy-2*Dx;
			glVertex2i(x, y);
			while (y < y2) {
				if (p < 0) p -= 2*Dx;
				else {
		            p -= 2*(Dy+Dx);
				    x--;
				}
				y++;
		        glVertex2i(x, y);
			}
		} else if(-1 <= k && k <= 0){
			int p = 2*Dy+Dx;
			glVertex2i(x, y);
			while (x < x2) {
				if (p > 0) p += 2*Dy;
				else {
		            p += 2*(Dy+Dx);
				    y--;
				}
				x++;
		        glVertex2i(x, y);
			}
		}
		glEnd();
	}
};

#endif


