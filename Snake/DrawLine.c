#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DrawLine.h"

int ** initWindow(int rows, int cols)
{
	int **window;
	window = (int **)malloc(rows * sizeof *window);
	for (int i = 0; i<rows; i++)
	{
		window[i] = (int *)malloc(cols * sizeof *window[i]);
	}

	for (int j = 0; j < rows; j++)
	{
		for (int k = 0; k<cols; k++)
		{
			window[j][k] = 32;
		}
	}
	return window;
}

void deinitWindow(int** window, int rows)
{
	for (int i = 0; i<rows; i++)
	{
		free(window[i]);
	}
	free(window);
	return;
}

void clearWindow(int** window, int rows, int cols){
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			window[i][j] = 32;
		}
		
	}
}

void drawWindow(int** window, int rows, int cols)
{
	for (int i = (rows - 1); i >= 0; i--)
	{
		for (int j = 0; j<cols; j++)
		{
			printf("%c", window[i][j]);
		}
		printf("\n");
	}
}

void drawLineDir(int** window, int xStart, int yStart, double dir, double length){
	drawLine(window, xStart, yStart, XEND, YEND);
	return;
}

void drawLine(int** window, int xStart, int yStart, int xEnd, int yEnd)
{
	drawLineChar(window, xStart, yStart, xEnd, yEnd, 48);
	return;
}

void drawLineCharDir(int** window, int xStart, int yStart, double dir, double length, char character){
	drawLineChar(window, xStart, yStart, XEND, YEND, character);
	return;
}


void drawLineChar(int** window, int xStart, int yStart, int xEnd, int yEnd, char character)
{
	int deltaX = xEnd - xStart;
	int deltaY = yEnd - yStart;
	int absdeltaX = abs(deltaX);
	int absdeltaY = abs(deltaY);
	double posX, posY, dx, dy;
	posX = (double)xStart;
	posY = (double)yStart;
	if (absdeltaY > absdeltaX)
	{
		dx = (double)deltaX / (double)absdeltaY;
		dy = (double)deltaY / (double)absdeltaY;
		for (int i = 0; i <= absdeltaY; i++)
		{
			window[(int)posY][(int)(posX + 0.5)] = character;
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
			window[(int)(posY + 0.5)][(int)posX] = character;
			posX += dx;
			posY += dy;
		}
	}
	return;
}