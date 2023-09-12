****
这是 `solego(zzzyc)` 的个人算法学习记录

***

目前有 `6` 个算法模板/专题和 `1` 个未分类
- /00-UnclassifiedAlgorithm   `未分类算法`
- /01-SparseTable             `ST表`
- /02-StringHash              `字符串哈希`
- /03-Trie                    `Trie 树`
- /04-UnionSet                `并查集（包括路径压缩和按秩合并）`
- /05-BigSmall                `根号分支专题`
- /06-Sort                    `排序算法（包括链表排序的实现）`
- /07-Skiplist                `跳表实现`
- /08-Cache                   `缓存实现`

# 注意事项

如果 `class` 中使用了数组，应该放在堆区，或者用 `new` 创建，或者作为全局变量，否则可能会有栈溢出带来的问题

# 使用说明
1. 每个文件夹代表一个算法的相关内容，以 `algorithm/01-SparseTable` 为例
2. `algorithm/01-SparseTable/01.cpp` 是 `ST表` 这个算法的第一道练习例题，`02.cpp`，`03.cpp` 分别对应第二道和第三道，以此类推。
3. `algorithm/01-SparseTable/README.md` 是 `ST` 表这个算法的主要介绍
4. `algorithm/01-SparseTable/SparseTable*.cpp` 是 `ST` 表这个算法的实现，通常是会封装成 `class` 或者 `struct` ，也有因为时间限制仅用数组实现
