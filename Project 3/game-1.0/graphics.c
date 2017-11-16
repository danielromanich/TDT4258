#include "graphics.h"

struct fb_copyarea screen;
int fbfd;

void setupGraphics() {
	fbfd = open("dev/fb0", O_RDWR);
	screen.dx = 0;
	screen.dy = 0;
	screen.width = 320;
	screen.height = 240;
	gamePixels = (uint16_t*)mmap(NULL, 153600, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	for (int i = 0; i < 76800; i++) {
		int x = getX(i);
		int y = getY(i);
		if (x == 0 && y >= MAP_HEIGHT_OFFSET || x == 319 && y >= MAP_HEIGHT_OFFSET || y == 238 || y == MAP_HEIGHT_OFFSET) {
			gamePixels[i] = 0xFFFF;
		} else
			gamePixels[i] = BACKGROUND_COLOR;
	}
	repaint();
}

void repaintSnake(GameObject tail, GameObject snake[MAP_WIDTH * MAP_HEIGHT], int snakeLength) {
	paintStruct(tail, BACKGROUND_COLOR);
	for (int i = 0; i < snakeLength; i++) {
		if (i == snakeLength - 1) {
			paintStruct(snake[i], SNAKE_HEAD_COLOR);
		} else {
			paintStruct(snake[i], SNAKE_BODY_COLOR);
		}
	}
}

void repaintFruit(GameObject fruit) {
	paintStruct(fruit, FRUIT_COLOR);
}

void paintStruct(GameObject tail, uint16_t color) {
	for (int x = tail.x * OBJECT_WIDTH + 2 + MAP_WIDTH_OFFSET; x < tail.x * OBJECT_WIDTH + OBJECT_WIDTH - 2 + MAP_WIDTH_OFFSET; x++) {
		for (int y = tail.y * OBJECT_HEIGHT + 2 + MAP_HEIGHT_OFFSET; y < tail.y * OBJECT_HEIGHT + OBJECT_HEIGHT + MAP_HEIGHT_OFFSET - 2; y++) {
			drawPixel(x, y, color);
		}
	}
}

int getPixel(int x, int y) {
	return 320 * y + x;
}

int getX(int index) {
	return index % 320;
}

int getY(int index) {
	return index / 320;
}

void drawPixel(int x, int y, uint16_t color) {
	gamePixels[getPixel(x, y)] = color;
}

void repaint() {
	ioctl(fbfd, 0x4680, &screen);
}
