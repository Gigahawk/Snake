#ifndef POINTTOOLS_H
#define POINTTOOLS_H

#include "DrawLine.h"

typedef struct node{
	int x;
	int y;
	struct node* next;
	struct node* prev;
}point;

typedef struct line{
	double length;
	double direction;
}line;

// Creates the head of a list
point* createListHead(int x, int y);

// Adds a corner to the list (After the indicated node)
// Returns the node added
point* addPoint(point* start, int x, int y, int index);

// Removes a corner from the list
// Returns the first available node after the deleted node
point* delPoint(point* start, int index);

//Edits a point in the list
point* editPoint(point* start, int x, int y, int index);

//Edits a point in the list by adding the values plugged in
point* editPointR(point* start, int x, int y, int index);

#ifdef DRAWLINE_H
//Draws out the line defined by all the points in a list
void drawLines(int** window, point* head, char character);
#endif //DRAWLINE_H

point* getPositions(point* start);

//Get's the length and direction of a line between the point given and the one after
line getLine(point* start, int index);

//Calculate the length and direction of a line
line calcLine(int xStart, int yStart, int xEnd, int yEnd);

//Low level: Adds a blank node
point* addNode(point* start);

//Low level: traverses across nodes
point* traverse(point* start, int index);


#endif //POINTTOOLS_H