#pragma once

#include <random>
#include <stack>
#include <vector>


using namespace std;

enum eState
{
	None ='1',
	Road = '0',
	Wall = '4',
	Entry = '2',
	CantRoad = '3'
};

enum eRot
{
	Left = 0,
	Right = 1,
	Up = 2,
	Down = 3
};

struct Pos
{
	int x;
	int y;

	inline Pos(int x = 0, int y = 0) : x(x), y(y) {}
	inline Pos Left() const { return Pos(this->x - 1, this->y); }
	inline Pos Right() const { return Pos(this->x + 1, this->y); }
	inline Pos Up() const { return Pos(this->x, this->y - 1); }
	inline Pos Down() const { return Pos(this->x, this->y + 1); }
	bool operator ==(Pos pos) const { return (pos.x == this->x && pos.y == this->y); }
	Pos operator +(Pos pos) const { return Pos(this->x + pos.x, this->y + pos.y); }
};

struct Posf
{
	float x;
	float y;

	inline Posf(float x = 0, float y = 0) : x(x), y(y) {}
	inline Posf Left() const { return Posf(this->x - 1, this->y); }
	inline Posf Right() const { return Posf(this->x + 1, this->y); }
	inline Posf Up() const { return Posf(this->x, this->y - 1); }
	inline Posf Down() const { return Posf(this->x, this->y + 1); }
	bool operator ==(Posf pos) const { return (pos.x == this->x && pos.y == this->y); }
	Posf operator +(Posf pos) const { return Posf(this->x + pos.x, this->y + pos.y); }
};

class Maze
{
private:
	int minLength;

	char** maze;
	char** solution;
	bool bSafe;
	int length;

	int width;
	int height;

	Pos startPos;
	Pos endPos;
	Pos beginPos;
	Pos lastPos;

	Pos solved_startPos;
	Pos solved_endPos;

public:
	Maze(int width, int height, int minLength);
	~Maze();

	inline char getMazePosition(Pos pos) const { return this->maze[pos.y][pos.x]; }
	inline void setMazePosition(Pos pos, char ch) { this->maze[pos.y][pos.x] = ch; }
	inline char getSolutionPosition(Pos pos) const { return this->solution[pos.y][pos.x]; }
	inline void setSolutionPosition(Pos pos, char ch) { this->solution[pos.y][pos.x] = ch; }
	inline Pos getMazeSize() const { return Pos(this->width, this->height); }
	inline int getSolutionLength() const { return this->length; }
	inline bool isSafe() const { return bSafe; }
	inline void SafeMaze() { do { this->initMaze(); } while (!bSafe); }

	// Initialization Maze
	void setPoint();
	void setPoint(Pos startPos, Pos endPos);
	void initMaze();
	inline Pos getStartPos() const { return this->startPos; }
	inline Pos getEndPos() const { return this->endPos; }
	inline Pos getBeginPos() const { return this->beginPos; }
	inline Pos getLastPos() const { return this->lastPos; }

	// Solution Maze
	void SolveMaze();
	int Solve(int index);
	inline Pos getSolvedStartPos() const { return this->solved_startPos; }
	inline Pos getSolvedEndPos() const { return this->solved_endPos; }
};