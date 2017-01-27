#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include "DrawLine.h"
//#include "LineTools.h"
#include "PointTools.h"
#include <Windows.h>

#define UP    M_PI_2
#define DOWN -M_PI_2
#define LEFT  M_PI
#define RIGHT 0

#define FRAMETIME 40

#define WINROWS 20
#define WINCOLS 40

pthread_mutex_t inputMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t inputCond = PTHREAD_COND_INITIALIZER;

char input = 'd';

typedef struct pVector{
	point* head;
	point* tail;
	int x;
	int y;
	int length;
	double direction;
	int speed;
}position;

void startGame(void);
void* directionSetter(void* arg);
void* showDisplay(void* arg);
bool isIntersecting(position* snake);

int main()
{
	startGame();
	
	system("PAUSE");

	return 0;
}


void startGame(void){
	srand(time(NULL));

	pthread_t inputThread, displayThread;

	position* snake = (position*)malloc(sizeof(position));
	snake->x = rand() % (WINCOLS - 6) + 6;;
	snake->y = rand() % (WINROWS - 4) + 2;;
	snake->head = createListHead(snake->x, snake->y);
	snake->tail = addPoint(snake->head, snake->x - 3, snake->y, 0);
	snake->length = 3;
	snake->direction = RIGHT;
	snake->speed = 1;

	pthread_create(&inputThread, NULL, directionSetter, (void*)snake);
	pthread_create(&displayThread, NULL, showDisplay, (void*)snake);

	pthread_join(inputThread, NULL);
	pthread_join(displayThread, NULL);

}

void* directionSetter(void* arg){
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	position* directionRef = (position*)arg;

	char inputbuffer;
	while (1){

		inputbuffer = _getch();
		pthread_mutex_lock(&inputMutex);

		if (inputbuffer == 'w' || inputbuffer == 'W')
		if (directionRef->direction != DOWN && directionRef->direction != UP){
			directionRef->direction = UP;
			if (directionRef->length > 1){
				addPoint(directionRef->head, directionRef->x, directionRef->y, 0);
			}
		}
		
		if (inputbuffer == 'a' || inputbuffer == 'A')
		if (directionRef->direction != RIGHT && directionRef->direction != LEFT){
			directionRef->direction = LEFT;
			if (directionRef->length > 1){
				addPoint(directionRef->head, directionRef->x, directionRef->y, 0);
			}
		}
		
		if (inputbuffer == 's' || inputbuffer == 'S')
		if (directionRef->direction != UP &&directionRef->direction != DOWN){
			directionRef->direction = DOWN;
			if (directionRef->length > 1){
				addPoint(directionRef->head, directionRef->x, directionRef->y, 0);
			}
		}

		if (inputbuffer == 'd' || inputbuffer == 'D')
		if (directionRef->direction != LEFT && directionRef->direction != RIGHT){
			directionRef->direction = RIGHT;
			if (directionRef->length > 1){
				addPoint(directionRef->head, directionRef->x, directionRef->y, 0);
			}
		}
		pthread_cond_wait(&inputCond, &inputMutex);
		pthread_mutex_unlock(&inputMutex);
	}
}

void* showDisplay(void* arg){
	srand(time(NULL));
	int **window = initWindow(WINROWS, WINCOLS);
	position* snake = (position*)arg;
	position food;

	line tail;

	food.x = rand() % (WINCOLS - 2) + 1;
	food.y = rand() % (WINROWS - 2) + 1;
	food.head = createListHead(food.x, food.y);
	food.tail = food.head;
	food.length = 0;
	food.direction = 0.0;
	food.speed = 0;

	while (1){
		drawLineChar(window, 0, 0, WINCOLS - 1, 0, '-');
		drawLineChar(window, 0, WINROWS - 1, WINCOLS - 1, WINROWS - 1, '-');
		drawLineChar(window, 0, 1, 0, WINROWS - 2, '|');
		drawLineChar(window, WINCOLS - 1, 1, WINCOLS - 1, WINROWS - 2, '|');

		drawLines(window, snake->head, '#');
		drawLines(window, food.head, '@');
		
		system("cls");
		
		drawWindow(window, WINROWS, WINCOLS);
		printf("Length: %d, sx: %d, sy: %d, dir: %.2f fx: %d, fy: %d", snake->length, snake->x, snake->y, snake->direction, food.x, food.y);
		Sleep(FRAMETIME);

		clearWindow(window, WINROWS, WINCOLS);

		pthread_cond_signal(&inputCond);

		snake->x += snake->speed*(cos(snake->direction));
		snake->y += snake->speed*(sin(snake->direction));

		editPoint(snake->head, snake->x, snake->y, 0);

		tail = calcLine(snake->tail->x, snake->tail->y, snake->tail->prev->x, snake->tail->prev->y);

		if (snake->x == 0 || snake->x == WINCOLS - 1){
			system("PAUSE");
			exit(0);
		}
		else if (snake->y == 0 || snake->y == WINROWS - 1){
			system("PAUSE");
			exit(0);
		}
		if (snake->x == food.x && snake->y == food.y){
			snake->length++;
			food.x = rand() % (WINCOLS - 2) + 1;
			food.y = rand() % (WINROWS - 2) + 1;
			editPoint(food.head, food.x, food.y, 0);
		}
		else{
			snake->tail = editPointR(snake->tail, snake->speed*(cos(tail.direction)), snake->speed*(sin(tail.direction)), 0);
		}

		if (isIntersecting(snake)){
			system("PAUSE");
			exit(0);
		}
	}
}

bool isIntersecting(position* snake){
	int dx, dy, delta;
	point* start = (point*)malloc(sizeof(point));
	start->next = snake->head->next;
	start->prev = snake->head->prev;
	start->x = snake->head->x;
	start->y = snake->head->y;

	if (snake->direction == UP)
		start->y--;
	else if (snake->direction == DOWN)
		start->y++;
	else if (snake->direction == LEFT)
		start->x++;
	else
		start->x--;
	
	if (start->next == NULL){
		//Only head exists, this should never happen but in case it does this will catch it
		return false;
	}
	point* next = start->next;
	point* compare;
	
	while (next != NULL){
		compare = getPositions(start);
		while (compare->next != NULL){
			if (compare->x == snake->head->x && compare->y == snake->head->y){
				return true;
			}
			compare = compare->next;
		}
		start = next;
		next = next->next;
	}
	return false;
}


