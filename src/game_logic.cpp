#include "include/game_logic.h"
//WARNING: DO NOT DELETE THE THREE LINES BELOW!
//WHEN YOU PUT YOUR CODE TO ACMOJ, YOU WOULD DELETE THE LINE 1 AND USE LINE 4-6 INSTEAD 
//#include "game_logic.h"
//#include "utils.h"
//#include "utils.cpp"

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
// You are free to add helper functions.

void Start(int row_num, int col_num, int target, uint game_seed) {
    /** implement here. **/
}

std::pair<int, int> EndGame() {
    /** implementation here **/
}

int GetRows() {
    /** implementation here **/
}

int GetCols() { 
    /** implementation here **/
}

bool TryRun(char dir) {
    /** implementation here **/
}

bool Undo() {
    /** implement here. **/
    /**in the process you need to undo the operation and both the score**/
    /**for example we have 0 0 0 4 4pts from 2 0 0 2 0pts, after we undo, we get 2 0 0 2 0pts**/
}

void SetTile(int row_index, int col_index, int value) {
    /** implement here. **/
}

int GetTile(int row_index, int col_index) {
    /** implement here. **/
}

int Score() { 
    /** implement here. **/ 
}

int Steps() { 
    /** implement here. **/ 
}

int GetTarget() { 
    /** implement here. **/ 
}

bool HasReachedTarget() {
    /** implement here. **/
}

bool Stuck() {
    /** implement here. **/
}

void PrintBoard() {
    /** implement here. **/
    /** Hint: You MUST USE std:cout **/
    /** Hint: When you print the board, you have to use 1 space to split the number**/
    /** Hint: More Specifically, you have to open *.ans to check whether your output format is correct**/
}

}
