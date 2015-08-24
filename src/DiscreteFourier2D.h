#ifndef DISCRETE_FOURIER_2D
#define DISCRETE_FOURIER_2D

#include <vector>
#include <array>

class DFourier2D{
	double period;
	int N; //matrix size
	std::vector< std::vector< std::array<double, 2> >> coefMat;
	std::vector< std::vector<double>> amplitudeMat; 
	std::vector< std::vector<double>> phaseShiftMat;

	std::array<double, 2> getCoef(int i, int j, const std::vector< std::vector<double> > &heightMap);
public:
	DFourier2D(double period, const std::vector< std::vector<double> > &heightMap);
	double getZ(double x, double y);
};

#endif