#include "game.h"
#include <cassert>

namespace tictactoe {
Game::Game() : number_of_move(0) {
    board.assign(HEIGHT, std::vector<char>(WIDTH, empty));
}

bool Game::is_correct_move(const std::pair<int, int> &point) const {
    return point.first >= 0 && point.first < HEIGHT && point.second >= 0 &&
           point.second < WIDTH && board[point.first][point.second] == empty;
}

void Game::make_move(const std::pair<int, int> &point) {
    assert(is_correct_move(point));
    board[point.first][point.second] = get_moving_char();
}

void Game::new_move() {
    number_of_move++;
}

char Game::get_moving_char() const {
    if (number_of_move % 2 == 0) {
        return o;
    }
    return x;
}

int Game::get_number_of_move() const {
    return number_of_move;
}

bool Game::is_board_completed() const {
    return number_of_move == HEIGHT * WIDTH;
}

bool Game::is_win() const {
    std::vector<std::vector<std::vector<int>>> rowData(
        HEIGHT, std::vector<std::vector<int>>(WIDTH, {0, 0, 0, 0}));
    std::vector<std::pair<int, int>> d = {{-1, 0}, {-1, -1}, {0, -1}, {-1, 1}};
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            for (int k = 0; k < 4; k++) {
                if (board[i][j] != empty && (i + d[k].first) >= 0 &&
                    (i + d[k].first) < HEIGHT && (j + d[k].second) >= 0 &&
                    (j + d[k].second) < WIDTH &&
                    board[i][j] == board[i + d[k].first][j + d[k].second]) {
                    rowData[i][j][k] =
                        rowData[i + d[k].first][j + d[k].second][k] + 1;
                } else {
                    rowData[i][j][k] = int(board[i][j] != empty);
                }
                if (rowData[i][j][k] >= ROW_TO_WIN) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::is_draw() const {
    return is_board_completed() && !is_win();
}

bool Game::is_game_finished() const {
    return is_draw() || is_win();
}

bool Game::is_exit(const std::pair<int, int> &point) {
    return point == std::make_pair(-1, -1);
}

char Game::get_cell(const std::pair<int, int> &point) const {
    return board[point.first][point.second];
}
}  // namespace tictactoe
