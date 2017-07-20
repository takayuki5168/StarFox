#pragma once

#include <cmath>
#include "include/util.hpp"

struct State {
public:
    double x, y, z;

    State operator+(const State state)
        const { return State{x + state.x, y + state.y, z + state.z}; }
    State operator-(const State state)
        const { return State{x - state.x, y - state.y, z - state.z}; }
    State operator*(const double num)
        const { return State{x * num, y * num, z * num}; }
    State operator/(const double num)
        const { return State{x / num, y / num, z / num}; }

    double norm() const { return Util::hypot(x, y, z); }

    State reg() const { return State{this->x, this->y, this->z} / this->norm(); }

    State mul(GLdouble phai) const { return State{
        this->x * std::cos(phai) + this->y * std::cos(-phai),
        this->x * std::sin(phai) + this->y * std::sin(phai),
        this->z}; }
};
