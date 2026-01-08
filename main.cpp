#include <iostream>
#include <vector>
#include <string>
#include "include/allocator.h"
#include "include/cache.h"
#include "include/virtual_memory.h"

using namespace std;

void dumpMemory() {
    cout << "\n--- Memory Map ---" << endl;
    for (const auto& block : memoryLayout) {
        string status = block.isfree ? "FREE" : "USED (ID: " + to_string(block.id) + ")";
        cout << "[" << block.startAddress << " - " << (block.startAddress + block.size - 1) 
             << "] " << status << endl;
    }
    cout << "------------------\n" << endl;
}

int main() {
    cout << "Memory Management Simulator Active" << endl;
    string cmd;

    while (true) {
        cout << "> ";
        if (!(cin >> cmd)) break;

        if (cmd == "init") {
            cin >> totalMemorySize;
            memoryLayout.clear();
            nextProcessId = 1;
            memoryLayout.push_back({0, 0, totalMemorySize, true});
            cout << "Memory: " << totalMemorySize << " bytes." << endl;
        } 
        else if (cmd == "malloc") {
            int size; cin >> size;
            if (currentAlgo == "first_fit") mallocFirstFit(size);
            else if (currentAlgo == "best_fit") mallocBestFit(size);
            else if (currentAlgo == "worst_fit") mallocWorstFit(size);
            else if (currentAlgo == "buddy") mallocBuddy(size);
        }
        else if (cmd == "free") {
            int id; cin >> id;
            freeBlock(id);
        }
        else if (cmd == "set") {
            string type, algo; cin >> type >> algo;
            if (type == "allocator") {
                currentAlgo = algo;
                cout << "Policy updated to: " << algo << endl;
            }
        }
        else if (cmd == "init_cache") {
            int s1, s2; cin >> s1 >> s2;
            L1 = new Cache("L1", s1);
            L2 = new Cache("L2", s2);
            cout << "L1/L2 Caches initialized." << endl;
        }
        else if (cmd == "init_vm") {
            int pages; cin >> pages;
            pageTable.clear();
            for(int i=0; i < pages; i++) pageTable.push_back({i + 2, false});
            cout << "Virtual Memory ready." << endl;
        }
        else if (cmd == "v_access") {
            int vAddr; cin >> vAddr;
            int pAddr = translateAddress(vAddr);
            if (pAddr != -1) accessAddress(pAddr);
        }
        else if (cmd == "report" || cmd == "stats") {
            showStats();
            if (L1) cout << "L1 Miss Rate: " << (L1->hits + L1->misses > 0 ? (double)L1->misses/(L1->hits+L1->misses)*100 : 0) << "%" << endl;
        }
        else if (cmd == "dump") dumpMemory();
        else if (cmd == "exit") break;
    }
    return 0;
}