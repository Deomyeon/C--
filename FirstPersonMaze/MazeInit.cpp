#include "Maze.h"

int checkRot(Maze& maze, Pos& pos);
Pos checkEntry(Maze& maze);

Maze::Maze(int width, int height, int minLength)
{
	this->width = width;
	this->height = height;
	this->maze = new char* [height];
	for (int i = 0; i < height; i++)
	{
		this->maze[i] = new char[width + 1];
		for (int j = 0; j < width; j++)
		{
			this->maze[i][j] = eState::None;
		}
	}
	this->solution = new char* [height];
	for (int i = 0; i < height; i++)
	{
		this->solution[i] = new char[width + 1];
		for (int j = 0; j < width; j++)
		{
			this->solution[i][j] = this->maze[i][j];
		}
	}
	this->minLength = minLength;
	this->length = 0;
	this->bSafe = true;
}

Maze::~Maze()
{
	for (int i = 0; i < this->height; i++)
	{
		delete[] this->maze[i];
	}
	delete[] this->maze;
	for (int i = 0; i < this->height; i++)
	{
		delete[] this->solution[i];
	}
	delete[] this->solution;
}

void Maze::setPoint()
{
	Pos* mainPos;
	Pos* subPos;
	int mainSize;
	int subSize;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, 1);
	for (int i = 0; i < 2; i++)
	{
		if (i)
		{
			mainPos = &this->endPos;
			subPos = &this->lastPos;
		}
		else
		{
			mainPos = &this->startPos;
			subPos = &this->beginPos;
		}
		int rand = dist(gen);
		if (rand)
		{
			mainSize = this->width;
			subSize = this->height;
			dist = uniform_int_distribution<>(1, mainSize - 2);
			int temp = dist(gen);
			mainPos->x = temp;
			subPos->x = temp;
			dist = uniform_int_distribution<>(0, 1);
			temp = dist(gen);
			mainPos->y = (subSize - 1) * temp;
			subPos->y = (subSize - 3) * temp + 1;
		}
		else
		{
			mainSize = this->height;
			subSize = this->width;
			dist = uniform_int_distribution<>(1, mainSize - 2);
			int temp = dist(gen);
			mainPos->y = temp;
			subPos->y = temp;
			dist = uniform_int_distribution<>(0, 1);
			temp = dist(gen);
			mainPos->x = (subSize - 1) * temp;
			subPos->x = (subSize - 3) * temp + 1;
		}
		if (this->startPos == this->endPos)
			i = 0;
	}
}

void Maze::setPoint(Pos startPos, Pos endPos)
{
	if (startPos == endPos)
		return;
	this->startPos = startPos;
	this->endPos = endPos;
	Pos* mainPos;
	Pos* subPos;
	for (int i = 0; i < 2; i++)
	{
		if (!i)
		{
			mainPos = &this->startPos;
			subPos = &this->beginPos;
		}
		else
		{
			mainPos = &this->endPos;
			subPos = &this->lastPos;
		}

		if (mainPos->x == 0 || mainPos->x == this->width - 1)
		{
			if (mainPos->x == 0)
				*subPos = Pos(1, mainPos->y);
			else if (mainPos->x == this->width - 1)
				*subPos = Pos(this->width - 2, mainPos->y);
		}
		else if (mainPos->y == 0 || mainPos->y == this->height - 1)
		{
			if (mainPos->y == 0)
				*subPos = Pos(mainPos->x, 1);
			else if (mainPos->y == this->height - 1)
				*subPos = Pos(mainPos->x, this->height - 2);
		}
	}
}

void Maze::initMaze()
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->maze[i][j] = eState::None;
		}
	}
	this->length = 0;

	stack<Pos, vector<Pos>> s;
	Pos pos;
	for (pos.y = 0; pos.y < this->height; pos.y++)
	{
		for (pos.x = 0; pos.x < this->width; pos.x += this->width - 1) {
			if (this->startPos == pos || this->endPos == pos)
				this->setMazePosition(pos, eState::Road);
			else
				this->setMazePosition(pos, eState::Wall);
		}
	}
	for (pos.x = 0; pos.x < this->width; pos.x++) {
		for (pos.y = 0; pos.y < this->height; pos.y += this->height - 1) {
			if (this->startPos == pos || this->endPos == pos)
				this->setMazePosition(pos, eState::Road);
			else
				this->setMazePosition(pos, eState::Wall);
		}
	}
	this->setMazePosition(this->beginPos, eState::Road);

	for (int i = 0; i < 2;)
	{
		if (!i)
			pos = this->beginPos;
		else
		{
			int rot = 0;
			for (rot = -1; !~rot;)
			{
				if (s.size() == 0)
					break;
				rot = checkRot(*this, s.top());
				if (!~rot)
					s.pop();
			}
			if (s.size() == 0)
				break;
			switch (rot)
			{
			case eRot::Left:
				pos = s.top().Left();
				break;
			case eRot::Right:
				pos = s.top().Right();
				break;
			case eRot::Up:
				pos = s.top().Up();
				break;
			case eRot::Down:
				pos = s.top().Down();
				break;
			}
		}
		for (int rot = 0; ~rot;)
		{
			this->setMazePosition(pos, eState::Road);
			s.push(pos);
			char ch = 0;
			Pos rotPos;
			for (int i = 0; i < 4; i++)
			{
				switch (i)
				{
				case eRot::Left:
					ch = this->getMazePosition(pos.Left());
					rotPos = pos.Left();
					break;
				case eRot::Right:
					ch = this->getMazePosition(pos.Right());
					rotPos = pos.Right();
					break;
				case eRot::Up:
					ch = this->getMazePosition(pos.Up());
					rotPos = pos.Up();
					break;
				case eRot::Down:
					ch = this->getMazePosition(pos.Down());
					rotPos = pos.Down();
					break;
				}
				switch (ch)
				{
				case eState::None:
					this->setMazePosition(rotPos, eState::Entry);
					break;
				case eState::Entry:
					this->setMazePosition(rotPos, eState::CantRoad);
					break;
				}
			}
			rot = checkRot(*this, pos);
			if (~rot)
			{
				Pos pivot;
				switch (rot)
				{
				case eRot::Left:
					pivot = pos.Left();
					break;
				case eRot::Right:
					pivot = pos.Right();
					break;
				case eRot::Up:
					pivot = pos.Up();
					break;
				case eRot::Down:
					pivot = pos.Down();
					break;
				}

				pos = pivot;
			}

		}
		i = 1;
	}

	char ch = 0;
	for (int y = 0; y < this->height; y++)
	{
		for (int x = 0; x < this->width; x++)
		{
			pos = Pos(x, y);
			ch = getMazePosition(pos);
			if (ch == eState::CantRoad || ch == eState::Wall)
				this->setMazePosition(pos, eState::None);
		}
	}

	this->SolveMaze();

}

int checkRot(Maze& maze, Pos& pos)
{
	char ch = 0;
	eRot rot;
	bool bRot[4]{ false };
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case eRot::Left:
			ch = maze.getMazePosition(pos.Left());
			rot = eRot::Left;
			break;
		case eRot::Right:
			ch = maze.getMazePosition(pos.Right());
			rot = eRot::Right;
			break;
		case eRot::Up:
			ch = maze.getMazePosition(pos.Up());
			rot = eRot::Up;
			break;
		case eRot::Down:
			ch = maze.getMazePosition(pos.Down());
			rot = eRot::Down;
			break;
		}

		if (ch == eState::None || ch == eState::Entry)
		{
			bRot[rot] = true;
		}
	}
	ch = 0;
	for (int i = 0; i < 4; i++)
	{
		if (bRot[i])
			ch++;
	}
	if (ch)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dist(0, 3);
		do
		{
			rot = (eRot)dist(gen);
		} while (!bRot[rot]);
		return rot;
	}
	else
		return -1;
}

Pos checkEntry(Maze& maze)
{
	for (int y = 0; y < maze.getMazeSize().y; y++)
	{
		for (int x = 0; x < maze.getMazeSize().x; x++)
		{
			if (maze.getMazePosition(Pos(x, y)) == eState::Entry)
				return Pos(x, y);
		}
	}
	return Pos(-1, -1);
}