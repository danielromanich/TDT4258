#include "graphics.h"

struct fb_copyarea screen;
struct fb_copyarea rect;
int fbfd;

//Sets up the map by opening the LED driver and mapping it to a int array (a pixel array)
void setupGraphics() 
{
	fbfd = open("dev/fb0", O_RDWR);
	gamePixels = (uint16_t*)mmap(NULL, 153600, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	//Draws a while line around the "map"
	for (int i = 0; i < 76800; i++) {
		int x = getX(i);
		int y = getY(i);
		if ((x == 0 && y >= MAP_HEIGHT_OFFSET) || (x == 319 && y >= MAP_HEIGHT_OFFSET) || y == 238 || y == MAP_HEIGHT_OFFSET) {
			gamePixels[i] = 0xFFFF;
		} else
			gamePixels[i] = BACKGROUND_COLOR;
	}
	setRect(0, 0, 320, 240);
	repaint();
}

//Repaints the required parts of the snake
void repaintSnake(GameObject tail, GameObject snake[MAP_WIDTH * MAP_HEIGHT], int snakeLength) 
{
	paintStruct(tail, BACKGROUND_COLOR);
	for (int i = 0; i < snakeLength; i++) {
		if (i == snakeLength - 1) {
			paintStruct(snake[i], SNAKE_HEAD_COLOR);
		} else {
			paintStruct(snake[i], SNAKE_BODY_COLOR);
		}
	}
}

//Repaints the fruit
void repaintFruit(GameObject fruit) 
{
	paintStruct(fruit, FRUIT_COLOR);
}

//Sets the update rectangle to the given x, y with the given bounds. When repaint is called its this rectangle that is updated.
void setRect(int x, int y, int width, int height) {
	rect.dx = x;
	rect.dy = y;
	rect.width = width;
	rect.height = height;
}

//Paints a gameobject with the given color
void paintStruct(GameObject tail, uint16_t color) 
{
	for (int x = tail.x * OBJECT_WIDTH + 2 + MAP_WIDTH_OFFSET; x < tail.x * OBJECT_WIDTH + OBJECT_WIDTH - 2 + MAP_WIDTH_OFFSET; x++) {
		for (int y = tail.y * OBJECT_HEIGHT + 2 + MAP_HEIGHT_OFFSET; y < tail.y * OBJECT_HEIGHT + OBJECT_HEIGHT + MAP_HEIGHT_OFFSET - 2; y++) {
			drawPixel(x, y, color);
		}
	}
	setRect(tail.x * OBJECT_WIDTH + MAP_WIDTH_OFFSET, tail.y * OBJECT_HEIGHT + MAP_HEIGHT_OFFSET, OBJECT_WIDTH, OBJECT_HEIGHT);
	repaint();
}

//Return the pixel position in the pixel array based on coordinates
int getPixel(int x, int y) 
{
	return 320 * y + x;
}

//Returns the x position in the pixel matrix based on its index
int getX(int index) 
{
	return index % 320;
}

//Retuns the y position in the pixel matrix based on its index
int getY(int index) 
{
	return index / 320;
}

//Draws a pixel in the x,y position
void drawPixel(int x, int y, uint16_t color) 
{
	gamePixels[getPixel(x, y)] = color;
}

//Repaints the given rectangle
void repaint() 
{
	ioctl(fbfd, 0x4680, &rect);
}
