#include <math.h>
#include "character.h"


void drawCharacter(Character character, uint16_t color, uint16_t bgColor, int x, int y) {
	for (int i = 0; i < CHARACTER_SIZE; i++) {
		int dx = x + i % CHARACTER_WIDTH;
		int dy = y + (int) i / CHARACTER_WIDTH;
		drawPixel(dx, dy, character.bits[i] ? color : bgColor);
	}
}

void drawString(char string[], uint16_t color, uint16_t bgColor, int x, int y) {
	for (int i = 0; string[i] != 0; i++) {
		drawCharacter(characters[getCharIndex(string[i])], color, bgColor, x + CHARACTER_WIDTH * i + 1, y);
	}
}

int getCharIndex(char c) {
	return c - ' ';
}
