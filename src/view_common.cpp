#include <cassert>
#include <iostream>
#include <sstream>
#include "game.h"
#include "view.h"

namespace tictactoe {
View::View(Game &game) : game_(game), current_point({0, 0}) {
    output_next_move();
}

void View::input() {
    std::string inputLine;
    getline(std::cin, inputLine);
    std::istringstream inputStream(inputLine);
    std::string word;
    std::vector<int> numbers;
    while (inputStream >> word && !word.empty()) {
        std::string::iterator it = word.begin();
        while (it != word.end() && ((std::isdigit(*it) != 0) ||
                                    (*it == '-' && it == word.begin()))) {
            ++it;
        }
        if (it != word.end() || word == "-") {
            current_point = {-1, 0};
            return;
        }
        numbers.push_back(stoi(std::string(word)));
    }
    if (numbers.size() != 2) {
        current_point = {-1, 0};
        return;
    }
    current_point = {numbers[0], numbers[1]};
}

void View::output_board() const {
    std::cout << '\n';
    for (int i = 0; i < tictactoe::Game::HEIGHT; i++) {
        for (int j = 0; j < tictactoe::Game::WIDTH; j++) {
            std::cout << game_.get_cell({i, j});
        }
        std::cout << '\n';
    }
}

std::string View::final_result_message() const {
    assert(game_.is_game_finished());
    if (game_.is_win()) {
        return std::string(1, game_.get_moving_char()) + " wins!\n";
    }
    return "Draw.\n";
}

std::string View::moving_message() const {
    assert(!game_.is_game_finished());
    return std::string(1, game_.get_moving_char()) + " move: ";
}

std::string View::bad_move_message() const {
    assert(!game_.is_game_finished());
    return "Bad move!\n";
}

std::pair<int, int> View::get_current_point() const {
    return current_point;
}
}  // namespace tictactoe
