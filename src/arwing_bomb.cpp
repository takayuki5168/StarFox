#include "include/arwing_bomb.hpp"
#include <iostream>
#include <GL/glut.h>

void ArwingBomb::updatePos()
{
    //std::cout << m_vel.x << std::endl;
    if (m_explode_cnt < 100) {
        m_pos.x += m_vel.x * 1;
        m_pos.y += m_vel.y * 1;
        m_pos.z += m_vel.z * 1;
    } else if (m_explode_cnt < 130) {
        m_radius += 12.0;
    } else {
        m_is_alive = false;
    }
    m_collision_dis = m_radius;
    m_explode_cnt++;
}

void ArwingBomb::draw()
{
    if (m_is_alive) {
        glPushMatrix();
        if (m_radius > 2.1) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_SRC_ALPHA);
            glColor4d(1.0, 0.0, 0.0, 0.5);
        } else {
            glColor3d(1.0, 0.0, 0.0);
        }
        glTranslated(m_pos.x,
            m_pos.y,
            m_pos.z);
        glutSolidSphere(m_radius, 10.0, 10.0);
        glPopMatrix();
        if (m_radius > 2.1) {
            glDisable(GL_BLEND);
        }
    }
}
