#ifndef LINETOOLS_H
#define LINETOOLS_H

#include "DrawLine.h"

//New data type containing the endpoints of a line
typedef struct node{
	double length;
	double dir;
	struct node* next;
	struct node* prev;
}linenode;

/*
* Creates the a line of length 1 at position x and y
*/
linenode* createLineList(void);

/*
* Adds a line to the list (After the indicated pointer)
*/
linenode* addLine(linenode* start,double length, double dir, int index);

/*
* Adds a line to the list (Before the indicated pointer)
*/
linenode* addLinePrev(linenode* start, double length, double dir, int index);

/*
* Removes a line from the list
*/
linenode* delLine(linenode* start, int index);

/*
* Edits a line in the list
*/
void editLine(linenode* start, double length, double dir, int index);

/*
* Edits a line in the list by adding the values plugged in
*/
void editLineR(linenode* start, double length, double dir, int index);


#ifdef DRAWLINE_H
void drawLines(int** window, linenode* head, int xstart, int ystart, char character);
#endif //DRAWLINE_H




/*
* Takes the first pointer for a linked list and prints out the data at each node
*/
//void printNums(linenode* head);

#endif //LINETOOLS_H