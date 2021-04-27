#include <iostream>
#include "Maze.h"
#include <fstream>
int main()
{
	Maze M(1000, 1000, 50000); // 생성에 시간이 소비될 수 있습니다.
	M.setPoint();
	M.initMaze();
	if (!M.isSafe())
		M.SafeMaze();

	ofstream of;
	ofstream aof;
	of.open("maze.txt");
	aof.open("answer.txt");

	for (int y = 0; y < M.getMazeSize().y; y++)
	{
		for (int x = 0; x < M.getMazeSize().x; x++)
		{
			of << (M.getMazePosition(Pos(x, y)));
		}

		for (int x = 0; x < M.getMazeSize().x; x++)
		{
			aof << (M.getSolutionPosition(Pos(x, y)));
		}
		of << endl;
		aof << endl;
	}
	of.close();
	aof.close();
	cout << M.getSolutionLength() << endl;
	cout << " 시작위치 : " << M.getSolvedStartPos().x << ", " << M.getSolvedStartPos().y << " 도착위치 : " << M.getSolvedEndPos().x << ", " << M.getSolvedEndPos().y;


	return 0;
}