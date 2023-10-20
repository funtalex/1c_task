//
// Created by funtalex on 20.10.23.
//

#ifndef INC_1C_LABIRINTH_SOLVER_H
#define INC_1C_LABIRINTH_SOLVER_H

//
// Created by funtalex on 20.10.23.
//
#include "labirinth_solver.h"
#include "cell.h"

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

class LabirinthSolver {
public:
    using CellMap = std::map<std::pair<int64_t, int64_t>, Cell>;
    using CoordT = std::pair<int64_t, int64_t>;

    LabirinthSolver(const Cell& start_cell, const Cell& next_cell, uint64_t step_time,
                    uint64_t turn_time, uint64_t fire_time, uint64_t sight_size);

    void Search();

private:
    Cell start_cell_;
    Cell next_cell_;
    Cell current_cell_;

    const uint64_t go_time_;
    const uint64_t turn_time_;
    const uint64_t fire_time_;
    const uint64_t sight_size_;

    static const int64_t LEFT = 0;
    static const int64_t UPPER = 1;
    static const int64_t RIGHT = 2;
    static const int64_t LOWER = 3;

    static const int64_t GO = 1;
    static const int64_t TURN = 2;
    static const int64_t FIRE = 3;

    int64_t current_side_;
    CellMap cell_map_;
    int64_t current_time_ = 0;
    bool is_finished_ = false;

    std::pair<int64_t, int64_t> NeighbourCoord(const Cell& cell, int64_t side) const;

    int64_t LeftTurn(int64_t) const;

    int64_t RightTurn(int64_t) const;

    int64_t OppositeTurn(int64_t) const;

    bool IsFence(char c);

    bool Go();

    void Turn(const std::string& where);

    void Fire();

    void Dfs(Cell& cell, Cell& parent_cell);

};
#endif //INC_1C_LABIRINTH_SOLVER_H
