#pragma once

#include <GL/glut.h>
#include "include/abst_object.hpp"

class Container : public AbstObject
{
public:
    explicit Container(double pos_x, double pos_y, double pos_z, int length)
        : AbstObject(pos_x, pos_y, pos_z,
              m_vel.x = 0.0, m_vel.y = 0.0, m_vel.z = 0.0,
              m_acc.x = 0.0, m_acc.y = 0.0, m_acc.z = 0.0,
              m_max_vel = 0.0, m_life_point = 10.0,
              m_collision_dis = length, m_cause_damage = -1.0),
          m_length(length) {}

    //void update() override { ; }
    //void update(State pos, State vel, State acc);
    //void updateAcc(double acc_x, double acc_y, double acc_z) override;
    //void updateVel() override { ; }
    //void updateVel(State pos, State vel, State acc);
    //void updatePos() override;
    //void updateOthers() override;

    void draw(void) override;

private:
    double m_length;
};
