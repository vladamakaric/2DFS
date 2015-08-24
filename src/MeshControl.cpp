#include "MeshControl.h"
#include "global.h"
using namespace std;

MeshControl::MeshControl(int matrixSize) : gen(rd()), dis(0.2, 0.5), currCol(0), currRow(0){

	for (int i = 0; i < matrixSize; i++){
		mesh.push_back(vector<double>(matrixSize));
		for (int j = 0; j < matrixSize; j++)
			mesh[i][j] =dis(gen);
	}
}

double MeshControl::getElevation(int i, int j){
	return mesh[i][j];
}

int MeshControl::getMatrixSize(){
	return mesh.size();
}

void MeshControl::changeCurrentElevation(double dy){
	mesh[currRow][currCol] += dy;
}

void MeshControl::AddNewRowCol(){

}

void MeshControl::RemoveLastRowCol(){

}


void MeshControl::changeCurrentPos(int newI, int newJ){
	
	if (newI < 0)
		newI = getMatrixSize() - 1;

	if (newI > getMatrixSize() - 1)
		newI = 0;

	if (newJ < 0)
		newJ = getMatrixSize() - 1;

	if (newJ > getMatrixSize() - 1)
		newJ = 0;

	currCol = newJ;
	currRow = newI;
}

int MeshControl::handleEvents(int e){

	
	if (e == FL_KEYDOWN){
		switch (Fl::event_key()){
		case 'k':
			changeCurrentElevation(0.5);
			meshChanged = true;
			return true;
		case 'j':
			changeCurrentElevation(-0.5);
			meshChanged = true;
			return true;
		case 'a':
			changeCurrentPos(currRow + 1, currCol);
			return true;
		case 'd':
			changeCurrentPos(currRow - 1, currCol);
			return true;
		case 's':
			changeCurrentPos(currRow, currCol + 1);
			return true;
		case 'w':
			changeCurrentPos(currRow, currCol - 1);
			return true;

			/*case 'w':
				currR += 1;
				return true;
				case 'd':
				xpos -= posInc;
				return true;
				case 'a':
				xpos += posInc;
				return true;*/
		};
	}
		return false;
}
