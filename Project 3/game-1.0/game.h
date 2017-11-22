#define _BSD_SOURCE
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

void sigio_handler(int);
int initGamepadDriver();
void setupGame();
void setupGraphics();
int handleGame();
int getIndex(int);
int getSpeed();
int getIndex(int);
void setDirection(int);

typedef enum {
	SW1,
	SW2,
	SW3,
	SW4,
	SW5,
	SW6,
	SW7,
	SW8
} Button;
