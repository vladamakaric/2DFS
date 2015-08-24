#include "AppWindow.h"
#include "global.h"

int main() {
	AppWindow win(SCREEN_WIDTH, SCREEN_HEIGHT, "2D Fourier Series visualizer");
	win.resizable(win);
	win.show();
	return(Fl::run());
}
