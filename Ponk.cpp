
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver, printed, ballDir[2];
int platform[2][3], score[2], platformX[2], ball[2];
int a;
const int width = 25;
const int height = 12;
enum eDirection { STOP = 0, UP, DOWN };
eDirection dir[2];
void LoginScreen() {

    switch (_getch())
    {
    case 'w': system("cls"); cout << "--------------\n-Made by Lupi-\n--------------\n" << "<<Start Game>>\n  Exit Game  "; a = 0; break;
    case 's': system("cls"); cout << "--------------\n-Made by Lupi-\n--------------\n" << " Start Game \n<<Exit Game>>" ; a = 1; break;
    case '\r': if (a == 0) { a = 2; }
             if (a == 1)
             {
                 a = 2;
                 gameOver = true;
             }
    }
}
void EndScreen() {
    system("cls");
    score[0] = 0;
    score[1] = 0;
    cout << "Game Over! ";
    if (score[0] >= 15) { cout << "\nPlayer 1 Won! "; }
    else if (score[1] >= 15) { cout << "\nPlayer 2 Won! "; }
    cout << "\nPress Space to play again! \nPress any other key to exit!\n";
    while (!_kbhit()) { if (_kbhit()) { break; } }
    if (_kbhit())
    {
        switch (_getch())
        {
        case ' ': gameOver = false;
        }
    }
}
void Setup() {
    score[0], score[1] = 0;
    platform[0][1] = height / 2;
    platform[1][1] = height / 2;
    platformX[0] = 0;
    platformX[1] = width;
    dir[0] = STOP;
    dir[1] = STOP;
    ball[0] = width / 2;
    ball[1] = height / 2;
    ballDir[0] = rand() % 2;
    ballDir[1] = rand() % 2;

}
void Draw() {
    system("cls");
    cout << "---------------------Ponk game--------------------- \n";
    for (int i = 0; i < width + 1; i++) //First Line
    {
        cout << "# ";
    }
    cout << endl;
    for (int i = 0; i < height; i++) //Rows
    {
        for (int j = 0; j < width + 2; j++)//Spaces
        {
            for (int k = 0; k < 2; k++)
            {
                for (int u = 0; u < 3; u++)
                {
                    if (platform[k][u] == i && platformX[k] == j) // platforms
                    {
                        cout << "| ";
                        printed = true;
                    }
                }
            }
            if (ball[0] == j && ball[1] == i && !printed)
            {
                cout << "O ";
                printed = true;
            }

            if (j == width / 2 && !printed)
            {
                cout << "# ";
            }
            else if (!printed)
            {
                cout << "  ";
            }
            printed = false;

        }
        cout << endl;
    }
    for (int i = 0; i < width + 1; i++) //Last Line
    {
        cout << "# ";
    }
    cout << endl << "P1 score: " << score[0] << "\t\t\t\t P2 score: " << score[1] << "\nPress WS to move!\t\t   Press 52 to move! \nPress X to end game!";

}
void Input() {
    if (_kbhit()) //Keyboard Input 
    {
        switch (_getch())
        {
        case 'w': dir[0] = UP; break;
        case 's': dir[0] = DOWN; break;
        case '5': dir[1] = UP; break;
        case '2': dir[1] = DOWN; break;
        case 'x': gameOver = true; break;
        case 'p': if (_kbhit()) { _getch; } break;
        }
    }
}
void Logic() {
    if (score[0] == 15)
    {
        gameOver = true;
    }
    else if (score[1] == 15)
    {
        gameOver = true;
    }
    switch (dir[0]) //P1 directions
    {
    case UP:dir[0] = STOP; if (platform[0][0] != 0) platform[0][1] --; break;
    case DOWN:dir[0] = STOP; if (platform[0][2] != height - 1) platform[0][1] ++; break;
    }
    switch (dir[1]) //P2 directions
    {
    case UP: dir[1] = STOP; if (platform[1][0] != 0) platform[1][1] --; break;
    case DOWN: dir[1] = STOP; if (platform[1][2] != height - 1) platform[1][1] ++; break;
    }
    for (int i = 0; i < 2; i++) //Equal platform elements
    {
        platform[i][0] = platform[i][1] - 1;
        platform[i][2] = platform[i][1] + 1;
    }


    if (ballDir[0]) { ball[0]++; }
    if (!ballDir[0]) { ball[0]--; }
    if (ballDir[1]) { ball[1]++; }
    if (!ballDir[1]) { ball[1]--; }

    if (ball[1] == 0) ballDir[1] = 1;
    if (ball[1] == height - 1) ballDir[1] = 0;
    for (int j = 0; j < 3; j++)
    {
        if (ballDir[0] && ball[0] + 1 == platformX[1] && ball[1] == platform[1][j])
        {
            ballDir[0] = false;
        }
        if (!ballDir[0] && ball[0] - 1 == platformX[0] && ball[1] == platform[0][j])
        {
            ballDir[0] = true;
        }
        if (ball[0] == -1)
        {
            score[1] += 1;
            ball[0] = (width / 2) + 1;
            ball[1] = height / 2;
            ballDir[0] = rand() % 2;
            ballDir[1] = rand() % 2;
        }
        if (ball[0] == width + 2)
        {
            score[0] += 1;
            ball[0] = (width / 2) + 1;
            ball[1] = height / 2;
            ballDir[0] = rand() % 2;
            ballDir[1] = rand() % 2;
        }
    }
}
int main()
{
   cout << "--------------\n-Made by Lupi-\n--------------\n" << "<<Start Game>>\n  Exit Game  " << "\n\nBuild 1.0";
    while (a != 2)
    {
        LoginScreen();
    }
    Start:
    Setup();
    do
    {
        Draw();
        Input();
        Logic();
        Sleep(5);
    } while (gameOver == false);
    EndScreen();
    if (gameOver == false)
    {
        goto Start;
    }
    return 0;
}

