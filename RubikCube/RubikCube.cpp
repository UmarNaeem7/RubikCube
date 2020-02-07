// RubikCube.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define N 3

//face 1: white (front)
//face 2: yellow opposite to 1 (back)
//face 3: orange (top)
//face 4: red opposite to 3 (bottom)
//face 5: green (left)
//face 6 blue opposite to 5 (right)


void inputCube(int cube[][3][3])
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				cube[i][j][k] = i + 1;
}

void inputCubeFromFile(string fileName, int initialCube[][N][N], int finalCube[][N][N])
{
	ifstream file;
	file.open(fileName);

	if (!file) {
		cerr << "Unable to open the input file";
		exit(1);   // call system to stop
	}

	while (!file.eof())
	{
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					file >> initialCube[i][j][k];

		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					file >> finalCube[i][j][k];
	}
}

void printCube(int cube[6][3][3])
{
	for (int i = 0; i < 6; i++)
	{
		cout << "Face " << i + 1 << ":" << endl;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cout << cube[i][j][k] << "  ";
			}
			cout << endl;
		}
	}
	cout << endl;
}

// An Inplace function to rotate a N x N matrix 
// by 90 degrees in anti-clockwise direction 
void rotateMatrixAntiClockwise(int mat[][N])
{
	// Consider all squares one by one 
	for (int x = 0; x < N / 2; x++)
	{
		// Consider elements in group of 4 in  
		// current square 
		for (int y = x; y < N - x - 1; y++)
		{
			// store current cell in temp variable 
			int temp = mat[x][y];

			// move values from right to top 
			mat[x][y] = mat[y][N - 1 - x];

			// move values from bottom to right 
			mat[y][N - 1 - x] = mat[N - 1 - x][N - 1 - y];

			// move values from left to bottom 
			mat[N - 1 - x][N - 1 - y] = mat[N - 1 - y][x];

			// assign temp to left 
			mat[N - 1 - y][x] = temp;
		}
	}
}

void rotateMatrixClockwise(int a[N][N])
{

	// Traverse each cycle 
	for (int i = 0; i < N / 2; i++) {
		for (int j = i; j < N - i - 1; j++) {

			// Swap elements of each cycle 
			// in clockwise direction 
			int temp = a[i][j];
			a[i][j] = a[N - 1 - j][i];
			a[N - 1 - j][i] = a[N - 1 - i][N - 1 - j];
			a[N - 1 - i][N - 1 - j] = a[j][N - 1 - i];
			a[j][N - 1 - i] = temp;
		}
	}
}

void moveCube(int cube[6][3][3], int faceNum, char move)
{
	switch (move)
	{
	case 'C': //clockwise rotation
		if (faceNum == 0)
		{
			rotateMatrixClockwise(cube[0]);

			//store right values from (orange) top face 
			int a = cube[2][0][2];
			int b = cube[2][1][2];
			int c = cube[2][2][2];

			//move right values in (green) left face to (orange) top face
			cube[2][0][2] = cube[4][0][2];
			cube[2][1][2] = cube[4][1][2];
			cube[2][2][2] = cube[4][2][2];

			//move right values in (red) bottom face to (green) left face
			cube[4][0][2] = cube[3][0][2];
			cube[4][1][2] = cube[3][1][2];
			cube[4][2][2] = cube[3][2][2];

			//move right values in (blue) right face to (red) bottom face
			cube[3][0][2] = cube[5][0][2];
			cube[3][1][2] = cube[5][1][2];
			cube[3][2][2] = cube[5][2][2];

			//move right values in (orange) top face to (blue) right face
			cube[5][0][2] = a;
			cube[5][1][2] = b;
			cube[5][2][2] = c;
		}
		else if (faceNum == 1)
		{
			rotateMatrixClockwise(cube[1]);

			//store right values from (blue) right face 
			int a = cube[5][0][2];
			int b = cube[5][1][2];
			int c = cube[5][2][2];

			//move right values in (red) bottom face to (blue) right face
			cube[5][0][2] = cube[3][0][2];
			cube[5][1][2] = cube[3][1][2];
			cube[5][2][2] = cube[3][2][2];

			//move right values in (green) left face to (red) bottom face
			cube[3][0][2] = cube[4][0][2];
			cube[3][1][2] = cube[4][1][2];
			cube[3][2][2] = cube[4][2][2];

			//move right values in (orange) top face to (green) left face
			cube[4][0][2] = cube[2][0][2];
			cube[4][1][2] = cube[2][1][2];
			cube[4][2][2] = cube[2][2][2];

			//move right values in (blue) right face to (orange) back face
			cube[2][0][2] = a;
			cube[2][1][2] = b;
			cube[2][2][2] = c;
		}
		else if (faceNum == 2)
		{
			rotateMatrixClockwise(cube[2]);

			//store right values from (green) left face 
			int a = cube[4][0][2];
			int b = cube[4][1][2];
			int c = cube[4][2][2];

			//move right values in (white) front face to (green) left face
			cube[4][0][2] = cube[0][0][2];
			cube[4][1][2] = cube[0][1][2];
			cube[4][2][2] = cube[0][2][2];

			//move right values in (blue) right face to (white) front face
			cube[0][0][2] = cube[5][0][2];
			cube[0][1][2] = cube[5][1][2];
			cube[0][2][2] = cube[5][2][2];

			//move right values in (yellow) back face to (blue) right face
			cube[5][0][2] = cube[1][0][2];
			cube[5][1][2] = cube[1][1][2];
			cube[5][2][2] = cube[1][2][2];

			//move right values in (green) left face to (yellow) back face
			cube[1][0][2] = a;
			cube[1][1][2] = b;
			cube[1][2][2] = c;
		}
		else if (faceNum == 3)
		{
			rotateMatrixClockwise(cube[3]);

			//store right values from (yellow) back face 
			int a = cube[1][0][2];
			int b = cube[1][1][2];
			int c = cube[1][2][2];

			//move right values in (blue) right face to (yellow) back face
			cube[1][0][2] = cube[5][0][2];
			cube[1][1][2] = cube[5][1][2];
			cube[1][2][2] = cube[5][2][2];

			//move right values in (white) front face to (blue) right face  
			cube[5][0][2] = cube[0][0][2];
			cube[5][1][2] = cube[0][1][2];
			cube[5][2][2] = cube[0][2][2];

			//move right values in (green) left face to (whute) front face
			cube[0][0][2] = cube[4][0][2];
			cube[0][1][2] = cube[4][1][2];
			cube[0][2][2] = cube[4][2][2];

			//move right values in (yellow) back face to (green) left face   
			cube[4][0][2] = a;
			cube[4][1][2] = b;
			cube[4][2][2] = c;
		}
		else if (faceNum == 4)
		{
			rotateMatrixClockwise(cube[4]);

			//store right values from (yellow) back face 
			int a = cube[1][0][2];
			int b = cube[1][1][2];
			int c = cube[1][2][2];

			//move right values in (red) bottom face to (yellow) back face
			cube[1][0][2] = cube[3][0][2];
			cube[1][1][2] = cube[3][1][2];
			cube[1][2][2] = cube[3][2][2];

			//move right values in (white) front face to (red) bottom face  
			cube[3][0][2] = cube[0][0][2];
			cube[3][1][2] = cube[0][1][2];
			cube[3][2][2] = cube[0][2][2];

			//move right values in (orange) top face to (white) left face  
			cube[0][0][2] = cube[2][0][2];
			cube[0][1][2] = cube[2][1][2];
			cube[0][2][2] = cube[2][2][2];

			//move right values in (yellow) back face to (orange) top face   
			cube[2][0][2] = a;
			cube[2][1][2] = b;
			cube[2][2][2] = c;
		}
		else if (faceNum == 5)
		{
			rotateMatrixClockwise(cube[5]);

			//store right values from (white) front face 
			int a = cube[0][0][2];
			int b = cube[0][1][2];
			int c = cube[0][2][2];

			//move right values in (red) bottom face to (white) front face
			cube[0][0][2] = cube[3][0][2];
			cube[0][1][2] = cube[3][1][2];
			cube[0][2][2] = cube[3][2][2];

			//move right values in (yellow) back face to (red) bottom face  
			cube[3][0][2] = cube[1][0][2];
			cube[3][1][2] = cube[1][1][2];
			cube[3][2][2] = cube[1][2][2];

			//move right values in (orange) top face to (yellow) back face  
			cube[1][0][2] = cube[2][0][2];
			cube[1][1][2] = cube[2][1][2];
			cube[1][2][2] = cube[2][2][2];

			//move right values in (white) front face to (orange) top face   
			cube[2][0][2] = a;
			cube[2][1][2] = b;
			cube[2][2][2] = c;
		}
		else
		{
			cout << "Invalid face number!!" << endl;
			return;
		}
		case 'A': //anti-clockwise rotation
			if (faceNum == 0)
			{
				rotateMatrixAntiClockwise(cube[0]);

				//store right values from (orange) top face 
				int a = cube[2][0][2];
				int b = cube[2][1][2];
				int c = cube[2][2][2];

				//move right values in (blue) right face to (orange) top face
				cube[2][0][2] = cube[5][0][2];
				cube[2][1][2] = cube[5][1][2];
				cube[2][2][2] = cube[5][2][2];

				//move right values in (red) bottom face to (blue) right face
				cube[5][0][2] = cube[3][0][2];
				cube[5][1][2] = cube[3][1][2];
				cube[5][2][2] = cube[3][2][2];

				//move right values in (green) left face to (red) bottom face
				cube[3][0][2] = cube[4][0][2];
				cube[3][1][2] = cube[4][1][2];
				cube[3][2][2] = cube[4][2][2];

				//move right values in (orange) top face to (green) left face
				cube[4][0][2] = a;
				cube[4][1][2] = b;
				cube[4][2][2] = c;
			}
			else if (faceNum == 1)
			{
				rotateMatrixAntiClockwise(cube[1]);

				//store right values from (blue) right face 
				int a = cube[5][0][2];
				int b = cube[5][1][2];
				int c = cube[5][2][2];

				//move right values in (orange) top face to (blue) right face
				cube[5][0][2] = cube[2][0][2];
				cube[5][1][2] = cube[2][1][2];
				cube[5][2][2] = cube[2][2][2];

				//move right values in (green) left face to (orange) top face
				cube[2][0][2] = cube[4][0][2];
				cube[2][1][2] = cube[4][1][2];
				cube[2][2][2] = cube[4][2][2];

				//move right values in (red) bottom face to (green) left face
				cube[4][0][2] = cube[3][0][2];
				cube[4][1][2] = cube[3][1][2];
				cube[4][2][2] = cube[3][2][2];

				//move right values in (blue) right face to (red) bottom face
				cube[3][0][2] = a;
				cube[3][1][2] = b;
				cube[3][2][2] = c;
			}
			else if (faceNum == 2)
			{
				rotateMatrixAntiClockwise(cube[2]);

				//store right values from (green) left face 
				int a = cube[4][0][2];
				int b = cube[4][1][2];
				int c = cube[4][2][2];

				//move right values in (yellow) back face to (green) left face
				cube[4][0][2] = cube[1][0][2];
				cube[4][1][2] = cube[1][1][2];
				cube[4][2][2] = cube[1][2][2];

				//move right values in (blue) right face to (yellow) back face
				cube[1][0][2] = cube[5][0][2];
				cube[1][1][2] = cube[5][1][2];
				cube[1][2][2] = cube[5][2][2];

				//move right values in (white) front face to (blue) right face
				cube[5][0][2] = cube[0][0][2];
				cube[5][1][2] = cube[0][1][2];
				cube[5][2][2] = cube[0][2][2];

				//move right values in (green) left face to (white) back face
				cube[0][0][2] = a;
				cube[0][1][2] = b;
				cube[0][2][2] = c;
			}
			else if (faceNum == 3)
			{
				rotateMatrixAntiClockwise(cube[3]);

				//store right values from (yellow) back face 
				int a = cube[1][0][2];
				int b = cube[1][1][2];
				int c = cube[1][2][2];

				//move right values in (green) left face to (yellow) back face
				cube[1][0][2] = cube[4][0][2];
				cube[1][1][2] = cube[4][1][2];
				cube[1][2][2] = cube[4][2][2];

				//move right values in (white) front face to (green) left face  
				cube[4][0][2] = cube[0][0][2];
				cube[4][1][2] = cube[0][1][2];
				cube[4][2][2] = cube[0][2][2];

				//move right values in (blue) right face to (white) front face
				cube[0][0][2] = cube[5][0][2];
				cube[0][1][2] = cube[5][1][2];
				cube[0][2][2] = cube[5][2][2];

				//move right values in (yellow) back face to (blue) right face   
				cube[5][0][2] = a;
				cube[5][1][2] = b;
				cube[5][2][2] = c;
			}
			else if (faceNum == 4)
			{
				rotateMatrixAntiClockwise(cube[4]);

				//store right values from (yellow) back face 
				int a = cube[1][0][2];
				int b = cube[1][1][2];
				int c = cube[1][2][2];

				//move right values in (orange) top face to (yellow) back face
				cube[1][0][2] = cube[2][0][2];
				cube[1][1][2] = cube[2][1][2];
				cube[1][2][2] = cube[2][2][2];

				//move right values in (white) front face to (orange) bottom face  
				cube[2][0][2] = cube[0][0][2];
				cube[2][1][2] = cube[0][1][2];
				cube[2][2][2] = cube[0][2][2];

				//move right values in (red) bottom face to (white) front face  
				cube[0][0][2] = cube[3][0][2];
				cube[0][1][2] = cube[3][1][2];
				cube[0][2][2] = cube[3][2][2];

				//move right values in (yellow) back face to (red) bottom face   
				cube[3][0][2] = a;
				cube[3][1][2] = b;
				cube[3][2][2] = c;
			}
			else if (faceNum == 5)
			{
				rotateMatrixAntiClockwise(cube[5]);

				//store right values from (white) front face 
				int a = cube[0][0][2];
				int b = cube[0][1][2];
				int c = cube[0][2][2];

				//move right values in (orange) top face to (white) front face
				cube[0][0][2] = cube[2][0][2];
				cube[0][1][2] = cube[2][1][2];
				cube[0][2][2] = cube[2][2][2];

				//move right values in (yellow) back face to (orange) top face  
				cube[2][0][2] = cube[1][0][2];
				cube[2][1][2] = cube[1][1][2];
				cube[2][2][2] = cube[1][2][2];

				//move right values in (red) bottom face to (yellow) back face  
				cube[1][0][2] = cube[3][0][2];
				cube[1][1][2] = cube[3][1][2];
				cube[1][2][2] = cube[3][2][2];

				//move right values in (white) front face to (red) bottom face   
				cube[3][0][2] = a;
				cube[3][1][2] = b;
				cube[3][2][2] = c;
			}
			else
			{
				cout << "Invalid face number!!" << endl;
				return;
			}
	default:
		break;
	}

	
}

int main()
{
	int initialCube[6][3][3];
	int finalCube[6][3][3];

	inputCubeFromFile("file.txt", initialCube, finalCube);

	cout << "Initial Cube:" << endl;
	printCube(initialCube);
	cout << "Final Cube:" << endl;
	printCube(finalCube);

	cout << "Cube after a move:" << endl;
	moveCube(initialCube, 0, 'A');
	printCube(initialCube);

	return 0;
}

