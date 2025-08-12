# Project 1: $\mathrm{PZ\ 2048}$

> SJTU CS1958-01 2025Fall 第一次大作业

## 内容简介

在本次作业中，你需要实现一个2048小游戏（如果你不知道2048是什么，你可以参考 [2048](https://2048game.com/)）。

通行版2048的规则主要有以下几条：

> 1.游戏在 4 \* 4 的方格棋盘上进行。
>
> 2.两个玩家，其中一个可以移动棋盘上的数字，记做 M ，另外一个可以向棋盘上放数字，记做 C ,在经典规则中，玩家 C 由电脑随机行动。
>
> 3.移动数字的规则如下:可以向上/下/左/右四个方向的其中之一移动。选定好方向后，所有数字都会向该方向靠拢，相同的两个数字相撞时会合并成一个新数字，这个数字是它们的和。在一次移动中，每个数字最多只能合并一次，优先合并靠近移动方向棋盘边缘的数字。
>
> 以 2*4 的棋盘举例如下(0 表示该位置为空):
>
> 2 2 2 2
>
> 2 2 0 2
>
> 向左移动后变为
>
> 4 4 0 0
>
> 4 2 0 0
>
> 每次合并后，将会获得一定的分数，获得的分数等于所有合并后数字相加之和。若无任何合并发生，则不得分。在上例中得分为 12。
>
> 移动前后，若棋盘上的所有数字大小和位置均没有变化，则不算做有效移动，否则即是有效移动。
>
> 4.向棋盘放置数字的规则如下:只能在棋盘上没有数字的位置放置一个数字，10% 的几率放置一个 4,90% 的几率放置一个 2，放置在每个空位的几率均等。
>
> 5.游戏开始时棋盘为空，分数为0。先由玩家 C 行动两步，接着玩家 M 和 C 轮流行动，中间的每一步都必须是有效的。当轮到玩家 M 时，若不能够进行有效移动，则游戏结束，此时的得分为最终得分。若某一时刻，棋盘上出现了2048，则玩家 M 胜利，如果一直没有出现 2048，则玩家 M 失败。

在这次大作业中，我们已经实现了这个项目的大部分内容，大致如下：

```
PZ2048/
├── CMakeLists.txt           # CMake 构建配置
├── README.md                # 项目说明
├── src/                     # 源代码
│   ├── game_logic.cpp       # 游戏核心逻辑
│   ├── game_logic_test.cpp  # 游戏逻辑测试
│   ├── user_logic.cpp       # 用户相关逻辑
│   ├── user_logic_test.cpp  # 用户逻辑测试
│   ├── server.cpp           # 服务端入口
│   ├── utils.cpp            # 工具函数
│   └── include/             # 头文件
│       ├── common.h
│       ├── game_logic.h
│       ├── user_logic.h
│       └── utils.h
├── testcase/                # 测试用例输入输出
│   ├── input
│   ├── output
│   └── ans
├── third_party/             # 第三方库
│   ├── asio-1.30.2/         # ASIO 网络库
│   └── Crow/                # Crow Web 框架
└── web/                     # 前端页面
    ├── index.html
    ├── app.js
    └── style.css
```

对此，你需要做的，是在基础部分和拓展部分分别完成 `game_logic.cpp`与`user_logic.cpp`，其中可能用到的常量、变量与函数以及它们的功能可以参见 `game_logic.h`，`user_logic.h`，`utils.h`。

## 基础任务

在这一部分，你需要实现通行版规则中电脑端 C 所要扮演的角色。为了方便我们在 `ACMOJ`上提交，我们对规则生成机制进行了一些修改，比如引入了随机数种子，引入了撤销机制（最多一次，不能连续，要求同时撤回分数与数字），不再限制2048的棋盘为 4 \* 4等等。总体来说，你需要实现`game_logic.cpp`中的所有函数，具体功能详见`game_logic.h`与`game_logic.cpp`.

## 拓展任务

这一步部分你需要实现通行版规则中玩家端 M 所要扮演的角色。完成 `user_logic.cpp`，这一函数的效果是仿照人工~~智障~~智能来帮助人更好地进行决策。你需要完成的核心是`PZ2048::Decide()`函数，现在给出的函数实现的效果是一直向上，这样做的得分效率显然比较低下，也不可能通关。

为此，请你优化 `PZ2048::Decide()` 函数，获取更高的平均得分。注意你无需给出必胜决策/最优决策，你只要做一些更 optimal 的调整即可，比如：

```
1. 按照下 > 左 > 右 > 上的优先级对棋盘进行操作
2. 优先上；否则若左右均可移动，则预测移动后的空单元格数量，选择保留更多空格的方向；若仅左或右可行，则直接选择可行方向；若左右均不可行，则最后尝试向下移动
3. Expectimax 算法
```

这些做法完全不唯一，在此我们提供我们实现过的一些方法供各位参考 ，请点击 [Here](https://notes.sjtu.edu.cn/AT7a_9C7SF2fpmOflkq3DQ?both)。当然我们更希望大家能够自行查阅互联网对自己的函数进行改进,比如参考[Here](https://stackoverflow.com/questions/22342854/what-is-the-optimal-algorithm-for-the-game-2048/22389702#22389702)，请在修改完你的函数后，在 wsl 中运行 ``user_logic_test.cpp`` 来得到你的 Average Score与得分，最后请在 ACMOJ 上进行打榜测试，请你修改你的函数来获取更高的得分！

**WARNING:** 在此期间，不允许使用撤销操作，一旦被发现，本部分分数将作零分处理。

## 须知

### 截止时间

第四周周日（10/13）24:00

### 如何完成程序

你有两种方式下载该仓库完成作业：

1. 在 GitHub 页面点击 Code - Download ZIP，仓库代码将会被下载到本地，随后你可以直接在本地仓库上进行编辑。
2. 若你掌握 Git 的使用，你可以 clone 该仓库进行操作，或者以该仓库为 Template 创建自己的仓库，在自己的仓库中进行操作（我们推荐使用最后一种操作方式）。

### 本地编译与运行

本项目将在 wsl 中运行，

对于 Basic 部分而言，请你在完成 `game_logic.cpp` 之后打开 wsl 的根目录，依次执行以下命令：

```
cd PZ2048         # 如果当前目录已在PZ2048 下可跳过
rm -rf build/ && mkdir build && cd build
cmake ..
```

到这里位置编译就完成了,下面继续运行：

```
make server
./server
```

**同时**请打开新的wsl窗口，注意不要关闭原来的窗口，在新的 wsl 中输入：

```
cd PZ2048          # 如果当前目录已在PZ2048下可跳过
cd web
python3 -m http.server 8000
```

然后打开浏览器，输入网址 `http://localhost:8000/`,你就能够看到你的程序在网页端生成的效果；可以通过这种方式对你的程序直观进行调试与游玩。

同时我们在下发的`testcase`文件中提供了部分样例供各位调试,其中可能会碰到路径问题，请自行在`testcase`文件夹下新建`output`文件夹；然后请你在完成 `game_logic.cpp` 后，打开 wsl 的根目录，依次执行以下命令：

```
cd PZ2048         # 如果当前目录已在PZ2048 下可跳过
rm -rf build/ && mkdir build && cd build
cmake ..
make game_logic_test
./game_logic_test
```
然后在终端将会出现形如下方的界面：
```
Case 1: Output matches, test passed!
Case 2: Output matches, test passed!
Case 3: Output matches, test passed!
Case 4: Output matches, test passed!
Case 5: Output matches, test passed!
All cases passed!
```
------------------------------------------------------------------------------

对于 Extension 部分而言，请你在完成 `user_logic.cpp` 后，打开 wsl 的根目录，依次执行以下命令：

```
cd PZ2048          # 如果当前目录已在PZ2048下可跳过
rm -rf build/ && mkdir build && cd build
cmake ..
make user_logic_test
./user_logic_test
```

然后在终端将会出现形如下方的界面：
```
Average score over 10000 games: 2307.89
Average steps over 10000 games: 199.08
Total run time: 7896 ms
Score by formula: 57
```

这便说明编译并运行成功了.

### 提交方式

请各位自行测试无误后将`game_logic.cpp`和`user_logic.cpp`分别提交到 [Basic](https://acm.sjtu.edu.cn/OnlineJudge/problem/2783) 与 [Extension](https://acm.sjtu.edu.cn/OnlineJudge/problem/2784) 即可.

### 评分规则

本项目 Basic 占 55%，Extension 占 30%，Code Review 占 20%。

对于 Basic 部分，只要你正确完成了 2048 的游戏逻辑，包括移动规则、计分规则、撤销规则，你就能完全获得这部分的分数，折合总分 55pts。

对于 Extension 部分，我们制定了以下公式用来换算你在本部分获得的分数:

$$
\begin{cases}
0, & \text{score} < 1000 \\\\
\left\lceil \dfrac{score^2}{2 \times 10^5} \right\rceil + 30, & 1000 \leq score < 3000 \quad (35\text{-}75\text{ pts}) \\\\
\left\lceil 12.27 \log_2\left(\dfrac{score}{1000}\right)  + 55.55\right\rceil, & 3000 \leq score < 8000 \quad (75\text{-}93\text{ pts}) \\\\
\min \left( \left\lceil 42.92 \sqrt{ \log_2 \left( \dfrac{score}{1000} \right) }  + 18.16\right\rceil, 110 \right), & score \geq 8000 \quad (93\text{-}110\text{ pts})
\end{cases}
$$

对于 Code Review 部分，我们将会考察包括但不限于：

* game_logic.cpp 中函数的具体实现细节
* 项目的框架结构布置
* git 与 linux 命令行的实践操作以及部分命令的含义

理论上的总分是115pts，但是你的得分上限为 105pts，你在 Extension 部分溢出的分数直接算入大作业总分。

## Acknowledgement
特别感谢2024级ACM孔繁亚，他不仅对这个项目框架进行了重构并且为我们的项目提供了`Web`服务器。

同时感谢 2024级龚王博，2024级黄佳瑞，2024级刘宇轩以及2024级ACM王翰宁，2024级ACM王越天以及ACM班的`MineSweeper`项目的开发者，他们对这个项目的IDEA、代码框架、评分标准、平台的可移植性、压力测试上提供了许多宝贵的改进建议，特此感谢。

感谢2025级黄捷航与2025级ACM赵睿城指出项目中 `Undo()` 函数及其相关数据点的错误，特此感谢。

如有问题请联系本项目的发布者`PhantomPhoenix`, 他的邮箱地址是: `logic_1729@sjtu.edu.cn`
