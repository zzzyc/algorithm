# UnionSet 并查集
通常用于集合之间合并的判断

可以实现 $O(\log n)$ 的合并和查询，初始化是 $O(n)$ 的，无任何优化的总时间复杂度大致为 $O(n\log n)$。

通过路径压缩和按秩合并，可以做到 $n\cdot \alpha(n)$ 

其中 $\alpha(x)$ 为反阿克曼函数，当自变量 $x$ 的值在人类可观测的范围内（宇宙中粒子的数量）时，函数 $\alpha(x)$ 的值不会超过 $5$，因此也可以看成是常数时间复杂度。