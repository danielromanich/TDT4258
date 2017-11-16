#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <linux/fb.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "game_logic.h"

#define BACKGROUND_COLOR 0X0000
#define SNAKE_HEAD_COLOR 0xFFF0
#define SNAKE_BODY_COLOR 0xFFFF
#define FRUIT_COLOR 0xF800

uint16_t* gamePixels;

void drawPixel(int, int, uint16_t);
void drawNumber(int, uint16_t, uint16_t, int, int);
void repaint();
int getPixel(int, int);
void paintStruct(GameObject, uint16_t);
