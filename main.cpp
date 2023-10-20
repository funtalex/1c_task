#include "cell.h"
#include "labirinth_solver.h"

#include <cstdint>
#include <iostream>

int main() {
    int64_t x;
    int64_t y;
    int64_t x_1;
    int64_t y_1;
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t k;



    LabirinthSolver solver(Cell(x, y), Cell(x_1, y_1), a, b, c, k);

    solver.Search();

    return 0;
}
