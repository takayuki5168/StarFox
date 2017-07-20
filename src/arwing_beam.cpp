#include <iostream>
#include <GL/glut.h>
#include "include/arwing_beam.hpp"

void ArwingBeam::draw()
{
    if (m_is_alive) {
        switch (m_type) {
        case 0: {
            GLdouble vertex[][3] = {
                {m_pos.x, m_pos.y, m_pos.z},
                {m_pos.x + m_vel.x * 1.5,
                    m_pos.y + m_vel.y * 1.5,
                    m_pos.z + m_vel.z * 1.5}};

            // clang-format off
            glLineWidth(4.0f);
            glBegin(GL_LINES);
                glColor3d(0.0, 0.8, 0.0);
                glVertex3dv(vertex[0]);
                glVertex3dv(vertex[1]);
            glEnd();
            // clang-format on
            break;
        }
        case 1: {
            /*
            GLdouble vertex1[][3] = {
                {m_pos.x, m_pos.y, m_pos.z},
                {m_pos.x + m_vel.x * 0.8,
                    m_pos.y + m_vel.y * 0.8,
                    m_pos.z + m_vel.z * 0.8}};
            GLdouble vertex2[][3] = {
                {m_pos.x, m_pos.y, m_pos.z},
                {m_pos.x + m_vel.x * 0.8,
                    m_pos.y + m_vel.y * 0.8,
                    m_pos.z + m_vel.z * 0.8}};

            // clang-format off
            glLineWidth(4.0f);
            glBegin(GL_LINES);
                glColor3d(0.0, 0.8, 0.0);
                glVertex3dv(vertex1[0]);
                glVertex3dv(vertex1[1]);
            glEnd();
            // clang-format on

            // clang-format off
            glLineWidth(4.0f);
            glBegin(GL_LINES);
                glColor3d(0.0, 0.8, 0.0);
                glVertex3dv(vertex2[0]);
                glVertex3dv(vertex2[1]);
            glEnd();
            // clang-format on
            */
            break;
        }
        default:
            break;
        }
    }
}
