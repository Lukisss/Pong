#include <windows.h>
#include <iostream>
#include <ctime>
#include <conio.h>
using namespace std;

const int width = 55;
const int height = 35;
const int oneCoord = 1;
const int zeroCoord = 0;
const int maxPoints = 5;

void gotoxy(short x, short y) {
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}


void displayWinner(string winner)
{
	system("CLS");
	gotoxy(10, 20);
	cout << " GAME OVER  !!!!!!! GAME WINNER: " << winner;
	gotoxy(20, 40);
}


void printScore(int humanPoints, int compPoints)
{
	const int sleepTime = 80;
	const int scorebordX = 4;
	const int scorebordY = 35;
	gotoxy(scorebordX, scorebordY);
	cout << "\n    Your score: " << humanPoints << "\tComp score: " << compPoints;
	Sleep(sleepTime);
}



bool noWinner(int humanPoints, int compPoints) {
	return (humanPoints < maxPoints && compPoints < maxPoints);
}



string checkWinner(int humanPoints, int compPoints)
{
	string winner;
	if (humanPoints == maxPoints)
		winner =  "YOU";
	else if (compPoints == maxPoints)
		winner = "COMPUTER";
	return winner;
}



class paddle
{
protected:
	int paddleStart, paddleEnd, paddleY;
	const int paddleLeft = 1;
	const int paddleRight = 0;
public:
	paddle() {
		paddleStart;
		paddleEnd;
		paddleY;
	}
	int getPaddleStart() {
		return paddleStart;
	}
	int getPaddleEnd() {
		return paddleEnd;
	}
	int getPaddleY() {
		return paddleY;
	}
};

class humanPaddle : public paddle
{
public:
	humanPaddle() {
		paddleStart = 10;
		paddleEnd = 40;
		paddleY = height - 2;
	}

	void humanPaddleLogic() {


		if (_kbhit())
		{
			switch (_getch())
			{
			case 'a':
				if (paddleStart - oneCoord != zeroCoord)
				{
					paddleStart = paddleStart - oneCoord;
					paddleEnd = paddleEnd - oneCoord;
					gotoxy(paddleStart, paddleY);
					for (int i = paddleStart; i < paddleEnd; i++)
					{
						cout << '=';
					}
					cout << ' ';
				}
				break;
			case 'd':
				if (paddleEnd + oneCoord * 2 != width)
				{
					paddleStart = paddleStart + oneCoord;
					paddleEnd = paddleEnd + oneCoord;
					gotoxy(paddleStart - oneCoord, paddleY);
					cout << ' ';
					for (int i = paddleStart; i < paddleEnd; i++)
					{
						cout << '=';
					}
				}
				break;
			}
		}


	}
};

class compPaddle : public paddle
{
public:
	compPaddle() {
		paddleStart = 10;
		paddleEnd = 40;
		paddleY = 2;
	}

	void compPaddleLogic() {
		if ((rand() % 2) == paddleLeft && paddleStart - oneCoord != zeroCoord)
		{
			paddleStart = paddleStart - oneCoord;
			paddleEnd = paddleEnd - oneCoord;
			gotoxy(paddleStart, paddleY);
			for (int i = paddleStart; i < paddleEnd; i++)
			{
				cout << '=';
			}
			cout << ' ';
		}
		else if ((rand() % 2) == paddleRight && paddleEnd - oneCoord * 2 != width)
		{
			paddleStart = paddleStart + oneCoord;
			paddleEnd = paddleEnd + oneCoord;
			gotoxy(paddleStart - oneCoord, paddleY);
			cout << ' ';
			for (int i = paddleStart; i < paddleEnd; i++)
			{
				cout << '=';
			}
		}
	}

};

class points
{
private:
	int humanPoints, compPoints;
	const int point = 1;
	const int humanPoint = 1;
	const int compPoint = -1;
public:
	points() {
		humanPoints = 0;
		compPoints = 0;
	}

	void setHumanPoints()
	{
		this->humanPoints = humanPoints + point;
	}

	void setCompPoints()
	{
		this->compPoints = compPoints + point;
	}


	void addPoint(int whoGetsPoint)
	{
		if (whoGetsPoint == humanPoint)
			setHumanPoints();
		else if (whoGetsPoint == compPoint)
			setCompPoints();
	}

	int getHumanPoints()
	{
		return humanPoints;
	}

	int getCompPoints()
	{
		return compPoints;
	}
};

class ball
{
private:
	const int halfBoardWidth = width / 2;
	const int halfBoardHeight = height / 2;
	const int leftWall = 1;
	const int rightWall = width - oneCoord * 2;
	const int ballRight = 0;
	const int ballLeft = 1;
	const int ballUp = 0;
	const int ballDown = 1;
	int ballX, ballY, ballVertical, ballHorizontal, point;



	void removeBall()
	{
		point = 0;
		gotoxy(ballX, ballY);
		cout << ' ';

	}

	void hitHumanPaddle(int humanY, int humanStart, int humanEnd)
	{
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
			point = -1;
		}
	}

	void hitCompPaddle(int compY, int compStart, int compEnd)
	{

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
			point = 1;
		}
	}

	void hitWall()
	{
		if (ballX == leftWall)
		{
			ballHorizontal = ballRight;
		}
		else if (ballX + oneCoord == rightWall) {
			ballHorizontal = ballLeft;
		}
	}

	void moveBall()
	{

		if (ballVertical == ballUp)
			ballY = ballY - oneCoord;
		else
			ballY = ballY + oneCoord;


		if (ballHorizontal == ballRight)
			ballX = ballX + oneCoord;
		else if (ballHorizontal == ballLeft) 
			ballX = ballX - oneCoord;


		gotoxy(ballX, ballY);
		cout << "0";
	}


public:


	ball()
	{ 
		ballX = halfBoardWidth;
		ballY = halfBoardHeight;
		ballVertical = rand() % 2;
		ballHorizontal = rand() % 2;
	}

	int ballLogic(humanPaddle humanPaddle, compPaddle compPaddle)
	{
		removeBall();
		hitHumanPaddle(humanPaddle.getPaddleY(), humanPaddle.getPaddleStart(), humanPaddle.getPaddleEnd());
		hitCompPaddle(compPaddle.getPaddleY(), compPaddle.getPaddleStart(), compPaddle.getPaddleEnd());
		hitWall();
		moveBall();
		return point;
	}

	int getY()
	{
		return ballY;
	}

	int getX()
	{
		return ballX;
	}

};

class initializeGame
{
private:
	const int spaceNumber = 32;
	const char spaceChar = ' ';

	void initializeConsole()
	{
		HANDLE outputHandle;
		outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		SMALL_RECT display = { 0, 0, width, height + 3 };
		SetConsoleWindowInfo(outputHandle, TRUE, &display);

		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.dwSize = 10;
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(outputHandle, &cursorInfo);

	}

	void drawBase()
	{

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


	}

	void drawStartingHumanPaddle(int humanY, int humanStart, int humanEnd) {

		gotoxy(humanStart, humanY);
		for (int i = humanStart; i < humanEnd; i++)
		{
			cout << '=';
		}
	}

	void drawStartingCompPaddle(int compY, int compStart, int compEnd) {
		gotoxy(compStart, compY);
		for (int i = compStart; i < compEnd; i++)
		{
			cout << '=';
		}
	}

	void drawStartingBall(int ballX, int ballY) {

		gotoxy(ballX, ballY);
		cout << "0";

	}

	void waitForStart()
	{
		gotoxy(2, 20);
		cout << "First to " << maxPoints <<" points wins.\n| Press spacebar to start the game........";

		while (_getch() != spaceNumber || _getch() != spaceChar);

		gotoxy(2, 20);
		cout << "                       \n|                                         ";
	}

public:
	void initialize(humanPaddle humanPaddle, compPaddle compPaddle, ball ball) {
		initializeConsole();

		drawBase();

		drawStartingHumanPaddle(humanPaddle.getPaddleY(), humanPaddle.getPaddleStart(), humanPaddle.getPaddleEnd());

		drawStartingCompPaddle(compPaddle.getPaddleY(), compPaddle.getPaddleStart(), compPaddle.getPaddleEnd());

		drawStartingBall(ball.getX(), ball.getY());

		waitForStart();

	}
};

int main() {

	srand(time(0));

	initializeGame game;
	ball ball;
	compPaddle compPaddle;
	humanPaddle humanPaddle;
	points points;
	game.initialize(humanPaddle,compPaddle,ball);

	while (noWinner(points.getHumanPoints(),points.getCompPoints()))
	{
		points.addPoint(ball.ballLogic(humanPaddle, compPaddle));

		compPaddle.compPaddleLogic();

		humanPaddle.humanPaddleLogic();

		printScore(points.getHumanPoints(), points.getCompPoints());
	}

	displayWinner(checkWinner(points.getHumanPoints(), points.getCompPoints()));

}



