#include <iostream>
#include <GL/glut.h>
#include "include/enemy_updown_bomb.hpp"

void EnemyUpdownBomb::update(State arwing_pos)
{
    if (m_is_alive) {
        //updateAcc(arwing_pos);
        updateVel(arwing_pos);
        updatePos();
        updateOthers();
    }
}
void EnemyUpdownBomb::updateAcc(State /*arwing_pos*/)
{
    ;  //m_acc = (arwing_pos - m_pos).reg() * 10.0;
}

void EnemyUpdownBomb::updateVel(State arwing_pos)
{
    // Arwingの目の前に来るように
    auto diff_pos_x = arwing_pos.x - m_pos.x;
    auto diff_pos_y = arwing_pos.y - m_pos.y;
    auto diff_pos_z = arwing_pos.z - m_pos.z;
    m_vel.x = diff_pos_x * 0.03;
    m_vel.y = diff_pos_y * 0.01;
    m_vel.z = diff_pos_z * 0.02;
}

void EnemyUpdownBomb::updatePos()
{
    if (m_timer_cnt < 300) {
        m_pos.x += m_vel.x;
        m_pos.y += m_vel.y;
        m_pos.z += m_vel.z;
    } else {
        m_is_alive = false;
    }
    m_timer_cnt++;
}

void EnemyUpdownBomb::draw()
{
    if (m_is_alive) {
        // clang-format off
        glPushMatrix();
            //if (m_radius > 10) {
            //    glColor3d(0.8, 0.0, 0.0);
            //} else {
                glColor3d(0.6, 0.6, 0.6);
            //}
            glTranslated(m_pos.x,
                m_pos.y,
                m_pos.z);
            glutSolidSphere(m_radius, 10.0, 10.0);
        glPopMatrix();
        // clang-format on
    }
}
