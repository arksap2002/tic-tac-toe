#include "game.h"
#include "mytest.h"

namespace tictactoe {

TEST_CASE("Correct constructor tests") {
    Game game;
    for (int i = 0; i < tictactoe::Game::HEIGHT; i++) {
        for (int j = 0; j < tictactoe::Game::WIDTH; j++) {
            CHECK(game.get_cell({i, j}) == game.empty);
        }
    }
}

TEST_CASE("Correct move tests") {
    Game game;
    for (int i = 0; i < tictactoe::Game::HEIGHT; i++) {
        for (int j = 0; j < tictactoe::Game::WIDTH; j++) {
            CHECK(game.is_correct_move({i, j}));
        }
    }
    int height = tictactoe::Game::HEIGHT;
    int width = tictactoe::Game::WIDTH;
    CHECK(!game.is_correct_move({-1, 0}));
    CHECK(!game.is_correct_move({0, -1}));
    CHECK(!game.is_correct_move({-1, -2}));
    CHECK(!game.is_correct_move({height, 0}));
    CHECK(!game.is_correct_move({height + 2, 0}));
    CHECK(!game.is_correct_move({0, width}));
    CHECK(!game.is_correct_move({0, width + 2}));
}

TEST_CASE("Is exit tests") {
    Game game;
    CHECK(game.is_exit({-1, -1}));
    for (int i = -100; i < 2 * tictactoe::Game::HEIGHT; i++) {
        for (int j = 0; j < 2 * tictactoe::Game::WIDTH; j++) {
            CHECK(!game.is_exit({i, j}));
        }
    }
}

TEST_CASE("New move tests") {
    Game game;
    CHECK(game.get_number_of_move() == 0);
    for (int i = 0; i < 100; i++) {
        game.new_move();
        CHECK(game.get_number_of_move() == i + 1);
    }
}

TEST_CASE("Make move tests") {
    Game game;
    for (int i = 0; i < tictactoe::Game::HEIGHT; i++) {
        for (int j = 0; j < tictactoe::Game::WIDTH; j++) {
            CHECK(game.get_cell({i, j}) == game.empty);
            game.make_move({i, j});
            CHECK(game.get_cell({i, j}) != game.empty);
        }
    }
}

TEST_CASE("Board completed tests") {
    Game game;
    for (int i = 0; i < tictactoe::Game::HEIGHT; i++) {
        for (int j = 0; j < tictactoe::Game::WIDTH; j++) {
            CHECK(!game.is_board_completed());
            game.make_move({i, j});
            game.new_move();
        }
    }
    CHECK(game.is_board_completed());
}

TEST_CASE("Move in non-empty cell tests") {
    Game game;
    for (int i = 0; i < tictactoe::Game::HEIGHT; i++) {
        for (int j = 0; j < tictactoe::Game::WIDTH; j++) {
            CHECK(game.is_correct_move({i, j}));
            game.make_move({i, j});
            game.new_move();
            CHECK(!game.is_correct_move({i, j}));
        }
    }
}

static const std::vector<std::vector<std::string>> newBoards = {
    {"..........", "..........", "..........", "..........", "..........",
     "..........", "..........", "..........", "..........", ".........."},
    {"..........", "..X....X..", "..XOOOOX..", "..XOOOOX..", "..XOOOOX..",
     "...OOOO...", "...XXXX...", "...XXXX...", "..........", ".........."},
    {"XOOXXOOXXO", "OXXOOXXOOX", "XXOOXXOOXO", "XOOXXOOXXO", "OXXOOXXOO.",
     "XOOXXOOXXO", "OXXOOXXOOX", "XOOXXOOXXO", "XXOOXXOOXO", "XXOOXXOOXO"},
    {"XOOXXOOXXO", "OXXOOXXOOX", "XXOOXXOOXO", "XOOXXOOXXO", "OXXOOXXOOX",
     "XOOXXOOXXO", "OXXOOXXOOX", "XOOXXOOXXO", "XXOOXXOOXO", "XXOOXXOOXO"},
    {"XOOXXOOXXO", "OXXOOXXOOX", "XXOOXXOOXO", "XOOXXOOXXO", "OXXOOXXOOX",
     "XOOXXOOXXO", "OXXOOXXOOO", "XOOXXOOXXO", "XXOOXXOOXO", "XXOOXXOXXO"},
    {"XXXX......", "OOOOO.....", "..........", "..........", "..........",
     "..........", "..........", "..........", "..........", ".........."},
    {"..........", "..........", "..XXXX....", "..........", "..........",
     "..........", "..........", "..........", "....OOOOO.", ".........."},
    {"XO........", "XO........", "XO........", "XO........", ".O........",
     "..........", "..........", "..........", ".........", ".........."},
    {".......X..", ".......X..", "..O....X..", "..O....X..", "..O....X..",
     "..O.......", "..O.......", "..........", ".........", ".........."},
    {"....X.....", ".....X....", "......X...", ".O.....X..", "....O...X.",
     "..O.......", "....O.....", "...O......", ".......O..", ".........."},
    {"...XO.....", "..XO......", ".XO.......", "XO........", "O.........",
     "..........", "..........", "..........", "..........", ".........."},
    {".......O..", "..........", "...O......", "..........", "...OO.....",
     "....O..X..", "......X...", ".....X....", "....X.....", "...X......"},
    {"..........", "..........", "..........", ".X........", "....X.....",
     ".O......X.", "..O....X..", "...O......", "....O.....", ".....O...."}};

static void redrawBoard(const std::vector<std::string> &vector, Game &game) {
    std::vector<std::pair<int, int>> xMoves;
    std::vector<std::pair<int, int>> oMoves;
    for (int i = 0; i < int(vector.size()); i++) {
        for (int j = 0; j < int(vector[i].size()); j++) {
            if (vector[i][j] == game.x) {
                xMoves.emplace_back(i, j);
            }
            if (vector[i][j] == game.o) {
                oMoves.emplace_back(i, j);
            }
        }
    }
    for (int i = 0; i < int(xMoves.size()); i++) {
        game.make_move(oMoves[i]);
        game.new_move();
        game.make_move(xMoves[i]);
        game.new_move();
    }
    if (oMoves.size() != xMoves.size()) {
        game.make_move(oMoves.back());
        game.new_move();
    }
}

TEST_CASE("Is board completed tests") {
    for (int i = 0; i < int(newBoards.size()); i++) {
        Game game;
        redrawBoard(newBoards[i], game);
        if (i == 3 || i == 4) {
            CHECK(game.is_board_completed());
        } else {
            CHECK(!game.is_board_completed());
        }
    }
}

TEST_CASE("Is game finished tests") {
    for (int i = 0; i < int(newBoards.size()); i++) {
        Game game;
        redrawBoard(newBoards[i], game);
        if (i >= 3) {
            CHECK(game.is_game_finished());
        } else {
            CHECK(!game.is_game_finished());
        }
    }
}

TEST_CASE("Is win tests") {
    for (int i = 0; i < int(newBoards.size()); i++) {
        Game game;
        redrawBoard(newBoards[i], game);
        if (i > 3) {
            CHECK(game.is_win());
        } else {
            CHECK(!game.is_win());
        }
    }
}

TEST_CASE("Is draw tests") {
    for (int i = 0; i < int(newBoards.size()); i++) {
        Game game;
        redrawBoard(newBoards[i], game);
        if (i == 3) {
            CHECK(game.is_draw());
        } else {
            CHECK(!game.is_draw());
        }
    }
}

TEST_CASE("Multi game tests") {
    Game game1;
    Game game2;
    game1.make_move({0, 0});
    CHECK(!game1.is_correct_move({0, 0}));
    CHECK(game2.is_correct_move({0, 0}));
}

}  // namespace tictactoe
