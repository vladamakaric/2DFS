#include "FourierGUI.h"
#include <FL/gl.h>
#include "global.h"
using namespace std;

// This is how a vector is specified in the base code
// The origin is assumed to be [0,0,0]

typedef struct vertex_s
{
	float x, y, z;
} vertex_t;

void normalize(vertex_t *v);
// normal(); - finds a normal vector and normalizes it
void normal(vertex_t v[3], vertex_t *normal)
{
	vertex_t a, b;

	// calculate the vectors A and B
	// note that v[3] is defined with counterclockwise winding in mind
	// a
	a.x = v[0].x - v[1].x;
	a.y = v[0].y - v[1].y;
	a.z = v[0].z - v[1].z;
	// b
	b.x = v[1].x - v[2].x;
	b.y = v[1].y - v[2].y;
	b.z = v[1].z - v[2].z;

	// calculate the cross product and place the resulting vector
	// into the address specified by vertex_t *normal
	normal->x = (a.y * b.z) - (a.z * b.y);
	normal->y = (a.z * b.x) - (a.x * b.z);
	normal->z = (a.x * b.y) - (a.y * b.x);

	// normalize
	normalize(normal);
}

void normalize(vertex_t *v)
{
	// calculate the length of the vector
	float len = (float)(sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z)));

	// avoid division by 0
	if (len == 0.0f)
		len = 1.0f;

	// reduce to unit size
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

FourierGUI::FourierGUI(int matrixSize, double cellSize) : mc(matrixSize), cellSize(cellSize)

{
	df2d = new DFourier2D(cellSize*mc.getMatrixSize(), mc.mesh);
	fmesh = computeFourier2D(SAMPLES);
	recompute = false;
}

void wireCube(){

	glPushMatrix();
	glTranslatef(-0.5, -0.5, -0.5);
	glLineWidth(1.0);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);

	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);

	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, 0);
	////////////
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);

	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0);
	//////////////

	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);


	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);

	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);

	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	//////////////////////

	glEnd();
	glPopMatrix();
}

vector<vector<double>> FourierGUI::computeFourier2D(int samples){
	vector<vector<double>> fmesh(samples);

	for (int i = 0; i < samples; i++)
		fmesh[i].resize(samples);

	double period = cellSize*mc.getMatrixSize();
	double stepSize = period / samples;

	for (int i = 0; i < samples; i++){
		for (int j = 0; j < samples; j++){
			double z = i*stepSize;
			double x = j*stepSize;
			fmesh[i][j] = df2d->getZ(z, x);
		}
	}

	return fmesh;
}

void FourierGUI::DrawFmesh(){

	glColor3f(1, 1, 0);
	glPointSize(2);
	glBegin(GL_POINTS);

	double period = cellSize*mc.getMatrixSize();
	double stepSize = period / fmesh.size();
	
	for (int i = 0; i < fmesh.size(); i++){
		for (int j = 0; j < fmesh.size(); j++){
			double z = i*stepSize;
			double x = j*stepSize;
			double height = fmesh[i][j];
			glVertex3f(x, height, z);
		}
	}

	glEnd();
}

//vertex_t getNormal(int i1, int j1, int i)



vertex_t getPoint(int i, int j, double stepSize, vector< vector<double> >& mesh){
	double z = i*stepSize;
	double x = j*stepSize;
	double height = mesh[i][j];
	return vertex_t{ x, height, z };
}


void drawPointf(int i, int j, double stepSize, vector< vector<double> >& mesh){
	double z = i*stepSize;
	double x = j*stepSize;
	double height = mesh[i][j];
	glVertex3f(x, height, z);
}

void FourierGUI::DrawTriangleFmesh()
{
	vertex_t triangle[3];
	vertex_t normalv;
	
	double period = cellSize*mc.getMatrixSize();
	double stepSize = period / fmesh.size();
	
	for (int i = 0; i < fmesh.size()-1; i++){
		glBegin(GL_TRIANGLES);


		for (int j = 1; j < fmesh.size()-1; j++){

			triangle[0] = getPoint(i, j, stepSize, fmesh);
			triangle[1] = getPoint(i + 1, j, stepSize, fmesh);
			triangle[2] = getPoint(i, j + 1, stepSize, fmesh);

			normal(triangle, &normalv);

			glNormal3f(normalv.x, normalv.y, normalv.z);
			drawPointf(i, j, stepSize, fmesh);
			drawPointf(i+1, j, stepSize, fmesh);
			drawPointf(i, j+1, stepSize, fmesh);

			////////////////////////////////////////////////////////

			triangle[0] = getPoint(i, j + 1, stepSize, fmesh);
			triangle[1] = getPoint(i + 1, j, stepSize, fmesh);
			triangle[2] = getPoint(i + 1, j + 1, stepSize, fmesh);

			normal(triangle, &normalv);

			glNormal3f(normalv.x, normalv.y, normalv.z);
			drawPointf(i, j + 1, stepSize, fmesh);
			drawPointf(i + 1, j, stepSize, fmesh);
			drawPointf(i + 1, j + 1, stepSize, fmesh);
		}
		
		glEnd();
	}

}

void FourierGUI::Draw(){

	if (mc.meshChanged)
	{

		delete df2d;
		df2d = new DFourier2D(cellSize*mc.getMatrixSize(), mc.mesh);
		mc.meshChanged = false;
		fmesh = computeFourier2D(SAMPLES);
	}


	//DrawFmesh();
	DrawTriangleFmesh();
	glPushMatrix();

	glTranslatef(cellSize*mc.getCol(), mc.getElevation(mc.getRow(), mc.getCol()), cellSize*mc.getRow());
	glScalef(0.2, 0.2, 0.2);


	glDisable(GL_LIGHTING);
	wireCube();

	glPopMatrix();

	glColor3f(1, 1, 1);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	int matSize = mc.getMatrixSize();
	for (int i = 0; i < matSize+1; i++){
		glVertex3f(0, 0, i*cellSize); 
		glVertex3f(matSize*cellSize, 0, i*cellSize);

		glVertex3f(i*cellSize, 0, 0);
		glVertex3f(i*cellSize, 0, matSize*cellSize);
	}
	glEnd();
	glLineWidth(1);
	glColor3f(1, 0, 1);
	glBegin(GL_LINES);
	double curX = 0, curZ = 0;
	for (int i = 0; i < matSize+1; i++){
		for (int j = 0; j < matSize; j++){
			glVertex3f(curX, mc.getElevation(i%matSize, j), curZ);
			glVertex3f(curX + cellSize, mc.getElevation(i%matSize, (j + 1) % matSize), curZ);
			curX += cellSize;
		}

		curX = 0;
		curZ += cellSize;
	}
	curX = curZ = 0;

	for (int j = 0; j < matSize + 1; j++){

		curZ = 0;
		for (int i = 0; i < matSize; i++){
			glVertex3f(curX, mc.getElevation(i, j % matSize), curZ);
			glVertex3f(curX, mc.getElevation((i + 1) % matSize, j % matSize), curZ + cellSize);
			curZ += cellSize;
		}
		
		curX += cellSize;
	}
	glEnd();

	glEnable(GL_LIGHTING);
}

int FourierGUI::handleEvents(int e){
	return mc.handleEvents(e);
}

/*
double period = cellSize*mc.getMatrixSize();
double stepSize = period / fmesh.size();

for (int i = 0; i < fmesh.size() - 1; i++){
	glBegin(GL_TRIANGLE_STRIP);


	drawPointf(i, 0, stepSize, fmesh);
	for (int j = 1; j < fmesh.size() - 1; j++){
		drawPointf(i + 1, j, stepSize, fmesh);
		drawPointf(i, j + 1, stepSize, fmesh);
	}
	drawPointf(i + 1, fmesh.size() - 1, stepSize, fmesh);
	glEnd();
}*/