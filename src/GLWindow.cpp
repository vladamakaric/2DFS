
#include "GLWindow.h"

#include "global.h"
#include <iostream>

void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}


GLWindow::GLWindow(int X, int Y, int W, int H, const char*L) : Fl_Gl_Window(X, Y, W, H, L), fgui(INPUT_POINTS,CELL_SIZE){
	end();

}

void GLWindow::FixViewport(int W, int H) {
	glLoadIdentity();
	glViewport(0, 0, W, H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	//glOrtho(-W, W, -H, H, -100, 100);
	perspectiveGL(45, (GLfloat)W / (GLfloat)H, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

}

void cubz(double side){
	glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
	glColor3f(1.0f, 0.0f, 0.0f);						// Red
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of Triangle (Front)
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glVertex3f(-1.0f, -1.0f, 1.0f);					// Left Of Triangle (Front)
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	glVertex3f(1.0f, -1.0f, 1.0f);					// Right Of Triangle (Front)
	glColor3f(1.0f, 0.0f, 0.0f);						// Red
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of Triangle (Right)
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	glVertex3f(1.0f, -1.0f, 1.0f);					// Left Of Triangle (Right)
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glVertex3f(1.0f, -1.0f, -1.0f);					// Right Of Triangle (Right)
	glColor3f(1.0f, 0.0f, 0.0f);						// Red
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of Triangle (Back)
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glVertex3f(1.0f, -1.0f, -1.0f);					// Left Of Triangle (Back)
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);					// Right Of Triangle (Back)
	glColor3f(1.0f, 0.0f, 0.0f);						// Red
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of Triangle (Left)
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);					// Left Of Triangle (Left)
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glVertex3f(-1.0f, -1.0f, 1.0f);					// Right Of Triangle (Left)
	glEnd();
}

void coordAxis(){
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

void GLWindow::draw() {
	if (!valid()) { valid(1); FixViewport(w(), h()); }

	glLoadIdentity();

	glPushMatrix();
	
	camera.transform();

	glClearColor(0, 0, 0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	coordAxis();

	fgui.Draw();

	glPopMatrix();
}

void GLWindow::resize(int X, int Y, int W, int H) {
	Fl_Gl_Window::resize(X, Y, W, H);
	FixViewport(W, H);
	redraw();
}

int GLWindow::handle(int e){

	int ret = Fl_Gl_Window::handle(e);
	if (camera.handleEvents(e)){
		redraw();
		ret = 1; 
	}
	else if (fgui.handleEvents(e)){
		redraw();
		ret = 1;
	}
	else
		return ret;
}
