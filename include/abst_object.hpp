#pragma once

#include "include/state.hpp"
#include "include/util.hpp"

class AbstObject
{
public:
    AbstObject(double pos_x, double pos_y, double pos_z,
        double vel_x, double vel_y, double vel_z,
        double acc_x, double acc_y, double acc_z,
        double max_vel, double life_point, double collision_dis, double cause_damage)
        : m_pos(State{pos_x, pos_y, pos_z}),
          m_vel(State{vel_x, vel_y, vel_z}),
          m_acc(State{acc_x, acc_y, acc_z}),
          m_max_vel(max_vel), m_life_point(life_point),
          m_collision_dis(collision_dis), m_cause_damage(cause_damage) {}

    State getPos() const { return m_pos; }
    State getVel() const { return m_vel; }
    State getAcc() const { return m_acc; }

    void setPos(double x, double y, double z) { m_pos = State{x, y, z}; }
    void setVel(double x, double y, double z) { m_vel = State{x, y, z}; }
    void setAcc(double x, double y, double z) { m_acc = State{x, y, z}; }

    double getCollisionDis() { return m_collision_dis; }

    void addPos(double x, double y, double z) { m_pos = m_pos + State{x, y, z}; }
    void addVel(double x, double y, double z)
    {
        m_vel = m_vel + State{x, y, z};
        rangeMaxVel();
    }
    void addAcc(double x, double y, double z) { m_acc = m_acc + State{x, y, z}; }

    double normPos() const { return m_pos.norm(); }
    double normVel() const { return m_vel.norm(); }
    double normAcc() const { return m_acc.norm(); }

    void rangeMaxVel();

    virtual void update();
    // 加速度の更新であるupdateAccをOverrideする
    virtual void updateAcc(double x, double y, double z) { m_acc = State{x, y, z}; }
    // 上記又は速度の更新であるupdateVecをOverrideする
    virtual void updateVel()
    {
        m_vel = m_vel + m_acc;
        rangeMaxVel();
    }
    virtual void updatePos() { m_pos = m_pos + m_vel; }
    virtual void updateOthers();

    virtual int makeObject() { return 0; };

    void setHitCnt(double hit_cnt) { m_hit_cnt = hit_cnt; }
    void updateHitCnt(double diff_hit_cnt) { m_hit_cnt += diff_hit_cnt; }

    void updateLifePoint(double diff_life_point) { m_life_point += diff_life_point; }

    void setDeath() { m_is_alive = false; }
    bool isAlive() { return m_is_alive; }

    virtual void draw() = 0;

    double getCauseDamage() { return m_cause_damage; }
    virtual void getDamage(double damage)
    {
        updateLifePoint(damage);
        if (damage < 0) {
            updateHitCnt(1.0);
        }
    }

protected:
    State m_pos, m_vel, m_acc;

    double m_max_vel;
    double m_life_point;
    double m_collision_dis;
    double m_cause_damage;  // if plus set aite death

    bool m_is_alive = true;
    double m_hit_cnt = 0;
    int m_hit_cnt_even = 0;  // 赤と点滅させるため
};
