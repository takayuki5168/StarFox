#pragma once

#include <GL/glut.h>
#include "include/abst_object.hpp"

class EnemyRandom : public AbstObject
{
public:
    explicit EnemyRandom(double pos_x, double pos_y, double pos_z,
        double vel_x = 0.0, double vel_y = 4.0, double vel_z = 0.0,
        double acc_x = 0.0, double acc_y = 0.0, double acc_z = 0.0)
        : AbstObject(pos_x, pos_y, pos_z,
              vel_x, vel_y, vel_z,
              acc_x, acc_y, acc_z,
              m_max_vel = 6.0, m_life_point = 6.0,
              m_collision_dis = 50.0, m_cause_damage = -1.0) {}


    //void update() override { ; }
    //void update(State pos, State vel, State acc);
    void updateAcc(double acc_x, double acc_y, double acc_z) override;
    //void updateVel() override { ; }
    //void updateVel(State pos, State vel, State acc);
    //void updatePos() override;

    void draw() override;

private:
};
