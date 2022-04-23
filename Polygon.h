#ifndef POLYGON_H
#define POLYGON_H
#include "LineBres.h"
#define RAD *3.14159/180
//class to draw rectangle
class Polygon {
protected:
	LineBres rectangle_top;
	LineBres rectangle_right;
	LineBres rectangle_bottom;
	LineBres rectangle_left;

public:
	Polygon() :
		rectangle_top(Point(0, 0), Point(0, 0)), 
		rectangle_right(Point(0, 0), Point(0, 0)), 
		rectangle_bottom(Point(0, 0), Point(0, 0)), 
		rectangle_left(Point(0, 0), Point(0, 0)) {}

	void setRectangleTop(LineBres t) { rectangle_top = t; }
	void setRectangleRight(LineBres r) { rectangle_right = r; }
	void setRectangleBottom(LineBres b) { rectangle_bottom = b; }
	void setRectangleLeft(LineBres l) { rectangle_left = l; }
	LineBres getRectangleTop() { return rectangle_top; }
	LineBres getRectangleRight() { return rectangle_right; }
	LineBres getRectangleBottom() { return rectangle_bottom; }
	LineBres getRectangleLeft() { return rectangle_left; }
	
	Point intersect(LineBres L1, LineBres L2) {
		GLint x1 = L1.getStartPoint().getx();
		GLint y1 = L1.getStartPoint().gety();
		GLint x2 = L1.getEndPoint().getx();
		GLint y2 = L1.getEndPoint().gety();
		GLint A1 = y2 - y1, B1 = x1 - x2;
		GLint C1 = x1*y2 - x2*y1;
		 x1 = L2.getStartPoint().getx();
		 y1 = L2.getStartPoint().gety();
		 x2 = L2.getEndPoint().getx();
		 y2 = L2.getEndPoint().gety();
		GLint A2 = y2 - y1, B2 = x1 - x2;
		GLint C2 = x1*y2 - x2*y1;
		GLint det = A1 * B2 - A2 * B1;
		if (det == 0) {
		    // Lines are parallel or coincident
		    if (A1 * C2 == A2 * C1) {
		        // Lines are coincident
		        return Point(0, 0);
		    }
		    else {
		        // Lines are parallel
		        return Point(0, 0);
		    }
		}
		else {
		    GLint x = (B2 * C1 - B1 * C2) / det;
		    GLint y = (A1 * C2 - A2 * C1) / det;
		    return Point(x, y);
		}
	}
	
	void balance4Lines() {
		if (rectangle_top.getStartPoint().gety() < rectangle_bottom.getStartPoint().gety()) {
			swap(rectangle_top, rectangle_bottom);
		}
		Point A = rectangle_top.getStartPoint();
		Point B = rectangle_top.getEndPoint();
		Point C = rectangle_bottom.getStartPoint();
		Point D = rectangle_bottom.getEndPoint();
		if (A.getx() > B.getx()) swap(A, B);
		if (D.getx() > C.getx()) swap(D, C);
		rectangle_left.SetStartPoint(D);
		rectangle_left.SetEndPoint(A);
		rectangle_right.SetStartPoint(C);
		rectangle_right.SetEndPoint(B);
		rectangle_top.SetStartPoint(A);
		rectangle_top.SetEndPoint(B);
		rectangle_bottom.SetStartPoint(D);
		rectangle_bottom.SetEndPoint(C);
//		if (rectangle_top.getStartPoint().getx() < rectangle_top.getEndPoint().getx()) cout << 2 << endl;
//		if(rectangle_right.getEndPoint().gety() > rectangle_right.getStartPoint().gety()) cout << 1 <<endl;
	}
	
	void drawRectangle() {
		rectangle_top.draw();
		rectangle_right.draw();
		rectangle_bottom.draw();
		rectangle_left.draw();
	}
	
	void drawTriangle() {
		Point A(
			(rectangle_top.getStartPoint().getx() + rectangle_top.getEndPoint().getx()) / 2,
			rectangle_top.getStartPoint().gety()
		);
		Point B(
			rectangle_bottom.getStartPoint().getx(),
			rectangle_bottom.getStartPoint().gety()
		);
		Point C(
			rectangle_bottom.getEndPoint().getx(),
			rectangle_bottom.getEndPoint().gety()
		);
		LineBres left(A, B); left.draw();
		LineBres right(A, C);right.draw();
		rectangle_bottom.draw();
	}
	
	void drawRTriangle() {
		LineBres cross(rectangle_top.getStartPoint(), rectangle_bottom.getEndPoint());
		cross.draw();
		rectangle_bottom.draw();
		rectangle_left.draw();		
	}
	
	void drawDiamond() {
		Point A(
			(rectangle_top.getStartPoint().getx() + rectangle_top.getEndPoint().getx()) / 2,
			rectangle_top.getStartPoint().gety()
		);
		Point B(
			rectangle_right.getStartPoint().getx(),
			(rectangle_right.getStartPoint().gety() + rectangle_right.getEndPoint().gety()) / 2
		);
		Point C(
			(rectangle_bottom.getStartPoint().getx() + rectangle_bottom.getEndPoint().getx()) / 2,
			rectangle_bottom.getStartPoint().gety()
		);
		Point D(
			rectangle_left.getStartPoint().getx(),
			(rectangle_left.getStartPoint().gety() + rectangle_left.getEndPoint().gety()) / 2
		);
		LineBres cross1(A, B); cross1.draw();
		LineBres cross2(C, B); cross2.draw();
		LineBres cross3(C, D); cross3.draw();
		LineBres cross4(A, D); cross4.draw();
	}
	
	void drawPentagon() {
		Point A(
			(rectangle_top.getStartPoint().getx() + rectangle_top.getEndPoint().getx()) / 2,
			rectangle_top.getStartPoint().gety()
		);
		Point B(
			rectangle_right.getStartPoint().getx(),
			rectangle_right.getEndPoint().gety() -
			tan(36 RAD) * (rectangle_right.getEndPoint().gety() - rectangle_right.getStartPoint().gety()) / 2
		);
		Point C(
			rectangle_bottom.getEndPoint().getx() -
			(1 - (tan(36 RAD)*1.0/2)) * (rectangle_bottom.getEndPoint().getx() - rectangle_bottom.getStartPoint().getx()) * 1.0 / tan(72 RAD),
			rectangle_bottom.getStartPoint().gety()
		);
		Point D(
			rectangle_bottom.getStartPoint().getx() +
			(1 - (tan(36 RAD)*1.0/2)) * (rectangle_bottom.getEndPoint().getx() - rectangle_bottom.getStartPoint().getx()) * 1.0 / tan(72 RAD),
			rectangle_bottom.getStartPoint().gety()
		);
		Point E(
			rectangle_left.getStartPoint().getx(),
			rectangle_left.getEndPoint().gety() -
			tan(36 RAD) * (rectangle_left.getEndPoint().gety() - rectangle_left.getStartPoint().gety()) / 2
		);
		LineBres AB(A, B); AB.draw();
		LineBres BC(B, C); BC.draw();
		LineBres CD(D, C); CD.draw();
		LineBres DE(D, E); DE.draw();
		LineBres AE(A, E); AE.draw();
	}
	
	void drawHexagon() {
		Point A(
			(rectangle_top.getStartPoint().getx() + rectangle_top.getEndPoint().getx()) / 2,
			rectangle_top.getStartPoint().gety()
		);
		Point C(
			rectangle_right.getStartPoint().getx(),
			(sqrt(3)/6) * (rectangle_right.getEndPoint().gety() - rectangle_right.getStartPoint().gety()) 
			+ rectangle_right.getStartPoint().gety()
		);
		Point B(
			rectangle_right.getStartPoint().getx(),
			(-sqrt(3)/6) * (rectangle_right.getEndPoint().gety() - rectangle_right.getStartPoint().gety()) 
			+ rectangle_right.getEndPoint().gety()
		);
		Point D(
			(rectangle_bottom.getStartPoint().getx() + rectangle_bottom.getEndPoint().getx()) / 2,
			rectangle_bottom.getStartPoint().gety()
		);
		Point F(
			rectangle_left.getStartPoint().getx(),
			(sqrt(3)/6) * (rectangle_left.getEndPoint().gety() - rectangle_left.getStartPoint().gety()) 
			+ rectangle_left.getStartPoint().gety()
		);
		Point E(
			rectangle_left.getStartPoint().getx(),
			(-sqrt(3)/6) * (rectangle_left.getEndPoint().gety() - rectangle_left.getStartPoint().gety()) 
			+ rectangle_left.getEndPoint().gety()
		);
		LineBres AB(A, B); AB.draw();
		LineBres BC(B, C); BC.draw();
		LineBres CD(C, D); CD.draw();
		LineBres DF(F, D); DF.draw();
		LineBres EF(E, F); EF.draw();
		LineBres AE(A, E); AE.draw();
	}
	
	void drawRightArrow() {
		Point A(
			rectangle_left.getEndPoint().getx(),
			rectangle_left.getEndPoint().gety() -
			(rectangle_left.getEndPoint().gety() - rectangle_left.getStartPoint().gety()) / 4
		);
		Point B(
			(rectangle_top.getEndPoint().getx() + rectangle_top.getStartPoint().getx()) / 2,
			rectangle_left.getEndPoint().gety() -
			(rectangle_left.getEndPoint().gety() - rectangle_left.getStartPoint().gety()) / 4
		);
		Point C(
			(rectangle_top.getEndPoint().getx() + rectangle_top.getStartPoint().getx()) / 2,
			rectangle_top.getEndPoint().gety()
		);
		Point D(
			rectangle_right.getEndPoint().getx(),
			(rectangle_left.getEndPoint().gety() + rectangle_left.getStartPoint().gety()) / 2
		);
		Point E(
			(rectangle_top.getEndPoint().getx() + rectangle_top.getStartPoint().getx()) / 2,
			rectangle_bottom.getEndPoint().gety()
		);
		Point F(
			(rectangle_top.getEndPoint().getx() + rectangle_top.getStartPoint().getx()) / 2,
			rectangle_left.getStartPoint().gety() +
			(rectangle_left.getEndPoint().gety() - rectangle_left.getStartPoint().gety()) / 4
		);
		Point G(
			rectangle_left.getEndPoint().getx(),
			rectangle_left.getStartPoint().gety() +
			(rectangle_left.getEndPoint().gety() - rectangle_left.getStartPoint().gety()) / 4
		);
		LineBres AB(A, B); AB.draw();
		LineBres BC(B, C); BC.draw();
		LineBres CD(C, D); CD.draw();
		LineBres DE(E, D); DE.draw();
		LineBres EF(E, F); EF.draw();
		LineBres GF(G, F); GF.draw();
		LineBres AG(A, G); AG.draw();
	}
	
	void drawLeftArrow() {
		Point A(
			rectangle_right.getEndPoint().getx(),
			rectangle_right.getEndPoint().gety() -
			(rectangle_right.getEndPoint().gety() - rectangle_right.getStartPoint().gety()) / 4
		);
		Point B(
			(rectangle_top.getEndPoint().getx() + rectangle_top.getStartPoint().getx()) / 2,
			rectangle_left.getEndPoint().gety() -
			(rectangle_left.getEndPoint().gety() - rectangle_left.getStartPoint().gety()) / 4
		);
		Point C(
			(rectangle_top.getEndPoint().getx() + rectangle_top.getStartPoint().getx()) / 2,
			rectangle_top.getEndPoint().gety()
		);
		Point D(
			rectangle_left.getEndPoint().getx(),
			(rectangle_left.getEndPoint().gety() + rectangle_left.getStartPoint().gety()) / 2
		);
		Point E(
			(rectangle_top.getEndPoint().getx() + rectangle_top.getStartPoint().getx()) / 2,
			rectangle_bottom.getEndPoint().gety()
		);
		Point F(
			(rectangle_top.getEndPoint().getx() + rectangle_top.getStartPoint().getx()) / 2,
			rectangle_left.getStartPoint().gety() +
			(rectangle_left.getEndPoint().gety() - rectangle_left.getStartPoint().gety()) / 4
		);
		Point G(
			rectangle_right.getEndPoint().getx(),
			rectangle_right.getStartPoint().gety() +
			(rectangle_right.getEndPoint().gety() - rectangle_right.getStartPoint().gety()) / 4
		);
		LineBres AB(A, B); AB.draw();
		LineBres BC(B, C); BC.draw();
		LineBres CD(C, D); CD.draw();
		LineBres DE(E, D); DE.draw();
		LineBres EF(E, F); EF.draw();
		LineBres GF(G, F); GF.draw();
		LineBres AG(A, G); AG.draw();
	}
	
	void drawUpArrow() {
		Point A(
			rectangle_bottom.getStartPoint().getx() +
			(rectangle_bottom.getEndPoint().getx() - rectangle_bottom.getStartPoint().getx()) / 4,
			rectangle_bottom.getEndPoint().gety()
		);
		Point B(
			rectangle_bottom.getStartPoint().getx() +
			(rectangle_bottom.getEndPoint().getx() - rectangle_bottom.getStartPoint().getx()) / 4,
			(rectangle_left.getEndPoint().gety() + rectangle_left.getStartPoint().gety()) / 2
		);
		Point C(
			rectangle_bottom.getStartPoint().getx(),
			(rectangle_left.getEndPoint().gety() + rectangle_left.getStartPoint().gety()) / 2
		);
		Point D(
			(rectangle_bottom.getStartPoint().getx() + rectangle_bottom.getEndPoint().getx()) / 2,
			rectangle_top.getEndPoint().gety()
		);
		Point E(
			rectangle_bottom.getEndPoint().getx(),
			(rectangle_right.getEndPoint().gety() + rectangle_right.getStartPoint().gety()) / 2
		);
		Point F(
			rectangle_bottom.getEndPoint().getx() -
			(rectangle_bottom.getEndPoint().getx() - rectangle_bottom.getStartPoint().getx()) / 4,
			(rectangle_right.getEndPoint().gety() + rectangle_right.getStartPoint().gety()) / 2
		);
		Point G(
			rectangle_bottom.getEndPoint().getx() -
			(rectangle_bottom.getEndPoint().getx() - rectangle_bottom.getStartPoint().getx()) / 4,
			rectangle_bottom.getEndPoint().gety()
		);
		LineBres AB(A, B); AB.draw();
		LineBres BC(B, C); BC.draw();
		LineBres CD(C, D); CD.draw();
		LineBres DE(E, D); DE.draw();
		LineBres EF(E, F); EF.draw();
		LineBres GF(G, F); GF.draw();
		LineBres AG(A, G); AG.draw();
	}
	
	void drawDownArrow() {
		Point A(
			rectangle_bottom.getStartPoint().getx() +
			(rectangle_bottom.getEndPoint().getx() - rectangle_bottom.getStartPoint().getx()) / 4,
			rectangle_top.getEndPoint().gety()
		);
		Point B(
			rectangle_bottom.getStartPoint().getx() +
			(rectangle_bottom.getEndPoint().getx() - rectangle_bottom.getStartPoint().getx()) / 4,
			(rectangle_left.getEndPoint().gety() + rectangle_left.getStartPoint().gety()) / 2
		);
		Point C(
			rectangle_bottom.getStartPoint().getx(),
			(rectangle_left.getEndPoint().gety() + rectangle_left.getStartPoint().gety()) / 2
		);
		Point D(
			(rectangle_bottom.getStartPoint().getx() + rectangle_bottom.getEndPoint().getx()) / 2,
			rectangle_bottom.getEndPoint().gety()
		);
		Point E(
			rectangle_bottom.getEndPoint().getx(),
			(rectangle_right.getEndPoint().gety() + rectangle_right.getStartPoint().gety()) / 2
		);
		Point F(
			rectangle_bottom.getEndPoint().getx() -
			(rectangle_bottom.getEndPoint().getx() - rectangle_bottom.getStartPoint().getx()) / 4,
			(rectangle_right.getEndPoint().gety() + rectangle_right.getStartPoint().gety()) / 2
		);
		Point G(
			rectangle_bottom.getEndPoint().getx() -
			(rectangle_bottom.getEndPoint().getx() - rectangle_bottom.getStartPoint().getx()) / 4,
			rectangle_top.getEndPoint().gety()
		);
		LineBres AB(A, B); AB.draw();
		LineBres BC(B, C); BC.draw();
		LineBres CD(C, D); CD.draw();
		LineBres DE(E, D); DE.draw();
		LineBres EF(E, F); EF.draw();
		LineBres GF(G, F); GF.draw();
		LineBres AG(A, G); AG.draw();
	}
	
	void drawFourStar() {
		Point A(
			(rectangle_top.getEndPoint().getx() + rectangle_top.getStartPoint().getx()) / 2,
			rectangle_top.getEndPoint().gety()
		);
		Point A1(
			rectangle_top.getEndPoint().getx() -
			(rectangle_top.getEndPoint().getx() - rectangle_top.getStartPoint().getx()) * 13 / 35,
			rectangle_right.getEndPoint().gety() -
			(rectangle_right.getEndPoint().gety() - rectangle_right.getStartPoint().gety()) * 13 / 35
		);
		Point B(
			rectangle_right.getStartPoint().getx(),
			(rectangle_right.getStartPoint().gety() + rectangle_right.getEndPoint().gety()) / 2
		);
		Point B1(
			rectangle_top.getEndPoint().getx() -
			(rectangle_top.getEndPoint().getx() - rectangle_top.getStartPoint().getx()) * 13 / 35,
			rectangle_right.getStartPoint().gety() +
			(rectangle_right.getEndPoint().gety() - rectangle_right.getStartPoint().gety()) * 13 / 35
		);
		Point C(
			(rectangle_bottom.getStartPoint().getx() + rectangle_bottom.getEndPoint().getx()) / 2,
			rectangle_bottom.getStartPoint().gety()
		);
		Point C1(
			rectangle_top.getStartPoint().getx() +
			(rectangle_top.getEndPoint().getx() - rectangle_top.getStartPoint().getx()) * 13 / 35,
			rectangle_right.getStartPoint().gety() +
			(rectangle_right.getEndPoint().gety() - rectangle_right.getStartPoint().gety()) * 13 / 35
		);
		Point D(
			rectangle_left.getStartPoint().getx(),
			(rectangle_left.getStartPoint().gety() + rectangle_left.getEndPoint().gety()) / 2
		);
		Point D1(
			rectangle_top.getStartPoint().getx() +
			(rectangle_top.getEndPoint().getx() - rectangle_top.getStartPoint().getx()) * 13 / 35,
			rectangle_right.getEndPoint().gety() -
			(rectangle_right.getEndPoint().gety() - rectangle_right.getStartPoint().gety()) * 13 / 35
		);
		LineBres AA1(A, A1); AA1.draw();
		LineBres A1B(A1, B); A1B.draw();
		LineBres BB1(B, B1); BB1.draw();
		LineBres B1C(B1, C); B1C.draw();
		LineBres CC1(C, C1); CC1.draw();
		LineBres C1D(C1, D); C1D.draw();
		LineBres DD1(D, D1); DD1.draw();
		LineBres D1A(D1, A); D1A.draw();
	}
	
	void drawFiveStar() {
		Point A(
			(rectangle_top.getStartPoint().getx() + rectangle_top.getEndPoint().getx()) / 2,
			rectangle_top.getStartPoint().gety()
		);
		Point B(
			rectangle_right.getStartPoint().getx(),
			rectangle_right.getEndPoint().gety() -
			tan(36 RAD) * (rectangle_right.getEndPoint().gety() - rectangle_right.getStartPoint().gety()) / 2
		);
		Point C(
			rectangle_bottom.getEndPoint().getx() -
			(1 - (tan(36 RAD)*1.0/2)) * (rectangle_bottom.getEndPoint().getx() - rectangle_bottom.getStartPoint().getx()) * 1.0 / tan(72 RAD),
			rectangle_bottom.getStartPoint().gety()
		);
		Point D(
			rectangle_bottom.getStartPoint().getx() +
			(1 - (tan(36 RAD)*1.0/2)) * (rectangle_bottom.getEndPoint().getx() - rectangle_bottom.getStartPoint().getx()) * 1.0 / tan(72 RAD),
			rectangle_bottom.getStartPoint().gety()
		);
		Point E(
			rectangle_left.getStartPoint().getx(),
			rectangle_left.getEndPoint().gety() -
			tan(36 RAD) * (rectangle_left.getEndPoint().gety() - rectangle_left.getStartPoint().gety()) / 2
		);
		Point A1 = intersect(LineBres(A, C), LineBres(B, E));
		Point B1 = intersect(LineBres(A, C), LineBres(B, D));
		Point C1 = intersect(LineBres(E, C), LineBres(B, D));
		Point D1 = intersect(LineBres(E, C), LineBres(A, D));
		Point E1 = intersect(LineBres(A, D), LineBres(B, E));
		if(	A1.getx()==0 && A1.gety()==0 || 
			B1.getx()==0 && B1.gety()==0 || 
			C1.getx()==0 && C1.gety()==0 || 
			D1.getx()==0 && D1.gety()==0 || 
			E1.getx()==0 && E1.gety()==0) return;// Lines are parallel or coincident
		LineBres AA1(A, A1); AA1.draw();
		LineBres A1B(A1, B); A1B.draw();
		LineBres BB1(B, B1); BB1.draw();
		LineBres B1C(B1, C); B1C.draw();
		LineBres CC1(C, C1); CC1.draw();
		LineBres C1D(C1, D); C1D.draw();
		LineBres DD1(D, D1); DD1.draw();
		LineBres D1E(D1, E); D1E.draw();
		LineBres EE1(E, E1); EE1.draw();
		LineBres E1A(E1, A); E1A.draw();
	}
	
	void drawSixStar() {
		Point A(
			(rectangle_top.getStartPoint().getx() + rectangle_top.getEndPoint().getx()) / 2,
			rectangle_top.getStartPoint().gety()
		);
		Point C(
			rectangle_right.getStartPoint().getx(),
			(sqrt(3)/6) * (rectangle_right.getEndPoint().gety() - rectangle_right.getStartPoint().gety()) 
			+ rectangle_right.getStartPoint().gety()
		);
		Point B(
			rectangle_right.getStartPoint().getx(),
			(-sqrt(3)/6) * (rectangle_right.getEndPoint().gety() - rectangle_right.getStartPoint().gety()) 
			+ rectangle_right.getEndPoint().gety()
		);
		Point D(
			(rectangle_bottom.getStartPoint().getx() + rectangle_bottom.getEndPoint().getx()) / 2,
			rectangle_bottom.getStartPoint().gety()
		);
		Point E(
			rectangle_left.getStartPoint().getx(),
			(sqrt(3)/6) * (rectangle_left.getEndPoint().gety() - rectangle_left.getStartPoint().gety()) 
			+ rectangle_left.getStartPoint().gety()
		);
		Point F(
			rectangle_left.getStartPoint().getx(),
			(-sqrt(3)/6) * (rectangle_left.getEndPoint().gety() - rectangle_left.getStartPoint().gety()) 
			+ rectangle_left.getEndPoint().gety()
		);
		Point A1 = intersect(LineBres(A, C), LineBres(B, F));
		Point B1 = intersect(LineBres(A, C), LineBres(B, D));
		Point C1 = intersect(LineBres(E, C), LineBres(B, D));
		Point D1 = intersect(LineBres(E, C), LineBres(F, D));
		Point E1 = intersect(LineBres(F, D), LineBres(A, E));
		Point F1 = intersect(LineBres(F, B), LineBres(A, E));
		if(	A1.getx()==0 && A1.gety()==0 || 
			B1.getx()==0 && B1.gety()==0 || 
			C1.getx()==0 && C1.gety()==0 || 
			D1.getx()==0 && D1.gety()==0 || 
			E1.getx()==0 && E1.gety()==0 ||
			F1.getx()==0 && F1.gety()==0) return;// Lines are parallel or coincident
		LineBres AA1(A, A1); AA1.draw();
		LineBres A1B(A1, B); A1B.draw();
		LineBres BB1(B, B1); BB1.draw();
		LineBres B1C(B1, C); B1C.draw();
		LineBres CC1(C, C1); CC1.draw();
		LineBres C1D(C1, D); C1D.draw();
		LineBres DD1(D, D1); DD1.draw();
		LineBres D1E(D1, E); D1E.draw();
		LineBres EE1(E, E1); EE1.draw();
		LineBres E1F(E1, F); E1F.draw();
		LineBres FF1(F, F1); FF1.draw();
		LineBres F1A(F1, A); F1A.draw();
	}
	
	void drawHeart() {
		if(rectangle_top.getStartPoint().getx() == 0 && rectangle_top.getStartPoint().gety() == 0) return;
		char msg[] = "Sorry it's hard for me :(";
		int len, i;
		glRasterPos2f(rectangle_top.getStartPoint().getx(), rectangle_top.getStartPoint().gety());
		len = (int)strlen(msg);
		for (i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg[i]);
		}
	}
};

#endif


