#include <iostream>
#include <cmath>
#include <random>
#include "include/enemy_random.hpp"
#include "include/params.hpp"
#include "include/util.hpp"

void EnemyRandom::updateAcc(double /*acc_x*/, double /*acc_y*/, double /*acc_z*/)
{
    if (m_life_point <= 0) {
        setDeath();
    }
    if (m_hit_cnt > 0) {
        m_hit_cnt -= 1;
    }

    constexpr int RAND_NUM = 500;
    constexpr int MAX_RANGE = 500;

    std::random_device rand;
    if (std::abs(m_pos.x) > MAX_RANGE) {
        m_acc.x
            = -Util::sgn(m_pos.x) * (rand() % RAND_NUM) / 500.0;
    } else {
        m_acc.x
            += (rand() % RAND_NUM - RAND_NUM / 2.0) / 30000.0;
    }
    if (std::abs(m_pos.y) > MAX_RANGE) {
        m_acc.y
            = -Util::sgn(m_pos.y) * (rand() % RAND_NUM) / 500.0;
    } else {
        m_acc.y
            += (rand() % RAND_NUM - RAND_NUM / 2.0) / 30000.0;
    }
    if (std::abs(m_pos.z) > MAX_RANGE) {
        m_acc.z
            = -Util::sgn(m_pos.z) * (rand() % RAND_NUM) / 500.0;
    } else {
        m_acc.z
            += (rand() % RAND_NUM - RAND_NUM / 2.0) / 30000.0;
    }
}

void EnemyRandom::draw()
{
    static int po = 0;
    po++;
    GLdouble phai = std::atan2(m_vel.y, m_vel.x);
    GLdouble theta = std::atan2(m_vel.z,
        std::hypot(m_vel.x, m_vel.y));

    {  // 本体
        glPushMatrix();
        if (m_hit_cnt > 0) {
            glColor3d(1.0, 0.0, 0.0);
        } else {
            //glColor3d(0.0, 1.0, 0.1);
            glColor3d(0.5, 0.19, 0.5);
        }
        glTranslated(m_pos.x, m_pos.y, m_pos.z);
        glRotated(phai * 180.0 / Params::PI - 90.0, 0.0, 0.0, 1.0);
        glRotated(theta * 180.0 / Params::PI, 1.0, 0.0, 0.0);
        glRotated(-90.0, 1.0, 0.0, 0.0);
        glutSolidCone(18, 54, 10, 10);
        glPopMatrix();
    }
    {  // 翼
        glPushMatrix();
        if (m_hit_cnt > 0) {
            glColor3d(1.0, 0.0, 0.0);
        } else {
            glColor3d(0.0, 0.8, 0.3);
        }
        glTranslated(m_pos.x, m_pos.y, m_pos.z);
        glRotated(phai * 180.0 / Params::PI - 90.0, 0.0, 0.0, 1.0);
        glRotated(theta * 180.0 / Params::PI, 1.0, 0.0, 0.0);
        glRotated(-90.0, 1.0, 0.0, 0.0);
        // 右翼
        glBegin(GL_TRIANGLE_FAN);
        glVertex3d(54, 0, 0);
        glVertex3d(18, 9, 0);
        glVertex3d(18, -9, 0);
        glVertex3d(18, 0, 18);
        glEnd();
        // 左翼
        glBegin(GL_TRIANGLE_FAN);
        glVertex3d(-54, 0, 0);
        glVertex3d(-18, 9, 0);
        glVertex3d(-18, -9, 0);
        glVertex3d(-18, 0, 18);
        glEnd();
        glPopMatrix();
    }
}
