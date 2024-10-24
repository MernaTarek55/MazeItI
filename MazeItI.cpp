#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib> 
#include <ctime>  
#include <conio.h>

using namespace std;

const int MAX_ROWS = 20; 
const int MAX_COLS = 68; 

bool readFile(char environment[MAX_ROWS][MAX_COLS], int& rows, int& cols, const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }

    rows = 0; 
    string line;
    while (getline(file, line) && rows < MAX_ROWS) {

        cols = line.size();
        for (int col = 0; col < cols && col < MAX_COLS; ++col) {
            environment[rows][col] = line[col]; 
        }
        for (int col = cols; col < MAX_COLS; ++col) {
            environment[rows][col] = ' '; 
        }
        ++rows;
    }

    

    file.close(); 
    return true; 
}


void clearConsole() {
    system("CLS");
}



void findTreasure(char environment[MAX_ROWS][MAX_COLS], int environmentRows, int environmentCols) {
    bool notwen = true;
    int u = 1, v = 1;

    srand(time(0));

    int tregerposx = rand() % (environmentRows - 2) + 1;
    int tregerposy = rand() % (environmentCols - 2) + 1;

    char character;

    cout << "Welcome to Find the Treasure game \nPlease enter your Character: ";
    cin >> character;


    environment[tregerposx][tregerposy] = 'O';
    environment[u][v] = character; 
    clearConsole();

 
    for (int i = 0; i < environmentRows; i++) {
        for (int j = 0; j < environmentCols; j++) {
            cout << environment[i][j];
        }
        cout << endl;
    }

    cout << "Use WASD to move. Find the treasure (O)! Press 'q' to quit.\n";

    while (notwen) {
        if (_kbhit()) {
            char move = _getch();
            environment[u][v] = ' '; 

            // Temporary variables for new position
            int newU = u; 
            int newV = v;

            switch (move) {
            case 'a': 
                if (v > 1) newV--; 
                break;
            case 'd':
                if (v < environmentCols - 2) newV++; 
                break;
            case 's': 
                if (u < environmentRows - 2) newU++; 
                break;
            case 'w': 
                if (u > 1) newU--; 
                break;
            case 'q': 
                notwen = false;
                break;
            default:
                break;
            }

            
            // Check if the new position is not a border or inner wall
            if (environment[newU][newV] != '|' && environment[newU][newV] != '-') {
                 u = newU;
                 v = newV;
            }

            environment[u][v] = character; 

            clearConsole();
            for (int i = 0; i < environmentRows; i++) {
                for (int j = 0; j < environmentCols; j++) {
                    cout << environment[i][j];
                }
                cout << endl;
            }

            cout << "Use WASD to move. Find the treasure (O)! Press 'q' to quit.\n";
        }

        if (u == tregerposx && v == tregerposy) {
            notwen = false;
            clearConsole();
            for (int i = 0; i < environmentRows; i++) {
                for (int j = 0; j < environmentCols; j++) {
                    cout << environment[i][j];
                }
                cout << endl;
            }
            cout << "########################## Congratulations! You WON! #########################" << endl;
        }
    }

    cout << endl << "---------------------------------------------------------------------------------" << endl;
}

int main() {
    char environment[MAX_ROWS][MAX_COLS];
    int environmentRows = 0;
    int environmentCols = 0; 

    string fileName = "Maze.txt";

    if (!readFile(environment, environmentRows, environmentCols, fileName)) {
        return 1; 
    }

    
    findTreasure(environment, environmentRows, environmentCols);

    return 0;
}
