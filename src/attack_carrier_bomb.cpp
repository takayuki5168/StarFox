#include <iostream>
#include <GL/glut.h>
#include "include/attack_carrier_bomb.hpp"

void AttackCarrierBomb::update(State arwing_pos)
{
    if (m_is_alive) {
        updateAcc(arwing_pos);
        updateVel();
        updatePos();
        updateOthers();
    }
}
void AttackCarrierBomb::updateAcc(State arwing_pos)
{
    m_acc = /*State{0, 0, 0};*/ (arwing_pos - m_pos).reg() * 0.4;
}

void AttackCarrierBomb::updatePos()
{
    if (m_explode_cnt < 100) {
        m_pos.x += m_vel.x;
        m_pos.y += m_vel.y;
        m_pos.z += m_vel.z;
    } else if (m_explode_cnt < 120) {
        m_radius += 2.0;
    } else {
        m_is_alive = false;
    }
    m_explode_cnt++;
}

void AttackCarrierBomb::draw()
{
    if (m_is_alive == true) {
        // clang-format off
        glPushMatrix();
            if (m_radius > 10) {
                glColor3d(0.8, 0.0, 0.0);
            } else {
                glColor3d(0.4, 0.4, 0.4);
            }
            glTranslated(m_pos.x,
                m_pos.y,
                m_pos.z);
            glutSolidSphere(m_radius, 10.0, 10.0);
        glPopMatrix();
        // clang-format on
    }
}
