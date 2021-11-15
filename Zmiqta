#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;
const int width = 20;
const int height = 20;
int x, y, FX, FY, score, a;
int tailX[100], tailY[100];
int nTail;
bool printed = 0;
char c;
enum eDirection { STOP = 0, UP, LEFT, RIGHT, DOWN };
eDirection dir;
bool gameOver;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	FX = rand() % width;
	FY = rand() % height;
}
void Nigger()
{
	if ((FX <= 0 || FX >= width - 1) || (FY <= 0 || FY >= height - 1))
	{
		FX = rand() % width;
		FY = rand() % height;
	}
}
void Draw()
{
	system("cls");
	cout << "WASD to move, X to end game!\n";
	cout << "Press P to pause!\n";
	for (int i = 0; i < width; i++)
	{
		cout << "0 ";
	}
	cout << endl;

	for (int i = 0; i < height - 2; i++)
	{
		cout << "0 ";
		for (int j = 0; j < width - 2; j++)
		{

			if (i + 1 == y && j + 1 == x)
			{
				cout << "O ";
			}
			else if (i + 1 == FY && j + 1 == FX)
			{
				cout << "# ";
			}
			else
			{
				bool printed = 0;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j + 1 && tailY[k] == i + 1)
					{
						cout << "o ";
						printed = true;
					}
				}
				if (!printed)
					cout << "  ";

			}

		}
		cout << "0 " << endl;
	}

	for (int i = 0; i < width; i++)
	{
		cout << "0 ";
	}

	cout << endl << "Your score is: " << score << endl;
	cout << "Fruit X: " << FX << endl << "Fruit Y: " << FY << endl;

}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'd': if (dir != LEFT || dir == STOP)
			dir = RIGHT;
			break;
		case 'a': if (dir != RIGHT || dir == STOP)
			dir = LEFT;
			break;
		case 's': if (dir != UP || dir == STOP)
			dir = DOWN;
			break;
		case 'w': if (dir != DOWN || dir == STOP)
			dir = UP;
			break;
		case 'p': _getch();
			

			break;
		case 'x': gameOver = true;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case UP: y--;
		break;
	case DOWN: y++;
		break;
	case RIGHT: x++;
		break;
	case LEFT: x--;
		break;
	
	}
	
	if (x == 0)
	{
		x = width - 2;
	}
	else if (x == width - 1)
	{
		x = 1;
	}
	else if (y == 0)
	{
		y = height - 2;
	}
	else if (y == height - 1)
	{
		y = 1;
	}
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == FX && y == FY)
	{
		FX = rand() % width;
		FY = rand() % height;
		score += 10;
		nTail += 1;
	}
}
void StartScreen()
{

	if (_kbhit)
	{
		c = _getch();
		system("cls");
		switch (c)
		{
		case 'w':
			cout << "\t---------------" << endl << "\t--Lobo i Andi--" << endl << "\t-Big time zmiq-" << endl << "\t---------------" << endl << "\n\n\t>START<" << "\n\tEXIT";
			a = 0;
			break;
		case 's':
			cout << "\t---------------" << endl << "\t--Lobo i Andi--" << endl << "\t-Big time zmiq-" << endl << "\t---------------" << endl << "\n\n\tSTART" << "\n\t>EXIT<";
			a = 1;
			break;
		case '\r':
			if (a == 0)
			{
				a = 2;
			}
			if (a == 1)
			{
				a = 2;
				gameOver = true;
			}
		}
	}
}
void LoseScreen()
{
	system("CLS");
	cout << "Better luck next time, buddy Ї\\_( :) )_/Ї\n";
	cout << "Press Space to Restart! \n" << "Press X to exit! \n";
}
int main()
{
	cout << "\t---------------" << endl << "\t--Lobo i Andi--" << endl << "\t-Big time zmiq-" << endl << "\t---------------" << endl << "\n\n\t>START<" << "\n\tEXIT";
	Setup();
	while (a != 2)
	{
		StartScreen();
	}
	do
	{
		Draw();
		Input();
		Logic();
		Nigger();
		Sleep(20);
		if (gameOver)
		{
			system("cls");
			LoseScreen();
			if (_getch() == ' ')
			{
				gameOver = false;

				nTail = 0;
				score = 0;
				Setup();
			}
		}
	} while (!gameOver);

	if (gameOver == true)
	{
		LoseScreen();
	}

	return 0;
}
