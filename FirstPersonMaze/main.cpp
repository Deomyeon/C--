#include <iostream>
#include <chrono>

#include <Windows.h>
#include <vector>
#include <algorithm>
#include <WinUser.h>

using namespace std;

#include "Maze.h"
#include "MazeInit.cpp"
#include "MazeSolve.cpp"

#define PI 3.14159265358979

void gameScene(Maze& M);

int nScreenWidth = 480;
int nScreenHeight = 270;

Posf PlayerPos;
Posf PlayerAngle;

float fPlayerSpeed = 1.0f;

int nFrame = 60;

float fFOV = PI / 2.0f;
float fDepth = 16.0f;

enum eGamePoint
{
	StartPoint = '#',
	EndPoint = '&'
};

int main()
{
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	
	nScreenWidth = width / 4;
	nScreenHeight = height / 4;
	
	cout << endl << "시야각 : ";
	int iFovRadian = 0;
	cin >> iFovRadian;

	fFOV = PI / (180 / iFovRadian);

	int mazeWidth;
	int mazeHeight;
	int mazeLength;
	cout << endl << "미로의 가로 길이 : ";
	cin >> mazeWidth;
	cout << endl << "미로의 세로 길이 : ";
	cin >> mazeHeight;
	cout << endl << "미로의 최단 거리 : ";
	cin >> mazeLength;
	Maze M(mazeWidth, mazeHeight, mazeLength);

	gameScene(M);


	SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);
	system("cls");
}

void gameScene(Maze& M)
{
	WORD* screen = new WORD[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 4;
	cfi.dwFontSize.Y = 4;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

	SetConsoleScreenBufferSize(hConsole, { (SHORT)nScreenWidth, (SHORT)nScreenHeight });

	SetConsoleActiveScreenBuffer(hConsole);

	COORD fontSize = GetConsoleFontSize(hConsole, 0);
	SetWindowPos(GetConsoleWindow(), (HWND)-1, 0, 0, nScreenWidth * fontSize.X, nScreenHeight * fontSize.Y, SWP_SHOWWINDOW);
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, 0);

	SetConsoleTitle(L"흑엽룡");

	DWORD dwBytesWritten = 0;

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	WORD LOADING[6][44] = {
		{255,   0,   0,   0,   0, 255, 255,   0,   0,   0, 255,   0,   0,   0, 255, 255, 255,   0,   0, 255, 255, 255,   0, 255,   0,   0, 255,   0,   0, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
		{255,   0,   0,   0, 255,   0,   0, 255,   0, 255, 255, 255,   0,   0, 255,   0,   0, 255,   0,   0, 255,   0,   0, 255, 255,   0, 255,   0, 255,   0,   0, 255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
		{255,   0,   0,   0, 255,   0,   0, 255,   0, 255,   0, 255,   0,   0, 255,   0,   0, 255,   0,   0, 255,   0,   0, 255, 255,   0, 255,   0, 255,   0,   0,   0,   0,   0, 255, 255,   0,   0, 255, 255,   0,   0, 255, 255},
		{255,   0,   0,   0, 255,   0,   0, 255,   0, 255, 255, 255,   0,   0, 255,   0,   0, 255,   0,   0, 255,   0,   0, 255,   0, 255, 255,   0, 255,   0, 255, 255,   0,   0, 255, 255,   0,   0, 255, 255,   0,   0, 255, 255},
		{255,   0,   0,   0, 255,   0,   0, 255,   0, 255,   0, 255,   0,   0, 255,   0,   0, 255,   0,   0, 255,   0,   0, 255,   0, 255, 255,   0, 255,   0,   0, 255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
		{255, 255, 255,   0,   0, 255, 255,   0,   0, 255,   0, 255,   0,   0, 255, 255, 255,   0,   0, 255, 255, 255,   0, 255,   0,   0, 255,   0,   0, 255, 255,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}
	};
	WORD CLEAR[6][22] = {
		{   0, 255, 255,   0,   0, 255,   0,   0,   0,   0, 255, 255,   0,   0,   0, 255,   0,   0,   0, 255, 255,   0 },
		{ 255,   0,   0, 255,   0, 255,   0,   0,   0, 255,   0,   0, 255,   0, 255, 255, 255,   0, 255,   0,   0, 255 },
		{ 255,   0,   0,   0,   0, 255,   0,   0,   0, 255, 255, 255, 255,   0, 255,   0, 255,   0, 255,   0,   0, 255 },
		{ 255,   0,   0,   0,   0, 255,   0,   0,   0, 255,   0,   0,   0,   0, 255, 255, 255,   0, 255, 255, 255,   0 },
		{ 255,   0,   0, 255,   0, 255,   0,   0,   0, 255,   0,   0, 255,   0, 255,   0, 255,   0, 255,   0,   0, 255 },
		{   0, 255, 255,   0,   0, 255, 255, 255,   0,   0, 255, 255,   0,   0, 255,   0, 255,   0, 255,   0,   0, 255 }
	};

	WORD FAIL[6][18] = {
		{ 255, 255, 255,   0,   0, 255,   0,   0,   0, 255, 255, 255,   0, 255,   0,   0 },
		{ 255,   0,   0,   0, 255, 255, 255,   0,   0,   0, 255,   0,   0, 255,   0,   0 },
		{ 255,   0,   0,   0, 255,   0, 255,   0,   0,   0, 255,   0,   0, 255,   0,   0 },
		{ 255, 255, 255,   0, 255, 255, 255,   0,   0,   0, 255,   0,   0, 255,   0,   0 },
		{ 255,   0,   0,   0, 255,   0, 255,   0,   0,   0, 255,   0,   0, 255,   0,   0 },
		{ 255,   0,   0,   0, 255,   0, 255,   0,   0, 255, 255, 255,   0, 255, 255, 255 }
	};
	for (int i = 0; i < 6; i++)
		WriteConsoleOutputAttribute(hConsole, LOADING[i], 44, { (SHORT)width / 8 - 22, (SHORT)i + (SHORT)height / 8 - 3 }, &dwBytesWritten);

	M.setPoint();
	M.initMaze();
	if (!M.isSafe())
		M.SafeMaze();

	M.setMazePosition(M.getStartPos(), eGamePoint::StartPoint);
	M.setMazePosition(M.getEndPos(), eGamePoint::EndPoint);

	PlayerPos.x = M.getBeginPos().x;
	PlayerPos.y = M.getBeginPos().y;

	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	POINT mousePoint;
	COORD mousePosition;


	bool bGameClear = false;
	bool bGiveUp = false;

	while (!bGameClear && !bGiveUp)
	{
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		COORD currentMousePosition;
		GetCursorPos(&mousePoint);
		mousePosition.X = mousePoint.x;
		mousePosition.Y = mousePoint.y;
		currentMousePosition = { mousePosition.X - (SHORT)width / 2, mousePosition.Y - (SHORT)height / 2 };
		SetCursorPos(width / 2, height / 2);

		PlayerAngle.x -= currentMousePosition.Y * fElapsedTime * 2400 / nScreenHeight;
		PlayerAngle.y += currentMousePosition.X * fElapsedTime * 24 / nScreenHeight;
		if (GetAsyncKeyState((unsigned short)'Q') & 0x8000)
		{
			bGiveUp = true;
		}
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
		{
			PlayerPos.x += sinf(PlayerAngle.y) * fPlayerSpeed * fElapsedTime;
			PlayerPos.y += cosf(PlayerAngle.y) * fPlayerSpeed * fElapsedTime;
			if (M.getMazePosition(Pos((int)PlayerPos.x, (int)PlayerPos.y)) == eState::None || M.getMazePosition(Pos((int)PlayerPos.x, (int)PlayerPos.y)) == eGamePoint::StartPoint)
			{
				PlayerPos.x -= sinf(PlayerAngle.y) * fPlayerSpeed * fElapsedTime;
				PlayerPos.y -= cosf(PlayerAngle.y) * fPlayerSpeed * fElapsedTime;
			}
		}
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
		{
			PlayerPos.x -= sinf(PlayerAngle.y) * fPlayerSpeed * fElapsedTime;
			PlayerPos.y -= cosf(PlayerAngle.y) * fPlayerSpeed * fElapsedTime;
			if (M.getMazePosition(Pos((int)PlayerPos.x, (int)PlayerPos.y)) == eState::None || M.getMazePosition(Pos((int)PlayerPos.x, (int)PlayerPos.y)) == eGamePoint::StartPoint)
			{
				PlayerPos.x += sinf(PlayerAngle.y) * fPlayerSpeed * fElapsedTime;
				PlayerPos.y += cosf(PlayerAngle.y) * fPlayerSpeed * fElapsedTime;
			}
		}
		if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
		{
			PlayerPos.x += sinf(PlayerAngle.y - PI / 2) * fPlayerSpeed * fElapsedTime;
			PlayerPos.y += cosf(PlayerAngle.y - PI / 2) * fPlayerSpeed * fElapsedTime;
			if (M.getMazePosition(Pos((int)PlayerPos.x, (int)PlayerPos.y)) == eState::None || M.getMazePosition(Pos((int)PlayerPos.x, (int)PlayerPos.y)) == eGamePoint::StartPoint)
			{
				PlayerPos.x -= sinf(PlayerAngle.y - PI / 2) * fPlayerSpeed * fElapsedTime;
				PlayerPos.y -= cosf(PlayerAngle.y - PI / 2) * fPlayerSpeed * fElapsedTime;
			}
		}
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
		{
			PlayerPos.x += sinf(PlayerAngle.y + PI / 2) * fPlayerSpeed * fElapsedTime;
			PlayerPos.y += cosf(PlayerAngle.y + PI / 2) * fPlayerSpeed * fElapsedTime;
			if (M.getMazePosition(Pos((int)PlayerPos.x, (int)PlayerPos.y)) == eState::None || M.getMazePosition(Pos((int)PlayerPos.x, (int)PlayerPos.y)) == eGamePoint::StartPoint)
			{
				PlayerPos.x -= sinf(PlayerAngle.y + PI / 2) * fPlayerSpeed * fElapsedTime;
				PlayerPos.y -= cosf(PlayerAngle.y + PI / 2) * fPlayerSpeed * fElapsedTime;
			}
		}

		if (M.getMazePosition(Pos((int)PlayerPos.x, (int)PlayerPos.y)) == eGamePoint::EndPoint)
			bGameClear = true;

		for (int x = 0; x < nScreenWidth; x++)
		{
			float fRayAngle = (PlayerAngle.y - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;

			float fDistanceToWall = 0;
			bool bHitWall = false;
			bool bStartPoint = false;
			bool bEndPoint = false;

			float fEyeX = sinf(fRayAngle);
			float fEyeY = cosf(fRayAngle);

			while (!bHitWall && fDistanceToWall < fDepth)
			{

				fDistanceToWall += 0.01f;

				int nTestX = (int)(PlayerPos.x + fEyeX * fDistanceToWall);
				int nTestY = (int)(PlayerPos.y + fEyeY * fDistanceToWall);

				if (nTestX < 0 || nTestX >= M.getMazeSize().x || nTestY < 0 || nTestY >= M.getMazeSize().y)
				{
					bHitWall = true;
					fDistanceToWall = fDepth;
				}
				else
				{
					if (M.getMazePosition(Pos((int)nTestX, (int)nTestY)) == eState::None)
					{
						bHitWall = true;
					}
					else if (M.getMazePosition(Pos((int)nTestX, (int)nTestY)) == eGamePoint::StartPoint)
					{
						bHitWall = true;
						bStartPoint = true;
					}
					else if (M.getMazePosition(Pos((int)nTestX, (int)nTestY)) == eGamePoint::EndPoint)
					{
						bHitWall = true;
						bEndPoint = true;
					}
				}
			}

			int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall) * 0.5;
			int nFloor = nScreenHeight - nCeiling; 
				nCeiling += PlayerAngle.x;
				nFloor += PlayerAngle.x;

			short nShade = 1;

			for (int y = 0; y < nScreenHeight; y++)
			{
				if (y < nCeiling)
				{
					float b = - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
					if (b < 0.1) nShade = 159;
					else if (b < 0.25) nShade = 159;
					else if (b < 0.5) nShade = 31;
					else if (b < 0.75) nShade = 31;
					else nShade = 31;
					screen[y * nScreenWidth + x] = nShade;
				}
				else if (y > nCeiling && y < nFloor)
				{
					if (fDistanceToWall <= fDepth / 14.0f) nShade = 255;
					else if (fDistanceToWall < fDepth / 11.0f) nShade = 127;
					else if (fDistanceToWall < fDepth / 9.0f) nShade = 136;
					else if (fDistanceToWall < fDepth / 7.0f) nShade = 1;
					else nShade = 1;
					screen[y * nScreenWidth + x] = nShade;
					if (bStartPoint)
						screen[y * nScreenWidth + x] = 221;
					if (bEndPoint)
						screen[y * nScreenWidth + x] = 170;
				}
				else if (y == nCeiling || y == nFloor)
					screen[y * nScreenWidth + x] = 67;
				else
				{
					float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
					if (b < 0.25) nShade = 31;
					else if (b < 0.5) nShade = 31;
					else if (b < 0.75) nShade = 31;
					else if (b < 0.9) nShade = 159;
					else nShade = 159;
					screen[y * nScreenWidth + x] = nShade;
				}
			}
		}


		Pos p;
		Pos miniMap(nScreenHeight / 10, nScreenHeight / 10);
		for (int y = 0; y < miniMap.y * 3; y++)
		{
			for (int x = 0; x < miniMap.x * 3; x++)
			{
				p.x = x / 3 + (int)PlayerPos.x - miniMap.x / 2;
				p.y = y / 3 + (int)PlayerPos.y - miniMap.y / 2;
				if (p.x >= 0 && p.y >= 0 && p.x <= M.getMazeSize().x - 1 && p.y <= M.getMazeSize().y - 1)
					if (p.x == (int)PlayerPos.x && p.y == (int)PlayerPos.y)
						screen[y * nScreenWidth + nScreenWidth - 1 - x] = 187;
					else
						screen[y * nScreenWidth + nScreenWidth - 1 - x] = M.getMazePosition(p) == eState::None ? 238 : 0;
				else
					screen[y * nScreenWidth + nScreenWidth - 1 - x] = 0;
			}
		}

		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		WriteConsoleOutputAttribute(hConsole, screen, nScreenWidth* nScreenHeight, { 0, 0 }, &dwBytesWritten);
	}
	FillConsoleOutputAttribute(hConsole, 0, nScreenWidth* nScreenHeight, { 0, 0 }, &dwBytesWritten);

	if (bGameClear)
	{
		for (int i = 0; i < 6; i++)
			WriteConsoleOutputAttribute(hConsole, CLEAR[i], 22, { (SHORT)width / 8 - 11, (SHORT)i + (SHORT)height / 8 - 3 }, &dwBytesWritten);
	}
	else if (bGiveUp)
	{
		for (int i = 0; i < 6; i++)
			WriteConsoleOutputAttribute(hConsole, FAIL[i], 18, { (SHORT)width / 8 - 9, (SHORT)i + (SHORT)height / 8 - 3 }, &dwBytesWritten);
	}
	Sleep(5000);

}