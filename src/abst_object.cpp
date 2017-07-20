#include <cmath>
#include <iostream>
#include "include/abst_object.hpp"

void AbstObject::update()
{
    if (m_is_alive) {
        updateAcc(0.0, 0.0, 0.0);
        updateVel();
        updatePos();
        updateOthers();
    }
}

void AbstObject::updateOthers()
{
    if (m_is_alive) {
        if (m_life_point <= 0) {
            m_is_alive = false;
        }
        if (m_hit_cnt > 0) {
            m_hit_cnt -= 1;
            m_hit_cnt_even += 1;
        }
    }
}

void AbstObject::rangeMaxVel()
{
    if (m_vel.norm() > m_max_vel) {
        m_vel = m_vel.reg() * m_max_vel;
    }
}
