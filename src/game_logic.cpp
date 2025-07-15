#include "include/game_logic.h"

#include <iomanip>
#include <iostream>

namespace PZ2048 {

// You can add global variables here.
// If your IDE suggested some identifiers like "static", "inline" or "extern", you'd better learn about them
// and decide whether, how and where to use them.
// Or if you want to use type aliases, structures, classes or something else,
// just go ahead! You are free (and encouraged) to use them to make your code clearer and more integrated.
// Or... can you?
// Just don't modify the signatures of existing functions.

// Don't try to use extern variables from user_logic.cpp. You're not supposed to communicate through this way.
// After all, the game logic on the online judger won't contain extern variables same as yours.

static int rows, cols, steps, score, prev_steps, prev_score, puzzle_target;
static std::vector<std::vector<int>> board, prev_board;
static bool prev_valid;

// You are free to add helper functions.

void Start(int row_num, int col_num, int target, uint game_seed) {
  /** implement here. **/
}

std::pair<int, int> EndGame() {
  /** implementation here **/
  return {steps, score};
}

int GetRows() { return rows; }

int GetCols() { return cols; }

bool TryRun(char dir) {
  /** implementation here **/
}

bool Undo() {
 /** implement here. **/
}

void SetTile(int row_index, int col_index, int value) {
  /** implement here. **/
}

int GetTile(int row_index, int col_index) {
  /** implement here. **/
}

int Score() { return score; }

int Steps() { return steps; }

int GetTarget() { return puzzle_target; }

bool HasReachedTarget() {
  /** implement here. **/
}

bool Stuck() {
  /** implement here. **/
}

void PrintBoard() {
 /** implement here. **/
}

}