#include "stones.h"
#include "max_heap.h"

#include <queue>

int lastStoneWeight(std::vector<int>& stones) {
    std::priority_queue<int> pq;
    for(auto it : stones) {
        pq.push(it);
    }
    int stone1;
    int stone2;
    while(pq.size() > 1) {
        stone1 = pq.top();
        pq.pop();
        stone2 = pq.top();
        pq.pop();

        if(stone1 != stone2) {
            pq.push(stone1-stone2);
        }
    }

    if(pq.size() == 0) {
        return 0;
    }
    return pq.top();
    
}
