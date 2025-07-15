#include "include/game_logic.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace PZ2048;

// Forward declaration for helper
void PrintBoardToStream(std::ostream &os);

void check_target(int &target) {
    if(target <= 4) {
        target = 8;
        std::cout << "Target too low. Automatically changed target to 8.\n";
        return;
    }
    if(target > 8192) {
        target = 8192;
        std::cout << "Target too large. Automatically changed target to 8192.\n";
        return;
    }
    int cnt = 0, tmp = target;
    while(tmp > 0) {
        cnt++;
        tmp >>= 1;
    }
    if(target != (1 << (cnt - 1))) {
        target = 1 << cnt;
        std::cout << "Target is not a power of 2. Automatically changed target to " << target << ".\n";
    }
}

int main() {
  bool all_passed = true;
  // 获取项目根目录（假定可执行文件在 build/ 下，项目根目录为其上一级）
  std::string root_path = "..";
  for (int case_id = 1; case_id <= 5; ++case_id) {
    std::string in_path = "../testcase/input/" + std::to_string(case_id) + ".in";
    std::string out_path = "../testcase/output/" + std::to_string(case_id) + ".out";
    std::string ans_path = "../testcase/ans/" + std::to_string(case_id) + ".ans";
    std::ifstream fin(in_path);
    std::ofstream fout(out_path);
    if (!fin.is_open() || !fout.is_open()) {
      std::cerr << "Failed to open input or output file for case " << case_id << "!\n";
      all_passed = false;
      continue;
    }
    int row_num, col_num, target;
    unsigned int seed;
    fin >> row_num >> col_num >> target >> seed;
    check_target(target);
    Start(row_num, col_num, target,seed);
    int index = 0;
    fout << '[' << index << "] ";
    fout << "Steps: " << Steps() << " Score: " << Score() << '\n';
    PrintBoardToStream(fout);
    while (true) {
      char oper;
      fin >> oper;
      if (fin.eof()) break;
      if (oper == ' ' || oper == '\n' || oper == '\r') continue;
      if (oper == '#') break;
      index++;
      fout << '[' << index << "] ";
      bool flag;
      if (oper == 'z') {
        fout << "Tried to undo previous operation.";
        flag = Undo();
      } else {
        switch (oper) {
          case 'w': fout << "Swiped upward."; break;
          case 'a': fout << "Swiped leftward."; break;
          case 's': fout << "Swiped downward."; break;
          case 'd': fout << "Swiped rightward."; break;
          default: fout << "Invalid operation.\n"; continue;
        }
        flag = TryRun(oper);
      }
      if (flag) {
        fout << " Operation succeeded.\n";
      } else {
        fout << " Operation failed.\n";
      }
      fout << "Steps: " << Steps() << " Score: " << Score() << '\n';
      PrintBoardToStream(fout);
      if (HasReachedTarget()) {
        fout << "You've merged a " << target << " tile!\n";
        break;
      }
      if (Stuck()) {
        fout << "You've stuck.\n";
        break;
      }
    }
    fout << "Game ended.\n";
    auto [steps, score] = EndGame();
    fout << "Steps: " << steps << "\n" << "Score: " << score << '\n';
    fin.close();
    fout.close();
    // 比对答案
    std::ifstream fans(ans_path);
    std::ifstream fout2(out_path);
    if (!fans.is_open() || !fout2.is_open()) {
      std::cerr << "Failed to open answer or output file for case " << case_id << "!\n";
      all_passed = false;
      continue;
    }
    std::string sans, sout;
    bool correct = true;
    int line_num = 1;
    while (std::getline(fans, sans) && std::getline(fout2, sout)) {
      // 去除所有空白字符
      sans.erase(std::remove_if(sans.begin(), sans.end(), ::isspace), sans.end());
      sout.erase(std::remove_if(sout.begin(), sout.end(), ::isspace), sout.end());
      if (sans != sout) {
        std::cout << "Case " << case_id << " Mismatch at line " << line_num << ":\nExpected: " << sans << "\nYour output: " << sout << '\n';
        correct = false;
      }
      ++line_num;
    }
    if (correct) std::cout << "Case " << case_id << ": Output matches, test passed!\n";
    else {
      std::cout << "Case " << case_id << ": Output mismatch, please check!\n";
      all_passed = false;
    }
    fans.close();
    fout2.close();
  }
  if (all_passed) std::cout << "All cases passed!\n";
  else std::cout << "Some cases failed.\n";
  return 0;
}

// Helper function for board output
void PrintBoardToStream(std::ostream &os) {
  for (int i = 0; i < GetRows(); ++i) {
    for (int j = 0; j < GetCols(); ++j) {
      os << GetTile(i, j) << ' ';
    }
    os << '\n';
  }
}