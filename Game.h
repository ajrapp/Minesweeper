//
//  Game.h
//  Minesweeper
//
//  Created by Aidan Rappaport on 4/8/22.
//

#ifndef Game_h
#define Game_h

#include "Grid.h"
using namespace std;

class Game {
private:
    Board board;
    
public:
    //EFFECTS: defaults to easy
    Game();
    
    //REQUIRES: difficulty must be "easy" "medium" "hard" or "expert"
    //EFFECTS: initializes game and board
    Game(std::string difficulty);
    
    //EFFECTS: returns cell at given location
    Cell* get_cell(int row, int col);
    
    //EFFECTS: flags given cell
    //MODIFIES: c
    void flag(Cell &c);
    
    void unflag(Cell &c);
    
    //EFFECTS: sets unhidden to false, unhides adj cells if adj_mines = 0
    //MODIFIES: c
    void unhide(Cell &c);
    
    //EFFECTS: returns number of unhidden cells
    int get_num_unhidden();
    
    //EFFECTS: returns number of flagged cells
    int get_num_flags();
    
    //EFFECTS: returns side
    int get_side();
    
    //EFFECTS: prints game board
    void print_board(std::ostream& os);
    
    //EFFECTS: prints board with adj_mines
    void print_board_vals(std::ostream& os);
};


#endif /* Game_h */
