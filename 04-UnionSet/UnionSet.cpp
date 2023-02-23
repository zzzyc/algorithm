#include <bits/stdc++.h>

class UnionSet {
private:
    std::vector<int> p;
    std::vector<int> rank;
    std::vector<int> sz;
    int n;

public:
    UnionSet(int n): n(n){
        p.resize(n);
        rank.resize(n);
        sz.resize(n);

        for (int i = 0; i < n; ++i) {
            p[i] = i;
            rank[i] = 0;
            sz[i] = 1;
        }
    }

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

    void merge(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            if (rank[pa] > rank[pb]) {
                std::swap(pa, pb);
            }

            if (rank[pa] == rank[pb]) {
                rank[pb] += 1;
            }

            p[pa] = pb;
            sz[pb] += sz[pa];
            sz[pa] = 0;
        }
    }

    bool isSame(int a, int b) {
        return find(a) == find(b);
    }

    int size(int a) {
        return sz[find(a)];
    }
};