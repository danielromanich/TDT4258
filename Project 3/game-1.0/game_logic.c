#include "game_logic.h"

//Index 0 is the tail of the snake
GameObject snake[MAP_WIDTH * MAP_HEIGHT];
GameObject fruit;
int snakeSize = 5;
Direction currentDir = RIGHT;
Direction tempDir = RIGHT;
Direction directions[4] = {LEFT, UP, RIGHT, DOWN};
int score = 0;

//Sets up the game by initializing the snake and drawing the text to the screen
void setupGame() 
{
	srand(time(NULL));
	for (int i = 0; i < snakeSize; i++) {
		snake[i].x = 0;
		snake[i].y = i;
		snake[i].width = OBJECT_HEIGHT;
		snake[i].height = OBJECT_HEIGHT;
	}
	updateFruit();
	drawString("SNAKE3000", 0xFFF0, 0x0, 240, 1);
	drawString("Score:0", 0xFFF0, 0x0, 5, 1);
}

//Called every tick, progresses the game
int handleGame() 
{
	currentDir = tempDir;
	GameObject tail = snake[0];
	GameObject head = snake[snakeSize - 1];
	if (!moveSnake(currentDir, head)) //Movement of snake is done
		return false;
	updateStruct(snake[0]);
	if (checkFruit(snake[snakeSize - 1])) {
		addSnakePart();	
		updateFruit();
		score += 100 + rand() % 50;
		char str[16]; //The total size of both the Score: and int maxsize
		char scoreString[] = "Score:";
		snprintf(str, sizeof str, "%s%d", scoreString, score);
		drawString(str, 0xFFF0, 0x0, 5, 1);
	}
	if (checkSnakeCollision(snake[snakeSize - 1])) {
		return false;
	}
	//Check for collision with self
	//Check for collision with fruit
	//Repaint snake
	repaintSnake(tail, snake, snakeSize);
	repaintFruit(fruit);
	return true;
}

//Moves the snake in the given direction
//Returns false if the snake is out of bounds and true if it is good
int moveSnake(Direction dir, GameObject head) 
{
	switch (dir) { //Update the snake position based on direction
		case UP:
			return move(0, head.x, head.y - 1);
		case RIGHT:
			return move(0, head.x + 1, head.y);
		case DOWN:
			return move(0, head.x, head.y + 1);
		case LEFT:
			return move(0, head.x - 1, head.y);
	}
	return false;
}

//Shifts the struct array one to the left and adds the first element last
//This way we only have to move our tail to our head to draw
void updateStruct(GameObject tail) 
{
	for (int i = 1; i < snakeSize; i++) {
		snake[i - 1] = snake[i];
	}
	snake[snakeSize - 1] = tail;
}

//Checks if the snake eats a fruit
int checkFruit(GameObject head) 
{
	return head.x == fruit.x && head.y == fruit.y;
}

//Checks if the snake collided in itself
int checkSnakeCollision(GameObject head) 
{
	for (int i = 0; i < snakeSize - 1; i++) {
		if (snake[i].x == head.x && snake[i].y == head.y)
			return true;
	}
	return false;
}

//Determines the tick speed based on the snake size
int getSpeed() 
{
	if (snakeSize >= 20) {
		return 90000;
	} else if (snakeSize >= 15) {
		return 110000;
	} else if (snakeSize >= 10) {
		return 125000;
	}
	return 150000;
}

//Moves the fruit to a new location 
void updateFruit() 
{
	int x = rand() % MAP_WIDTH;
	int y = rand() % MAP_HEIGHT;
	fruit.x = x;
	fruit.y = y;
}

//Shifts every part in the array one position right
void shiftArrayRight() {
	for (int i = snakeSize - 1; i >= 0; i--) {
		snake[i + 1] = snake[i];
	}
}

//Adds a new part to the snake 
void addSnakePart() 
{
	shiftArrayRight();
	snakeSize += 1;
	GameObject snakePart = {snake[1].x, snake[1].y, OBJECT_WIDTH, OBJECT_HEIGHT};
	snake[0] = snakePart;
}

//Moves the snake part at the given index. Returns false if the new location of the part is outside of the bounds
int move(int index, int x, int y) 
{
	snake[index].x = x;
	snake[index].y = y;
	if (snake[index].x < 0 || snake[index].y < 0 || snake[index].y >= MAP_HEIGHT 
		|| snake[index].x >= MAP_WIDTH)
		return false;
	return true;
}

//Returns a direction based on the button input. Checks if the direction is a valid direction
Direction getDirection(int button) 
{
	if (button < 4 && isValidDirection(directions[button], currentDir)) {
		return directions[button];
	}
	return currentDir;
}

//Determines if a direction is valid based on its current direction
int isValidDirection(Direction newDir, Direction currentDir) 
{
	switch (currentDir) {
		case UP:
			return newDir != DOWN;
		case DOWN:
			return newDir != UP;
		case RIGHT:
			return newDir != LEFT;
		case LEFT:
			return newDir != RIGHT;
	}
	return false;
}

//Sets the temporary direction. Used when the signal updates the direction
void setDirection(int button) 
{
	tempDir = getDirection(button);
}

//Finds the index of the button pushed
int getIndex(int input) 
{
	input = ~input;
	for (int i = 0; i < 8; i++) {
		if (((input >> i) & 1) == 1)
			return i;
	}
	return -1;
}

