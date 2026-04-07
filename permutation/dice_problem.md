# 骰子组成数字问题（排列组合 + 去重）

## 问题描述
有三颗六面骰子，每面点数0-9。可以用1颗、2颗或3颗骰子排成一排，顶部点数从左到右组成一个数字（允许前导0，但数值本身会忽略前导0）。问能组成多少种不同的数字？

## 核心思路
1. **枚举所有可能性**：分别考虑1颗、2颗、3颗骰子的情况，注意顺序重要（排列）。
2. **使用vis数组去重**：因为数字最大为999，开一个`vis[1000]`数组标记是否出现过。
3. **统计不同数字的个数**。

## 代码实现（C语言）
```c
#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int dice[3][6];
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 6; j++)
                scanf("%d", &dice[i][j]);

        int vis[1000] = {0};
        int cnt = 0;   //记录数字是否出现过

        // 1颗骰子
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 6; j++) {
                int num = dice[i][j];
                if (!vis[num]) { vis[num] = 1; cnt++; }
            }

        // 2颗骰子（有序对）-------设计排序
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                if (i == j) continue;
                for (int x = 0; x < 6; x++)
                    for (int y = 0; y < 6; y++) {
                        int num = dice[i][x] * 10 + dice[j][y];
                        if (!vis[num]) { vis[num] = 1; cnt++; }
                    }
            }

        // 3颗骰子（全排列）
        int perm[6][3] = {
            {0,1,2}, {0,2,1}, {1,0,2},
            {1,2,0}, {2,0,1}, {2,1,0}
        };
        for (int p = 0; p < 6; p++) {
            int i = perm[p][0], j = perm[p][1], k = perm[p][2];  //编号
            for (int x = 0; x < 6; x++)  //枚举面
                for (int y = 0; y < 6; y++)
                    for (int z = 0; z < 6; z++) {
                        int num = dice[i][x] * 100 + dice[j][y] * 10 + dice[k][z];
                        if (!vis[num]) { vis[num] = 1; cnt++; }
                    }
        }

        printf("%d\n", cnt);
    }
    return 0;
}
