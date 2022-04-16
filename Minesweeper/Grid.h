//
//  Grid.h
//  Minesweeper
//
//  Created by Aidan Rappaport on 4/7/22.
//

#ifndef Grid_h
#define Grid_h

#include <stdio.h>
#include <string>
#include <tuple>
#include <iostream>
#include <vector>
using namespace std;

static const int MAX_SIDE = 30;
static const int MAX_MINES = 150;

struct Cell {
    bool is_mine;
    bool is_hidden;
    bool is_flagged;
    int row, col;
    int adj_mines;
    vector<Cell*> adj;
};

class Board {
private:
    Cell grid[MAX_SIDE * MAX_SIDE];
    int side;
    int num_mines;
    int num_flagged;
    int num_hidden;
    std::string difficulty;
        //EASY: 9x9, 10 mines
        //MED: 16x16, 40 mines
        //HARD: 24x24, 99 mines
        //EXPERT: 30x30, 180 mines
    
public:
    //Default ctor: sets to easy
    Board();
    
    // REQUIRES: deiificulty_in is "easy" "medium" or "hard" or "expert"
    // EFFECTS: sets width, height, and mines
    Board(std::string difficulty_in);
    
    // EFFECTS: returns side
    int get_side();
    
    // EFFECTS: returns num_mines
    int get_mines();
    
    //EFFECTS: returns difficulty
    std::string get_difficulty();
    
    // EFFFECTS: returns grid array
    Cell* get_grid();
    
    // EFFECTS: sets starting values of given cell
    void init_cell(Cell &c, int row, int col);
    
    // EFFECTS: sets cell to specified location
    void set_cell(Cell &insert, int row, int col);
    
    // EFFECTS: flags given cell
    // MODIFIES: c
    void set_flag(Cell &c);
    
    void unflag(Cell &c);
    
    int get_num_flagged();
    
    int get_num_showing();
    
    // EFFECTS: sets is_hidden to false
    // MODIFIES: c
    void show_cell(Cell &c);

    // EFFECTS: returns cell at specified location
    Cell* grid_at(int row, int col);
    
    // sets each cell to approriate state;
    void init_board();
    
    // EFFECTS: removes all mines
    void clear_board();
    
    //EFFECTS: sets adj vector
    void set_adj_v(Cell &c);
    
    // EFFECTS: sets adj_mines for all cells
    void set_cells_adj();
    
    // MODIFIES: c
    // EFFECTS: sets adj_mines for cell given
    void set_adj_mines(Cell &c);
    
    // EFFECTS: return the type of placement of the cell
    // TL,TR,BR,BL corner, or T,L,R,B side
    std::string get_type(Cell c);
    
    // EFFECTS: prints the board with the mines hidden
    void print_board_hidden(std::ostream &os);
    
    // EFFECTS: prints the board with mines showing
    void print_board_mines(std::ostream &os);
    
    // EFFECTS: prints the board as in gameplay
    void print_board_game(std::ostream &os);
};

#endif /* Grid_h */
