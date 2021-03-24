#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>

using namespace std;

struct RRect
{
	int width;
	int height;
	int offsetX;
	int offsetY;
	RRect() {}
	RRect(int width, int height, int offsetX, int offsetY)
	{
		this->width = width;
		this->height = height;
		this->offsetX = offsetX;
		this->offsetY = offsetY;
	}
};

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void giveCard(int card[], bool b[])
{
	for (int i = 0; i < 10; i++)
	{
		bool s = false;
		while (!s)
		{
			int temp = rand() % 10 + 1;
			if (!b[temp])
			{
				for (int j = 0; j < 2; j++)
				{
					s = true;
					while (s)
					{
						int tempnum = rand() % 20;
						if (card[tempnum] == 0)
						{
							card[tempnum] = temp;
							b[temp] = true;
							s = false;
						}
					}
				}
				break;
			}
		}
	}
}

bool setCard(int number, const int card[], RRect rect)
{
	if (number > -1)
	{
		int i = number % 5;
		int j = number / 5;
		gotoxy(i * rect.width + rect.offsetX, j * rect.height + rect.offsetY);
		cout << "  ";
		gotoxy(i * rect.width + rect.offsetX, j * rect.height + rect.offsetY);
		cout << card[number];
		return true;
	}
	return false;
}

bool hideCard(int number, RRect rect)
{
	if (number > -1)
	{
		int i = number % 5;
		int j = number / 5;
		gotoxy(i * rect.width + rect.offsetX, j * rect.height + rect.offsetY);
		cout << "  ";
		gotoxy(i * rect.width + rect.offsetX, j * rect.height + rect.offsetY);
		cout << "■";
		return true;
	}
	return false;
}

int keyInput()
{
	if (_kbhit())
	{
		return _getch();
	}
}

int ReadKey(char keys[], int input)
{
	for (int i = 0; i < 20; i++)
	{
		if (keys[i] == input)
		{
			return i;
		}
	}
	return -1;
}

int main()
{

	int card[20] = { 0 };
	bool b[11] = { false }; // false 는 안 쓴 수 true는 이미 쓴 수
	char keys[20] =
	{
		'1', '2', '3', '4', '5',
		'q', 'w', 'e', 'r', 't',
		'a', 's', 'd', 'f', 'g',
		'z', 'x', 'c', 'v', 'b'
	};
	bool a = true;
	int key = 0, input = 0, count = 0;
	int counts[2] = { -1 };
	RRect rect = RRect(10, 2, 20, 6);
	srand((unsigned)time(NULL));
	giveCard(card, b);
	for (int i = 0; i < 20; i++)
	{
		setCard(i, card, rect);
		hideCard(i, rect);
	}
	while (a)
	{
		input = keyInput();
		key = ReadKey(keys, input);
		if (setCard(key, card, rect))
		{
			(count == 0) ? counts[0] = key : counts[1] = key;
			count++;
		}
		if (count == 2)
		{
			Sleep(1000);
			if (counts[0] != counts[1])
			{
				for (int i = 0; i < 2; i++)
				{
					hideCard(counts[i], rect);
				}
			}
			for (int i = 0; i < 2; i++)
			{
				counts[i] = -1;
			}
			count = 0;
		}
	}
}