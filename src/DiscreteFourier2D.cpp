#include "DiscreteFourier2D.h"
#include <cmath>

using namespace std;

#define PI 3.14159265

DFourier2D::DFourier2D(double period, const std::vector< std::vector<double> > &heightMap) : period(period) {

	
	N = heightMap.size();
	
	amplitudeMat.resize(N);
	phaseShiftMat.resize(N);

	for (int i = 0; i < N; i++){
		amplitudeMat[i].resize(N);
		phaseShiftMat[i].resize(N);
	}

	for (int p = 0; p < N; p++){
		for (int q = 0; q < N; q++){

			auto coef = getCoef(p, q, heightMap);
			double ampl = amplitudeMat[p][q] = sqrt(coef[0] * coef[0] + coef[1] * coef[1]);

			if (ampl)
				phaseShiftMat[p][q] = atan2(coef[1], coef[0]);
			else
				phaseShiftMat[p][q] = 0;
		}
	}
}

std::array<double, 2> DFourier2D::getCoef(int p, int q, const std::vector< std::vector<double> > &heightMap){
	double Im = 0, Re = 0;

	double angularStepFreq = (2 * PI) / N;

	for (int n = 0; n < N; n++){
		for (int m = 0; m < N; m++){
			Re += (heightMap[n][m] / (N*N)) * cos(angularStepFreq*(p*n + q*m));
			Im += (heightMap[n][m] / (N*N)) * sin(angularStepFreq*(p*n + q*m));
		}
	}

	return array < double, 2 > {{Re, Im}};
}

double DFourier2D::getZ(double x, double y){

	double z = 0;
	for (int p = 0; p < N; p++){
		for (int q = 0; q < N; q++){
			z += amplitudeMat[p][q] * cos(phaseShiftMat[p][q] - 2 * PI*(p*x + q*y)/period);
		}
	}

	return z;
}