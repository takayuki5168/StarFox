#include <iostream>
#include <cmath>
#include <random>
#include "include/attack_carrier.hpp"
#include "include/params.hpp"
#include "include/util.hpp"

void AttackCarrier::update(State arwing_pos, State arwing_vel, State arwing_acc)
{
    if (m_is_alive) {
        // 物理状態を更新
        updateAcc(0.0, 0.0, 0.0);
        updateVel(arwing_pos, arwing_vel, arwing_acc);
        updatePos();
        updateOthers();
    }
}

void AttackCarrier::updateOthers()
{
    if (m_is_alive) {
        if (m_phase == 0) {
            for (unsigned int i = 0; i < m_each_hit_cnt.size(); i++) {
                if (m_each_hit_cnt.at(i) > 0) {
                    m_each_hit_cnt.at(i) -= 1;
                    m_each_hit_cnt_even.at(i) += 1;
                }
            }
            if (m_each_life_point.at(0) < 0.1
                and m_each_life_point.at(1) < 0.1
                and m_each_life_point.at(2) < 0.1) {
                m_phase = 1;
            }
        } else if (m_phase == 1) {
            if (m_hit_cnt > 0) {
                m_hit_cnt -= 1;
                m_hit_cnt_even += 1;
            }
            if (m_life_point < 0.1) {
                m_is_alive = false;
            }
        }
        m_timer_cnt++;
    }
}

void AttackCarrier::updateVel(State arwing_pos, State arwing_vel, State /*acc*/)
{
    m_vel.x += m_acc.x;
    m_vel.y += m_acc.y;
    m_vel.z += m_acc.z;

    // Arwingの目の前に来るように
    auto diff_pos_x = arwing_pos.x + arwing_vel.x * 400 - m_pos.x;
    auto diff_pos_y = arwing_pos.y + arwing_vel.y * 400 - m_pos.y;
    auto diff_pos_z = arwing_pos.z - 400 /*+ arwing_vel.z * 400*/ - m_pos.z;
    m_vel.x = velFunc(diff_pos_x);
    m_vel.y = velFunc(diff_pos_y);
    m_vel.z = velFunc(diff_pos_z);
}

int AttackCarrier::makeObject()
{
    if (m_timer_cnt % 400 > 200 and m_timer_cnt % 400 < 300) {
        if (m_timer_cnt % 40 == 0) {
            if (m_each_life_point.at(0) > 0) {
                if (m_each_life_point.at(1) > 0) {
                    return 0;
                } else {
                    return 1;
                }
            } else {
                if (m_each_life_point.at(1) > 0) {
                    return 2;
                } else {
                    return 3;
                }
            }
        }
    }
    return 3;
}

void AttackCarrier::draw(State arwing_pos)
{
    m_phai = Params::PI + std::atan2(arwing_pos.y - m_pos.y, arwing_pos.x - m_pos.x);

    double ang = 0;
    if (m_timer_cnt % 400 < 100) {
        ang = 0.0;
    } else if (m_timer_cnt % 400 < 200) {
        ang = (m_timer_cnt % 400 - 100) / 100.0 * 90;
    } else if (m_timer_cnt % 400 < 300) {
        ang = 90;
    } else {
        ang = (-m_timer_cnt % 400 - 400) / 100.0 * 90;
    }

    // 本体
    // clang-format off
    glPushMatrix();
        glTranslated(m_pos.x, m_pos.y, m_pos.z);
        if (m_phase == 1 and m_hit_cnt > 0 and static_cast<int>(m_hit_cnt_even) % 2 == 0) {
            glColor3d(1.0, 0.0, 0.0);
        } else {
          glColor3d(0.3, 0.3, 0.3);
        }
        glRotated(m_phai * 180.0 / static_cast<float>(Params::PI) - 90.0, 0.0, 0.0, 1.0);
        Util::drawRectangular(200, 100, 100);
    glPopMatrix();
    // clang-format on

    // 左
    if (m_each_life_point.at(2) > 0) {
        // clang-format off
        glPushMatrix();
            glTranslated(m_pos.x, m_pos.y, m_pos.z);
            if (m_each_hit_cnt.at(2) > 0 and static_cast<int>(m_each_hit_cnt_even.at(2)) % 2 == 0) {
                glColor3d(1.0, 0.0, 0.0);
            } else {
                glColor3d(0.6, 0.1, 0.1);
            }
            glRotated(m_phai * 180.0 / static_cast<float>(Params::PI) - 90.0, 0.0, 0.0, 1.0);
            glTranslated(160.0,0.0 ,0.0 );
            Util::drawRectangular(100, 300, 120);
        glPopMatrix();
        // clang-format on
    }

    if (m_each_life_point.at(0) > 0) {
        // 右上非可動部
        // clang-format off
        glPushMatrix();
            glTranslated(m_pos.x, m_pos.y, m_pos.z);
            if (m_each_hit_cnt.at(0) > 0 and static_cast<int>(m_each_hit_cnt_even.at(0)) % 2 == 0) {
                glColor3d(1.0, 0.0, 0.0);
            } else {
                glColor3d(0.3, 0.3, 0.3);
            }
            glRotated(m_phai * 180.0 / static_cast<float>(Params::PI) - 90.0, 0.0, 0.0, 1.0);
            glTranslated(-150.0,50.0 ,80.0 );
            Util::drawRectangular(60, 100, 100);
        glPopMatrix();
        // clang-format on

        // 右上可動部
        // clang-format off
        glPushMatrix();
            glTranslated(m_pos.x, m_pos.y, m_pos.z);
            glRotated(m_phai * 180.0 / static_cast<float>(Params::PI) - 90.0, 0.0, 0.0, 1.0);
            glTranslated(-150.0, 0.0, 130.0);
            glRotated(-ang, 1.0, 0.0, 0.0);
            glTranslated(0.0, -50.0, -50.0);
            if (m_each_hit_cnt.at(0) > 0 and static_cast<int>(m_each_hit_cnt_even.at(0)) % 2 == 0) {
                glColor3d(1.0, 0.0, 0.0);
            } else {
                glColor3d(0.6, 0.1, 0.1);
            }
            Util::drawRectangular(60, 100, 100);
        glPopMatrix();
     
        // 黒い部分上
        // clang-format off
        glPushMatrix();
            glTranslated(m_pos.x, m_pos.y, m_pos.z);
            //if (m_hit_cnt > 0) {
            //    glColor3d(1.0, 0.0, 0.0);
            //} else {
                glColor3d(0.1, 0.1, 0.1);
            //}
            glRotated(m_phai * 180.0 / static_cast<float>(Params::PI) - 90.0, 0.0, 0.0, 1.0);
            glTranslated(-150.0, -3.0 ,80.0);
            glBegin(GL_QUADS);
                glVertex3d(25.0, 0.0, 45.0);
                glVertex3d(25.0, 0, -45.0);
                glVertex3d(-25.0, 0.0, -45.0);
                glVertex3d(-25.0, 0.0, 45.0);
            glEnd();
        glPopMatrix();
        // clang-format on
    }

    if (m_each_life_point.at(1) > 0) {
        // 右下非可動部
        // clang-format off
        glPushMatrix();
            glTranslated(m_pos.x, m_pos.y, m_pos.z);
            if (m_each_hit_cnt.at(1) > 0 and static_cast<int>(m_each_hit_cnt_even.at(1)) % 2 == 0) {
                glColor3d(1.0, 0.0, 0.0);
            } else {
                glColor3d(0.3, 0.3, 0.3);
            }
            glRotated(m_phai * 180.0 / static_cast<float>(Params::PI) - 90.0, 0.0, 0.0, 1.0);
            glTranslated(-150.0,50.0 ,-100.0 );
            Util::drawRectangular(60, 100, 100);
        glPopMatrix();
        // clang-format on

        // 可動部右下
        // clang-format off
        glPushMatrix();
            glTranslated(m_pos.x, m_pos.y, m_pos.z);
            glRotated(m_phai * 180.0 / static_cast<float>(Params::PI) - 90.0, 0.0, 0.0, 1.0);
            glTranslated(-150.0, 0.0, -150.0);
            glRotated(ang, 1.0, 0.0, 0.0);
            glTranslated(0.0, -50.0, 50.0);
            if (m_each_hit_cnt.at(1) > 0 and static_cast<int>(m_each_hit_cnt_even.at(1)) % 2 == 0) {
                glColor3d(1.0, 0.0, 0.0);
            } else {
                glColor3d(0.6, 0.1, 0.1);
            }
            Util::drawRectangular(60, 100, 100);
        glPopMatrix();
        // clang-format on

        // 黒い部分右下
        // clang-format off
        glPushMatrix();
            glTranslated(m_pos.x, m_pos.y, m_pos.z);
            //if (m_hit_cnt > 0) {
            //    glColor3d(1.0, 0.0, 0.0);
            //} else {
                glColor3d(0.1, 0.1, 0.1);
            //}
            glRotated(m_phai * 180.0 / static_cast<float>(Params::PI) - 90.0, 0.0, 0.0, 1.0);
            glTranslated(-150.0, -3.0 ,-100.0);
            glBegin(GL_QUADS);
                glVertex3d(25.0, 0.0, 45.0);
                glVertex3d(25.0, 0, -45.0);
                glVertex3d(-25.0, 0.0, -45.0);
                glVertex3d(-25.0, 0.0, 45.0);
            glEnd();
        glPopMatrix();
        // clang-format on
    }


    //glPushMatrix();
    //glColor3d(1, 1, 1);
    //State left = {350, -200, 0};
    //State right_down = {50, -200, -100};
    //State right_up = {50, -200, 100};
    //auto pos = m_pos + left.mul(m_phai - Params::PI / 2.0);
    //glTranslated(pos.x, pos.y, pos.z);
    //glutSolidSphere(70, 10.0, 10.0);
    //glPopMatrix();
}

std::array<State, 3> AttackCarrier::getWeakPos()
{
    State left = {350, -200, 0};
    State right_down = {50, -200, -100};
    State right_up = {50, -200, 100};

    if (m_timer_cnt % 400 > 150 and m_timer_cnt % 400 < 350) {
        return {m_pos + right_up.mul(m_phai - Params::PI / 2.0),
            m_pos + right_down.mul(m_phai - Params::PI / 2.0),
            m_pos + left.mul(m_phai - Params::PI / 2.0)};
    } else {
        return {State{0.0, 0.0, 0.0},
            State{0.0, 0.0, 0.0},
            m_pos + left.mul(m_phai - Params::PI / 2.0)};
    }
}

double AttackCarrier::velFunc(double diff_pos)
{
    return diff_pos * 0.01;
}
