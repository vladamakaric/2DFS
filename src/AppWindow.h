#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Window.H>

#include "GLWindow.h"

class AppWindow : public Fl_Window {
	GLWindow *glw;                    
	Fl_Multiline_Output *tArea;
	Fl_Text_Display* td;
public:

	int handle(int e);

	AppWindow(int W, int H, const char*L = 0) : Fl_Window(W, H, L){
		glw = new GLWindow(0, 0, w(), h() - 60);
		
		td = new Fl_Text_Display(0, h()-60, W, 60);
		Fl_Text_Buffer *buff = new Fl_Text_Buffer();
		td->buffer(buff);
		glw->resizable(*td);
		buff->text("Controls:" 
				   "\nLeft mouse drag - PAN, Right mouse drag - ROTATE, Mouse Wheel - Zoom"
				   "\nMove the sample point - WASD, Modify sample value - j,k keys");
		end();
	}
};


#endif
