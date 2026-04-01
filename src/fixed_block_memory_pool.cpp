#include "fixed_block_memory_pool.h"

#include <algorithm>
#include <stdexcept>

namespace {

std::size_t normalize_block_size(std::size_t requested_size) {
    if (requested_size == 0) {
        throw std::invalid_argument("block size must be greater than zero");
    }

    return std::max(requested_size, sizeof(void*));
}

}  // namespace

FixedBlockMemoryPool::FixedBlockMemoryPool(std::size_t block_size, std::size_t blocks_per_chunk)
    : block_size_(normalize_block_size(block_size)),
      blocks_per_chunk_(blocks_per_chunk),
      free_list_head_(nullptr),
      chunks_(),
      free_block_count_(0),
      total_block_count_(0) {
    if (blocks_per_chunk_ == 0) {
        throw std::invalid_argument("blocks per chunk must be greater than zero");
    }
}

FixedBlockMemoryPool::~FixedBlockMemoryPool() {
    for (std::uint8_t* chunk : chunks_) {
        delete[] chunk;
    }
}

void* FixedBlockMemoryPool::allocate() {
    if (free_list_head_ == nullptr) {
        allocate_chunk();
    }

    // TODO(student):
    // 1. 取出 free_list_head_ 当前指向的空闲块
    // 2. 让 free_list_head_ 指向下一个空闲块
    // 3. 将 free_block_count_ 减 1
    // 4. 返回这块内存的地址
    throw std::runtime_error("TODO: implement FixedBlockMemoryPool::allocate");
}

void FixedBlockMemoryPool::deallocate(void* ptr) {
    if (ptr == nullptr) {
        return;
    }

    if (!owns(ptr)) {
        throw std::invalid_argument("pointer does not belong to this pool");
    }

    if (!points_to_block_start(ptr)) {
        throw std::invalid_argument("pointer is not aligned to the start of a block");
    }

    // TODO(student):
    // 1. 将 ptr 转成 FreeNode*
    // 2. 用头插法把它挂回 free_list_head_
    // 3. 将 free_block_count_ 加 1
    throw std::runtime_error("TODO: implement FixedBlockMemoryPool::deallocate");
}

void FixedBlockMemoryPool::allocate_chunk() {
    const std::size_t chunk_size = block_size_ * blocks_per_chunk_;
    auto* chunk = new std::uint8_t[chunk_size];
    chunks_.push_back(chunk);
    total_block_count_ += blocks_per_chunk_;

    // TODO(student):
    // 目标：把整个 chunk 切成多个 block，再把它们串成 free list。
    //
    // 提示：
    // - 第 i 个 block 的起始地址是 chunk + i * block_size_
    // - 每个 block 的起始位置都可以当成一个 FreeNode
    // - 最容易的写法是用头插法构造链表
    // - 别忘了把 free_block_count_ 增加 blocks_per_chunk_
    throw std::runtime_error("TODO: implement FixedBlockMemoryPool::allocate_chunk");
}

bool FixedBlockMemoryPool::owns(void* ptr) const noexcept {
    auto* raw = static_cast<std::uint8_t*>(ptr);

    for (const std::uint8_t* chunk : chunks_) {
        const std::uint8_t* begin = chunk;
        const std::uint8_t* end = chunk + block_size_ * blocks_per_chunk_;
        if (raw >= begin && raw < end) {
            return true;
        }
    }

    return false;
}

bool FixedBlockMemoryPool::points_to_block_start(void* ptr) const noexcept {
    auto* raw = static_cast<std::uint8_t*>(ptr);

    for (const std::uint8_t* chunk : chunks_) {
        const std::uint8_t* begin = chunk;
        const std::uint8_t* end = chunk + block_size_ * blocks_per_chunk_;
        if (raw >= begin && raw < end) {
            const std::ptrdiff_t offset = raw - begin;
            return offset % static_cast<std::ptrdiff_t>(block_size_) == 0;
        }
    }

    return false;
}
