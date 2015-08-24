#include "AppWindow.h"

int AppWindow::handle(int e)
//=======================================================================
{

	if (glw->fgui.handleEvents(e))
	{
		glw->redraw();
		return 1;
	}
	else
	return Fl_Window::handle(e);
}