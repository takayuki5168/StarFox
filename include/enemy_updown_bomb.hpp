#pragma once

#include <vector>
#include "include/abst_object.hpp"

class EnemyUpdownBomb : public AbstObject
{
public:
    explicit EnemyUpdownBomb(State pos)
        : AbstObject(pos.x, pos.y, pos.z,
              m_vel.x = 0.0, m_vel.y = 0.0, m_vel.z = 0.0,
              m_acc.x = 0.0, m_acc.y = 0.0, m_acc.z = 0.0,
              m_max_vel = 2.0, m_life_point = 1.0,
              m_collision_dis = 0.0, m_cause_damage = -8.0) {}

    void update() override { ; }
    void update(State arwing_pos);
    void updateAcc(double /*acc_x*/, double /*acc_y*/, double /*acc_z*/) override { ; }
    void updateAcc(State arwing_pos);
    void updateVel() override { ; }
    void updateVel(State arwing_pos);
    void updatePos() override;

    void draw() override;

    void getDamage(double /*damage*/) override { setDeath(); }

private:
    double m_radius = 5.0;
    int m_timer_cnt = 0;
};
