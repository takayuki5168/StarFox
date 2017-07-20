#include <iostream>
#include <cmath>
#include <random>
#include "include/enemy_updown.hpp"
#include "include/params.hpp"
#include "include/util.hpp"

void EnemyUpdown::updateAcc(double /*acc_x*/, double /*acc_y*/, double /*acc_z*/)
{
    //if (m_life_point <= 0) {
    //    m_is_alive = false;
    //}
    //if (m_hit_cnt > 0) {
    //    m_hit_cnt -= 1;
    //}

    // 周期的に上下する
    if (m_timer_cnt % 300 > 150) {
        m_acc.z = 1;
    } else {
        m_acc.z = -1;
    }
    m_timer_cnt++;
}

int EnemyUpdown::makeObject()
{
    if (m_timer_cnt % 100 == 0) {
        return 0;
    } else {
        return 1;
    }
}


void EnemyUpdown::draw()
{
    glPushMatrix();
    glTranslated(m_pos.x, m_pos.y, m_pos.z);
    glRotated(m_timer_cnt * 10.0, 0.0, 0.0, 1.0);

    // clang-format off
    if (m_hit_cnt > 0 && m_hit_cnt_even % 2 == 0) {
        glColor3d(1.0, 0.0, 0.0);
    } else {
        //glColor3d(0.62, 0.31, 0.18);
        glColor3d(0.0, 0.0, 0.6);
    }
    glBegin(GL_POLYGON);
        glVertex3d(45, 0, 45);
        glVertex3d(6, 0, 12);
        glVertex3d(6, 0, -45);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3d(-45, 0, 45);
        glVertex3d(-6, 0, 12);
        glVertex3d(-6, 0, -45);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3d(6, 0, -60);
        glVertex3d(30, 0, -90);
        glVertex3d(60, 0, -105);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3d(-6, 0, -60);
        glVertex3d(-30, 0, -90);
        glVertex3d(-60, 0, -105);
    glEnd();
    if (m_hit_cnt > 0) {
        glColor3d(1.0, 0.0, 0.0);
    } else {
        glColor3d(1.0, 1.0, 0.0);
    }
    glBegin(GL_POLYGON);
        glVertex3d(12, 0, -39);
        glVertex3d(12, 0, -66);
        glVertex3d(-12, 0, -66);
        glVertex3d(-12, 0, -39);
    glEnd();
    // clang-format on
    glPopMatrix();
}
