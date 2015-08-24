#include "camera.h"
#include "global.h"
#include <FL/gl.h>
#include <algorithm>

Camera::Camera() : xpos(0), ypos(0), zpos(10), posInc(10), zoom(1), leftMouseDown(false), prevMousePos(0, 0){
	yrot = zrot = xrot = rot = 0;

}

void Camera::transform(){
	glTranslated(-xpos, -ypos, -zpos);
	glScalef(zoom, zoom, 1);
	glRotatef(xrot, 1, 0, 0);
	glRotatef(yrot, 0, 1, 0);
	glRotatef(zrot, 0, 0, 1);
}

void cross(double *x, double *y, double *z, double x1, double y1, double z1, double x2, double y2, double z2){
	*x = (y1 * z2) - (y2 * z1);
	*y = (z1 * x2) - (z2 * x1);
	*z = (x1 * y2) - (x2 * y1);
}

bool Camera::handleEvents(int e){

		
			if (e == FL_MOUSEWHEEL){
			zoom += Fl::event_dy()*0.1;

			return true;
			}
			else if (e == FL_PUSH){
				prevMousePos.Set(Fl::event_x(), Fl::event_y());
				return true;
			}
			else if (e == FL_DRAG){
				
				CVector currentMousePos(Fl::event_x(), Fl::event_y());

				CVector dr = currentMousePos - prevMousePos;

				if (Fl::event_button() == FL_LEFT_MOUSE)
				{
					xpos += -dr.x / 100.0;
					ypos += dr.y / 100.0;
				}
				else if (Fl::event_button() == FL_RIGHT_MOUSE)
				{
					double r = std::min(SCREEN_WIDTH, SCREEN_HEIGHT);
					CVector screenCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

					CVector toCenter2 = currentMousePos - screenCenter;
					CVector toCenter1 = prevMousePos - screenCenter;
					toCenter1 /= r;
					toCenter2 /= r;
					if (toCenter1.Length() > 1 || toCenter2.Length() > 1)
						return true;

					double z1 = sqrt(1 - toCenter1.LengthSq());
					double z2 = sqrt(1 - toCenter2.LengthSq());

					double x, y, z;

					cross(&x, &y, &z, toCenter1.x, toCenter1.y, z1, toCenter2.x, toCenter2.y, z2);

					double lenght = sqrt(x*x + y*y + z*z);
					double normalX, normalY, normalZ; 
					normalX = x / lenght;
					normalY = y / lenght;
					normalZ = z / lenght;

					xrot -= normalX;
					yrot += normalY;
					zrot -= normalZ;
				}

				prevMousePos = currentMousePos;
				return true;
	
			}

			return false;
	



}

/*
if (e == FL_KEYDOWN){
	switch (Fl::event_key()){
	case 's':
		ypos += posInc;
		return true;
	case 'w':
		ypos -= posInc;
		return true;
	case 'd':
		xpos -= posInc;
		return true;
	case 'a':
		xpos += posInc;
		return true;
	};
	}*/
