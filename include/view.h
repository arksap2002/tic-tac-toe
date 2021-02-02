#ifndef VIEW_H_
#define VIEW_H_

#include <iostream>
#include "game.h"

namespace tictactoe {
struct View {
private:
    Game &game_;
    std::pair<int, int> current_point;

public:
    explicit View(Game &game);

    void input();

    void output_bad_move() const;

    void output_end_game() const;

    void output_next_move() const;

    void output_board() const;

    [[nodiscard]] std::string final_result_message() const;

    [[nodiscard]] std::string moving_message() const;

    [[nodiscard]] std::string bad_move_message() const;

    [[nodiscard]] std::pair<int, int> get_current_point() const;
};
}  // namespace tictactoe

#endif
