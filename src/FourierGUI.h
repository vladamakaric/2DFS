#ifndef FOURIER_GUI_H
#define FOURIER_GUI_H

#include "MeshControl.h"
#include "DiscreteFourier2D.h"


class FourierGUI{
	bool recompute;
	double cellSize;
	MeshControl mc;
	DFourier2D *df2d;
	std::vector<std::vector<double>> fmesh;
public:
	std::vector<std::vector<double>> computeFourier2D(int samples);
	int handleEvents(int e);
	FourierGUI(int matrixSize, double cellSize);
	void DrawFmesh();

	void DrawTriangleFmesh();
	void Draw();
};

#endif