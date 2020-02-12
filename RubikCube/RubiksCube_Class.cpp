#include "pch.h"
#include <iostream>
#include "RubiksCube_Class.h"


RubiksCube_Class::RubiksCube_Class() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				cube[i][j][k] = i;
			}
		}
	}
}

void RubiksCube_Class::rotateMatrixAntiClockwise(int mat[3][3]) {
	// Consider all squares one by one 
	for (int x = 0; x < 3 / 2; x++)
	{
		// Consider elements in group of 4 in  
		// current square 
		for (int y = x; y < 3 - x - 1; y++)
		{
			// store current cell in temp variable 
			int temp = mat[x][y];

			// move values from right to top 
			mat[x][y] = mat[y][3 - 1 - x];

			// move values from bottom to right 
			mat[y][3 - 1 - x] = mat[3 - 1 - x][3 - 1 - y];

			// move values from left to bottom 
			mat[3 - 1 - x][3 - 1 - y] = mat[3 - 1 - y][x];

			// assign temp to left 
			mat[3 - 1 - y][x] = temp;
		}
	}
}

void RubiksCube_Class::rotateMatrixClockwise(int mat[3][3]) {
	// Traverse each cycle 
	for (int i = 0; i < 3 / 2; i++) {
		for (int j = i; j < 3 - i - 1; j++) {

			// Swap elements of each cycle 
			// in clockwise direction 
			int temp = mat[i][j];
			mat[i][j] = mat[3 - 1 - j][i];
			mat[3 - 1 - j][i] = mat[3 - 1 - i][3 - 1 - j];
			mat[3 - 1 - i][3 - 1 - j] = mat[j][3 - 1 - i];
			mat[j][3 - 1 - i] = temp;
		}
	}
}

RubiksCube_Class::RubiksCube_Class(const RubiksCube_Class &rubiksCube) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				this->cube[i][j][k] = rubiksCube.cube[i][j][k];
			}
		}
	}
}

void RubiksCube_Class::copyCube(RubiksCube_Class rubiksCube) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				this->cube[i][j][k] = rubiksCube.cube[i][j][k];
			}
		}
	}
}

void RubiksCube_Class::print() {
	for (int i = 0; i < 6; i++)
	{
		std::cout << "Face " << i + 1 << ":" << std::endl;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				std::cout << cube[i][j][k] << "  ";
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

bool RubiksCube_Class::isEqual(RubiksCube_Class rubiksCube) {
	bool isEqual = true;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if (this->cube[i][j][k] != rubiksCube.cube[i][j][k]) {
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

void RubiksCube_Class::rotateCubeClockwise(int face) {
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


void RubiksCube_Class::rotateCubeCounterClockwise(int face) {
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

float RubiksCube_Class::heuristic(RubiksCube_Class rubiksCube)
{
	float manhattanDistance = 0;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{
				//if a cube tile is not at its supposed position
				if (this->cube[i][j][k] != rubiksCube.cube[i][j][k])
				{
					int face_original = this->cube[i][j][k];
					//find out on which face number the tile is
					manhattanDistance += abs(face_original - i);
				}
			}
	manhattanDistance = manhattanDistance / 8;
	return manhattanDistance;
}

RubiksCube_Class RubiksCube_Class::nextState(int faceNum, char direction) {
	//Create new cube and copy the current cube into it
	//Rotate the cube to get the next state
	RubiksCube_Class newCube;
	newCube.copyCube(*this);

	if (direction == 'C')
		newCube.rotateCubeClockwise(faceNum);
	else if (direction == 'A')
		newCube.rotateCubeCounterClockwise(faceNum);

	return newCube;
}


RubiksCube_Class::~RubiksCube_Class() {
}
