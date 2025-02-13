/*

AC自动机 多模式串匹配（KMP是一个模式串 + 一个文本串）
类似 Trie 上加了 fail 指针 匹配失败后根据 fail 指针跳转
fail 指针指向当前节点表示的串的最长后缀
比如 hello 在 o 处的 fail 指针 就尝试链接到 ello llo lo 等
具体构建方法参考资料

*/

#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

// copied from: https://oi-wiki.org/string/ac-automaton/
namespace aho_corasick {

using namespace std;

constexpr int N = 2e5 + 6; // 模式串数量 pattern
constexpr int LEN = 2e6 + 6; // 文本串长度 text
constexpr int SIZE = 2e5 + 6; // 模式串总长度 pattern total

struct Node {
    int son[26];
    int ans;
    int fail;
    int idx;

    void init() {
        memset(son, 0, sizeof(son));
        ans = idx = 0;
    }
} tr[SIZE];

int tot;
int ans[N], pidx;

vector<int> g[SIZE];  // fail 树

void init() {
    tot = pidx = 0;
    tr[0].init();
}

void insert(char s[], int &idx) {
    int u = 0;
    for (int i = 1; s[i]; i++) {
        int &son = tr[u].son[s[i] - 'a'];
        if (!son) son = ++tot, tr[son].init();
        u = son;
    }
    // 由于有可能出现相同的模式串，需要将相同的映射到同一个编号
    if (!tr[u].idx) tr[u].idx = ++pidx;  // 第一次出现，新增编号
    idx = tr[u].idx;  // 这个模式串的编号对应这个结点的编号
}

void build() {
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (tr[0].son[i]) {
            q.push(tr[0].son[i]);
            g[0].push_back(tr[0].son[i]);  // 不要忘记这里的 fail
        }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (tr[u].son[i]) {
                tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
                g[tr[tr[u].fail].son[i]].push_back(tr[u].son[i]);  // 记录 fail 树
                q.push(tr[u].son[i]);
            } else
                tr[u].son[i] = tr[tr[u].fail].son[i];
        }
    }
}

void query(char t[]) {
    int u = 0;
    for (int i = 1; t[i]; i++) {
        u = tr[u].son[t[i] - 'a'];
        tr[u].ans++;
    }
}

void dfs(int u) {
    for (int v : g[u]) {
        dfs(v);
        tr[u].ans += tr[v].ans;
    }
    ans[tr[u].idx] = tr[u].ans;
}
}  // namespace aho_corasick

int aho_corasick_toolkit() {
    char s[aho_corasick::LEN]; // text
    int idx[aho_corasick::N]; // 有 n 个模式串 但是其中可能存在重复 idx[i] 表示第 i 个模式串的编号（相同模式串归为同一个编号）
    int n;

    aho_corasick::init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1); // 1-indexed
        aho_corasick::insert(s, idx[i]); // 插入模式串 i 然后得到其编号（idx[i]）
        aho_corasick::ans[i] = 0; // idx 为 i 的模式串匹配命中的次数
    }
    aho_corasick::build(); // 全部模式串 insert 后 执行 build

    scanf("%s", s + 1); // text, 1-indexed
    aho_corasick::query(s); // 执行匹配
    aho_corasick::dfs(0); // 优化

    // 输出结果
    for (int i = 1; i <= n; i++) {
        printf("%d\n", aho_corasick::ans[idx[i]]); // 输出第 i 个模式串匹配命中的次数
    }
    return 0;
}