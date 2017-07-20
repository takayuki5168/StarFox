#pragma once

#include <mutex>

namespace SharedData
{
extern int pos_x, pos_y, area;
extern std::mutex pos_mutex;
extern std::mutex area_mutex;

void setPos(int tmp_x, int tmp_y);
std::pair<int, int> getPos();

void setArea(int tmp_area);
int getArea();
}
