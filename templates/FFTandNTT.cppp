#include <bits/stdc++.h>
using namespace std;

struct FFT_Recursion {

    // N 对应的是大于答案的数据长度对应的最小的2的幂
    static const int N = 512;
    double PI = acos(-1);
    struct Complex {
        double x, y;

        Complex() {}
        Complex(double _x, double _y): x(_x), y(_y) {}
        Complex operator+ (const Complex& A) { return Complex(x + A.x, y + A.y); }
        Complex operator- (const Complex& A) { return Complex(x - A.x, y - A.y); }
        Complex operator* (const Complex& A) { return Complex(x * A.x - y * A.y, A.x * y + A.y * x); }

        void init() { x = 0, y = 0; }
    };

    Complex A[N], B[N];
    int bit, len;

    // 递归版本 FFT
    void FFT(Complex a[], int len, int inv) {
        // 当长度为1，到达递归出口
        if (len == 1) return ;

        // 分成奇数项和偶数项
        Complex a0[len >> 1], a1[len >> 1];
        for (int i = 0; i < len; i += 2)
            a0[i >> 1] = a[i], a1[i >> 1] = a[i + 1];

        // 递归解决左半部分子问题
        FFT(a0, len >> 1, inv);
        // 递归解决右边部分子问题
        FFT(a1, len >> 1, inv);

        // 单位复根
        Complex w1(cos(2.0 * PI / len), inv * sin(2.0 * PI / len));

        // 初始 w
        Complex w(1, 0);

        // 根据奇数项和偶数项来更新答案
        for (int k = 0; k < (len >> 1); ++k) {
            a[k] = a0[k] + w * a1[k];
            a[k + (len >> 1)] = a0[k] - w * a1[k];
            w = w * w1;
        }

        // 如果是逆FFT，还需要除this->len
        if (len == this->len && inv == -1) {
            for (int i = 0; i < len; ++i) a[i].x = a[i].x / len;
        }
    }

    // 通过FFT计算
    void calculate(int n, int m) {
        // 将多项式乘法的长度更新成满足答案范围的最小2的幂
        len = 1;
        while (len <= n + m) len <<= 1;

        // 将 A 转换成点值表示
        FFT(A, len, 1);
        // 将 B 转换成点值表示
        FFT(B, len, 1);
        // 点值乘法
        for (int i = 0; i < len; ++i) A[i] = A[i] * B[i];

        // 将答案的点值表示通过逆FFT转换回系数表示
        FFT(A, len, -1);
    }

    string multiply(string num1, string num2) {
        int n = int(num1.size()) - 1, m = int(num2.size()) - 1;
        for (int i = 0; i < N; ++i) A[i].init(), B[i].init();
        for (int i = 0; i <= n; ++i) A[i].x = num1[i] - '0', A[i].y = 0;
        for (int i = 0; i <= m; ++i) B[i].x = num2[i] - '0', B[i].y = 0;

        calculate(n, m);

        int temp = 0;
        string ans;
        for (int i = n + m; i >= 0; --i) {
            temp += int(A[i].x + 0.5);
            ans += char(temp % 10 + '0');
            temp /= 10;
        }

        while (temp > 0) ans += char(temp % 10 + '0'), temp /= 10;
        while (ans.size() > 1 && ans.back() == '0') ans.pop_back();
        reverse(ans.begin(), ans.end());

        return ans;
    }
}fft_recursion;
struct FFT_Iteration {

    static constexpr int N = 512;
    double PI = acos(-1);
    struct Complex {
        double x, y;

        Complex() {}
        Complex(double _x, double _y): x(_x), y(_y) {}
        Complex operator+ (const Complex& A) { return Complex(x + A.x, y + A.y); }
        Complex operator- (const Complex& A) { return Complex(x - A.x, y - A.y); }
        Complex operator* (const Complex& A) { return Complex(x * A.x - y * A.y, A.x * y + A.y * x); }

        void init() { x = 0, y = 0; }
    };

    Complex A[N], B[N];
    int bit, len;
    int rev[N];

    // 迭代版本 FFT
    void FFT(Complex a[], int inv) {
        for (int i = 0; i < len; ++i)
            if (i < rev[i]) swap(a[i], a[rev[i]]);

        // 从第2层开始（第1层无需计算），计算每个奇数项和偶数项的值
        for (int mid = 1; mid < len; mid <<= 1) {
            // 初始化每一层的单位复根
            Complex w1(cos(PI / mid), inv * sin(PI / mid));
            for (int i = 0; i < len; i += mid * 2) {
                Complex w(1, 0);
                for (int j = 0; j < mid; ++j) {
                    // 蝴蝶变换，减少乘法次数
                    Complex u = a[i + j], v = a[i + j + mid] * w;
                    // 更新后的值为下一层的值
                    a[i + j] = u + v;
                    a[i + j + mid] = u - v;
                    w = w * w1;
                }
            }
        }

        // 如果是逆FFT，还需要除len
        if (inv == -1) {
            for (int i = 0; i < len; ++i)
                a[i].x = a[i].x / len;
        }
    }

    // 通过FFT计算
    void calculate(int n, int m) {
        // 将多项式乘法的长度更新成满足答案范围的最小2的幂
        bit = 0;
        while ((1 << bit) <= n + m) bit += 1;
        len = 1 << bit;

        // 初始化位逆置变换，即每个值实际在第一层对应的位置
        if (bit > 0) {
            for (int i = 0; i < len; ++i) {
                rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
            }
        }

        // 将 A 转换成点值表示
        FFT(A, 1);
        // 将 B 转换成点值表示
        FFT(B, 1);
        // 点值乘法
        for (int i = 0; i < len; ++i) A[i] = A[i] * B[i];
        // 将答案的点值表示通过逆FFT转换回系数表示
        FFT(A, -1);
    }

    string multiply(string num1, string num2) {
        int n = int(num1.size()) - 1, m = int(num2.size()) - 1;
        for (int i = 0; i < N; ++i) A[i].init(), B[i].init();
        for (int i = 0; i <= n; ++i) A[i].x = num1[i] - '0';
        for (int i = 0; i <= m; ++i) B[i].x = num2[i] - '0';

        calculate(n, m);

        int temp = 0;
        string ans;
        for (int i = n + m; i >= 0; --i) {
            temp += int(A[i].x + 0.5);
            ans += char(temp % 10 + '0');
            temp /= 10;
        }

        while (temp > 0) ans += char(temp % 10 + '0'), temp /= 10;
        while (ans.size() > 1 && ans.back() == '0') ans.pop_back();
        reverse(ans.begin(), ans.end());

        return ans;
    }
}fft_iteration;
struct NTT_Iteration {

    typedef long long ll;
    static constexpr int N = 512;
    // 模数取 998244353, 则原根为 3
    static constexpr int mod = 998244353;
    static constexpr int g = 3;
    ll A[N], B[N];
    int bit, len;
    int rev[N];

    // 快速幂，O(logn)复杂度计算a的b次方在模意义下的值
    ll qp(ll a, ll b) {
        ll res = 1;
        while (b) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }

    // 迭代版本 NTT
    void NTT(ll a[], int inv) {
        for (int i = 0; i < len; ++i)
            if (i < rev[i]) swap(a[i], a[rev[i]]);

        // 从第2层开始（第1层无需计算），计算每个奇数项和偶数项的值
        for (int mid = 1; mid < len; mid <<= 1) {
            // 初始化每一层的单位复根
            ll g1 = qp(g, (mod - 1) / (mid * 2));
            if (inv == -1) g1 = qp(g1, mod - 2);
            for (int i = 0; i < len; i += mid * 2) {
                ll gk = 1;
                for (int j = 0; j < mid; ++j) {
                    // 蝴蝶变换，减少乘法次数
                    ll u = a[i + j], v = a[i + j + mid] * gk % mod;
                    // 更新后的值为下一层的值
                    a[i + j] = (u + v) % mod;
                    a[i + j + mid] = (u - v + mod) % mod;
                    gk = gk * g1 % mod;
                }
            }
        }

        // 如果是逆NTT，还需要除len，对应到模意义下即乘上len的逆元
        if (inv == -1) {
            ll len_inv = qp(len, mod - 2);
            for (int i = 0; i < len; ++i)
                a[i] = a[i] * len_inv % mod;
        }
    }

    // 通过FFT计算
    void calculate(int n, int m) {
        // 将多项式乘法的长度更新成满足答案范围的最小2的幂
        bit = 0;
        while ((1 << bit) <= n + m) bit += 1;
        len = 1 << bit;

        // 初始化位逆置变换，即每个值实际在第一层对应的位置
        if (bit > 0) {
            for (int i = 0; i < len; ++i) {
                rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
            }
        }

        // 将 A 转换成点值表示
        NTT(A, 1);
        // 将 B 转换成点值表示
        NTT(B, 1);
        // 点值乘法
        for (int i = 0; i < len; ++i) A[i] = A[i] * B[i] % mod;
        // 将答案的点值表示通过逆NTT转换回系数表示
        NTT(A, -1);
    }

    string multiply(string num1, string num2) {
        int n = int(num1.size()) - 1, m = int(num2.size()) - 1;
        for (int i = 0; i < N; ++i) A[i] = B[i] = 0;
        for (int i = 0; i <= n; ++i) A[i] = num1[i] - '0';
        for (int i = 0; i <= m; ++i) B[i] = num2[i] - '0';

        calculate(n, m);

        ll temp = 0;
        string ans;
        for (int i = n + m; i >= 0; --i) {
            temp += A[i];
            ans += char(temp % 10 + '0');
            temp /= 10;
        }

        while (temp > 0) ans += char(temp % 10 + '0'), temp /= 10;
        while (ans.size() > 1 && ans.back() == '0') ans.pop_back();
        reverse(ans.begin(), ans.end());

        return ans;
    }
}ntt_iteration;

int main()
{
    string num1;
    string num2;
    cin >> num1 >> num2;
    cout << "  num1 = " << num1 << endl;
    cout << "  num2 = " << num2 << endl;
    auto ans_FFT_recursion = fft_recursion.multiply(num1, num2);
    auto ans_FFT_iteration = fft_iteration.multiply(num1, num2);
    auto ans_NTT_iteration = ntt_iteration.multiply(num1, num2);
    cout << "  ans_FFT_recursion = " << ans_FFT_recursion << endl;
    cout << "  ans_FFT_iteration = " << ans_FFT_iteration << endl;
    cout << "  ans_NTT_iteration = " << ans_NTT_iteration << endl;

    if (ans_FFT_recursion == ans_FFT_iteration && ans_FFT_recursion == ans_NTT_iteration) {
        cout << "  FFT的递归版本 与 FFT的迭代版本 与 NTT的迭代版本 计算结果相等" << endl;
    } else {
        cout << "  FFT的递归版本 与 FFT的迭代版本 与 NTT的迭代版本 计算结果不等" << endl;
    }

    return 0;
}
