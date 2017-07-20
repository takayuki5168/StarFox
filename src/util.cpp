#include <cmath>
#include "include/util.hpp"

namespace Util
{

double sgn(double num)
{
    if (num > 0)
        return 1.0;
    else
        return -1.0;
}

double hypot(double num1, double num2, double num3)
{
    return std::sqrt(pow(num1, 2.0) + pow(num2, 2.0) + pow(num3, 2.0));
}

void drawRectangular(double width, double depth, double height)
{
    auto w = width / 2.0;
    auto d = depth / 2.0;
    auto h = height / 2.0;
    GLdouble vertex[][3] = {
        {-w, -d, -h},
        {w, -d, -h},
        {w, d, -h},
        {-w, d, -h},
        {-w, -d, h},
        {w, -d, h},
        {w, d, h},
        {-w, d, h}};
    int face[][4] = {
        {0, 1, 2, 3},
        {1, 5, 6, 2},
        {5, 4, 7, 6},
        {4, 0, 3, 7},
        {4, 5, 1, 0},
        {3, 2, 6, 7}};

    glBegin(GL_QUADS);
    for (int j = 0; j < 6; ++j) {
        for (int i = 0; i < 4; ++i) {
            glVertex3dv(vertex[face[j][i]]);
        }
    }
    glEnd();
}

}  // namespace Util
