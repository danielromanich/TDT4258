#include "game.h"
#include "game_logic.h"

FILE* driver;
bool gamePause = false;


int main(int argc, char *argv[])
{
	printf("Hello! This is snake!\n");
	init_gamepad();
	setupGraphics();
	setupGame();
	while(true) {
		if (!gamePause) {
			if (!handleGame()) {
				drawString("GAME OVER FAKKING PLEB", 0xFFF0, 0x0, 90, 100);
				repaint();
				break;
			}
		}
		usleep(getSpeed());
	}
	exit(EXIT_SUCCESS);
}

void sigio_handler(int signo)
{
	if (signo == SIGIO) {
		int reg = (int) fgetc(driver);
		int button = getIndex(reg);
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

int init_gamepad()
{
	driver = fopen("/dev/gamepad", "rb");
	int oflags;
	
	signal(SIGIO, &sigio_handler);
	fcntl(fileno(driver), F_SETOWN, getpid());
	oflags = fcntl(fileno(driver), F_GETFL);
	fcntl(fileno(driver), F_SETFL, oflags | FASYNC);
    return EXIT_SUCCESS;
}
