#pragma once
#include <array>
#include <GL/glut.h>
#include "include/abst_object.hpp"

class AttackCarrier : public AbstObject
{
public:
    explicit AttackCarrier(double pos_x = 0.0, double pos_y = 0.0, double pos_z = 0.0,
        double vel_x = 0.0, double vel_y = 0.0, double vel_z = 0.0,
        double acc_x = 0.0, double acc_y = 0.0, double acc_z = 0.0)
        : AbstObject(pos_x, pos_y, pos_z,
              vel_x, vel_y, vel_z,
              acc_x, acc_y, acc_z,
              m_max_vel = 10.0, m_life_point = 10.0,
              m_collision_dis = 50.0, m_cause_damage = -5.0)
    {
        m_each_life_point = {m_life_point * 1.5, m_life_point * 1.5, m_life_point * 2};
        m_each_hit_cnt = {0.0, 0.0, 0.0};
        m_each_hit_cnt_even = {0.0, 0.0, 0.0};
    }

    void update() override { ; }
    void update(State arwing_pos, State arwing_vel, State arwing_acc);
    //void updateAcc(double acc_x, double acc_y, double acc_z) override;
    void updateVel() override { ; }
    void updateVel(State arwing_pos, State arwing_vel, State arwing_acc);
    //void updatePos() override;
    void updateOthers() override;

    int makeObject() override;

    void draw() override { ; }
    void draw(State arwing_pos);

    double getPhai() { return m_phai; }
    std::array<State, 3> getWeakPos();
    double getWeakCollisionDis() { return 70; }

    void getEachDamage(int cnt, double damage)
    {
        m_each_life_point.at(cnt) += damage;
        if (damage < 0) {
            m_each_hit_cnt.at(cnt) += 1.0;
        }
    }

    int getPhase() { return m_phase; }


private:
    //int m_type;
    int m_timer_cnt = 0;
    double m_phai = 0.0;
    ///*constexpr */ double max_vel = 10.0;
    std::array<double, 3> m_each_life_point;
    std::array<double, 3> m_each_hit_cnt;
    std::array<double, 3> m_each_hit_cnt_even;

    double velFunc(double diff_pos);
    int m_phase = 0;
};
