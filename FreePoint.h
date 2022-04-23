#ifndef FREEPOINT_H
#define FREEPOINT_H
#include "Point.h"

//class to free hand draw
class FreePoint {
protected:
	Point* FreePointHead;
public:
	FreePoint() 						{ FreePointHead = NULL; }
	void setFreePointHead(Point* h)	{ FreePointHead = h; }
	Point* getFreePointHead()		{ return FreePointHead; }
	void InsertFreePointNode(Point* newFreePointNode){
		Point* currFreePointNode = FreePointHead;
		Point* prevFreePointNode = NULL;
		while (currFreePointNode) {
			prevFreePointNode = currFreePointNode;
			currFreePointNode = currFreePointNode->next;
		}
		//case where there are elements in list
		if (prevFreePointNode){
			newFreePointNode->next = prevFreePointNode->next;
			prevFreePointNode->next = newFreePointNode;
		}
		//case where list is empty, set a head
		else{
			newFreePointNode->next = FreePointHead;
			FreePointHead = newFreePointNode;
		}
	}
	void draw()	{
		Point* temp = FreePointHead;
		while (temp){
			temp->draw();
			temp = temp->next;
		}
	}
};

#endif


