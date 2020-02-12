// RubikCube.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define N 3

int*** initCube();

int*** initialCube = initCube();
int*** finalCube = initCube();
bool cubeSolved = false;
vector<string> moveList;

//face 1: white (front)
//face 2: yellow opposite to 1 (back)
//face 3: orange (top)
//face 4: red opposite to 3 (bottom)
//face 5: green (left)
//face 6 blue opposite to 5 (right)

float heuristic(int*** cube, int*** finalCube)
{
	float manhattanDistance = 0;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{
				//if a cube tile is not at its supposed position
				if (cube[i][j][k] != finalCube[i][j][k])
				{
					int face_original = cube[i][j][k];
					//find out on which face number the tile is
					manhattanDistance += abs(face_original - i);		
				}
			}
	manhattanDistance = manhattanDistance / 8;
	return manhattanDistance;
}

void printMoveList(int x = 0) {
	if (x = -1) {//prints movelist in reverse
		cout << "==============Move List==============" << endl;
		for (int i = moveList.size()-1; i >= 0; i--) {
			cout << moveList[i] << endl;
		}
		cout << "=====================================" << endl;
	}
	else {
		cout << "==============Move List==============" << endl;
		for (int i = 0; i < moveList.size(); i++) {
			cout << moveList[i] << endl;
		}
		cout << "=====================================" << endl;
	}
	
}

void inputCube(int*** cube)
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				cube[i][j][k] = i + 1;
}

void inputCubeFromFile(string fileName)
{
	ifstream file;
	file.open(fileName);

	if (!file) {
		cerr << "Unable to open the input file";
		exit(1);   // call system to stop
	}

	while (!file.eof())
	{
		//final cube is solved state
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					file >> finalCube[i][j][k];

		//initial cube is unsolved state
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					file >> initialCube[i][j][k];
	}
}

void printCube(int*** cube)
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
void rotateMatrixAntiClockwise(int** mat)
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

void rotateMatrixClockwise(int** mat)
{
	// Traverse each cycle 
	for (int i = 0; i < N / 2; i++) {
		for (int j = i; j < N - i - 1; j++) {

			// Swap elements of each cycle 
			// in clockwise direction 
			int temp = mat[i][j];
			mat[i][j] = mat[N - 1 - j][i];
			mat[N - 1 - j][i] = mat[N - 1 - i][N - 1 - j];
			mat[N - 1 - i][N - 1 - j] = mat[j][N - 1 - i];
			mat[j][N - 1 - i] = temp;
		}
	}
}

void moveCube(int*** cube, int faceNum, char move)
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

int*** initCube() {
	int*** newCube = new int**[6];

	for (int i = 0; i < 6; i++) {
		newCube[i] = new int*[3];

		for (int j = 0; j < 3; j++)
			newCube[i][j] = new int[3];
	}


	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				newCube[i][j][k] = 0;
			}
		}
	}

	return newCube;
}

void deallocateCube(int*** cube) {
	for (int i = 0; i != 6; ++i)
	{
		for (int j = 0; j != 3; ++j) {
			delete[] cube[i][j];
		}

		delete[] cube[i];
	}
	delete[] cube;
}

bool isEqual(int*** destCube, int*** srcCube) {
	bool isEqual = true;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if (destCube[i][j][k] != srcCube[i][j][k]) {
					isEqual = false;
					break;
				}
			}
			if (!isEqual)
				break;
		}
		if (!isEqual)
			break;
	}
	return isEqual;
}

void rotateCubeClockwise(int*** & cube, int face) {
	int orange1;	int orange2;	int orange3;
	int blue1;		int blue2;		int blue3;
	int red1;		int red2;		int red3;
	int green1;		int green2;		int green3;
	int white1;		int white2;		int white3;
	int yellow1;	int yellow2;	int yellow3;

	switch (face) {
	case 0:
		rotateMatrixClockwise(cube[0]);
		//store top row of orange, green, red and blue face
		orange1 = cube[2][0][0]; red1 = cube[3][0][0]; green1 = cube[4][0][0]; blue1 = cube[5][0][0];
		orange2 = cube[2][0][1]; red2 = cube[3][0][1]; green2 = cube[4][0][1]; blue2 = cube[5][0][1];
		orange3 = cube[2][0][2]; red3 = cube[3][0][2]; green3 = cube[4][0][2]; blue3 = cube[5][0][2];


		//first row of orange = first row of green
		cube[2][0][0] = green1;
		cube[2][0][1] = green2;
		cube[2][0][2] = green3;

		//first row of red = first row of blue
		cube[3][0][0] = blue1;
		cube[3][0][1] = blue2;
		cube[3][0][2] = blue3;

		//first row of green = first row of red
		cube[4][0][0] = red1;
		cube[4][0][1] = red2;
		cube[4][0][2] = red3;

		//first row of blue = first row of orange
		cube[5][0][0] = orange1;
		cube[5][0][1] = orange2;
		cube[5][0][2] = orange3;

		break;
	case 1:
		rotateMatrixClockwise(cube[1]);

		orange1 = cube[2][2][0]; red1 = cube[3][2][0]; green1 = cube[4][2][0]; blue1 = cube[5][2][0];
		orange2 = cube[2][2][1]; red2 = cube[3][2][1]; green2 = cube[4][2][1]; blue2 = cube[5][2][1];
		orange3 = cube[2][2][2]; red3 = cube[3][2][2]; green3 = cube[4][2][2]; blue3 = cube[5][2][2];

		//last row of orange = last row of blue
		cube[2][2][0] = blue1;
		cube[2][2][1] = blue2;
		cube[2][2][2] = blue3;

		//last row of red = last row of green
		cube[3][2][0] = green1;
		cube[3][2][1] = green2;
		cube[3][2][2] = green3;

		//last row of green = last row of orange
		cube[4][2][0] = orange1;
		cube[4][2][1] = orange2;
		cube[4][2][2] = orange3;

		//last row of blue = last row of red
		cube[5][2][0] = red1;
		cube[5][2][1] = red2;
		cube[5][2][2] = red3;
		break;
	case 2:
		rotateMatrixClockwise(cube[2]);

		white1 = cube[0][0][0]; yellow1 = cube[1][0][0]; green1 = cube[4][0][0]; blue1 = cube[5][0][2];
		white2 = cube[0][1][0]; yellow2 = cube[1][1][0]; green2 = cube[4][1][0]; blue2 = cube[5][1][2];
		white3 = cube[0][2][0]; yellow3 = cube[1][2][0]; green3 = cube[4][2][0]; blue3 = cube[5][2][2];

		//first column of white = last column of blue
		cube[0][0][0] = blue1;
		cube[0][1][0] = blue2;
		cube[0][2][0] = blue3;

		//first column of yellow = first column of green
		cube[1][0][0] = green1;
		cube[1][1][0] = green2;
		cube[1][2][0] = green3;

		//first column of green = first column of white
		cube[4][0][0] = white1;
		cube[4][1][0] = white2;
		cube[4][2][0] = white3;

		//last column of blue = first column of yellow
		cube[5][0][0] = yellow1;
		cube[5][1][0] = yellow2;
		cube[5][2][0] = yellow3;
		break;
	case 3:
		rotateMatrixClockwise(cube[3]);

		white1 = cube[0][0][2]; yellow1 = cube[1][0][2]; green1 = cube[4][0][2]; blue1 = cube[5][0][0];
		white2 = cube[0][1][2]; yellow2 = cube[1][1][2]; green2 = cube[4][1][2]; blue2 = cube[5][1][0];
		white3 = cube[0][2][2]; yellow3 = cube[1][2][2]; green3 = cube[4][2][2]; blue3 = cube[5][2][0];

		//last column of white = last column of green
		cube[0][0][2] = green1;
		cube[0][1][2] = green2;
		cube[0][2][2] = green3;

		//last column of yellow = first column of blue
		cube[1][0][2] = blue1;
		cube[1][1][2] = blue2;
		cube[1][2][2] = blue3;

		//last column of green = last column of yellow
		cube[4][0][2] = yellow1;
		cube[4][1][2] = yellow2;
		cube[4][2][2] = yellow3;

		//first column of blue = last column of white
		cube[5][0][0] = white1;
		cube[5][1][0] = white2;
		cube[5][2][0] = white3;
		break;

	case 4:
		rotateMatrixClockwise(cube[4]);

		white1 = cube[0][2][0]; yellow1 = cube[1][0][0]; orange1 = cube[2][0][2]; red1 = cube[3][0][0];
		white2 = cube[0][2][1]; yellow2 = cube[1][0][1]; orange2 = cube[2][1][2]; red2 = cube[3][1][0];
		white3 = cube[0][2][2]; yellow3 = cube[1][0][2]; orange3 = cube[2][2][2]; red3 = cube[3][2][0];

		//last row of white = last column of orange
		cube[0][2][0] = orange1;
		cube[0][2][1] = orange2;
		cube[0][2][2] = orange3;

		//first row of yellow = first column of red
		cube[1][0][0] = red1;
		cube[1][0][1] = red2;
		cube[1][0][2] = red3;

		//last column of orange = first row of yellow
		cube[2][0][2] = yellow1;
		cube[2][1][2] = yellow2;
		cube[2][2][2] = yellow3;

		//first column of red = last row of white
		cube[3][0][0] = white1;
		cube[3][1][0] = white2;
		cube[3][2][0] = white3;
		break;
	case 5:
		rotateMatrixClockwise(cube[5]);

		white1 = cube[0][0][0]; yellow1 = cube[1][2][0]; orange1 = cube[2][0][0]; red1 = cube[3][0][2];
		white2 = cube[0][0][1]; yellow2 = cube[1][2][1]; orange2 = cube[2][1][0]; red2 = cube[3][1][2];
		white3 = cube[0][0][2]; yellow3 = cube[1][2][2]; orange3 = cube[2][2][0]; red3 = cube[3][2][2];

		//first row of white = last column of red
		cube[0][0][0] = red1;
		cube[0][0][1] = red2;
		cube[0][0][2] = red3;

		//last row of yellow = first column of orange
		cube[1][2][0] = orange1;
		cube[1][2][1] = orange2;
		cube[1][2][2] = orange3;

		//first column of orange = first row of white
		cube[2][0][0] = white1;
		cube[2][1][0] = white2;
		cube[2][2][0] = white3;

		//last column of red = last row of yellow
		cube[3][0][2] = yellow1;
		cube[3][1][2] = yellow2;
		cube[3][2][2] = yellow3;

		break;
	default:
		break;
	}
}

void rotateCubeCounterClockwise(int*** & cube, int face) {
	int orange1;	int orange2;	int orange3;
	int blue1;		int blue2;		int blue3;
	int red1;		int red2;		int red3;
	int green1;		int green2;		int green3;
	int white1;		int white2;		int white3;
	int yellow1;	int yellow2;	int yellow3;

	switch (face) {
	case 0:
		rotateMatrixClockwise(cube[0]);
		//store top row of orange, green, red and blue face
		orange1 = cube[2][0][0]; red1 = cube[3][0][0]; green1 = cube[4][0][0]; blue1 = cube[5][0][0];
		orange2 = cube[2][0][1]; red2 = cube[3][0][1]; green2 = cube[4][0][1]; blue2 = cube[5][0][1];
		orange3 = cube[2][0][2]; red3 = cube[3][0][2]; green3 = cube[4][0][2]; blue3 = cube[5][0][2];


		//first row of orange = first row of blue
		cube[2][0][0] = blue1;
		cube[2][0][1] = blue2;
		cube[2][0][2] = blue3;

		//first row of red = first row of green
		cube[3][0][0] = green1;
		cube[3][0][1] = green2;
		cube[3][0][2] = green3;

		//first row of green = first row of orange
		cube[4][0][0] = orange1;
		cube[4][0][1] = orange2;
		cube[4][0][2] = orange3;

		//first row of blue = first row of red
		cube[5][0][0] = red1;
		cube[5][0][1] = red2;
		cube[5][0][2] = red3;

		break;
	case 1:
		rotateMatrixClockwise(cube[1]);

		orange1 = cube[2][2][0]; red1 = cube[3][2][0]; green1 = cube[4][2][0]; blue1 = cube[5][2][0];
		orange2 = cube[2][2][1]; red2 = cube[3][2][1]; green2 = cube[4][2][1]; blue2 = cube[5][2][1];
		orange3 = cube[2][2][2]; red3 = cube[3][2][2]; green3 = cube[4][2][2]; blue3 = cube[5][2][2];

		//last row of orange = last row of green
		cube[2][0][0] = green1;
		cube[2][0][1] = green2;
		cube[2][0][2] = green3;

		//last row of red = last row of blue
		cube[3][0][0] = blue1;
		cube[3][0][1] = blue2;
		cube[3][0][2] = blue3;

		//last row of green = last row of red
		cube[4][0][0] = red1;
		cube[4][0][1] = red2;
		cube[4][0][2] = red3;

		//last row of blue = last row of orange
		cube[5][0][0] = orange1;
		cube[5][0][1] = orange2;
		cube[5][0][2] = orange3;
		break;
	case 2:
		rotateMatrixClockwise(cube[2]);

		white1 = cube[0][0][0]; yellow1 = cube[1][0][0]; green1 = cube[4][0][0]; blue1 = cube[5][0][2];
		white2 = cube[0][1][0]; yellow2 = cube[1][1][0]; green2 = cube[4][1][0]; blue2 = cube[5][1][2];
		white3 = cube[0][2][0]; yellow3 = cube[1][2][0]; green3 = cube[4][2][0]; blue3 = cube[5][2][2];

		//first column of white = first column of green
		cube[0][0][0] = green1;
		cube[0][1][0] = green2;
		cube[0][2][0] = green3;

		//first column of yellow = last column of blue
		cube[1][0][0] = blue1;
		cube[1][1][0] = blue2;
		cube[1][2][0] = blue3;

		//first column of green = first column of yellow
		cube[4][0][0] = yellow1;
		cube[4][1][0] = yellow2;
		cube[4][2][0] = yellow3;

		//last column of blue = first column of white
		cube[5][0][0] = white1;
		cube[5][1][0] = white2;
		cube[5][2][0] = white3;
		break;
	case 3:
		rotateMatrixClockwise(cube[3]);

		white1 = cube[0][0][2]; yellow1 = cube[1][0][2]; green1 = cube[4][0][2]; blue1 = cube[5][0][0];
		white2 = cube[0][1][2]; yellow2 = cube[1][1][2]; green2 = cube[4][1][2]; blue2 = cube[5][1][0];
		white3 = cube[0][2][2]; yellow3 = cube[1][2][2]; green3 = cube[4][2][2]; blue3 = cube[5][2][0];

		//last column of white = first column of blue
		cube[0][0][2] = blue1;
		cube[0][1][2] = blue2;
		cube[0][2][2] = blue3;

		//last column of yellow = last column of green
		cube[1][0][2] = green1;
		cube[1][1][2] = green2;
		cube[1][2][2] = green3;

		//last column of green = last column of white
		cube[4][0][2] = white1;
		cube[4][1][2] = white2;
		cube[4][2][2] = white3;

		//first column of blue = last column of yellow
		cube[5][0][0] = yellow1;
		cube[5][1][0] = yellow2;
		cube[5][2][0] = yellow3;
		break;

	case 4:
		rotateMatrixClockwise(cube[4]);

		white1 = cube[0][2][0]; yellow1 = cube[1][0][0]; orange1 = cube[2][0][2]; red1 = cube[3][0][0];
		white2 = cube[0][2][1]; yellow2 = cube[1][0][1]; orange2 = cube[2][1][2]; red2 = cube[3][1][0];
		white3 = cube[0][2][2]; yellow3 = cube[1][0][2]; orange3 = cube[2][2][2]; red3 = cube[3][2][0];

		//last row of white = first column of red
		cube[0][2][0] = red1;
		cube[0][2][1] = red2;
		cube[0][2][2] = red3;

		//first row of yellow = last column of orange
		cube[1][0][0] = orange1;
		cube[1][0][1] = orange2;
		cube[1][0][2] = orange3;

		//last column of orange = last row of white
		cube[2][0][2] = white1;
		cube[2][1][2] = white2;
		cube[2][2][2] = white3;

		//first column of red = first row of yellow
		cube[3][0][0] = yellow1;
		cube[3][1][0] = yellow2;
		cube[3][2][0] = yellow3;
		break;
	case 5:
		rotateMatrixClockwise(cube[5]);

		white1 = cube[0][0][0]; yellow1 = cube[1][2][0]; orange1 = cube[2][0][0]; red1 = cube[3][0][2];
		white2 = cube[0][0][1]; yellow2 = cube[1][2][1]; orange2 = cube[2][1][0]; red2 = cube[3][1][2];
		white3 = cube[0][0][2]; yellow3 = cube[1][2][2]; orange3 = cube[2][2][0]; red3 = cube[3][2][2];

		//first row of white = first column of orange
		cube[0][0][0] = orange1;
		cube[0][0][1] = orange2;
		cube[0][0][2] = orange3;

		//last row of yellow = last column of red
		cube[1][2][0] = red1;
		cube[1][2][1] = red2;
		cube[1][2][2] = red3;

		//first column of orange = last row of yellow
		cube[2][0][0] = yellow1;
		cube[2][1][0] = yellow2;
		cube[2][2][0] = yellow3;

		//last column of red = first row of white
		cube[3][0][2] = white1;
		cube[3][1][2] = white2;
		cube[3][2][2] = white3;

		break;
	default:
		break;
	}
}

int*** copyCube(int*** destCube, int*** srcCube) {

	//Copy cube into newCube
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				destCube[i][j][k] = srcCube[i][j][k];
			}
		}
	}
	return destCube;
}

int*** nextState(int*** srcCube, int faceNum, char direction) {
	//Create new cube and copy the current cube into it
	//Rotate the cube to get the next state
	int*** newCube = initCube();
	copyCube(newCube, srcCube);

	if (direction == 'C')
		rotateCubeClockwise(newCube, faceNum);
	else if (direction == 'A')
		rotateCubeCounterClockwise(newCube, faceNum);

	return newCube;
}

bool deepSearch(int*** cube, int depth) {
	//DFS
	if (isEqual(cube, finalCube)) {
		cout << "CUBE SOLVED" << endl;
		copyCube(initialCube, cube);
		cubeSolved = true;
		return true;
	}

	if (depth == 0)
		return false;

	for (int i = 0; i < 6; i++) {
		int*** tempCube = nextState(cube, i, 'C');

		if (deepSearch(tempCube, depth - 1)) {
			string s = "Face ";
			s += (i+'0');
			s += " turned Clockwise";
			moveList.push_back(s);
		}
		deallocateCube(tempCube);
		if (cubeSolved) return true;
	}


	for (int i = 0; i < 6; i++) {
		int*** tempCube = nextState(cube, i, 'A');

		if (deepSearch(tempCube, depth - 1)) {
			string s = "Face ";
			s += (i+'0');
			s += " turned Counter Clockwise";
			moveList.push_back(s);
		}
		deallocateCube(tempCube);
		if (cubeSolved) return true;
	}
	return false;
}

bool solveWithIterativeDeepening(int*** cube) {
	//as rubiks cube can be solved in 20 moves
	int max_depth = 20;
	for (int i = 1; i < max_depth; i++) {
		cout << "DEPTH " << i << endl;
		if (deepSearch(cube, i)) {
			//Print list of moves 
			printMoveList(-1);
			return true;
		}
		else {
			cout << "UNABLE TO SOLVE IN " << i << " MOVES" << endl;
		}
	}

	return false;
}

int*** aStarAlgorithm(int*** cube, int*** finalCube)
{
	vector<float> v;
	vector<int***> tempCubes;
	string direction[] = { "Clockwise", "Counter-Clockwise" };

	//store all possible moves in a vector
	for (int i = 0; i < 6; i++) {
		int*** tempCube = initCube();
		copyCube(tempCube, cube);
		rotateCubeClockwise(tempCube, i);

		tempCubes.push_back(tempCube);
		v.push_back(heuristic(tempCubes[i], finalCube));
	}

	for (int i = 6; i < 12; i++) {
		int*** tempCube = initCube();
		copyCube(tempCube, cube);
		rotateCubeCounterClockwise(tempCube, i-6);

		tempCubes.push_back(tempCube);
		v.push_back(heuristic(tempCubes[i], finalCube));
	}

	//find best move i.e least heuristic value
	int minElementIndex = min_element(v.begin(), v.end()) - v.begin();
	
	//make best move
	copyCube(cube, tempCubes[minElementIndex]);

	if (minElementIndex < 6) {
		string s = "Face ";
		s += minElementIndex + '0';
		s += " turned ";
		s += direction[minElementIndex / 6];
		moveList.push_back(s);
	}
	else {
		string s = "Face ";
		s += (minElementIndex - 6) + '0';
		s += " turned ";
		s += direction[minElementIndex / 6];
		moveList.push_back(s);
	}
		

	//free up all the space used
	for (int i = 0; i < 12; i++) {
		deallocateCube(tempCubes[i]);
	}

	return cube;
}

void solveWithAStar(int*** cube, int*** finalCube)
{
	for (int i = 0; i < 20; i++) {
		cube = aStarAlgorithm(cube, finalCube);

		if (isEqual(cube, finalCube)) break;
	}
		
	cout << "After A*:" << endl;
	printCube(cube);

	printMoveList();
}

int main()
{
	inputCubeFromFile("file.txt");

	cout << "Initial Cube:" << endl;
	printCube(initialCube);
	cout << "Final Cube:" << endl;
	printCube(finalCube);

	//solveWithIterativeDeepening(initialCube);
	solveWithAStar(initialCube, finalCube);

	deallocateCube(initialCube);
	deallocateCube(finalCube);
	return 0;
}

