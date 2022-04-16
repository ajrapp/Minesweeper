//
//  Grid_tests.cpp
//  Minesweeper
//
//  Created by Aidan Rappaport on 4/7/22.
//

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>

#include "Grid_tests.h"
#include "Grid.h"
#include <string>
#include <iostream>
using namespace std;

void test_default_ctor(void);
void test_ctor_easy(void);
void test_ctor_med(void);
void test_ctor_hard(void);
void test_grid_at(void);
void test_init_clear_board(void);
void test_board_1(void);
void test_board_2(void);
void test_board_med(void);
void test_board_hard(void);
void test_board_expert(void);
void test_set_flag(void);
void test_set_flag_board(void);
void test_set_cells_adj(void);
void test_set_adj(void);
void test_set_adj_v(void);

void start_grid_tests(void) {
    test_default_ctor();
    test_ctor_easy();
    test_ctor_med();
    test_ctor_hard();
    test_grid_at();
    test_init_clear_board();
    test_board_1();
    test_board_2();
    test_board_med();
    test_board_hard();
    test_board_expert();
    test_set_flag();
    test_set_flag_board();
    test_set_cells_adj();
    test_set_adj();
    test_set_adj_v();
}

void test_default_ctor(void) {
    cout << "testing default_ctor: ";
    Board b;
    
    assert(b.get_side() == 9);
    assert(b.get_mines() == 10);
    assert(b.get_difficulty() == "easy");
    cout << "pass" << endl;
}

void test_ctor_easy(void) {
    cout << "testing ctor_easy: ";
    Board b("easy");
    
    assert(b.get_side() == 9);
    assert(b.get_mines() == 10);
    assert(b.get_difficulty() == "easy");
    cout << "pass" << endl;
}

void test_ctor_med(void) {
    cout << "testing ctor_med: ";
    Board b("medium");
    
    assert(b.get_side() == 16);
    assert(b.get_mines() == 40);
    assert(b.get_difficulty() == "medium");
    cout << "pass" << endl;
}

void test_ctor_hard(void) {
    cout << "testing ctor_hard: ";
    Board b("hard");
    
    assert(b.get_side() == 24);
    assert(b.get_mines() == 99);
    assert(b.get_difficulty() == "hard");
    cout << "pass" << endl;
}

void test_grid_at(void) {
    cout << "testing grid_at: ";
    Board b;
    Cell insert;
    
    b.set_cell(insert, 0, 0);
    assert(b.grid_at(0, 0)->row == insert.row);
    assert(b.grid_at(0, 0)->col == insert.col);
    cout << "pass" << endl;
}

void test_init_clear_board(void) {
    cout << "testing init_board: " << endl;
    Board b;
    b.init_board();
    b.print_board_mines(cout);
    
    cout << "testing clear_board: " << endl;
    b.clear_board();
    b.print_board_mines(cout);
}

void test_board_1(void) {
    cout << "testing boards: " << endl;
    cout << "1: " << endl;
    Board b;
    b.init_board();
    b.print_board_mines(cout);
}

void test_board_2(void) {
    cout << "2: " << endl;
    sleep(1);
    Board b;
    b.init_board();
    b.print_board_mines(cout);
}

void test_board_med(void) {
    cout << "testing board_med: " << endl;
    Board b("medium");
    b.init_board();
    b.print_board_mines(cout);
}

void test_board_hard(void) {
    cout << "testing board_hard: " << endl;
    Board b("hard");
    b.init_board();
    b.print_board_mines(cout);
}

void test_board_expert(void) {
    cout << "testing board_expert: " << endl;
    Board b("expert");
    b.init_board();
    b.print_board_mines(cout);

}

void test_set_flag_board(void) {
    cout << "testing set_flag_board: " << endl;
    Board b;
    b.init_board();
    b.set_flag(*b.grid_at(5, 6));
    b.set_flag(*b.grid_at(0, 0));
    b.set_flag(*b.grid_at(8, 1));
    b.print_board_hidden(cout);
}

void test_set_flag(void) {
    cout << "testing set_flag: ";
    Board b;
    b.init_board();
    Cell c = *b.grid_at(4, 6);
    b.set_flag(c);
    assert(c.is_flagged);
    cout << "pass" << endl;
}

void test_set_cells_adj(void) {
    cout << "testing set_cells: ";
    Board b;
    Cell c;
    b.init_cell(c, 0, 1);
    c.is_mine = true;
    b.set_cell(c, 0, 1);
    b.init_board();
    if (!b.grid_at(0, 0)->is_mine) {
        assert(b.grid_at(0, 0)->adj_mines >= 1);
    }
    assert(b.grid_at(0, 1)->adj_mines == 0);
    cout << "pass" << endl;
}

void test_set_adj(void) {
    cout << "testing set_adj: ";
    Board b;
    b.init_board();
    for (int row = 0; row < b.get_side(); row++) {
        for (int col = 0; col < b.get_side(); col++) {
            Cell curr_cell = *b.grid_at(row, col);
            if (b.get_type(curr_cell) == "TR corner") {
                assert(curr_cell.adj_mines <= 3);
            }
            else if (b.get_type(curr_cell) == "TL corner") {
                assert(curr_cell.adj_mines <= 3);

            }
            else if (b.get_type(curr_cell) == "BR corner") {
                assert(curr_cell.adj_mines <= 3);

            }
            else if (b.get_type(curr_cell) == "BL corner") {
                assert(curr_cell.adj_mines <= 3);

            }
            else if (b.get_type(curr_cell) == "T side") {
                assert(curr_cell.adj_mines <= 5);

            }
            else if (b.get_type(curr_cell) == "B side") {
                assert(curr_cell.adj_mines <= 5);
            }
            else if (b.get_type(curr_cell) == "L side") {
                assert(curr_cell.adj_mines <= 5);
            }
            else if (b.get_type(curr_cell) == "R side") {
                assert(curr_cell.adj_mines <= 5);
            }
            else if (b.get_type(curr_cell) == "middle") {
                assert(curr_cell.adj_mines <= 8);
            }
        }
    }
    cout << "pass" << endl;
}

void test_set_adj_v(void) {
    cout << "testing set_adj_v: ";
    Board b;
    Cell* c = b.grid_at(0, 0);
    Cell* c1 = b.grid_at(3,3);
    Cell* c2 = b.grid_at(0, 4);
    assert(c->adj.size() == 3);
    assert(c1->adj.size() == 8);
    assert(c2->adj.size() == 5);
    cout << "pass" << endl;
}

#endif
