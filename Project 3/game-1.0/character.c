#include <math.h>
#include "character.h"

//Draws a given character
void drawCharacter(Character character, uint16_t color, uint16_t bgColor, int x, int y) 
{
	for (int i = 0; i < CHARACTER_SIZE; i++) {
		int dx = x + i % CHARACTER_WIDTH;
		int dy = y + (int) i / CHARACTER_WIDTH;
		drawPixel(dx, dy, character.bits[i] ? color : bgColor);
	}
}

//Draws a string of characters and repaints its given area
void drawString(char string[], uint16_t color, uint16_t bgColor, int x, int y) 
{
	int size;
	for (int i = 0; string[i] != 0; i++) {
		drawCharacter(characters[getCharIndex(string[i])], color, bgColor, x + CHARACTER_WIDTH * i + 1, y);
		size = i;
	}
	setRect(x, y, CHARACTER_WIDTH * size + size + 5, CHARACTER_HEIGHT);
	repaint();
}

//Returns the index of the character in the character array. This is calculated based on offset from the ASCII value
//of space. 
int getCharIndex(char c) 
{
	return c - ' ';
}
