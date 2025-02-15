/*

nim game 是一种公平游戏
n 堆物品，每堆有 a_i 个，两个玩家轮流取走任意一堆的任意个物品，但不能不取
取走最后一个物品的人获胜

代码尚未测试

SG函数的定义、证明和应用

*/

#include <algorithm>
#include <iostream>
#include <vector>

// copied from: https://oi-wiki.org/math/game-theory/impartial-game/
namespace nim {
    using namespace std;

    // 先手是否是必胜状态（是否有必胜策略）
    bool win(const vector<int> &stones) {
        int res = 0;
        for(int i : stones) res ^= i;
        return res;
    }
}