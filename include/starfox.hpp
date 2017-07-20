#pragma once

#include <vector>
#include <GL/glut.h>
#include "include/arwing.hpp"
#include "include/enemy_random.hpp"
#include "include/enemy_updown.hpp"
#include "include/enemy_updown_bomb.hpp"
#include "include/attack_carrier.hpp"
#include "include/attack_carrier_bomb.hpp"
#include "include/arwing_bomb.hpp"
#include "include/arwing_beam.hpp"
#include "include/container.hpp"
#include "include/state.hpp"
#include "util.hpp"

class StarFox
{
public:
    static void init(void)
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glEnable(GL_DEPTH_TEST);
    }
    void display();

    void update();
    void makeObject();
    void detectCollision();
    void draw();
    void drawGround();

    void updateArwingAcc(double acc_x, double acc_y, double acc_z)
    {
        m_arwing.updateAcc(acc_x, acc_y, acc_z);
    }
    void setArwingAccZero(int num) { m_arwing.setAccZero(num); }

    void addArwingBomb(ArwingBomb arwing_bomb) { m_arwing_bombs.push_back(arwing_bomb); }
    void addArwingBeam(ArwingBeam arwing_beam) { m_arwing_beams.push_back(arwing_beam); }
    void addContainer(Container container) { m_containers.push_back(container); }
    void addEnemyRandom(EnemyRandom enemy_random) { m_enemies_random.push_back(enemy_random); }
    void addEnemyUpdown(EnemyUpdown enemy_updown) { m_enemies_updown.push_back(enemy_updown); }
    void addEnemyUpdownBomb(EnemyUpdownBomb enemy_updown_bomb)
    {
        m_enemy_updown_bombs.push_back(enemy_updown_bomb);
    }
    void addAttackCarrier(AttackCarrier attack_carrier)
    {
        m_attack_carriers.push_back(attack_carrier);
    }
    void addAttackCarrierBomb(AttackCarrierBomb attack_carrier_bomb)
    {
        m_attack_carrier_bombs.push_back(attack_carrier_bomb);
    }

    void setArwingRotate(int rotate_cnt) { m_arwing.setRotate(rotate_cnt); };

    State getArwingPos() { return m_arwing.getPos(); }
    State getArwingVel() { return m_arwing.getVel(); }
    State getArwingAcc() { return m_arwing.getAcc(); }

private:
    Arwing m_arwing;
    std::vector<ArwingBomb> m_arwing_bombs;
    std::vector<ArwingBeam> m_arwing_beams;
    std::vector<Container> m_containers;
    std::vector<EnemyRandom> m_enemies_random;
    std::vector<EnemyUpdown> m_enemies_updown;
    std::vector<EnemyUpdownBomb> m_enemy_updown_bombs;
    std::vector<AttackCarrier> m_attack_carriers;
    std::vector<AttackCarrierBomb> m_attack_carrier_bombs;

    double m_timer = 0.0;
};
