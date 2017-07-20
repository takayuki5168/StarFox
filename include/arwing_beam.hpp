#pragma once

#include <vector>
#include "include/abst_object.hpp"

class ArwingBeam : public AbstObject
{
public:
    explicit ArwingBeam(State pos, State vel, State acc, int type)
        : AbstObject(pos.x, pos.y, pos.z,
              vel.x, vel.y, vel.z,
              acc.x, acc.y, acc.z,
              m_max_vel = 100.0, m_life_point = 1.0,
              m_collision_dis = 0.0, m_cause_damage = -2.0),
          m_type(type) {}

    //void update() override;
    //void updateAcc(double acc_x, double acc_y, double acc_z) override;
    //void updateVel() override;
    //void updatePos() override;

    void draw() override;

    void getDamage(double /*damage*/) override { setDeath(); }

private:
    int m_type;
};
