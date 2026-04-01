# Memory Pool Lab

这是一个面向自学的 C++ 内存池实验项目。

你将亲手实现一个最基础但很有代表性的 `FixedBlockMemoryPool`，学习下面这些核心概念：

- 为什么频繁调用 `new` / `delete` 会带来额外开销
- 固定大小内存块池的设计方式
- 空闲链表（free list）如何管理可复用块
- 批量向系统申请大块内存（chunk）的思路
- 如何统计内存池的使用情况

## 项目结构

- `include/fixed_block_memory_pool.h`: 对外接口和数据结构
- `src/fixed_block_memory_pool.cpp`: 主要实现，已经故意留空若干关键逻辑
- `src/main.cpp`: 简单演示程序
- `LAB_TODO.md`: 明确列出哪些位置需要你自己实现

## 建议学习顺序

1. 先阅读 `include/fixed_block_memory_pool.h`
2. 再读 `src/fixed_block_memory_pool.cpp`，理解整体流程
3. 对照 `LAB_TODO.md` 逐个补全
4. 每补完一步就编译并运行
5. 最后尝试自己扩展功能

## 构建

```bash
cmake -S . -B build
cmake --build build
```

## 运行

```bash
./build/memory_pool_demo
```

在你补完关键逻辑前，程序会因为 `TODO` 抛出异常，这是预期行为。

## 完成后你可以继续挑战

- 支持内存对齐
- 支持不同大小类别的池
- 增加线程安全版本
- 增加性能对比测试
