#pragma once
class RubiksCube_Class
{
private:
	void rotateMatrixClockwise(int mat[3][3]);
	void rotateMatrixAntiClockwise(int mat[3][3]);

public:
	int cube[6][3][3];

	RubiksCube_Class();
	RubiksCube_Class(const RubiksCube_Class &RubiksCube_Class);
	~RubiksCube_Class();

	void copyCube(RubiksCube_Class RubiksCube_Class);
	void print();
	bool isEqual(RubiksCube_Class RubiksCube_Class);
	void rotateCubeClockwise(int face);
	void rotateCubeCounterClockwise(int face);
	float heuristic(RubiksCube_Class RubiksCube_Class);
	RubiksCube_Class nextState(RubiksCube_Class srcCube, int faceNum, char direction);
};

