#include "game.h"
#include "view.h"

int main() {
    tictactoe::Game game;
    tictactoe::View view(game);
    while (true) {
        view.input();
        if (game.is_correct_move(view.get_current_point())) {
            game.make_move(view.get_current_point());
            if (game.is_game_finished()) {
                view.output_end_game();
                break;
            } else {
                game.new_move();
                view.output_next_move();
            }
        } else {
            if (tictactoe::Game::is_exit(view.get_current_point())) {
                break;
            }
            view.output_bad_move();
        }
    }
}
