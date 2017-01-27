#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>
#include "PointTools.h"


point* createListHead(int x, int y){
	point* head = (point*)malloc(sizeof(point));
	head->x = x;
	head->y = y;
	head->next = NULL;
	head->prev = NULL;

	return head;
}

point* addPoint(point* start, int x, int y, int index){
	point* retnode = addNode(traverse(start, index));

	retnode->x = x;
	retnode->y = y;

	return retnode;
}

point* delPoint(point* start, int index){
	point* delnode = traverse(start, index);
	if (delnode->next == NULL){
		//Last line in list (return last node in list)
		delnode = delnode->prev;
		free(delnode->next);
		delnode->next = NULL;
	}
	else if (delnode->prev == NULL){
		//Head of list (reurn new head)
		delnode = delnode->next;
		free(delnode->prev);
		delnode->prev = NULL;
	}
	else {
		//Middle of list, reconnect and return node after delnode
		point* tempnode;
		tempnode = delnode->prev;
		tempnode->next = delnode->next;
		tempnode = delnode->next;
		tempnode->prev = delnode->prev;
		free(delnode);
		delnode = tempnode;
	}

	return delnode;
}

#ifdef DRAWLINE_H
void drawLines(int** window, point* head, char character){
	int isEnd, xStart, yStart, xEnd, yEnd;

	if (head->next == NULL && head->prev == NULL){
		//Only one point provided, print dot
		xStart = head->x;
		yStart = head->y;
		drawLineChar(window, xStart, yStart, xStart, yStart, character);
			return;
	}

	if (head->prev == NULL){
		//start of list, proceed forward
		isEnd = 0;
	}
	else {
		//End of list, proceed backward
		isEnd = 1;
	}
	
	while((head->next!= NULL&&!isEnd) || (head->prev != NULL && isEnd)){
		xStart = head->x;
		yStart = head->y;

		if (!isEnd){
			head = head->next;
		}
		else {
			head = head->prev;
		}

		xEnd = head->x;
		yEnd = head->y;

		drawLineChar(window, xStart, yStart, xEnd, yEnd, character);
	}


}


#endif //DRAWLINE_H

line getLine(point* start, int index){

	line segment;

	start = traverse(start, index);

	int deltaX, deltaY;
	deltaX = start->next->x - start->x;
	deltaY = start->next->y - start->y;
	segment.length = sqrt(deltaX*deltaX + deltaY*deltaY);
	if (deltaX > 0){
		segment.direction = atan(deltaY / deltaX);
	}
	else if (deltaX < 0){
		deltaX = -deltaX;
		segment.direction = M_PI - atan(deltaY / deltaX);
	}
	else {
		if (deltaY > 0){
			segment.direction = M_PI_2;
		}
		else {
			segment.direction = -M_PI_2;
		}
	}

	return segment;
}

line calcLine(int xStart, int yStart, int xEnd, int yEnd){
	line segment;

	int deltaX, deltaY;
	deltaX = xEnd - xStart;
	deltaY = yEnd - yStart;
	segment.length = sqrt(deltaX*deltaX + deltaY*deltaY);
	if (deltaX > 0){
		segment.direction = atan(deltaY / deltaX);
	}
	else if (deltaX < 0){
		deltaX = -deltaX;
		segment.direction = M_PI - atan(deltaY / deltaX);
	}
	else {
		if (deltaY > 0){
			segment.direction = M_PI_2;
		}
		else {
			segment.direction = -M_PI_2;
		}
	}

	return segment;
}

point* getPositions(point* start){
	if (start->next == NULL){
		//Only one point exists
		return start;
	}
	point* end = start->next;
	point* head = (point*)malloc(sizeof(point));
	point* crawler = head;
	int deltaX = end->x - start->x;
	int deltaY = end->y - start->y;
	int absdeltaX = abs(deltaX);
	int absdeltaY = abs(deltaY);
	double posX, posY, dx, dy;
	posX = (double)start->x;
	posY = (double)start->y;
	if (absdeltaY > absdeltaX)
	{
		dx = (double)deltaX / (double)absdeltaY;
		dy = (double)deltaY / (double)absdeltaY;
		for (int i = 0; i <= absdeltaY; i++)
		{
			crawler->x = (int)posX;
			crawler->y = (int)posY;
			crawler->next = (point*)malloc(sizeof(point));
			crawler = crawler->next;
			posY += dy;
			posX += dx;
		}
	}
	else
	{
		dx = (double)deltaX / (double)absdeltaX;
		dy = (double)deltaY / (double)absdeltaX;
		for (int j = 0; j <= absdeltaX; j++)
		{
			crawler->x = (int)posX;
			crawler->y = (int)posY;
			crawler->next = (point*)malloc(sizeof(point));
			crawler = crawler->next;
			posX += dx;
			posY += dy;
		}
	}
	
	crawler->next = NULL;

	return head;
}


point* editPoint(point* start, int x, int y, int index){
	start = traverse(start, index);
	point* next;
	point* prev;

	start->x = x;
	start->y = y;

	next = start->next;
	prev = start->prev;

	if (next != NULL){
		if (start->x == next->x && start->y == next->y){
			start = delPoint(start, 0);
			return start;
		}
	}
	else if (prev != NULL){
		if (start->x == prev->x && start->y == prev->y){
			start =delPoint(start, 0);
			return start;
		}
	}
	return start;
}

point* editPointR(point* start, int x, int y, int index){
	start = traverse(start, index);
	point* next;
	point* prev;

	start->x += x;
	start->y += y;

	next = start->next;
	prev = start->prev;

	if (next != NULL){
		if (start->x == next->x && start->y == next->y){
			start = delPoint(start, 0);
			return start;
		}
	}
	else if (prev != NULL){
		if (start->x == prev->x && start->y == prev->y){
			start = delPoint(start, 0);
			return start;
		}
	}

	return start;
}

point* addNode(point* start){
	point* newnode;

	if (start->next == NULL){
		//start is at the end of list, make new node
		start->next = (point*)malloc(sizeof(point));
		newnode = start->next;
		newnode->next = NULL;
		newnode->prev = start;
	}
	else {
		//start has some value after it, retain rest of list
		newnode = (point*)malloc(sizeof(point));
		newnode->next = start->next;
		newnode->prev = start;
		start->next = newnode;
		start = newnode->next;
		start->prev = newnode;
	}

	return newnode;
}

point* traverse(point* start, int index){
	point* retnode = start;

	if(index < 0){
		index = -index;
		while (index > 0 && retnode->prev != NULL){
			retnode = retnode->prev;
			index--;
		}
	}
	else {
		while (index > 0 && retnode->next != NULL){
			retnode = retnode->next;
			index--;
		}
	}
	return retnode;
}
