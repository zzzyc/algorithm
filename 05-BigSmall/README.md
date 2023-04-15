> bigsmall 是一种将问题暴力解在其擅长的数据规模下使用的方法，也叫根号分治。

# 牛客练习赛110 G. 嘤嘤的闺蜜
给你一个  $n$  行  $m$  列的矩阵  $a$ , 初始值都为 $0$ , 给一些位置赋值, 之后每次询问给出  t  个数  $b_{1}, \ldots, b_{t}$ , 求  $\sum_{i=1}^{n} \max \left(a_{i b 1}, \ldots, a_{i b t}\right)$  。


# EDU19 E. Array Queries
**题意：**
给定长度为 $n$ 的数组 $a$，初始所有的 $a_i\leq n$ 。$q$ 次询问，每次给定一个 $p$ 和 $k$ ，问需要执行最少几次操作可以使得 $p>n$。
每次操作为：$p=p+a_p+k$

数据范围：$1\leq n, q\leq 10^5, 1\leq a_i,p,k\leq n$

**题解：**
考虑 $k$ 很大的时候，无论 $p$ 多大，都会很快就超过 $n$。
如：$k=\sqrt{n}$，则至多 $\sqrt{n}$ 次操作后，$p$ 就会超过 $n$ 。

对查询进行分类操作，分类依据为 $k$ 的大小：
- 当 $k>\sqrt{n}$ ，直接暴力模拟即可，单次查询复杂度为 $O(\sqrt{n})$
- 当 $k<\sqrt{n}$ ，$f[k][p]$ 表示给定的为 $k$ 和 $p$ 的情况下，超过 $n$ 需要的最小操作次数。这里至多有 $n\sqrt{n}$ 个状态，通过记忆化搜索填满这些状态即可。

**时间复杂度分析：**
- 如果都是 $k>\sqrt{n}$ 这样的操作，复杂度为：$O(n\sqrt{n})$
- 如果都是 $k<\sqrt{n}$ 这样的操作，复杂度为：$O(q\sqrt{n})$，因为 $q$ 和 $n$ 同阶，故复杂度为：$O(n\sqrt{n})$。

则总复杂度为：$O(n\sqrt{n})$ 。

**代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const int M = 317;
int a[N];
int f[M][N];
int n, m, Q;
int p, k;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    m = sqrt(n);

    for (int k = 1; k < m; ++k)
        for (int p = n; p >= 1; --p) {
            if (p == 1) {
                int x = 1;
            }
            if (p + k + a[p] > n) f[k][p] = 1;
            else f[k][p] = f[k][p + k + a[p]] + 1;
        }


    scanf("%d", &Q);
    while (Q--) {
        scanf("%d%d", &p, &k);
        int ans = 0;
        if (k >= m) {
            int now = p;
            while (now <= n) {
                now = now + a[now] + k;
                ans += 1;
            }
        } else {
            ans = f[k][p];
        }
        printf("%d\n", ans);
    }

    return 0;
}
```

# Round201(Div.1) C. Subset Sums
**题意：**
给定一个长度为 $n$ 的数组 $a$，一个长度为 $m$ 的集合数组 $S$，$S[i]$ 表示第 $i$ 个集合。
$q$ 次操作，有两种类型的操作可选：
- 求和：计算 $S[k]$ 中的元素对应在 $a$ 中下标的元素之和，
	即$\sum\limits_{i=1}^{|S[k]|}a[S[k][i]]$
- 更新：将计算$S[k]$ 中的元素对应在 $a$ 中下标的元素都加上 $x$ ，即$a[S[k][i]] = a[S[k][i]]  + x$

数据范围：$1\leq n,m,q\leq 10^5, 1\leq k\leq m,1\leq S[k][i]\leq n,1\leq |a_i|,|x|\leq 10^8$

**题解：**
将集合分为大集合和小集合
- 当 $|S[k]|>cnt$，称为大集合
- 当 $|S[k]|\leq cnt$，称为小集合


构建一些针对大集合的数组：
- $sum[i]$ 表示集合 $S[i]$ 中的所有元素在 $a$ 中下标的元素之和，只有小集合的更新会更新这个数组
- $f[i]$ 表示集合 $S[i]$ 更新的值的总和，只有大集合的更新会更新这个数组
- $g[i][j]$ 表示对大集合 $S[i]$和所有其他集合 $S[j]$ 之间的交集大小，只有大集合有

除此之外：
小集合更新时，会对$a$数组进行更新

我们分别考虑四种更新情况：
- 大集合对大集合
大集合只需要更新 $sum[i]$和 $f[i]$，所以只需要更新 $f[i]$ 即可
- 大集合对小集合
更新 $f[i]$，故当小集合计算时，再额外计算 $f[i]$ 对其影响即可
- 小集合对大集合
小集合更新时，对大集合来说只有 $sum$ 数组有用，故需要 $sum$ 数组
- 小集合对小集合
小集合更新时，对小集合来说求和时需要 $f$ 数组和 $a$ 数组，故需要更新 $a$ 数组

分别考虑对大集合和小集合的操作：
- 对大集合
	- 求和：$sum[i]+\sum\limits_{j=1}^{大集合数量} f[j]\times g[j][i]$
  	- 更新：$f[i] = f[i] + x$
- 对小集合
  - 求和：$(\sum\limits_{j=1}^{|S[i]|}a[S[i][j]])+\sum\limits_{j=1}^{大集合数量} f[j]\times g[j][i]$
  - 更新：$a[i][j] = a[i][j] + x,\ sum[j]=sum[j]+g[j][i]\times k$

**时间复杂度分析：**
我们令 $sumn = \sum\limits_{i=1}^{m}|S_i|, sqn=\sqrt{sumn}$
对于小集合，即小于 $sqn$ 的集合：
- 求和：需要枚举至多 $sqn$ 个只有大集合才拥有的 $f$ 数组，以及自身至多 $sqn$ 个元素的相加，单次求和复杂度为 $O(\sqrt{n})$
- 更新：需要枚举至多 $sqn$ 个元素，使得集合内这些元素对应的下标都加上 $x$ ，以及至多 $sqn$ 个只有大集合才拥有的 $f$ 数组，单次更新复杂度为 $O(\sqrt{n})$

对于大集合，即大于 $sqn$ 的集合：
- 求和：需要枚举至多 $sqn$ 个只有大集合才拥有的 $f$ 数组，单次求和复杂度为 $O(\sqrt{n})$
- 更新：只需要更新自身的 $f$ 数组即可，单次更新复杂度为 $O(1)$

则 $q$ 次询问的总复杂度为：$O(q\sqrt{n})$。

**代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100010;
const int M = N;
const int SQN = 320;
int n, m, Q, sqc;
int len, k, x; char op[2];
int id[M];
ll a[N];
vector<int> s[N];

ll sum[N];
ll f[N];
vector<int> g[N];

int cnt[N];

ll allc;

int main()
{
    scanf("%d%d%d", &n, &m, &Q);
    for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &len);
        s[i].resize(len);
        for (int j = 0; j < len; ++j) scanf("%d", &s[i][j]);
        allc += len;
    }

    for (int i = 1; i <= m; ++i) id[i] = i;
    sort(id + 1, id + m + 1, [&](const int x, const int y) {
        return s[x].size() > s[y].size();
    });

    /*
        前一半是大集合，后一半是小集合，只有大集合拥有下面的数组
        sum[i]
        f[i]
        g[i][]
    */

    sqc = sqrt(allc);
    int p = -1;
    for (int c = 1; c <= m; ++c) {
        int i = id[c];
        if (s[i].size() > sqc) p = c;
        else break;
        g[i].resize(m + 1);
    }

    for (int c = 1; c <= p; ++c) {
        int i = id[c];

        for (int t = 0; t < s[i].size(); ++t) {
            sum[i] += a[s[i][t]];
            cnt[s[i][t]] = 1;
        }

        g[i][id[c]] = s[i].size(); // 自己和自己
        for (int d = c + 1; d <= m; ++d) {
            int j = id[d];

            int act = 0;
            for (int t = 0; t < s[j].size(); ++t) {
                if (cnt[s[j][t]]) act += 1;
            }
            g[i][j] = act;
            if (s[j].size() > sqc) g[j][i] = act;
        }

        for (int t = 0; t < s[i].size(); ++t) {
            cnt[s[i][t]] = 0;
        }
    }

    while (Q--) {
        scanf("%s%d", op, &k);
        if (*op == '?') {
            // query
            ll ans = 0;
            if (s[k].size() > sqc) {
                ans += sum[k];
                for (int d = 1; d <= p; ++d) {
                    int j = id[d];
                    ans += f[j] * g[j][k];
                }
            } else {
                for (int j = 0; j < s[k].size(); ++j) ans += a[s[k][j]];
                for (int d = 1; d <= p; ++d) {
                    int j = id[d];
                    ans += f[j] * g[j][k];
                }
            }
            printf("%lld\n", ans);
        } else {
            // update
            scanf("%d", &x);
            if (s[k].size() > sqc) {
                f[k] += x;
            } else {
                for (int j = 0; j < s[k].size(); ++j) a[s[k][j]] += x;
                for (int d = 1; d <= p; ++d) {
                    int j = id[d];
                    sum[j] += 1ll * g[j][k] * x;
                }
            }
        }
    }

    return 0;
}
```

# Round411(Div.1) D. Expected diameter of a tree

**题意：**
给定 $n$ 个点 $m$ 条边，这些点和边构成了森林（若干棵树构成森林）。$q$ 次询问。每个询问给定点 $u$ 和 $v$ ，$U$ 是点 $u$ 所在的连通分量，$V$ 是 $v$ 所在的连通分量。
在 $U$ 和 $V$ 之间添加一条边，得到一个新的连通分量，如果这个连通分量是树，$d$ 就是这个树的直径，否则 $d=-1$ 。如果我们随机选择 $U$ 和 $V$ 中的点，这样构成的 $d$ 的期望是多少？

数据范围：$1\leq n,m,q\leq 10^5,1\leq u,v\leq n$

**题解：**
考虑大树为树的元素个数大于 $\sqrt{n}$ 的树，小树为树的元素个数小于 $\sqrt{n}$ 的树。

我们可以通过预处理每棵树中每个点可以到的最远的点的距离，然后通过距离对每棵树中的点从大到小排序。假设一次查询中两棵树中的元素个数分别为：$n_1,n_2$，其中 $n_1\leq n_2$，则单次查询的复杂度为：$n_1\log (n_2)$。

**时间复杂度分析：**
我们分别考虑大树和小树：
- 如果查询中存在小树，那么单次查询的复杂度至多为 $O(\sqrt{n}\log {n})$
- 如果查询中都是大树，假设大树中元素个数为 $k$ ，则有 $\frac{n}{k}$ 棵大树，则最多有 $(\frac{n}{k})^2$ 个不同的方案，由于 $k>\sqrt{n}$，故最多是 $O(n)$ 种不同方案。$O((\frac{n}{k})^2k\log n)=O(\frac{n^2}{k}\log n)$。因为 $k>\sqrt{n}$，所以复杂度不会超过 $O(n\sqrt{n}\log n)$

则 $q$ 次询问的总复杂度为：$O(n\sqrt{n}\log n)$。

**代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100010;
const int SQN = 320;
const double eps = 1e-4;
int n, m, Q, sqn;
int u, v;
vector<int> g[N];
vector<int> conn[N];
vector<ll> pre[N];

double f[SQN][SQN];

int p[N], sz[N];
int find(int x) {
    int root = x;
    while (root != p[root]) root = p[root];
    while (x != p[x]) {
        int nx = p[x];
        p[x] = root;
        x = nx;
    }
    return root;
}

int vis[N];
int down1[N], down2[N];
int maxd[N];
void dfs1(int u, int fa) {
    if (vis[u]) return ;
    vis[u] = 1;

    down1[u] = down2[u] = 0;
    for (int v: g[u]) {
        if (v == fa) continue ;
        dfs1(v, u);
        if (down1[v] + 1 > down1[u]) {
            down2[u] = down1[u];
            down1[u] = down1[v] + 1;
        } else if (down1[v] + 1 > down2[u]) {
            down2[u] = down1[v] + 1;
        }
    }
}

int up[N];
void dfs2(int u, int fa) {
    if (vis[u]) return ;
    vis[u] = 1;
    for (int v: g[u]) {
        if (v == fa) continue ;
        up[v] = up[u] + 1;
        if (down1[v] + 1 == down1[u]) {
            up[v] = max(up[v], down2[u] + 1);
        } else {
            up[v] = max(up[v], down1[u] + 1);
        }
        dfs2(v, u);
    }
}

double process(int u, int v) {
    // v 小 u 大
    int dd = max(maxd[conn[u].front()], maxd[conn[v].front()]);
    if (pre[u].empty()) {
        pre[u].resize(conn[u].size() + 1);
        pre[u][0] = 0;
        for (int i = 0; i < conn[u].size(); ++i) {
            pre[u][i + 1] = pre[u][i] + maxd[conn[u][i]];
        }
    }

    ll sum = 0;
    for (auto v1: conn[v]) {
        int l = 0, r = int(conn[u].size()) - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (maxd[conn[u][mid]] + maxd[v1] + 1 > dd) l = mid;
            else r = mid - 1;
        }

        if (l + 1 < conn[u].size()) sum += 1ll * (int(conn[u].size()) - l - 1) * dd;
        sum += (pre[u][l + 1] + 1ll * (l + 1) * (maxd[v1] + 1));
    }

    return 1.0 * sum / (1ll * conn[u].size() * conn[v].size());
}

int tot = 0;
int idx2f[N];
int get(int u) {
    if (idx2f[u] == 0) idx2f[u] = ++tot;
    return idx2f[u];
}

int main()
{
    scanf("%d%d%d", &n, &m, &Q);
    sqn = sqrt(n);
    for (int i = 1; i <= n; ++i) p[i] = i, sz[i] = 1;
    for (int i = 1; i <= sqn; ++i)
        for (int j = 1; j <= sqn; ++j)
            f[i][j] = -1;

    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
        int pu = find(u), pv = find(v);
        p[pu] = pv;
        sz[pv] += sz[pu];
    }

    // 求每个点到其连通分量内一点的最远距离，答案就是 max(down1[i], up[i])
    for (int i = 1; i <= n; ++i) vis[i] = 0;
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs1(i, 0);
    for (int i = 1; i <= n; ++i) vis[i] = 0;
    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs2(i, 0);
    for (int i = 1; i <= n; ++i) maxd[i] = max(down1[i], up[i]);

    for (int i = 1; i <= n; ++i) {
        conn[find(i)].push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        sort(conn[i].begin(), conn[i].end(), [&](const int x, const int y) {
            return maxd[x] > maxd[y];
        });
    }


    while (Q--) {
        scanf("%d%d", &u, &v);
        u = find(u), v = find(v);
        if (u == v) {
            puts("-1");
            continue ;
        }

        if (sz[u] < sz[v]) swap(u, v);

        double ans = 0.0;
        if (sz[u] > sqn && sz[v] > sqn && f[get(u)][get(v)] >= 0) {
            ans = f[get(u)][get(v)];
        } else {
            ans = process(u, v);
            if (sz[u] > sqn && sz[v] > sqn) {
                f[get(u)][get(v)] = f[get(v)][get(u)] = ans;
            }
        }

        printf("%.10lf\n", ans);
    }

    return 0;
}
```

# Round80(Div.1) D. Time to Raid Cowavans
**题意：**
给定一个长度为 $n$ 的数组 $w$ 。
$q$ 次询问，每次给定 $a,b$，问 $\sum\limits_{i=a}^n[i\%b=a\%b]\times w[i]$
- 当 $i\%b=a\%b$ ，表示选择 $w[i]$
- 当 $i\%b\neq a\%b$，表示不选择 $w[i]$

数据范围：
$1\leq n,q\leq 3\cdot 10^5,1\leq w[i]\leq 10^9,1\leq a,b\leq n$

**题解：**
- 当 $b>\sqrt{n}$，此时从 $a$ 到 $n$ 至多会加 $\sqrt{n}$ 个数，直接暴力即可。
- 当 $b<\sqrt{n}$，对于每个询问，我们需要 $O(n)$ 的复杂度才能解决这个询问。如果我们对于询问中具有相同的 $b$ 的情况同时解决，那么这部分最多的总复杂度就是 $O(n\sqrt{n})$ 。
	
	我们可以按照 $b$ 作为第一关键字（从大到小或者从小到大无所谓），$a$ 的大小作为第二关键字从大到小，对所有的询问进行排序。
	此时 $b$ 相同的询问作为一组，我们处理询问时的 $a$ 是递减的，从 $n$ 到 $1$ 依次将每个值累加到取模后对应的索引即可。

**时间复杂度分析：**
- 当 $b>\sqrt{n}$，至多 $q$ 个询问，故复杂度为 $O(q\sqrt{n})$
- 当 $b<\sqrt{n}$，至多 $\sqrt{n}$ 个不同的 $b$ ，每个 $b$ 可以在 $O(n)$ 的时间复杂度内处理完所有的询问，故复杂度为 $O(n\sqrt{n})$

因为 $q$ 和 $n$ 同阶，总复杂度为：$O(n\sqrt{n})$

**代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 300010;
const int M = N;
int n, m, sqn, x, y;
int w[N];
ll ans[N];
ll tmp[N];

struct Node {
    int x, y, id;
}q[M];

int main()
{
    scanf("%d", &n);
    sqn = sqrt(n);
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);

    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &q[i].x, &q[i].y);
        q[i].id = i;
    }

    sort(q + 1, q + m + 1, [&](const Node& A, const Node& B) {
        if (A.y == B.y) return A.x > B.x;
        return A.y < B.y;
    });

    for (int c = 1; c <= m; ++c) {
        if (q[c].y > sqn) {
            ll res = 0;
            for (int i = q[c].x; i <= n; i += q[c].y) res += w[i];
            ans[q[c].id] = res;
        } else {
            int d = c + 1;
            while (d <= m && q[d].y == q[c].y) d += 1;

            for (int e = c; e < d; ++e) {
                tmp[q[e].x % q[e].y] = 0;
            }

            for (int e = c, now = n; e < d; ++e) {
                while (now >= q[e].x) {
                    tmp[now % q[e].y] += w[now];
                    now -= 1;
                }
                ans[q[e].id] = tmp[q[e].x % q[e].y];
            }
            c = d - 1;
        }
    }

    for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);

    return 0;
}
```

# luogu P3396 哈希冲突
**题意：**
给定一个长度为 $n$ 的数组 $val$ ，$m$ 次操作。
每次操作给出 $x$ 和 $y$ ，有两种选择：
- 求 $\sum\limits_{i=1}^n [i\%x=y]\times val[i]$
- 修改 $val[x]=y$

数据范围：$1\leq n,m\leq 1.5\times 10^5, 1\leq val_i\leq 1000$

**题解：**
- 对于求和操作：
	- 当 $x>\sqrt{n}$ ，此时从 $y$ 到 $n$ 至多 $\sqrt{n}$ 个值
	- 当 $x<\sqrt{n}$ ，当查询时，对于每个 $x$ ，有至多 $\sqrt{n}$ 个不同的索引，可以对每个 $x$ 通过 $O(n)$ 遍历预处理出每个 $x$ 下对应的索引的值之和，总复杂度为 $O(n\sqrt{n})$。
- 对于修改操作：
	- 只需要对 小于 $\sqrt{n}$ 的这些模数对应的预处理结果进行修改即可。


**时间复杂度分析：**
- 对于求和操作：
	- 当 $x>\sqrt{n}$ ，对于 $m$ 次操作，总复杂度为 $O(m\sqrt{n})$
	- 当 $x<\sqrt{n}$ ，预处理出求和的复杂度为 $O(n\sqrt{n})$
- 对于修改操作：
	- 由于只需要对 $x$ 在 $\sqrt{n}$ 个模数下取模的值进行修改，复杂度为 $O(\sqrt{n})$

由于 $m$ 次操作，且 $m$ 和 $n$ 同阶，总复杂度为 $O(n\sqrt{n})$

**代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 150010;
const int SQN = 390;
int w[N], n, m, sqn;
ll sum[SQN][SQN];

char op[2];
int x, y;

int main()
{
    scanf("%d%d", &n, &m);
    sqn = sqrt(n);
    for (int i = 1; i <= n; ++i) scanf("%d", &w[i]);

    for (int i = 1; i <= sqn; ++i)
        for (int j = 1; j <= n; ++j)
            sum[i][j % i] += w[j];


    while (m--) {
        scanf("%s%d%d", op, &x, &y);

        if (*op == 'A') {
            ll ans = 0;
            if (x > sqn) {
                ll res = 0;
                for (int i = y; i <= n; i += x) res += w[i];
                ans = res;
            } else {
                ans = sum[x][y];
            }
            printf("%lld\n", ans);
        } else {
            for (int i = 1; i <= sqn; ++i)
                sum[i][x % i] += y - w[x];
            w[x] = y;
        }
    }

    return 0;
}
```

****

# Rectangles
**题意：**
给定 $n$ 个点 $(x_i,y_i)$，问这些点可以构成多少个不同的矩形，即我 $C_n^4$ 这样选择点，有多少种选择可以构成矩形。

数据范围： $1\leq n\leq 10^5,1\leq x_i,y_i\leq 10^9$

**题解：**
将点按 $x$ 进行分类，假设共有 $k$ 行，第 $i$ 行有 $k_i$ 个不同的 $y$。对于行中点数大于 $\sqrt{n}$ 的行，称为大行。对于行中点数小于 $\sqrt{n}$ 的行，称为小行。

- 对于大行 $big$，用数组 $f$ 统计每个 $y$ 是否出现，对其他所有行 $other$，遍历 $other$ 和 $line$，计算两者的交集大小 $cnt$。$C_{cnt}^2$ 即答案。这里统计的是（大行，大行）、（大行，小行）这两种。

- 对于小行 $small$，用数组 $p[l,r]$ 判断在行 $small$ 中是否出现 $y_1=l,y_2=r,l<r$。
枚举每个小行，然后遍历得到其中的 $(l,r)$ 则共 $\frac{n}{k}$ 行，至多存在 $\frac{n}{k} \times k^2=nk$ 个不同的点对数。由于 $k<\sqrt{n}$，故最多 $n\sqrt{n}$ 个点对。那么我们可以对每一个点对 $(l,r)$ 中，以 $l$ 作为索引存下所有的 $r$ ，然后用一个数组去统计数量即可。

**时间复杂度分析：**
- 对于大行 $big$ ，统计其与其他行，共有 （大行，大行）、（大行，小行）这两种的方案。
首先大行至多 $\sqrt{n}$ 个，枚举每个大行，并统计每个大行中的数是否出现。再枚举其他行，并遍历每个行中的数是否出现，共 $O(n)$ 的复杂度，总复杂度 $O(n\sqrt{n})$
- 对小行 $small$ ，统计的复杂度为 $O(n\sqrt{n})$，遍历也是 $O(n\sqrt{n})$。

故总时间复杂度为 $O(n\sqrt{n})$

**代码：**
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 250010;
int n, sqn;
int b[N], g;
pair<int, int> p[N];
vector<int> vec[N];
vector<int> small[N];
int f[N];
int tot;

int get(int x) {
    int l = 1, r = g;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (b[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main()
{
    tot = 0;
    scanf("%d", &n);
    sqn = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &p[i].first, &p[i].second);
        b[++g] = p[i].second;
    }

    sort(b + 1, b + g + 1);
    g = unique(b + 1, b + g + 1) - b - 1;

    sort(p + 1, p + n + 1);
    for (int i = 1; i <= n; ++i) {
        int j = i + 1;
        while (j <= n && p[j].first == p[i].first) j += 1;
        vec[tot].resize(j - i);
        for (int k = i; k < j; ++k) {
            vec[tot][k - i] = get(p[k].second);
        }
        tot += 1;
        i = j - 1;
    }

    sort(vec, vec + tot, [](const vector<int>& A, const vector<int>& B) {
        return A.size() > B.size();
    });

    for (int i = 0; i < tot; ++i) {
        sort(vec[i].begin(), vec[i].end());
    }

    long long ans = 0;
    for (int i = 0; i < tot; ++i) {
        if (int(vec[i].size()) > sqn) {
            for (int u: vec[i]) f[u] = 1;

            for (int j = i + 1; j < tot; ++j) {
                int cnt = 0;
                for (int u: vec[j]) if (f[u]) cnt += 1;
                ans += 1ll * cnt * (cnt - 1) / 2;
            }
            for (int u: vec[i]) f[u] = 0;
        } else {
            for (int j = i; j < tot; ++j) {
                int sz = vec[j].size();
                auto& v = vec[j];
                for (int x = 0; x < sz; ++x)
                    for (int y = x + 1; y < sz; ++y)
                        small[v[x]].push_back(v[y]);
            }
            break;
        }
    }

    for (int i = 1; i <= g; ++i) {
        if (small[i].size() > 1) {
            for (int u: small[i]) f[u] += 1;
            for (int u: small[i]) {
                if (f[u] > 1) ans += 1ll * f[u] * (f[u] - 1) / 2;
                f[u] = 0;
            }
        }
    }

    printf("%lld\n", ans);

    return 0;
}
```

# 暂时不能提交的题
**题意：**
给定一个集合 $S$ ，初始为空，$m$ 次操作每次有两种
- 添加一个新的数 $x$ 至 $S$ 中
- 查询 $S$ 中的所有数，对 $y$ 取模的最小值

数据范围：$1\leq m,x,y\leq 10^5$
假设 $n$ 是操作中最大的值，即 $n=10^5$

**题解：**
维护一个线段树，这个线段树中的节点表示 $[l,r]$ 这个区间内出现的值最小的数。

-  对于添加一个新的数 $x$
	- 将 $x$ 对 $[1,\sqrt{n})$ 这些数取模的值直接添加到预处理数组中。
	- 将 $x$ 添加到线段树中，这里是指对线段树中的值设置为 $1$ ，表示该值存在。

- 对于查询操作
	- 当 $y<\sqrt{n}$，可以直接查询预处理数组
	- 当 $y>\sqrt{n}$，可以将值区间拆分为 $[0,y),[y,2y),...,[\lfloor\frac{n}{y}\rfloor\times y,n]$，我们在线段树中分别查询这至多 $\sqrt{n}$ 个区间内可以获得的最小值。取 $\mathrm{min}$ 即可。

**时间复杂度分析：**
- 对于添加一个新的数 $x$
	- 添加到预处理数组中，时间复杂度为 $O(\sqrt{n})$
	- 对于添加到线段树中，时间复杂度为 $O(\log n)$
	- 时间复杂度为 $O(n\sqrt{n})$
- 对于查询操作
	- 当 $y<\sqrt{n}$，直接查询预处理数组即可，每个 $y$ 至多 $\sqrt{n}$ 次，时间复杂度为 $O(\sqrt{n})$
	- 当 $y>\sqrt{n}$，有 $\sqrt{n}$ 个区间，每个区间查询复杂度为 $O(\log n)$，故时间复杂度为 $\sqrt{n}\log n$
	- 时间复杂度为 $O(n\sqrt{n}\log n)$

故总时间复杂度为 $O(n\sqrt{n}\log n)$
