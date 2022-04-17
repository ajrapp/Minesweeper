//
//  main.cpp
//  Minesweeper
//
//  Created by Aidan Rappaport on 3/10/22.
//

#include "Grid_tests.h"
#include "Game_tests.h"
#include "Grid.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

void play_game() {
    stringstream in;
    cout << "Enter difficulty ('easy' 'medium' 'hard' or 'expert'): ";
    string difficulty;
    bool valid_difficulty = false;
    while (!valid_difficulty) {
        cin >> difficulty;
        if (difficulty == "easy" || difficulty == "medium"
            || difficulty == "hard" || difficulty == "expert") {
            valid_difficulty = true;
            cout << "difficulty: " << difficulty << endl;
        }
        else {
            cout << "Please enter a valid difficulty: ";
        }
    }
    Game game(difficulty);
    
    bool play = true;
    while (play) {
        game.print_board(cout);
        char action;
        string action_in;
        cout << "Show (S) or Flag (F) or Unflag (U): ";
        cin >> action_in;
        while (action_in.size() > 1 || (toupper(action_in[0]) != 'S'
                && toupper(action_in[0]) != 'F' && toupper(action_in[0]) != 'U')) {
            cout << "Please enter a valid input ('S' or 'F' or 'U'): ";
            cin >> action_in;
        }
        action = action_in[0];
        action = toupper(action);
        string action_s;
        if (action == 'S') {
            action_s = "Show";
        }
        else if (action == 'F') {
            action_s = "Flag";
        }
        else if (action == 'U') {
            action_s = "Unflag";
        }
        cout << "Action: " << action_s << endl;
        
        int row, col;
        cout << "select cell:" << endl;
        cout << "row: ";
        cin >> row;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Please enter a valid number: ";
            cin >> row;
        }
        cout << "col: ";
        cin >> col;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Please enter a valid number: ";
            cin >> col;
        }
        cout << endl;
        Cell* c = game.get_cell(row, col);
        
        if (action == 'S') {
            if (c->is_hidden == false || c->is_flagged) {
                cout << "Invalid move" << endl;
            }
            else {
                game.unhide(*c);
                if (c->is_mine) {
                    play = false;
                    game.print_board(cout);
                    cout << "GAME OVER!" << endl;
                }
            }
        }
        else if (action == 'F') {
            game.flag(*c);
        }
        else if (action == 'U') {
            game.unflag(*c);
        }
        int num_done = 0;
        int side = game.get_side();
        for (int row = 0; row < side; row++) {
            for (int col = 0; col < side; col++) {
                Cell* curr = game.get_cell(row, col);
                if (curr->is_flagged || !curr->is_hidden) {
                    num_done++;
                }
            }
        }
        int num_cells = game.get_side() * game.get_side();
        if (num_done == num_cells) {
            game.print_board(cout);
            cout << "YOU WIN!" << endl;
            play = false;
        }
    }
}

int main(int argc, const char * argv[]) {
    cout << "Test Grid: 1" << endl;
    cout << "Test Game: 2" << endl;
    cout << "Play: 3" << endl;
    
    int input;
    cin >> input;
    while (cin.fail() || (input != 1
            && input != 2 && input != 3)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Please enter a valid input (1, 2, or 3): ";
        cin >> input;
    }
    if (input == 1) {
        start_grid_tests();
    }
    else if (input == 2) {
        start_game_tests();
    }
    else if (input == 3) {
        play_game();
    }
    
    return 0;
}
