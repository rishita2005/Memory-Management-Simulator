#include "../include/cache.h"
#include <iostream>

Cache* L1 = nullptr;
Cache* L2 = nullptr;

Cache::Cache(std::string n, int s) : name(n), size(s), hits(0), misses(0) {
    data.assign(s, -1); // Initialize empty
}

bool Cache::check(int address) {
    int index = address % size; // Direct mapping logic
    
    if (data[index] == address) {
        hits++;
        return true;
    } else {
        misses++;
        data[index] = address; // Update cache on miss
        return false;
    }
}

void accessAddress(int pAddr) {
    std::cout << "Accessing Physical Address " << pAddr << "..." << std::endl;
    
    // Check hierarchy: L1 -> L2 -> Main Memory
    if (L1 && L1->check(pAddr)) {
        std::cout << "L1 Hit!" << std::endl;
    } else {
        std::cout << "L1 Miss. Checking L2..." << std::endl;
        if (L2 && L2->check(pAddr)) {
            std::cout << "L2 Hit!" << std::endl;
        } else {
            std::cout << "L2 Miss. Fetching from Main Memory." << std::endl;
        }
    }
}