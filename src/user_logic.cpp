#include <algorithm>
#include "include/user_logic.h"

#include "include/utils.h"
#include "include/game_logic.h"

namespace PZ2048 {

// You can add global variables here.
// If your IDE suggested some identifiers like "static", "inline" or "extern", you'd better learn about them
// and decide whether, how and where to use them.
// Or if you want to use type aliases, structures, classes or something else,
// just go ahead! You are free (and encouraged) to use them to make your code clearer and more integrated.
// Just don't modify the signatures of existing functions.

// You are free to add helper functions.

// Don't try to use extern variables from game_logic.cpp. You're not supposed to communicate through this way.
// After all, the game logic on the online judger won't contain extern variables same as yours.

using std::find;

static int row_num = 0, col_num = 0;
static std::vector<std::vector<int>> board;

void ClientPrepare(int r, int c) {
    row_num = r;
    col_num = c;
    board.assign(row_num, std::vector<int>(col_num, 0));
}

void ReadBoard() {
    for (int i = 0; i < row_num; ++i) {
        for (int j = 0; j < col_num; ++j) {
            std::cin >> board[i][j];
        }
    }
}

char Decide() {
    // 0=w, 1=s, 2=a, 3=d
    static const char dir_map[4] = {'w', 's', 'a', 'd'};
    static int currentDirection = 0;
    int directions[4] = {0, 2, 1, 3}; // W, A, S, D
    int attempts = 0;
    while (attempts < 4) {
        int direction = directions[currentDirection % 4];
        currentDirection++;
        // 检查该方向是否能移动
        std::vector<std::vector<int>> test_board = board;
        bool moved = false;
        if (direction == 0) { // w
            for (int j = 0; j < col_num; ++j) {
                int t = 0;
                std::vector<int> arr(row_num, 0);
                for (int i = 0; i < row_num; ++i) {
                    if (test_board[i][j] > 0) arr[t++] = test_board[i][j];
                }
                for (int i = 0; i + 1 < t; ++i) {
                    if (arr[i] == arr[i + 1]) {
                        arr[i] *= 2;
                        arr[i + 1] = 0;
                        ++i;
                    }
                }
                int idx = 0;
                for (int i = 0; i < t; ++i) {
                    if (arr[i] > 0) test_board[idx++][j] = arr[i];
                }
                while (idx < row_num) test_board[idx++][j] = 0;
                for (int i = 0; i < row_num; ++i) {
                    if (test_board[i][j] != board[i][j]) moved = true;
                }
            }
        } else if (direction == 1) { // s
            for (int j = 0; j < col_num; ++j) {
                int t = 0;
                std::vector<int> arr(row_num, 0);
                for (int i = row_num - 1; i >= 0; --i) {
                    if (test_board[i][j] > 0) arr[t++] = test_board[i][j];
                }
                for (int i = 0; i + 1 < t; ++i) {
                    if (arr[i] == arr[i + 1]) {
                        arr[i] *= 2;
                        arr[i + 1] = 0;
                        ++i;
                    }
                }
                int idx = row_num - 1;
                for (int i = 0; i < t; ++i) {
                    if (arr[i] > 0) test_board[idx--][j] = arr[i];
                }
                while (idx >= 0) test_board[idx--][j] = 0;
                for (int i = 0; i < row_num; ++i) {
                    if (test_board[i][j] != board[i][j]) moved = true;
                }
            }
        } else if (direction == 2) { // a
            for (int i = 0; i < row_num; ++i) {
                int t = 0;
                std::vector<int> arr(col_num, 0);
                for (int j = 0; j < col_num; ++j) {
                    if (test_board[i][j] > 0) arr[t++] = test_board[i][j];
                }
                for (int j = 0; j + 1 < t; ++j) {
                    if (arr[j] == arr[j + 1]) {
                        arr[j] *= 2;
                        arr[j + 1] = 0;
                        ++j;
                    }
                }
                int idx = 0;
                for (int j = 0; j < t; ++j) {
                    if (arr[j] > 0) test_board[i][idx++] = arr[j];
                }
                while (idx < col_num) test_board[i][idx++] = 0;
                for (int j = 0; j < col_num; ++j) {
                    if (test_board[i][j] != board[i][j]) moved = true;
                }
            }
        } else if (direction == 3) { // d
            for (int i = 0; i < row_num; ++i) {
                int t = 0;
                std::vector<int> arr(col_num, 0);
                for (int j = col_num - 1; j >= 0; --j) {
                    if (test_board[i][j] > 0) arr[t++] = test_board[i][j];
                }
                for (int j = 0; j + 1 < t; ++j) {
                    if (arr[j] == arr[j + 1]) {
                        arr[j] *= 2;
                        arr[j + 1] = 0;
                        ++j;
                    }
                }
                int idx = col_num - 1;
                for (int j = 0; j < t; ++j) {
                    if (arr[j] > 0) test_board[i][idx--] = arr[j];
                }
                while (idx >= 0) test_board[i][idx--] = 0;
                for (int j = 0; j < col_num; ++j) {
                    if (test_board[i][j] != board[i][j]) moved = true;
                }
            }
        }
        if (moved) {
            return dir_map[direction];
        }
        attempts++;
    }
    // 所有方向都无法移动，返回'w'
    return 'w';
}

}

