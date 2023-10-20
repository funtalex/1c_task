//
// Created by funtalex on 20.10.23.
//
#include "labirinth_solver.h"
#include "cell.h"

#include <vector>
#include <map>
#include <stdexcept>
#include <string>

LabirinthSolver::LabirinthSolver(const Cell& start_cell, const Cell& next_cell, uint64_t step_time,
                uint64_t turn_time, uint64_t fire_time, uint64_t sight_size) :
                start_cell_(start_cell), next_cell_(next_cell), current_cell_(start_cell),
                go_time_(step_time), turn_time_(turn_time), fire_time_(fire_time),
                sight_size_(sight_size) {
    start_cell_.is_visited = true;
    cell_map_[CoordT(start_cell.x, start_cell_.y)] = start_cell_;
    cell_map_[CoordT(next_cell.x, next_cell.y)] = next_cell_;

    if (start_cell.y == next_cell.y) {
        if (start_cell.x - 1 == next_cell.x) {
            current_side_ = LEFT;
        } else {
            current_side_ = RIGHT;
        }
    } else {
        if (start_cell.y - 1 == next_cell.y) {
            current_side_ = LOWER;
        } else {
            current_side_ = UPPER;
        }
    }
}

void LabirinthSolver::Search() {
    Cell& start = cell_map_[CoordT(start_cell_.x, start_cell_.y)];
    Dfs(start, start);
    std::cout << "4, " << current_time_;
}

std::pair<int64_t, int64_t> LabirinthSolver::NeighbourCoord(const Cell& cell, int64_t side) const {
    if (side == LEFT) {
        return {cell.x - 1, cell.y};
    }
    if (side == RIGHT) {
        return {cell.x + 1, cell.y};
    }
    if (side == UPPER) {
        return {cell.x, cell.y + 1};
    }
    if (side == LOWER) {
        return {cell.x, cell.y - 1};
    }

    throw std::invalid_argument("Wrong side: " + side);
}

int64_t LabirinthSolver::LeftTurn(int64_t side) const {
    return (side + 3) % 4;
}

int64_t LabirinthSolver::RightTurn(int64_t side) const {
    return (side + 1) % 4;
}

int64_t LabirinthSolver::OppositeTurn(int64_t side) const {
    return (side + 2) % 4;
}

bool LabirinthSolver::IsFence(char c) {
    return c == '#';
}

bool LabirinthSolver::Go() {
    std::cout << GO << '\n';
    uint64_t feedback;
    std::cin >> feedback;

    current_time_ += go_time_;

    if (feedback == 0) {
        return false;
    }

    if (current_side_ == LEFT) {
        current_cell_.x -= 1;
    }
    if (current_side_ == RIGHT) {
        current_cell_.x += 1;
    }
    if (current_side_ == LOWER) {
        current_cell_.y -= 1;
    }
    if (current_side_ == UPPER) {
        current_cell_.y += 1;
    }
    return true;
}

void LabirinthSolver::Turn(const std::string& where) {
    std::cout << TURN << ", ";
    if (where == "left") {
        std::cout << 0 << '\n';
        current_side_ = (current_side_ + 3) % 4;
    } else {
        std::cout << 1 << '\n';
        current_side_ = (current_side_ + 1) % 4;
    }
    current_time_ += turn_time_;
    uint64_t feedback;
    std::cin >> feedback;
}

void LabirinthSolver::Fire() {
    std::cout << FIRE;
    current_time_ += fire_time_;
    std::string sight;
    int64_t center = sight_size_ + 1;

    for (int64_t y_index = 0; y_index < 2 * sight_size_ + 1; ++y_index) {
        std::cin >> sight;
        for (int64_t x_index = 0; x_index < 2 * sight_size_ + 1; ++x_index) {
            cell_map_[CoordT(current_cell_.x + x_index - center,
                             current_cell_.y + y_index - center)].is_fence = IsFence(sight[x_index]);
        }
    }
}

void LabirinthSolver::Dfs(Cell& current_cell, Cell& parent_cell) {
    Cell center_cell;
    Cell left_cell;
    Cell right_cell;

    center_cell = cell_map_[NeighbourCoord(current_cell, current_side_)];
    left_cell = cell_map_[NeighbourCoord(current_cell, LeftTurn(current_side_))];
    right_cell = cell_map_[NeighbourCoord(current_cell, RightTurn(current_side_))];



    if (fire_time_ < 3 * turn_time_) {
        Fire();
        if (!center_cell.is_visited && !center_cell.is_fence) {
            Go();
            Dfs(current_cell_, current_cell);
            if (!left_cell.is_visited && !left_cell.is_fence) {
                Turn("right");
                Go();
                Dfs(current_cell_, current_cell);
                if (!right_cell.is_visited && !right_cell.is_fence) {
                    Go();
                    Dfs(current_cell_, current_cell);
                    Turn("left");
                } else {
                    Turn("right");
                }
            } else {
                if (!right_cell.is_visited && !right_cell.is_fence) {
                    Turn("left");
                    Go();
                    Dfs(current_cell_, current_cell);
                    Turn("left");
                } else {
                    Turn("right");
                }
            }
        } else {
            if (!left_cell.is_visited && !left_cell.is_fence) {
                Turn("left");
                Go();
                Dfs(current_cell_, current_cell);

                if (!right_cell.is_visited && !right_cell.is_fence) {
                    Go();
                    Dfs(current_cell_, current_cell);
                    Turn("left");
                } else {
                    Turn("right");
                }
                Go();
                Dfs(current_cell_, current_cell);
            } else {
                Turn("right");
                if (!right_cell.is_visited && !right_cell.is_fence) {
                    Go();
                    Dfs(current_cell_, current_cell);
                    Turn("right");
                }
            }
        }
    } else {
        if (!center_cell.is_visited && Go()) {
            Dfs(current_cell_, current_cell);
            Turn("right");
            if (!left_cell.is_visited && Go()) {
                Dfs(current_cell_, current_cell);
                if (!right_cell.is_visited && Go()) {
                    Dfs(current_cell_, current_cell);
                    Turn("left");
                } else {
                    Turn("right");
                }
            }
        } else {
            if (!left_cell.is_visited) {
                Turn("left");
                if (Go()) {
                    Dfs(current_cell_, current_cell);
                }
                if (!right_cell.is_visited) {
                    Turn("right");
                } else {
                    Turn("left");
                    Go();
                    return;
                }
            }
            Turn("right");
            if (!right_cell.is_visited && Go()) {
                Dfs(current_cell_, current_cell);
                Turn("right");
            }
        }
    }
    Go();
}