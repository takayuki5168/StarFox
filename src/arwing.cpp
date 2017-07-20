#include <iostream>
#include <cmath>
#include "include/arwing.hpp"
#include "include/params.hpp"
#include "include/util.hpp"

void Arwing::update()
{
    if (isAlive()) {
        // 物理状態を更新
        //updateAcc(0.0, 0.0, 0.0 /*acc_x, acc_y, acc_z*/);
        updateVel();
        updatePos();
        updateOthers();
    }
}

void Arwing::updateOthers()
{
    if (m_is_alive) {
        if (m_hit_cnt > 0) {
            m_hit_cnt -= 1;
            m_hit_cnt_even += 1;
        }
    }
}

void Arwing::updateAcc(double acc_x, double acc_y, double acc_z)
{
    m_acc = State{acc_x, acc_y, acc_z};
}

void Arwing::updateVel()
{
    auto arwing_vel = getVel();
    auto arwing_acc = getAcc();

    auto theta = std::atan2(arwing_vel.y, arwing_vel.x);

    auto diff_vel_x = 6 * arwing_acc.x
                      * std::cos(Params::PI / 2.0 - theta);
    auto diff_vel_y = 6 * arwing_acc.x
                      * -std::sin(Params::PI / 2.0 - theta);
    auto diff_vel_z = 6 * arwing_acc.z;

    addVel(diff_vel_x, diff_vel_y, diff_vel_z);
}

void Arwing::updatePos()
{
    auto arwing_vel = getVel();
    auto arwing_acc = getAcc();

    addPos(arwing_vel.x * (1.0 + arwing_acc.y),
        arwing_vel.y * (1.0 + arwing_acc.y),
        arwing_vel.z * (1.0 + arwing_acc.y));
}

void Arwing::draw()
{
    State arwing_vel = getVel();

    GLdouble phai = std::atan2(arwing_vel.y, arwing_vel.x);
    GLdouble theta = std::atan2(arwing_vel.z,
        std::hypot(arwing_vel.x, arwing_vel.y));

    {  // アーウィン
        glPushMatrix();
        if (m_hit_cnt > 0 && m_hit_cnt_even % 2 == 0) {
            glColor3d(1.0, 0.0, 0.0);
        } else {
            glColor3d(0.5, 0.5, 0.5);
        }
        glTranslated(m_pos.x, m_pos.y, m_pos.z);
        glRotated(phai * 180.0 / static_cast<float>(Params::PI) - 90.0, 0.0, 0.0, 1.0);
        glRotated(theta * 180.0 / static_cast<float>(Params::PI), 1.0, 0.0, 0.0);
        glRotated(-90.0, 1.0, 0.0, 0.0);
        if (getRotate() > 0) {
            glRotated(getRotate() * 36.0 * 2, 0.0, 0.0, 1.0);
            updateRotate(-1);
        }
        glutSolidCone(18, 54, 10, 10);
        //glPopMatrix();

        if (m_hit_cnt > 0 && m_hit_cnt_even % 2 == 0) {
            glColor3d(1.0, 0.0, 0.0);
        } else {
            glColor3d(0.0, 0.0, 0.6);
        }
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
        /*
        // 右肩
        glBegin(GL_TRIANGLE_FAN);
        glVertex3d(-6, 0, 0);
        glVertex3d(-2, 1, 0);
        glVertex3d(-2, -1, 0);
        glVertex3d(-2, 0, 2);
        glEnd();
        // 左肩
        glBegin(GL_TRIANGLE_FAN);
        glVertex3d(-6, 0, 0);
        glVertex3d(-2, 1, 0);
        glVertex3d(-2, -1, 0);
        glVertex3d(-2, 0, 2);
        glEnd();
        */

        glPopMatrix();
    }


    {  // 的
        // clang-format off
        glPushMatrix();
            glColor3d(0.0, 0.8, 0.0);
            glTranslated(m_vel.x * 20,
                m_vel.y * 20,
                m_vel.z * 20);
            glTranslated(m_pos.x, m_pos.y, m_pos.z);
            glRotated(phai * 180.0 / static_cast<float>(Params::PI) - 90.0, 0.0, 0.0, 1.0);
            glRotated(theta * 180.0 / static_cast<float>(Params::PI), 1.0, 0.0, 0.0);

            glLineWidth(1.5f);
            glBegin(GL_LINE_LOOP);
                glVertex3d(10, 0, -10);
                glVertex3d(10, 0, 10);
                glVertex3d(-10, 0, 10);
                glVertex3d(-10, 0, -10);
            glEnd();
        glPopMatrix();
        // clang-format on

        glPushMatrix();
        glColor3d(0.0, 1.0, 0.0);
        glTranslated(m_vel.x * 30,
            m_vel.y * 30,
            m_vel.z * 30);
        glTranslated(m_pos.x, m_pos.y, m_pos.z);
        glRotated(phai * 180.0 / static_cast<float>(Params::PI) - 90.0, 0.0, 0.0, 1.0);
        glRotated(theta * 180.0 / static_cast<float>(Params::PI), 1.0, 0.0, 0.0);

        glLineWidth(1.2f);
        glBegin(GL_LINE_LOOP);
        glVertex3d(5, 0, -5);
        glVertex3d(5, 0, 5);
        glVertex3d(-5, 0, 5);
        glVertex3d(-5, 0, -5);
        glEnd();
        glPopMatrix();
    }
}

void Arwing::setAccZero(int num)
{
    switch (num) {
    case 0:
        m_acc.x = 0.0;
        break;
    case 1:
        m_acc.y = 0.0;
        break;
    case 2:
        m_acc.z = 0.0;
        break;
    default:
        break;
    }
}
