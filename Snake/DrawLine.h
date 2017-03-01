#ifndef DRAWLINE_H
#define DRAWLINE_H

#define _CRT_SECURE_NO_WARNINGS

#define XEND (xStart + cos(dir)*length)
#define YEND (yStart + sin(dir)*length)

//allocates and initializes a Window to draw into
int ** initWindow(int rows, int cols);

/* deallocates space used for window
* (it's good practice to use this at
* the end of your program but technically
* the OS handles it for you)
*/
void deinitWindow(int** window, int rows);

//places a line between two points with default char '0'
void drawLine(int** window, int xStart, int yStart, int xEnd, int yEnd);

//places a line starting from (xStart,yStart) with in direction dir and length with default char '0'
//Note: 1 unit length is the distance between two "pixels", i.e to draw 1 pixel, length must be 0.5
void drawLineDir(int** window, int xStart, int yStart, double dir, double length);

//places a line between two points with specified char
void drawLineChar(int** window, int xStart, int yStart, int xEnd, int yEnd, char character);

//places a line starting from (xStart,yStart) with in direction dir and length with specified char
void drawLineDirChar(int** window, int xStart, int yStart, double dir, double length, char character);

//removes all lines in a window
void clearWindow(int** window, int rows, int cols);

//draws the window on screen
void drawWindow(int** window, int rows, int cols);

void writeBuffer(int** window, char* buffer, int rows, int cols);

void printBuffer(char* buffer);

char* initBuffer(int rows, int cols);

#endif //DRAWLINE_H