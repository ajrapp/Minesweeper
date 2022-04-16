//
//  Game.cpp
//  Minesweeper
//
//  Created by Aidan Rappaport on 4/8/22.
//

#include "Game.h"
#include <string>
using namespace std;

Game::Game() : board("easy") {
    board.init_board();
}

Game::Game(std::string difficulty) : board(difficulty) {
    board.init_board();
}

Cell* Game::get_cell(int row, int col) {
    return board.grid_at(row, col);
}

void Game::flag(Cell &c) {
    board.set_flag(c);
}

void Game::unflag(Cell &c) {
    board.unflag(c);
}

void Game::unhide(Cell &c) {
    board.show_cell(c);
    if (c.adj_mines == 0) {
        for (int i = 0; i < c.adj.size(); i++) {
            Cell* curr = c.adj[i];
            if (curr->is_hidden) {
                board.show_cell(*curr);
                if (curr->adj_mines == 0) {
                    unhide(*curr);
                }
            }
        }
    }
}

int Game::get_num_flags() {
    return board.get_num_flagged();
}

int Game::get_num_unhidden() {
    return board.get_num_showing();
}

int Game::get_side() {
    return board.get_side();
}

void Game::print_board(std::ostream& os) {
    board.print_board_game(os);
}

void Game::print_board_vals(std::ostream& os) {
    board.print_board_mines(os);
}
