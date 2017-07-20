#pragma once

#include <GL/glut.h>
#include "include/abst_object.hpp"

class Arwing : public AbstObject
{
public:
    Arwing(double pos_x = 2000.0, double pos_y = -3000.0, double pos_z = 2000.0,
        double vel_x = 0.0, double vel_y = 4.0, double vel_z = 0.0,
        double acc_x = 0.0, double acc_y = 0.0, double acc_z = 0.0)
        : AbstObject(pos_x, pos_y, pos_z,
              vel_x, vel_y, vel_z,
              acc_x, acc_y, acc_z,
              m_max_vel = 16.0, m_life_point = 100.0,
              m_collision_dis = 5.0, m_cause_damage = 0.0) {}

    void update() override;
    void updateAcc(double acc_x, double acc_y, double acc_z) override;
    void updateVel() override;
    void updatePos() override;
    void updateOthers() override;
    void updateByVel();

    void draw() override;

    void setRotate(int rotate_cnt) { m_rotate_cnt = rotate_cnt; }
    int getRotate(void) { return m_rotate_cnt; }
    void updateRotate(int rotate_cnt) { m_rotate_cnt += rotate_cnt; }
    void setAccZero(int num);
    void setVel(double max_vel);

private:
    int m_rotate_cnt = 0;  // 回転
};
