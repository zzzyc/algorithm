这是 `solego` 的个人算法模板

目前有 `4` 个算法模板
- SparseTable.cpp        `ST表`
- StringHash.cpp         `字符串哈希`
- Trie.cpp               `Trie 树`
- UnionSet.cpp           `并查集（包括路径压缩和按秩合并）`

# 注意事项

1. 如果 `class` 中使用了数组，应该放在堆区，或者用 `new` 创建，或者作为全局变量，否则可能会有栈溢出带来的问题

# 使用说明
1. 每个文件夹代表一个算法的相关内容，以下以 `Templates/SparseTable` 为例
2. `Templates/SparseTable/01.cpp` 是 `ST表` 这个算法的第一道练习例题，`02.cpp`，`03.cpp` 分别对应第二道和第三道，以此类推。
3. `Templates/SparseTable/README.md` 是 `ST` 表这个算法的主要介绍
4. `Templates/SparseTable/SparseTable*.cpp` 是 `ST` 表这个算法的实现，通常是会封装成 `class` 或者 `struct` ，也有因为时间限制仅用数组实现 