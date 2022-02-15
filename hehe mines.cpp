#include <iostream>
#include <ctime>
#include <cstdlib> 
bool gameover = false;

bool win = false;
void display_field(int** field, int field_size) {
    system("cls");
    for (int i = 0; i < field_size; ++i) {
        for (int j = 0; j < field_size; ++j)
            std::cout << field[i][j] << ' ';
        std::cout << std::endl;
    }
}
int select_difficulty() {
difficulty_select:
    int difficulty; //inputs field difficulty
    std::cin >> difficulty;
    switch (difficulty) {
    case 1: return 9; break;
    case 2: return 16; break;
    case 3: return 24; break;
    default: std::cout << "Invalid difficulty!"; goto difficulty_select;
    }
}
int help;
int number_of_possible_mines(const int size) {
    switch (size) { //selects field size according to difficulty
    case 9: return 10; break;
    case 16: return 40; break;
    case 24: return 99; break;
    }
}
void mines_algorithm(int **field, const int size) { //separates mines evenly on the field
   srand(time(0)); //this gives rand() a seed, otherwise the field will always have the same random mines             
    int mines = number_of_possible_mines(size); //time generates a different seed, unless we compile two times in one second
    for (int i = 0; i < mines; ++i)
        if (field[rand() % size][rand() % size] != 1) 
            field[rand() % size][rand() % size] = 1;
        else 
            --i;
    for (int i = 0; i < size; ++i)                            
        for (int j = 0; j < size; ++j) {
            if (field[i][j] == 1)
                continue;
            field[i][j] = 0;
        }                                         
}
bool revealed(char** field, int y, int x) {
    if (field[y][x] != '*')
        return true;
    else
        return false;
}
bool isValid(int row, int col,int size) { //Returns true if row number and column number is in range
    return (row >= 0) && (row < size) &&
        (col >= 0) && (col < size);
}
void evaluate_field(int** field, const int size) {
    for (int i = 0; i < size; ++i) 
        for (int j = 0; j < size; ++j) {
            if (field[i][j] == 1)
                field[i][j] = 9;
        }
    for (int i = 0; i < size; ++i) 
        for (int j = 0; j < size; ++j) {
             if (field[i][j] == 9)
                 continue;
             if (isValid(i - 1, j, size) && field[i - 1][j] == 9)field[i][j]++;    
             if (isValid(i + 1, j, size) && field[i + 1][j] == 9)field[i][j]++;
             if (isValid(i, j - 1, size) && field[i][j - 1] == 9)field[i][j]++;
             if (isValid(i, j + 1, size) && field[i][j + 1] == 9)field[i][j]++;

             if (isValid(i + 1, j + 1, size) && field[i + 1][j + 1] == 9)field[i][j]++;
             if (isValid(i - 1, j + 1, size) && field[i - 1][j + 1] == 9)field[i][j]++;
             if (isValid(i + 1, j - 1, size) && field[i + 1][j - 1] == 9)field[i][j]++;
             if (isValid(i - 1, j - 1, size) && field[i - 1][j - 1] == 9)field[i][j]++;
        }
}
void replace(int** original_field, char** game_field, int y, int x) {
    if (original_field[y][x] == 9)
    {
        gameover = true;
    }
    if (original_field[y][x] == 0) {   
        if (isValid(y - 1, x, help) && !revealed(game_field, y - 1, x)) replace(original_field, game_field, y - 1, x);
        if (isValid(y, x - 1, help) && !revealed(game_field, y, x - 1)) replace(original_field, game_field, y, x - 1);
    }
    game_field[y][x] = original_field[y][x] + '0';
    if (original_field[y][x] == 0) {
        if (isValid(y + 1, x, help) && !revealed(game_field, y + 1, x)) replace(original_field, game_field, y + 1, x);
        if (isValid(y, x + 1, help) && !revealed(game_field, y, x + 1)) replace(original_field, game_field, y, x + 1);
    }
}

void pick_a_cell(int size, int** field) {
    char** game_field = new char* [size];
    for (int i = 0; i < size; ++i)
        game_field[i] = new char[size];

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            game_field[i][j] = '*';
    start:
    system("cls");
    std::cout << std::endl;
    for (int i = 0; i < size; ++i)
        std::cout << i << "  ";
    std::cout << std::endl;
    for (int i = 0; i < size; ++i)
        std::cout << "|  ";
    std::cout << std::endl;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            std::cout << game_field[i][j] << "  ";
        }
        std::cout << "-  " << i;
        std::cout << std::endl;
    }
    if (gameover == false) {
        std::cout << "\nPick a cell (first x, then y):\n";
        int y, x;
        std::cin >> x >> y;
        replace(field, game_field, y, x);
        goto start;
    }
    else
    {
        std::cout << "\nYou Lose!\n";
    }

    for (int i = 0; i < size; ++i)
        delete[] game_field[i];
    delete[] game_field;
}
int main() {
    std::cout << "Select Difficulty.\n1-Easy. 9*9 Board and 10 mines.\n2-Medium. 16*16 Board and 40 mines.\n3-Hard. 24*24 Board and 99 mines.\nInput difficulty: ";
    int size = select_difficulty();
    help = size;
    std::cout << "help: " << help;
    int** field = new int* [size];
    for (int i = 0; i < size; ++i)
        field[i] = new int[size];
    mines_algorithm(field, size);
    std::cout << std::endl;
    evaluate_field(field, size);
    while (gameover == false && win == false) {
        pick_a_cell(size, field);
    }
    if (win == true)
    {
        std::cout << "You won!";
    }

    for (int i = 0; i < size; ++i)
        delete[] field[i];
    delete[] field;
    return 0;
}
/*
Create a function that takes an array representation of a Minesweeper board, and returns another board where the value of each cell is the amount of its neighbouring mines.
The input may look like this:
  [0, 1, 0, 0],
  [0, 0, 1, 0],
  [0, 1, 0, 1],
  [1, 1, 0, 0],

  [1, 9, 2, 1],
  [2, 3, 9, 2],
  [3, 9, 4, 9],
  [9, 9, 3, 1],
*/
