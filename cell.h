//
// Created by funtalex on 20.10.23.
//

#ifndef INC_1C_CELL_H
#define INC_1C_CELL_H

#include <cstdint>

struct Cell {
    Cell();
    Cell(int64_t x, int64_t y);

    int64_t x = 0;
    int64_t y = 0;

    bool is_visited = false;
    bool is_last_path = false;

    //false <=> false or not known
    bool is_fence = false;

    uint64_t time_visit = 0;
};

#endif //INC_1C_CELL_H
