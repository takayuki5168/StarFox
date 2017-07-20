#include "include/shared_data.hpp"

namespace SharedData
{
int pos_x = 0, pos_y = 0;
int area = 0;
std::mutex pos_mutex;
std::mutex area_mutex;

void setPos(int tmp_x, int tmp_y)
{
    std::lock_guard<std::mutex> pos_lock(pos_mutex);
    pos_x = tmp_x;
    pos_y = tmp_y;
}

std::pair<int, int> getPos()
{
    std::lock_guard<std::mutex> pos_lock(pos_mutex);
    return {pos_x, pos_y};
}

void setArea(int tmp_area)
{
    std::lock_guard<std::mutex> pos_lock(pos_mutex);
    area = tmp_area;
}

int getArea()
{
    std::lock_guard<std::mutex> pos_lock(pos_mutex);
    return area;
}
}
