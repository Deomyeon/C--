#include "Maze.h"

int checkRot(Maze& maze, Pos pos, int index);

void Maze::SolveMaze()
{
	int dir[4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		dir[i] = Solve(i);
	}
	int min = 0;
	if (dir[min] > dir[1]) min = 1;
	if (dir[min] > dir[2]) min = 2;
	if (dir[min] > dir[3]) min = 3;
	if (dir[min] == 0) return;
	else
	{
		this->length = dir[min];
		Solve(min);
	}
	if (this->length < this->minLength)
	{
		this->bSafe = false;
		return;
	}
	else
		this->bSafe = true;
}


int Maze::Solve(int index)
{
	int count = 0;

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->solution[i][j] = this->maze[i][j];
		}
	}

	stack<Pos, vector<Pos>> s;
	Pos pos = this->beginPos;
	this->solved_startPos = this->startPos;
	for (int i = 0; i < 2;)
	{

		if (!i)
			pos = this->beginPos;
		else
		{
			int rot = 0;
			for (rot = -1; !~rot;)
			{
				rot = checkRot(*this, s.top(), index);
				if (!~rot)
				{
					this->setSolutionPosition(s.top(), eState::CantRoad);
					if (s.size() == 1)
					{
						this->bSafe = false;
						return 0;
					}
					s.pop();
					count--;
				}
			}
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
		if (pos.x == 0 || pos.x == this->width - 1 || pos.y == 0 || pos.y == this->height - 1)
			break;

		for (int rot = 0; ~rot;)
		{
			this->setSolutionPosition(pos, eState::Entry);
			s.push(pos);
			count++;
			rot = checkRot(*this, pos, index);
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

				if (pivot.x == 0 || pivot.x == this->width - 1 || pivot.y == 0 || pivot.y == this->height - 1)
					break;

				pos = pivot;
			}

		}
		i = 1;
	}
	this->solved_endPos = pos;

	char ch = 0;
	for (int y = 0; y < this->height; y++)
	{
		for (int x = 0; x < this->width; x++)
		{
			pos = Pos(x, y);
			ch = getSolutionPosition(pos);
			if (ch == eState::CantRoad || ch == eState::Road)
				this->setSolutionPosition(pos, eState::None);
			if (ch == eState::Entry)
				this->setSolutionPosition(pos, eState::Road);
		}
	}
	this->setSolutionPosition(this->startPos, eState::Road);
	this->setSolutionPosition(this->endPos, eState::Road);

	return count;
}


int checkRot(Maze& maze, Pos pos, int index)
{
	Pos temp;
	char ch = 0;
	eRot rot;

	for (int i = 0; i < 4; i++)
	{
		switch ((i + index) % 4)
		{
		case eRot::Left:
			temp = pos.Left();
			rot = eRot::Left;
			break;
		case eRot::Right:
			temp = pos.Right();
			rot = eRot::Right;
			break;
		case eRot::Up:
			temp = pos.Up();
			rot = eRot::Up;
			break;
		case eRot::Down:
			temp = pos.Down();
			rot = eRot::Down;
			break;
		}
		if (!(temp == maze.getStartPos()))
		{
			ch = maze.getSolutionPosition(temp);
			if (ch == eState::Road)
				return rot;
		}
	}
	return -1;
}