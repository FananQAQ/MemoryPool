#include "fixed_block_memory_pool.h"

#include <cstring>
#include <exception>
#include <iostream>

int main() {
    try {
        FixedBlockMemoryPool pool(32, 4);

        std::cout << "Initial state\n";
        std::cout << "  block size      : " << pool.block_size() << "\n";
        std::cout << "  blocks per chunk: " << pool.blocks_per_chunk() << "\n";
        std::cout << "  total blocks    : " << pool.total_block_count() << "\n";
        std::cout << "  free blocks     : " << pool.free_block_count() << "\n\n";

        void* a = pool.allocate();
        void* b = pool.allocate();

        std::memset(a, 0x11, pool.block_size());
        std::memset(b, 0x22, pool.block_size());

        std::cout << "After two allocations\n";
        std::cout << "  total blocks: " << pool.total_block_count() << "\n";
        std::cout << "  free blocks : " << pool.free_block_count() << "\n";
        std::cout << "  used blocks : " << pool.used_block_count() << "\n\n";

        pool.deallocate(a);
        pool.deallocate(b);

        std::cout << "After deallocation\n";
        std::cout << "  total blocks: " << pool.total_block_count() << "\n";
        std::cout << "  free blocks : " << pool.free_block_count() << "\n";
        std::cout << "  used blocks : " << pool.used_block_count() << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Program stopped: " << ex.what() << "\n";
        std::cerr << "This is expected before you finish the TODOs.\n";
        return 1;
    }

    return 0;
}
