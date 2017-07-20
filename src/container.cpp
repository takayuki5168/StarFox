#include <iostream>
#include <cmath>
#include "include/container.hpp"

//void Container::updateOthers()
//{
//    if (m_is_alive == true) {
//        if (m_life_point <= 0) {
//            setDeath();
//        }
//        if (m_hit_cnt > 0) {
//            m_hit_cnt -= 1;
//            m_hit_cnt_even += 1;
//        }
//    }
//}

void Container::draw()
{
    if (m_is_alive) {
        glPushMatrix();
        if (m_hit_cnt > 0 and m_hit_cnt_even % 2 == 0) {
            glColor3d(1.0, 0.0, 0.0);
        } else {
            glColor3d(0.62, 0.31, 0.18);
            //glColor3d(0.2, 0.2, 0.2);
            //glColor3d(1.0, 1.0, 0.2);
        }
        glTranslated(m_pos.x, m_pos.y, m_pos.z);
        glutSolidCube(m_length);
        glPopMatrix();
    }
}
