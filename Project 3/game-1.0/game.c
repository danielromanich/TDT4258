#include "game.h"
#include "game_logic.h"
#include <sys/time.h>

FILE* driver;
bool gamePause = false;
bool newTick = false;
struct timeval tv1;
struct timeval tv2;

int main(int argc, char *argv[])
{
	printf("Snake game started!\n");
	initGamepadDriver(); //Setting up the gamepad driver
	setupGraphics(); //Initialize the graphics
	setupGame(); //Initialize the game
	gettimeofday(&tv1, 0);
	while(true) {
		gettimeofday(&tv2, 0);
		long time = (tv2.tv_sec - tv1.tv_sec)*1000000 + tv2.tv_usec - tv1.tv_usec;
		if (time >= getSpeed()) {
			gettimeofday(&tv1, 0);
			if (!gamePause) {
				if (!handleGame()) {
					drawString("GAME OVER!", 0xFFF0, 0x0, 90, 100);
					break;
				}
			}
		} else {
			usleep(getSpeed() - time);
		}
	}
	exit(EXIT_SUCCESS);
}

//Handles signals
//Reads the driver and determines the button(s) pushed
void sigioHandler(int signo)
{
	if (signo == SIGIO) {
		int data = (int) fgetc(driver);
		int button = getIndex(data);
		if (button != -1)
			setDirection(button);
		switch (button) {
			case SW5:
				gamePause = !gamePause;
				break;
			default:
				break;
		}
	}
}

//Initializes the gamepad driver
int initGamepadDriver()
{
	driver = fopen("/dev/gamepad", "rb");
	signal(SIGIO, &sigioHandler);
	fcntl(fileno(driver), F_SETOWN, getpid());
	int oflags = fcntl(fileno(driver), F_GETFL);
	fcntl(fileno(driver), F_SETFL, oflags | FASYNC);
    return EXIT_SUCCESS;
}
