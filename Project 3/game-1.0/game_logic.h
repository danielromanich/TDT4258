#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#define OBJECT_WIDTH 16
#define OBJECT_HEIGHT 16
#define MAP_WIDTH 20
#define MAP_HEIGHT 14
#define MAP_HEIGHT_OFFSET OBJECT_HEIGHT*1
#define MAP_WIDTH_OFFSET 0

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
} GameObject;

typedef enum 
{
	UP,
	RIGHT,
	LEFT,
	DOWN
} Direction;

int checkFruit(GameObject);
void addSnakePart();
int checkSnakeCollision(GameObject);
int isValidDirection(Direction, Direction);
void drawString(char[], uint16_t, uint16_t, int, int);
Direction getNextDirection(Direction);
int moveSnake(Direction, GameObject);
void updateStruct(GameObject);
void repaintSnake(GameObject, GameObject[MAP_WIDTH * MAP_HEIGHT], int);
void repaint();
void updateFruit();
void repaintFruit(GameObject);
int move(int, int, int);
