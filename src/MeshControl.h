#ifndef MESH_CONTROL_H
#define MESH_CONTROL_H

#include <vector>
#include <random>

class MeshControl{
	
	
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<> dis;

	int currRow, currCol;
public:
	bool meshChanged;
	std::vector< std::vector<double> > mesh;
	int getRow() { return currRow; }
	int getCol() { return currCol; }
	int handleEvents(int e);
	MeshControl(int matrixSize);
	void changeCurrentPos(int newI, int newJ);
	void changeCurrentElevation(double dy);
	int getMatrixSize();
	double getElevation(int i, int j);
	void AddNewRowCol();
	void RemoveLastRowCol();



};

#endif