class Solution {
    public:
        int numberOfPaths(vector<vector<int>>& grid, int p) {
            const int mod = 1e9 + 7;
            int n = grid.size(), m = grid[0].size();
            vector f(2, vector<vector<int>>(m, vector<int>(p, 0)));
            f[0][0][grid[0][0] % p] = 1;

            auto get = [&](int x) {
                x %= p;
                if (x < 0) x += p;
                return x;
            };

            for (int i = 0; i < n; ++i) {
                int u = i & 1;
                int v = u ^ 1;
                for (int j = 0; j < m; ++j)
                    for (int k = 0; k < p; ++k) {
                        if (i > 0) {
                            f[u][j][k] = (f[u][j][k] + f[v][j][get(k - grid[i][j])]) % mod;
                        }

                        if (j > 0) {
                            f[u][j][k] = (f[u][j][k] + f[u][j - 1][get(k - grid[i][j])]) % mod;
                        }
                    }
                for (int j = 0; j < m; ++j)
                    for (int k = 0; k < p; ++k)
                        f[v][j][k] = 0;
            }

            return f[(n - 1) & 1][m - 1][0];
        }
};
