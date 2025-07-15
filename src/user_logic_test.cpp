#include "include/game_logic.h"
#include "include/user_logic.h"

#include <chrono>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace PZ2048;

void SingleTest() {
    int row_num, col_num;
    uint seed;
    int target = 2048;
    std::cin >> row_num >> col_num >> seed;

    ClientPrepare(row_num, col_num);
    Start(row_num, col_num, target, seed);
    while(true) {

        std::ostringstream oss;
        auto *obuf = std::cout.rdbuf(oss.rdbuf()); // redirect std::cout.

        PrintBoard();

        std::istringstream iss(oss.str());
        std::cout.rdbuf(obuf);                     // reset std:cout.
        auto *ibuf = std::cin.rdbuf(iss.rdbuf());  // redirect std::cin.

        ReadBoard();                               // read what PrintBoard() has output.

        std::cin.rdbuf(ibuf);                      // reset std::cin.

        char oper = Decide();
        // must be a valid move. No undo allowed. No Steins-Gate.
        if(oper != 'w' && oper != 's' && oper != 'a' && oper != 'd') {
            std::cout << " Invalid Operation.\n";
            continue;
        }

        TryRun(oper);

    /*
    if(flag) {
      std::cout << "Operation succeeded.\n";
    } else {
      std::cout << "Operation failed.\n";
    }
    std::cout << RowNum() << ' ' << ColNum() << ' ' << Steps() << ' ' << Score() << '\n';
    PrintBoard();
    */

    if(HasReachedTarget()) {
      std::cout << "You've merged an 2048 tile!\n";
      auto [steps, score] = EndGame();
      std::cout << "Steps: " << steps << "\nScore: " << score << '\n';
      std::cout << "Final Score: " << score << std::endl;
      break;
    }
    if(Stuck()) {
      std::cout << "You've stuck.\n";
      auto [steps, score] = EndGame();
      std::cout << "Steps: " << steps << "\nScore: " << score << '\n';
      std::cout << "Final Score: " << score << std::endl;
      break;
    }
  }
}

int main() {
    auto start_time = std::chrono::steady_clock::now();
    int total_score = 0;
    int total_steps = 0;
    int games = 10000;
    int target = 2048;
    int row_num = 4, col_num = 4;
    for (int i = 0; i < games; ++i) {
        uint seed = i + 1;
        ClientPrepare(row_num, col_num);
        Start(row_num, col_num, target,seed);
        while (true) {
            std::ostringstream oss;
            auto *obuf = std::cout.rdbuf(oss.rdbuf());
            PrintBoard();
            std::istringstream iss(oss.str());
            std::cout.rdbuf(obuf);
            auto *ibuf = std::cin.rdbuf(iss.rdbuf());
            ReadBoard();
            std::cin.rdbuf(ibuf);
            char oper = Decide();
            if (oper != 'w' && oper != 's' && oper != 'a' && oper != 'd') {
                continue;
            }
            TryRun(oper);
            if (HasReachedTarget()) {
                auto [steps, score] = EndGame();
                total_score += score;
                total_steps += steps;
                break;
            }
            if (Stuck()) {
                auto [steps, score] = EndGame();
                total_score += score;
                total_steps += steps;
                break;
            }
        }
    }
    auto end_time = std::chrono::steady_clock::now();
    double avg_score = total_score * 1.0 / games;
    double avg_steps = total_steps * 1.0 / games;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Average score over " << games << " games: " << avg_score << std::endl;
    std::cout << "Average steps over " << games << " games: " << avg_steps << std::endl;
    std::cout << "Total run time: " << ms << " ms" << std::endl;
    std::cout.flush();

    // 按公式输出分数
    int final_score = static_cast<int>(avg_score + 0.5);
    int output_pts = 0;
    if (final_score < 1000) {
        output_pts = 0;
    } else if (final_score < 3000) {
        output_pts = static_cast<int>(std::ceil(final_score * final_score / 200000.0)) + 30;
    } else if (final_score < 8000) {
        output_pts = static_cast<int>(std::ceil(12.27 * std::log2(final_score / 1000.0) + 55.55));
    } else {
        output_pts = std::min(static_cast<int>(std::ceil(42.92 * std::sqrt(std::log2(final_score / 1000.0)) + 18.16)), 110);
    }
    std::cout << "Score by formula: " << output_pts << std::endl;
    std::cout.flush();
    return 0;
}
