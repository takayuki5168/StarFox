#pragma once

#include <GL/glut.h>
#include "include/abst_object.hpp"

class EnemyUpdown : public AbstObject
{
public:
    explicit EnemyUpdown(double pos_x, double pos_y, double pos_z)
        : AbstObject(pos_x, pos_y, pos_z,
              m_vel.x = 0.0, m_vel.y = 0.0, m_vel.z = 0.0,
              m_acc.x = 0.0, m_acc.y = 0.0, m_acc.z = 0.0,
              m_max_vel = 2.0, m_life_point = 10.0,
              m_collision_dis = 50.0, m_cause_damage = -1.0) {}

    //void update() override { ; }
    //void update(State pos, State vel, State acc);
    void updateAcc(double acc_x, double acc_y, double acc_z) override;
    //void updateVel() override { ; }
    //void updateVel(State pos, State vel, State acc);
    //void updatePos() override;

    int makeObject() override;

    void draw() override;

private:
    int m_timer_cnt = 0;
};
