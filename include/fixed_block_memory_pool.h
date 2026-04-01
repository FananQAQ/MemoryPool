#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

class FixedBlockMemoryPool {
public:
    FixedBlockMemoryPool(std::size_t block_size, std::size_t blocks_per_chunk);
    ~FixedBlockMemoryPool();

    FixedBlockMemoryPool(const FixedBlockMemoryPool&) = delete;
    FixedBlockMemoryPool& operator=(const FixedBlockMemoryPool&) = delete;

    void* allocate();
    void deallocate(void* ptr);

    std::size_t block_size() const noexcept { return block_size_; }
    std::size_t blocks_per_chunk() const noexcept { return blocks_per_chunk_; }
    std::size_t chunk_count() const noexcept { return chunks_.size(); }
    std::size_t free_block_count() const noexcept { return free_block_count_; }
    std::size_t total_block_count() const noexcept { return total_block_count_; }
    std::size_t used_block_count() const noexcept { return total_block_count_ - free_block_count_; }

private:
    struct FreeNode {
        // 指向下一个空闲块，用来把所有可复用块串成单链表。
        FreeNode* next;
    };

    void allocate_chunk();
    bool owns(void* ptr) const noexcept;
    bool points_to_block_start(void* ptr) const noexcept;

private:
    // 每个 block 的大小。内存池一次分配出去的最小单位就是一个 block。
    std::size_t block_size_;

    // 每次向系统申请一个 chunk 时，会切分出多少个 block。
    std::size_t blocks_per_chunk_;

    // 空闲链表的表头，指向当前第一个可用 block。
    FreeNode* free_list_head_;

    // 记录所有向系统申请过的 chunk 起始地址，析构时需要统一释放。
    std::vector<std::uint8_t*> chunks_;

    // 当前空闲 block 的数量，用来观察池子的剩余容量。
    std::size_t free_block_count_;

    // 池子总共管理的 block 数量，通常会随着新 chunk 的加入而增长。
    std::size_t total_block_count_;
};
