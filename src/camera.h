#ifndef CAMERA_H
#define CAMERA_H
#include "Vector.h"


class Camera{
public:
	bool leftMouseDown;
	double posInc;

	double xpos;
	double ypos;
	double zpos;
	double zoom;
	double yrot, zrot, xrot;
	double rot;
	CVector prevMousePos;


	Camera();
	void transform();

	bool handleEvents(int e);
};

#endif