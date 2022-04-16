//
//  Game_tests.cpp
//  Minesweeper
//
//  Created by Aidan Rappaport on 4/10/22.
//


#include "Game.h"
#include "Grid.h"
#include "Game_tests.h"

void test_ctor(void);
void test_get_cell(void);
void test_flag(void);
void test_unhide(void);
void test_get_num_unhidden(void);
void test_get_num_flags(void);
void test_get_side(void);
void test_print_board(void);

void start_game_tests(void) {
    test_ctor();
    test_get_cell();
    test_flag();
    test_unhide();
    test_get_num_unhidden();
    test_get_num_flags();
    test_get_side();
    test_print_board();
}

void test_ctor(void) {
    cout << "testing ctor: ";
    Game game("easy");
    assert(game.get_side() == 9);
    cout << "easy:" << endl;
    game.print_board_vals(cout);
    
    Game gamee("medium");
    assert(gamee.get_side() == 16);
    cout << "medium:" << endl;
    gamee.print_board_vals(cout);
    
    Game gameee("hard");
    assert(gameee.get_side() == 24);
    cout << "hard:" << endl;
    gameee.print_board_vals(cout);
    
    Game gameeee("expert");
    assert(gameeee.get_side() == 30);
    cout << "expert:" << endl;
    gameeee.print_board_vals(cout);
    cout << "pass" << endl;
}
void test_get_cell(void) {
    cout << "testing get_cell: ";
    Game game;
    Cell* c = game.get_cell(1, 4);
    assert(c->row == 1 && c->col == 4);
    cout << "pass" << endl;
}
void test_flag(void) {
    cout << "testing flag: ";
    Game game;
    Cell* c = game.get_cell(4, 5);
    game.flag(*c);
    assert(c->is_flagged == true);
    cout << "pass" << endl;
}
void test_unhide(void) {
    cout << "testing unhide: ";
    Game g;
    Cell* c = g.get_cell(7, 2);
    g.unhide(*c);
    assert(c->is_hidden == false);
    cout << "pass" << endl;
}
void test_get_num_unhidden(void) {
    cout << "testing get_num_unhidden: ";
    Game g;
    Cell* c1 = g.get_cell(1, 5);
    Cell* c2 = g.get_cell(5, 3);
    g.unhide(*c1);
    g.unhide(*c2);
    assert(g.get_num_unhidden() >= 2);
    
    Cell* c3 = g.get_cell(8, 8);
    g.unhide(*c3);
    assert(g.get_num_unhidden() >= 3);
    cout << "pass" << endl;
}
void test_get_num_flags(void) {
    cout << "testing get_num_flags: ";
    Game g;
    Cell* c1 = g.get_cell(1, 6);
    Cell* c2 = g.get_cell(2, 8);
    g.flag(*c1);
    g.flag(*c2);
    assert(g.get_num_flags() == 2);
    cout << "pass" << endl;
}
void test_get_side(void) {
    cout << "testing get_side: ";
    Game g("medium");
    assert(g.get_side() == 16);
    cout << "pass" << endl;
}
void test_print_board(void) {
    cout << "tesing print_board_vals: " << endl;
    Game g;
    g.print_board_vals(cout);
}
