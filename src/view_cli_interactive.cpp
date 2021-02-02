#include <cassert>
#include "game.h"
#include "ncurses.h"
#include "view.h"

namespace tictactoe {
View::View(Game &game) : game_(game) {
    initscr();
    keypad(stdscr, true);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    curs_set(0);
    refresh();
}

void View::input() {
    output_board();
    int input = getch();
    while (input != '\n') {
        if (input == 'x') {
            endwin();
            current_point = {-1, -1};
            break;
        }
        if (input == KEY_LEFT) {
            current_point.second = std::max(0, current_point.second - 1);
        }
        if (input == KEY_RIGHT) {
            current_point.second =
                std::min(tictactoe::Game::WIDTH - 1, current_point.second + 1);
        }
        if (input == KEY_UP) {
            current_point.first = std::max(0, current_point.first - 1);
        }
        if (input == KEY_DOWN) {
            current_point.first =
                std::min(tictactoe::Game::HEIGHT - 1, current_point.first + 1);
        }
        output_board();
        input = getch();
    }
}

void View::output_bad_move() const {
    //        press doesn't change anything
}

std::pair<int, int> View::get_current_point() const {
    return current_point;
}

std::string View::final_result_message() const {
    assert(game_.is_game_finished());
    if (game_.is_win()) {
        attron(COLOR_PAIR((game_.get_number_of_move() + 1) % 2 + 2));
        return std::string(1, game_.get_moving_char()) + " wins!\n";
    }
    attron(COLOR_PAIR(1));
    return "Draw.\n";
}

void View::output_end_game() const {
    output_board();
    attron(COLOR_PAIR(1));
    addstr(final_result_message().c_str());
    refresh();
    getch();
    endwin();
}

void View::output_next_move() const {
    //        depends on colour
}

void View::output_board() const {
    clear();
    addch('\n');
    for (int i = 0; i < tictactoe::Game::HEIGHT; i++) {
        for (int j = 0; j < tictactoe::Game::WIDTH; j++) {
            if (i == current_point.first && j == current_point.second) {
                attron(COLOR_PAIR(game_.get_number_of_move() % 2 + 2));
                addch(game_.get_cell({i, j}));
            } else {
                attron(COLOR_PAIR(1));
                addch(game_.get_cell({i, j}));
            }
        }
        addch('\n');
    }
    refresh();
}
}  // namespace tictactoe
