// RubikCube.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "RubiksCube_Class.h"
using namespace std;

//face 1: white (front)
//face 2: yellow opposite to 1 (back)
//face 3: orange (top)
//face 4: red opposite to 3 (bottom)
//face 5: green (left)
//face 6 blue opposite to 5 (right)

RubiksCube_Class initialCube;
RubiksCube_Class finalCube;
bool cubeSolved = false;
vector<string> moveList;

void printMoveList(int x = 0) {
	if (x == -1) {//prints movelist in reverse
		cout << "==============Move List==============" << endl;
		for (int i = moveList.size() - 1; i >= 0; i--) {
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

void inputInitialAndFinalCubeFromFile(string fileName)
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
					file >> finalCube.cube[i][j][k];

		//initial cube is unsolved state
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					file >> initialCube.cube[i][j][k];
	}
}

bool deepSearch(RubiksCube_Class cube, int depth) {
	//DFS
	if (cube.isEqual(finalCube)) {
		cout << "Cube Solved!" << endl;
		initialCube.copyCube(cube);
		cubeSolved = true;
		return true;
	}

	if (depth == 0)
		return false;

	for (int i = 0; i < 6; i++) {
		RubiksCube_Class tempCube = cube.nextState(i, 'C');

		if (deepSearch(tempCube, depth - 1)) {
			string s = "Face ";
			s += (i + '0');
			s += " turned Clockwise";
			moveList.push_back(s);
		}
		//deallocateCube(tempCube);
		if (cubeSolved) return true;
	}


	for (int i = 0; i < 6; i++) {
		RubiksCube_Class tempCube = cube.nextState(i, 'A');

		if (deepSearch(tempCube, depth - 1)) {
			string s = "Face ";
			s += (i + '0');
			s += " turned Counter Clockwise";
			moveList.push_back(s);
		}
		//deallocateCube(tempCube);
		if (cubeSolved) return true;
	}
	return false;
}

bool solveWithIterativeDeepening(RubiksCube_Class cube) {
	cout << "Solving with Iterative Deepening..." << endl;
	moveList.clear();
	//as rubiks cube can be solved in 20 moves
	int max_depth = 20;
	for (int i = 1; i < max_depth; i++) {
		cout << "->Depth " << i << endl;
		if (deepSearch(cube, i)) {
			//Print list of moves 
			printMoveList(-1);
			cout << endl;
			return true;
		}
		else {
			cout << "Unable to solve in " << i << " moves" << endl;
		}
	}

	return false;
}

RubiksCube_Class aStarAlgorithm(RubiksCube_Class cube) {
	vector<float> v;
	vector<RubiksCube_Class> tempCubes;
	string direction[] = { "Clockwise", "Counter-Clockwise" };

	//store all possible moves in a vector
	for (int i = 0; i < 6; i++) {
		RubiksCube_Class* tempCube = new RubiksCube_Class();
		tempCube->copyCube(cube);
		tempCube->rotateCubeClockwise(i);

		tempCubes.push_back(*tempCube);
		v.push_back(tempCubes[i].heuristic(finalCube));
	}

	for (int i = 6; i < 12; i++) {
		RubiksCube_Class tempCube;
		tempCube.copyCube(cube);
		tempCube.rotateCubeCounterClockwise(i - 6);

		tempCubes.push_back(tempCube);
		v.push_back(tempCubes[i].heuristic(finalCube));
	}

	//find best move i.e least heuristic value
	int minElementIndex = min_element(v.begin(), v.end()) - v.begin();

	//make best move
	cube.copyCube(tempCubes[minElementIndex]);

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
	/*for (int i = 0; i < 12; i++) {
		deallocateCube(tempCubes[i]);
	}*/

	return cube;
}

void solveWithAStar(RubiksCube_Class cube)
{
	cout << "Solving with A* Algorithm..." << endl;
	moveList.clear();
	if (!cube.isEqual(finalCube)) {
		for (int i = 0; i < 20; i++) {
			cube = aStarAlgorithm(cube);

			if (cube.isEqual(finalCube)) break;
		}
	}

	cout << "A* Result:" << endl;
	cube.print();

	printMoveList();
}

int main()
{
	inputInitialAndFinalCubeFromFile("file.txt");

	cout << "Initial Cube:" << endl;
	initialCube.print();

	int option = 0;
	cout << "1.Iterative Deepening Search		2. A* search" << endl << endl;
	cout << "Enter an option = ";
	cin >> option;

	if (option == 1)
		solveWithIterativeDeepening(initialCube);
	else if (option == 2)
		solveWithAStar(initialCube);
	else
		cout << "Invalid choice!" << endl;

	return 0;
}

