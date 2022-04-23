#ifndef FREELINE_H
#define FREELINE_H
#include "LineBres.h"

//class to free hand draw
class FreeLine {
protected:
	LineBres* FreeLineHead;
public:
	FreeLine() { FreeLineHead = NULL; }
	void setFreeLineHead(LineBres* h) { FreeLineHead = h; }
	LineBres* getFreeLineHead() { return FreeLineHead; }
	void InsertFreeLineNode(LineBres* newFreeLineNode)
	{
		LineBres* currFreeLineNode = FreeLineHead;
		LineBres* prevFreeLineNode = NULL;
		while (currFreeLineNode) {
			prevFreeLineNode = currFreeLineNode;
			currFreeLineNode = currFreeLineNode->next;
		}
		//case where there are elements in list
		if (prevFreeLineNode){
			newFreeLineNode->next = prevFreeLineNode->next;
			prevFreeLineNode->next = newFreeLineNode;
			//set the end position of previous node to be the start point of new node
			prevFreeLineNode->SetEndPoint(newFreeLineNode->getStartPoint());
		}
		//case where list is empty, set a head
		else {
			newFreeLineNode->next = FreeLineHead;
			FreeLineHead = newFreeLineNode;
		}
	}
	void draw()
	{
		LineBres* temp = FreeLineHead;
		while (temp)
		{
			temp->draw();
			temp = temp->next;
		}
	}
};

#endif



