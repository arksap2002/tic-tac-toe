#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <vector>

namespace tictactoe {
struct Game {
private:
    std::vector<std::vector<char>> board;
    int number_of_move;

public:
    static const int HEIGHT = 10;
    static const int WIDTH = 10;
    static const int ROW_TO_WIN = 5;
    enum Cell { empty = '.', x = 'X', o = 'O' };

    Game();

    [[nodiscard]] char get_moving_char() const;

    [[nodiscard]] bool is_board_completed() const;

    [[nodiscard]] bool is_win() const;

    [[nodiscard]] bool is_draw() const;

    [[nodiscard]] bool is_correct_move(const std::pair<int, int> &point) const;

    [[nodiscard]] static bool is_exit(const std::pair<int, int> &point);

    void make_move(const std::pair<int, int> &point);

    void new_move();

    [[nodiscard]] bool is_game_finished() const;

    [[nodiscard]] char get_cell(const std::pair<int, int> &point) const;

    [[nodiscard]] int get_number_of_move() const;
};
}  // namespace tictactoe

#endif
