#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Window.H>

#include "GLWindow.h"

class AppWindow : public Fl_Window {
	GLWindow *glw;                    
	Fl_Multiline_Output *tArea;
public:

	int handle(int e);

	AppWindow(int W, int H, const char*L = 0) : Fl_Window(W, H, L){
		glw = new GLWindow(0, 0, w(), h() - 60);
		tArea = new Fl_Multiline_Output(0, h()-60, W, 60);
		tArea->value("smor");
		tArea->box(FL_NO_BOX);
		end();
	}

	//int handle(int e);
};


#endif
