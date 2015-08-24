#ifndef GL_WINDOW
#define GL_WINDOW

#include <FL/gl.h>
#include <FL/Fl_Gl_Window.H>
#include "camera.h"
#include "FourierGUI.h"

class GLWindow : public Fl_Gl_Window {
	
	void FixViewport(int W, int H);
	void draw();
	void resize(int X, int Y, int W, int H);
	int handle(int e);
public:
	FourierGUI fgui;
	Camera camera;
	GLWindow(int X, int Y, int W, int H, const char*L = 0);
};


#endif