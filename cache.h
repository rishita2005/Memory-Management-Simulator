#ifndef CACHE_H
#define CACHE_H
#include <vector>
#include <string>

class Cache {
public:
    std::string name;
    int size;
    int hits, misses;
    std::vector<int> data;

    Cache(std::string n, int s);
    bool check(int address);
};

extern Cache* L1;
extern Cache* L2;

void accessAddress(int pAddr);
#endif