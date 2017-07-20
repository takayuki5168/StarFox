#pragma once

#include "include/abst_object.hpp"

class ArwingBomb : public AbstObject
{
public:
    explicit ArwingBomb(State pos, State vel)
        : AbstObject(pos.x, pos.y, pos.z,
              vel.x, vel.y, vel.z,
              m_acc.x = 0.0, m_acc.y = 0.0, m_acc.z = 0.0,
              m_max_vel = 100.0, m_life_point = 1.0,
              m_collision_dis = 0.0, m_cause_damage = -25.0) {}

    // void update() ovrride;
    // void updateAcc(double acc_x, double acc_y, double acc_z) override;
    // void updateVel() override;
    void updatePos() override;

    void getDamage(double /*damage*/) override { ; }

    void draw() override;

private:
    double m_radius = 2.0;
    int m_explode_cnt = 0;  // 爆発までのカウント
};
