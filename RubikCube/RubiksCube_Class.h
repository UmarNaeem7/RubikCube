#pragma once
class RubiksCube_Class
{
private:
	void rotateMatrixClockwise(int mat[3][3]);
	void rotateMatrixAntiClockwise(int mat[3][3]);

public:
	int cube[6][3][3];

	RubiksCube_Class();
	RubiksCube_Class(const RubiksCube_Class &rubiksCube);
	~RubiksCube_Class();

	void copyCube(RubiksCube_Class rubiksCube);
	void print();
	bool isEqual(RubiksCube_Class rubiksCube);
	void rotateCubeClockwise(int face);
	void rotateCubeCounterClockwise(int face);
	float heuristic(RubiksCube_Class rubiksCube);
	RubiksCube_Class nextState(int faceNum, char direction);
};

