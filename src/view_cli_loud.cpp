#include "game.h"
#include "view.h"

namespace tictactoe {
void View::output_bad_move() const {
    std::cout << bad_move_message() << moving_message();
}

void View::output_end_game() const {
    output_board();
    std::cout << final_result_message();
}

void View::output_next_move() const {
    output_board();
    std::cout << moving_message();
}
}  // namespace tictactoe
