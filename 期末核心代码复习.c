 
> **一句话框架**：用三个指针，把每个节点的箭头掰向左边。
> **适用变形**：逆序输出链表、判断回文链表。

```c
// 假设链表节点长这样
// struct ListNode {
//     int val;
//     struct ListNode *next;
// };

struct ListNode* reverseList(struct ListNode* head){
    struct ListNode *prev = NULL;   // 前一个节点，头结点前面是NULL
    struct ListNode *curr = head;   // 当前要掰的节点
    
    while (curr != NULL) {
        struct ListNode *nextTemp = curr->next; // 先记下后一个节点，不然等会找不到了
        curr->next = prev;          // 反向掰：原来指向后，现在指向前
        prev = curr;                // 前指针往后走
        curr = nextTemp;            // 当前指针也往后走
    }
    return prev;                    // prev就是新头结点
}
```

---

## 2. 括号匹配（栈）
> **一句话框架**：遇左括号入栈，遇右括号就和栈顶配对，配不上就是错。
> **适用变形**：表达式求值、括号生成合法性。

```c
// 用数组模拟栈，简单到爆炸
bool isValid(char * s){
    char stack[10000];             // 栈数组，大小看题目
    int top = -1;                  // 栈顶，-1表示空
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            stack[++top] = s[i];   // 左括号直接入栈
        } else {
            if (top == -1) return false;  // 栈空了还来右括号，错
            char left = stack[top--];     // 弹出栈顶左括号
            // 看看它俩配不配，不配就false
            if (left == '(' && s[i] != ')') return false;
            if (left == '{' && s[i] != '}') return false;
            if (left == '[' && s[i] != ']') return false;
        }
    }
    return top == -1;              // 栈空才说明全配上了
}
```

---

## 3. 二叉树递归先序/中序/后序遍历
> **一句话框架**：只需要决定“打印自己”的位置。
> *   先序：自己 -> 左 -> 右
> *   中序：左 -> 自己 -> 右
> *   后序：左 -> 右 -> 自己
> **适用变形**：求高度、求叶子数、求祖先，全是改这个“打印”的位置。

```c
// 假设树节点长这样
// struct TreeNode {
//     int val;
//     struct TreeNode *left;
//     struct TreeNode *right;
// };

// 先序遍历：根左右
void preorder(struct TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->val);      // ①先打印自己
    preorder(root->left);          // ②再处理左边
    preorder(root->right);         // ③最后处理右边
}

// 中序遍历：左根右
void inorder(struct TreeNode* root) {
    if (root == NULL) return;
    inorder(root->left);           // ①先处理左边
    printf("%d ", root->val);      // ②再打印自己
    inorder(root->right);          // ③最后处理右边
}

// 后序遍历：左右根
void postorder(struct TreeNode* root) {
    if (root == NULL) return;
    postorder(root->left);         // ①先处理左边
    postorder(root->right);        // ②再处理右边
    printf("%d ", root->val);      // ③最后打印自己
}
```

---

## 4. 二叉树层次遍历（队列）
> **一句话框架**：排队！根先排，然后排左孩子，再排右孩子，每出来一个就输出。
> **适用变形**：求宽度、判断完全二叉树。

```c
void levelOrder(struct TreeNode* root) {
    if (root == NULL) return;
    struct TreeNode* queue[10000]; // 用数组模拟队列
    int front = 0, rear = 0;
    queue[rear++] = root;          // 根节点入队
    
    while (front < rear) {         // 队列不空就循环
        struct TreeNode* node = queue[front++]; // 队首出队
        printf("%d ", node->val);  // 打印
        if (node->left)  queue[rear++] = node->left;  // 左孩子入队
        if (node->right) queue[rear++] = node->right; // 右孩子入队
    }
}
```

---

## 5. 图的DFS（邻接矩阵/邻接表）
> **一句话框架**：一条路走到黑。走过的点用 `visited` 数组标记，别回头。
> **适用变形**：找连通块、判断图是否连通、拓扑排序。

```c
// 邻接矩阵版，n是顶点个数
int visited[1000];  // 标记数组，0没走过，1走过

void DFS_Matrix(int graph[][1000], int v, int n) {
    visited[v] = 1;                 // 标记为“到了”
    printf("%d ", v);               // 输出访问的顶点
    for (int i = 0; i < n; i++) {
        if (graph[v][i] == 1 && !visited[i]) { // 有边且没走过
            DFS_Matrix(graph, i, n); // 递归进去，一条路走到黑
        }
    }
}
```

---

## 6. 图的BFS
> **一句话框架**：和树的层次遍历一模一样，只是加了个 `visited` 防重复。
> **适用变形**：最短路径长度、迷宫。

```c
void BFS_Matrix(int graph[][1000], int start, int n) {
    int visited[1000] = {0};
    int queue[10000];               // 又是数组模拟队列
    int front = 0, rear = 0;
    
    visited[start] = 1;
    queue[rear++] = start;          // 起点入队
    
    while (front < rear) {
        int v = queue[front++];     // 队首出队
        printf("%d ", v);
        for (int i = 0; i < n; i++) {
            if (graph[v][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;  // 邻居入队
            }
        }
    }
}
```

---

## 7. 快速排序（partition + 递归）
> **一句话框架**：挑一个“老大”，比它小的放左边，比它大的放右边，然后左右分别再找“老大”。
> **适用变形**：找第K大元素。

```c
int partition(int a[], int low, int high) {
    int pivot = a[low];             // 挑最左边的当“老大”
    while (low < high) {
        while (low < high && a[high] >= pivot) high--; // 从右找比老大小的
        a[low] = a[high];           // 扔到左边
        while (low < high && a[low] <= pivot) low++;    // 从左找比老大大的
        a[high] = a[low];           // 扔到右边
    }
    a[low] = pivot;                 // 老大归位
    return low;                     // 返回老大的位置
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int pivotPos = partition(a, low, high); // 切一刀
        quickSort(a, low, pivotPos - 1);        // 左边再切
        quickSort(a, pivotPos + 1, high);       // 右边再切
    }
}
```

---

## 8. 二分查找（非递归）
> **一句话框架**：左指针和右指针赛跑，往中间夹，直到找到目标或挤没地方。
> **适用变形**：找第一个等于x的数、找旋转数组的最小值。

```c
int binarySearch(int a[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {         // 一定要注意，是小于等于
        int mid = left + (right - left) / 2; // 防溢出写法
        if (a[mid] == target)
            return mid;             // 找到了！
        else if (a[mid] < target)
            left = mid + 1;         // 目标在右边，左边界右移
        else
            right = mid - 1;        // 目标在左边，右边界左移
    }
    return -1;                      // 没找到
}
```

---

## 9. 螺旋矩阵（右螺旋阵）
> **一句话框架**：上下左右四个边界，往一个方向走到头，边界缩一格，换方向。
> **适用变形**：蛇形填数、对角线遍历。

```c
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    if (matrixSize == 0) { *returnSize = 0; return NULL; }
    int top = 0, bottom = matrixSize - 1;
    int left = 0, right = matrixColSize[0] - 1;
    int* res = (int*)malloc(sizeof(int) * matrixSize * matrixColSize[0]);
    *returnSize = 0;
    
    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) res[(*returnSize)++] = matrix[top][i]; // 向右
        top++;  // 上面一层走完了，删了
        for (int i = top; i <= bottom; i++) res[(*returnSize)++] = matrix[i][right]; // 向下
        right--;// 右边一列走完了，删了
        if (top > bottom || left > right) break; // 防重复打印
        for (int i = right; i >= left; i--) res[(*returnSize)++] = matrix[bottom][i]; // 向左
        bottom--;// 下面一层走完了，删了
        for (int i = bottom; i >= top; i--) res[(*returnSize)++] = matrix[i][left]; // 向上
        left++; // 左边一列走完了，删了
    }
    return res;
}
```

---

## 10. KMP字符串匹配
> **一句话框架**：给模式串建个“后悔表”（next），匹配失败时不用回退到底，只回溯一点点。
> **适用变形**：重复子串、字符串匹配。

```c
int* getNext(char* p) {
    int m = strlen(p);
    int* next = (int*)malloc(sizeof(int) * m);
    next[0] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && p[i] != p[j]) j = next[j - 1]; // 最重要的一句，找上一个相同前缀
        if (p[i] == p[j]) j++;
        next[i] = j;
    }
    return next;
}

int strStr(char* s, char* p) {
    int n = strlen(s), m = strlen(p);
    if (m == 0) return 0;
    int* next = getNext(p);
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && s[i] != p[j]) j = next[j - 1]; // 和建next时一模一样
        if (s[i] == p[j]) j++;
        if (j == m) { free(next); return i - m + 1; }  // 找到了
    }
    free(next);
    return -1;
}
 
