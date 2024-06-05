#include <vector>
#include "building.h"
#include "mine.h"
#include "merger.h"
#include"splitter.h"
#include "buffer.h"

class CombinedIterator {
public:
    CombinedIterator(std::vector<std::vector<Selectable*>>& vectors)
        : vectors(vectors) {
        for (auto& vec : vectors) {
            if (!vec.empty()) {
                iters.push_back(vec.begin());
                ends.push_back(vec.end());
            }
        }
    }

    Selectable* next() {
        while (current < iters.size()) {
            if (iters[current] != ends[current]) {
                return *(iters[current]++);
            }
            ++current;
        }
        return nullptr;
    }

private:
    std::vector<std::vector<Selectable*>>& vectors;
    std::vector<std::vector<Selectable*>::iterator> iters;
    std::vector<std::vector<Selectable*>::iterator> ends;
    size_t current = 0;
};