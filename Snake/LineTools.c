#include <stdio.h>
#include <math.h>
#include "LineTools.h"

linenode* addNode(linenode* start);
linenode* traverse(linenode* start, int index);

linenode* createLineList(void){
	linenode* head = NULL;
	if (head == NULL){
		head = (linenode*)malloc(sizeof(linenode));
		head->dir = 0;
		head->length = 0.5;
		head->next = NULL;
		head->prev = NULL;
	}

	return head;
}

linenode* addLine(linenode* start, double length, double dir, int index){
	linenode* retnode = addNode(traverse(start, index));
	retnode->dir = dir;
	retnode->length = length;

	return retnode;
}

linenode* addLinePrev(linenode* start, double length, double dir, int index){
	int isHead = 0;
	if (start->prev == NULL){
		start->prev = (linenode*)malloc(sizeof(linenode));
		start->prev->next = start;
		start = start->prev;
		isHead = 1;
	}
	linenode* retnode = addNode(traverse(start, index));
	retnode->dir = dir;
	retnode->length = length;

	if (isHead){
		retnode->prev = NULL;
	}

	return retnode;
}

linenode* delLine(linenode* start, int index){
	linenode* delnode = traverse(start, index);
	if (delnode->next == NULL){
		//Last line in list (return last node in list)
		delnode = delnode->prev;
		free(delnode->next);
		delnode->next = NULL;
	}
	else if (delnode->prev == NULL){
		//Head of list (return new head)
		delnode = delnode->next;
		free(delnode->prev);
		delnode->prev = NULL;
	}
	else {
		//Middle of list reconnect and return node after delnode
		linenode* tempnode;
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
void drawLines(int** window, linenode* head, int xStart, int yStart, char character){
	int xEnd, yEnd, isEnd;
	double length, dir;
	if (head->prev == NULL){
		//Start of list, proceed forward
		isEnd = 0;
	} else {
		//End of list, proceed backward
		isEnd = 1;
	}
	do{
		length = head->length;
		dir = head->dir;
		xEnd = XEND;
		yEnd = YEND;
		drawLineChar(window, xStart, yStart, xEnd, yEnd, character);
		xStart = xEnd;
		yStart = yEnd;
		if (!isEnd)
			head = head->next;
		else
			head = head->prev;
	} while (head != NULL);
 
}
#endif //DRAWLINE_H

void editLine(linenode* start, double length, double dir, int index){
	start = traverse(start, index);
	
	start->length = length;
	start->dir = dir;

	return;
}

void editLineR(linenode* start, double length, double dir, int index){
	start = traverse(start, index);

	start->length += length;
	start->dir += dir;

	if (start->length = 0.0){
		delLine(start, 0);
	}

	return;
}


linenode* addNode(linenode* start){
	linenode* newnode;
	if (start->next == NULL){
		//start is at end of list, make new node
		start->next = (linenode*)malloc(sizeof(linenode));
		newnode = start->next;
		newnode->next = NULL;
		newnode->prev = start;

	}
	else {
		//start has some value after it, retain rest of list
		newnode = (linenode*)malloc(sizeof(linenode));
		newnode->next = start->next;
		newnode->prev = start;
		start->next = newnode;
	}
	return newnode;
}

linenode* traverse(linenode* start, int index){
	linenode* retnode = start;
	if (index < 0){
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


/*
int isZero(char* input){
	int i = 0;
	int check = 0;
	do{
		if ((!isdigit(input[i])) && input[i] != '.' && input[i] != '-'){
			if (input[i] != '\n')
				check = 1;
			break;
		}
		i++;
	} while (input[i] != NULL);
	return check;
}

node_t* getNums(void){
	double d;
	char* input = (char*)malloc(INPUTBUFFER * sizeof(char));
	node_t* head = NULL;
	node_t* temp = NULL;

	printf("Please enter a number to add to the list or Ctrl+Z to end: ");
	while (fgets(input, INPUTBUFFER, stdin) != NULL){

		if (!isZero(input)){
			printf("I didn't understand that input, please try again: ");
			continue;
		}
		d = atof(input);
		if (head == NULL){
			head = (node_t*)malloc(sizeof(node_t));
			head->data = d;
			head->next = NULL;
			temp = head;
		}
		else{
			temp->next = (node_t*)malloc(sizeof(node_t));
			temp = temp->next;
			temp->data = d;
			temp->next = NULL;
		}

		//fputc(EOF, stdin);
		//printf("Press Enter to continue or Ctrl+Z and Enter to end.\n");
		printf("Please enter a number to add to the list or Ctrl+Z to end: ");
	}
	return head;
}

void printNums(node_t* head){
	printf("Printing Numbers...\n");
	while (head != NULL){
		printf("%f\n", head->data);
		head = head->next;
	}
	return;
}

double* listToArr(node_t* head, int* size){
	double* output;
	node_t* root = head; //list needs to be traversed twice, so the head pointer is cloned
	int count = 0;
	*size = 0;

	//Ideally you would only traverse the list once, but I can't think of a better way of getting the size to initialize the array
	while (head != NULL){
		(*size)++;
		head = head->next;
	}

	//Create array after getting its size
	output = (double*)malloc(*size * sizeof(double));

	//traverse list and put values into array
	while (root != NULL && count < *size){
		output[count] = root->data;
		root = root->next;
		count++;
	}
	return output;
}

int* listToArrInt(node_t* head, int* size){
	int* output;
	node_t* root = head; //list needs to be traversed twice, so the head pointer is cloned
	int count = 0;
	*size = 0;

	//Ideally you would only traverse the list once, but I can't think of a better way of getting the size to initialize the array
	while (head != NULL){
		(*size)++;
		head = head->next;
	}

	//Create array after getting its size
	output = (int*)malloc(*size * sizeof(double));

	//traverse list and put values into array
	while (root != NULL && count < *size){
		output[count] = (int)(root->data);
		root = root->next;
		count++;
	}
	return output;
}

int* arrDoubleToInt(double array[], int size){
	int* arr = (int*)malloc(size*sizeof(int));
	while (size > 0){
		size--;
		arr[size] = (int)array[size];
	}
	return arr;
}

double* arrIntToDouble(int array[], int size){
	double* arr = (double*)malloc(size*sizeof(double));
	while (size > 0){
		size--;
		arr[size] = (double)array[size];
	}
	return arr;
}

*/