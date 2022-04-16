//
//  Grid.cpp
//  Minesweeper
//
//  Created by Aidan Rappaport on 3/10/22.
//

#include "Grid.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

Board::Board()
: side(9), num_mines(10), num_flagged(0), num_hidden(81), difficulty("easy") {
    for (int row = 0; row < side; row++) {
        for (int col = 0; col < side; col++) {
            init_cell(*grid_at(row, col), row, col);
        }
    }
}

Board::Board(std::string difficulty_in) {
    num_flagged = 0;
    if (difficulty_in == "easy") {
        side = 9;
        num_mines = 10;
        difficulty = "easy";
    }
    else if (difficulty_in == "medium") {
        side = 16;
        num_mines = 40;
        difficulty = "medium";
    }
    else if (difficulty_in == "hard") {
        side = 24;
        num_mines = 99;
        difficulty = "hard";
    }
    else {
        side = MAX_SIDE;
        num_mines = MAX_MINES;
        difficulty = "expert";
    }
    num_hidden = side * side;
    for (int row = 0; row < side; row++) {
        for (int col = 0; col < side; col++) {
            init_cell(*grid_at(row, col), row, col);
        }
    }
}

void Board::init_cell(Cell &c, int row, int col) {
    c.row = row;
    c.col = col;
    c.adj_mines = 0;
    c.is_mine = false;
    c.is_flagged = false;
    c.is_hidden = true;
    set_adj_v(c);
}

int Board::get_side() {
    return side;
}

int Board::get_mines() {
    return num_mines;
}

std::string Board::get_difficulty() {
    return difficulty;
}

Cell* Board::get_grid() {
    return grid;
}

void Board::set_cell(Cell &insert, int row, int col) {
    insert.row = row;
    insert.col = col;
    grid[(row * side) + col] = insert;
    return;
}

void Board::set_flag(Cell &c) {
    c.is_flagged = true;
    num_flagged++;
    return;
}

void Board::unflag(Cell &c) {
    c.is_flagged = false;
    num_flagged--;
}

int Board::get_num_flagged() {
    return num_flagged;
}

int Board::get_num_showing() {
    int num = (side * side) - num_hidden;
    return num;
}

void Board::show_cell(Cell &c) {
    c.is_hidden = false;
    num_hidden--;
    return;
}

Cell* Board::grid_at(int row, int col) {
    auto grid = get_grid();
    return &grid[(row * side) + col];
}

string Board::get_type(Cell c) {
    if (c.row == 0) {
        if (c.col == 0) {
            return "TL corner";
        }
        else if (c.col == side - 1) {
            return "TR corner";
        }
        else {return "T side";}
    }
    else if (c.row == side - 1) {
        if (c.col == 0) {
            return "BL corner";
        }
        else if (c.col == side - 1) {
            return "BR corner";
        }
        else {return "B side";}
    }
    else if (c.col == 0) {
        return "L side";
    }
    else if (c.col == side - 1) {
        return "R side";
    }
    else {
        return "middle";
    }
}

void Board::set_adj_v(Cell &c) {
    string type = get_type(c);
    int row = c.row;
    int col = c.col;
    if (type == "TL corner") {
        c.adj.push_back(grid_at(row, col + 1));
        c.adj.push_back(grid_at(row+1, col));
        c.adj.push_back(grid_at(row+1, col + 1));
    }
    else if (type == "TR corner") {
        c.adj.push_back(grid_at(row, col - 1));
        c.adj.push_back(grid_at(row+1, col));
        c.adj.push_back(grid_at(row+1, col - 1));
    }
    else if (type == "BL corner") {
        c.adj.push_back(grid_at(row, col + 1));
        c.adj.push_back(grid_at(row-1, col));
        c.adj.push_back(grid_at(row-1, col + 1));
    }
    else if (type == "BR corner") {
        c.adj.push_back(grid_at(row, col - 1));
        c.adj.push_back(grid_at(row-1, col));
        c.adj.push_back(grid_at(row-1, col - 1));
    }
    else if (type == "T side") {
        c.adj.push_back(grid_at(row, col + 1));
        c.adj.push_back(grid_at(row, col - 1));
        c.adj.push_back(grid_at(row+1, col));
        c.adj.push_back(grid_at(row+1, col + 1));
        c.adj.push_back(grid_at(row+1, col - 1));
    }
    else if (type == "B side") {
        c.adj.push_back(grid_at(row, col + 1));
        c.adj.push_back(grid_at(row, col - 1));
        c.adj.push_back(grid_at(row-1, col));
        c.adj.push_back(grid_at(row-1, col + 1));
        c.adj.push_back(grid_at(row-1, col - 1));
    }
    else if (type == "L side") {
        c.adj.push_back(grid_at(row, col + 1));
        c.adj.push_back(grid_at(row+1, col + 1));
        c.adj.push_back(grid_at(row-1, col+1));
        c.adj.push_back(grid_at(row-1, col));
        c.adj.push_back(grid_at(row+1, col));
    }
    else if (type == "R side") {
        c.adj.push_back(grid_at(row, col - 1));
        c.adj.push_back(grid_at(row+1, col - 1));
        c.adj.push_back(grid_at(row-1, col-1));
        c.adj.push_back(grid_at(row-1, col));
        c.adj.push_back(grid_at(row+1, col));
    }
    else {
        c.adj.push_back(grid_at(row, col + 1));
        c.adj.push_back(grid_at(row+1, col + 1));
        c.adj.push_back(grid_at(row-1, col+1));
        c.adj.push_back(grid_at(row-1, col));
        c.adj.push_back(grid_at(row+1, col));
        c.adj.push_back(grid_at(row, col - 1));
        c.adj.push_back(grid_at(row+1, col - 1));
        c.adj.push_back(grid_at(row-1, col-1));
    }
}

void Board::set_adj_mines(Cell &c) {
    c.adj_mines = 0;
    if (c.is_mine) return;
    for (int i = 0; i < c.adj.size(); i++) {
        if (c.adj[i]->is_mine) c.adj_mines++;
    }
}

void Board::set_cells_adj() {
    for (int row = 0; row < side; row++) {
        for (int col = 0; col < side; col++) {
            Cell curr_cell = *grid_at(row, col);
            set_adj_mines(*grid_at(row, col));
        }
    }
}

void Board::clear_board() {
    for (int row = 0; row < side; row++) {
        for (int col = 0; col < side; col++) {
            Cell insert;
            init_cell(insert, row, col);
            set_cell(insert, row, col);
        }
    }
}

void Board::init_board() {
    int mines_placed = 0;
    srand(static_cast<int>(time(0)));
    
    while (mines_placed < num_mines) {
        int row = rand() % side;
        int col = rand() % side;
        if (grid_at(row, col)->is_mine) {
            continue;
        }
        Cell insert;
        insert.is_mine = true;
        set_cell(insert, row, col);
        mines_placed++;
    }
    
    for (int row = 0; row < side; row++) {
        for (int col = 0; col < side; col++) {
            Cell* curr_cell = grid_at(row, col);
            curr_cell->is_hidden = true;
            curr_cell->is_flagged = false;
            curr_cell->row = row;
            curr_cell->col = col;
        }
    }
    set_cells_adj();
}

void Board::print_board_hidden(std::ostream &os) {
    int size = get_side();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (grid_at(row, col)->is_flagged) {
                os << "F ";
            }
            else {
                os << "O ";
            }
        }
        os << endl;
    }
}

void Board::print_board_mines(std::ostream &os) {
    int size = get_side();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (grid_at(row, col)->is_mine) {
                os << "X ";
            }
            else {
                os << grid_at(row, col)->adj_mines << " ";
            }
        }
        os << endl;
    }
}

void Board::print_board_game(std::ostream &os) {
    int size = get_side();
    for (int i = 0; i < size; i ++) {
        os << i%10 << " ";
    }
    os << endl;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (grid_at(row, col)->is_hidden) {
                if (grid_at(row, col)->is_flagged) {
                    os << "F ";
                }
                else {
                    os << "+ ";
                }
            }
            else {
                if (grid_at(row, col)->is_mine) {
                    os << "X ";
                }
                else {
                    os << grid_at(row, col)->adj_mines << " ";
                }
            }
        }
        os << row << " ";
        os << endl;
    }
}
