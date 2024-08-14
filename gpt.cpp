#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct myleft {
    int M;  // 传教士数量
    int C;  // 食人族数量
    myleft(int m, int c) : M(m), C(c) {}

    // 比较运算符用于集合(set)中保存状态
    bool operator<(const myleft& other) const {
        if (M != other.M) return M < other.M;
        return C < other.C;
    }
};

// 五种可能的移动方式
myleft action[5] = {myleft(0, 1), myleft(1, 0), myleft(1, 1), myleft(0, 2),
                    myleft(2, 0)};

// 判断当前状态是否合法
bool right_state(myleft left) {
    // 检查是否超出边界条件
    if (left.C < 0 || left.M < 0 || left.C > 3 || left.M > 3) {
        return false;
    }

    // 检查左岸和右岸是否满足条件
    if ((left.M >= left.C || left.M == 0) &&
        (3 - left.M >= 3 - left.C || 3 - left.M == 0)) {
        return true;
    }

    return false;
}

// 深度优先搜索 (DFS) 算法
bool dfs(myleft left, bool boat, set<pair<myleft, bool>>& visited, int depth) {
    // 目标状态：左岸为(0, 0)，即所有传教士和食人族都到达了右岸
    if (left.M == 0 && left.C == 0) {
        cout << "Solution found in " << depth << " steps!" << endl;
        return true;
    }

    // 检查当前状态是否已被访问
    if (visited.find({left, boat}) != visited.end()) {
        return false;
    }

    // 标记当前状态为已访问
    visited.insert({left, boat});

    // 尝试所有可能的移动方式
    for (int i = 0; i < 5; ++i) {
        myleft new_left = left;

        // 根据船的位置决定人员的移动方向
        if (boat == false) {  // 船在左岸
            new_left.M -= action[i].M;
            new_left.C -= action[i].C;
        } else {  // 船在右岸
            new_left.M += action[i].M;
            new_left.C += action[i].C;
        }

        // 检查新状态是否合法
        if (right_state(new_left)) {
            // 切换船的位置
            bool new_boat = !boat;

            // 递归地进行深度优先搜索
            if (dfs(new_left, new_boat, visited, depth + 1)) {
                cout << "Move: (" << action[i].M << " missionaries, "
                     << action[i].C << " cannibals) ";
                cout << (boat ? "from right to left" : "from left to right")
                     << endl;
                return true;
            }
        }
    }

    return false;
}

int main() {
    // 初始状态：3个传教士和3个食人族在左岸，船在左岸
    myleft left(3, 3);
    bool boat = false;                // false == left, true == right
    set<pair<myleft, bool>> visited;  // 用于保存访问过的状态

    // 开始深度优先搜索
    if (!dfs(left, boat, visited, 0)) {
        cout << "No solution found!" << endl;
    }

    return 0;
}
