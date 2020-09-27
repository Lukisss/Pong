#include <windows.h>
#include <iostream>
#include <ctime>
#include <conio.h>
using namespace std;

const int sleepTime = 80;
const int width = 55;
const int height = 35;
const int ballRight = 0;
const int ballLeft = 1;
const int ballUp = 0;
const int ballDown = 1;
const int oneCoord = 1;
const int humanY = 33;
const int compY = 2;
const int scorebordX = 4;
const int scorebordY = 35;
const int leftWall = 1;

void gotoxy(short x, short y) {
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

int main() {
	HANDLE outputHandle;
	outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT display = { 0, 0, width, height + 3 };
	SetConsoleWindowInfo(outputHandle, TRUE, &display);

	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 10;
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(outputHandle, &cursorInfo);

	srand(time(0));

	bool gameOver = false;
	int test, humanPoints = 0, compPoints = 0;
	//int humanStart = width / 2 - 4;
	//int humanEnd = width / 2 + 3;
	//int compStart = width / 2 - 4;
	//int compEnd = width / 2 + 3;
	int humanStart = 10;
	int humanEnd = 40;
	int compStart = 10;
	int compEnd = 40;
	int ballVertical = rand() % 2;
	int ballHorizontal = rand() % 2;
	int ballX = width / 2;
	int ballY = height / 2;
	// 0 - up, right
	// 1 - down, left
//draw
	for (int i = 0; i < width - 1; ++i)
		cout << '-';

	for (int i = 0; i < height - 1; ++i)
	{
		cout << "\n|";

		for (int i = 0; i < width - 3; ++i)
			cout << ' ';

		cout << "|";
	}

	cout << '\n';
	for (int i = 0; i < width - 1; ++i)
		cout << '-';
	cout << "\n    Your score: 0\tComp score: 0\n";

	for (int i = 0; i < width - 1; ++i)
		cout << '-';

	gotoxy(compStart, 2);
	for (int i = compStart; i < compEnd; i++)
	{
		cout << '=';
	}
	for (int i = 1; i < 30; i++)

		gotoxy(humanStart, humanY);
	for (int i = humanStart; i < humanEnd; i++)
	{
		cout << '=';
	}

	gotoxy(ballX, ballY);
	cout << "0";

	gotoxy(2, 20);
	cout << "First to 5 points wins.\n| Press spacebar to start the game........";

	//end draw
	while (_getch() != 32 || _getch() != ' ');

	gotoxy(2, 20);
	cout << "                       \n|                                         ";
	while (humanPoints < 5 && compPoints < 5)
	{
		//ball

		gotoxy(ballX, ballY);
		cout << ' ';
		// check if it hit paddles or went through
		if (ballY + oneCoord == humanY && ballX >= humanStart && ballX <= humanEnd)
		{
			ballVertical = ballUp;
		}
		else if (ballY + oneCoord == humanY && (ballX < humanStart || ballX > humanEnd))
		{
			ballX = width / 2;
			ballY = height / 2;
			ballVertical = rand() % 2;
			ballHorizontal = rand() % 2;
			compPoints++;
		}

		if (ballY - oneCoord == compY && ballX >= compStart && ballX <= compEnd)
		{
			ballVertical = ballDown;
		}
		else if (ballY - oneCoord == compY && (ballX < compStart || ballX > compEnd))
		{
			ballX = width / 2;
			ballY = height / 2;
			ballVertical = rand() % 2;
			ballHorizontal = rand() % 2;
			humanPoints++;
		}



		if (ballX == leftWall)
		{
			ballHorizontal = ballRight;
		}
		else if (ballX + oneCoord == width - oneCoord * 2) {
			ballHorizontal = ballLeft;
		}

		if (ballVertical == ballUp)
			ballY = ballY - oneCoord;
		else
			ballY = ballY + oneCoord;

		// if ball hits paddle, swap ballvertical, if width - 1 or 1 then game over, points on which

		if (ballHorizontal == ballRight)
			ballX = ballX + oneCoord;
		else if (ballHorizontal == ballLeft) ballX = ballX - oneCoord;


		gotoxy(ballX, ballY);
		cout << "0";
		//end ball draw

		//comp draw
		if ((rand() % 2) == oneCoord && compStart - oneCoord != 0)
		{
			compStart--;
			compEnd--;
			gotoxy(compStart, compY);
			for (int i = compStart; i < compEnd; i++)
			{
				cout << '=';
			}
			cout << ' ';
		}
		else if ((rand() % 2) == 0 && compEnd - oneCoord * 2 != width)
		{
			compStart++;
			compEnd++;
			gotoxy(compStart - 1, compY);
			cout << ' ';
			for (int i = compStart; i < compEnd; i++)
			{
				cout << '=';
			}
		}

		//end comp draw
		//human draw
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'a':
				if (humanStart - oneCoord != 0)
				{
					humanStart = humanStart - oneCoord;
					humanEnd = humanEnd - oneCoord;
					gotoxy(humanStart, humanY);
					for (int i = humanStart; i < humanEnd; i++)
					{
						cout << '=';
					}
					cout << ' ';
				}
				break;
			case 'd':
				if (humanEnd + oneCoord * 2 != width)
				{
					humanStart = humanStart + oneCoord;
					humanEnd = humanEnd + oneCoord;
					gotoxy(humanStart - 1, humanY);
					cout << ' ';
					for (int i = humanStart; i < humanEnd; i++)
					{
						cout << '=';
					}
				}
				break;
			}
		}
		//end human draw
		//print points
		gotoxy(scorebordX, scorebordY);
		cout << "\n    Your score: " << humanPoints << "\tComp score: " << compPoints;
		Sleep(sleepTime);
	}

	system("CLS");
	gotoxy(10, 20);
	cout << " GAME OVER  !!!!!!! GAME WINNER: ";
	if (humanPoints == 5)
		cout << "YOU";
	else
		cout << "COMPUTER";
	gotoxy(20, 40);
}



