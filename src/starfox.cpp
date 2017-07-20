#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <GL/glut.h>
#include "include/starfox.hpp"
#include "include/params.hpp"

void StarFox::update()
{
    m_timer += 1;
    //std::cout << m_timer << std::endl;

    // update Arwing
    //switch (Params::mode) {
    //case 0:
    m_arwing.update();
    //    break;
    //case 1:
    //case 2:
    //    m_arwing.updateByVel();
    //    break;
    //default:
    //    break;
    //}

    // update ArwingBeam
    auto itr_be = m_arwing_beams.begin();
    while (itr_be != m_arwing_beams.end()) {
        if (itr_be->isAlive() == false) {
            itr_be = m_arwing_beams.erase(itr_be);
        } else {
            itr_be->update();
            itr_be++;
        }
    }

    // update ArwingBomb
    auto itr_bo = m_arwing_bombs.begin();
    while (itr_bo != m_arwing_bombs.end()) {
        if (itr_bo->isAlive() == false) {
            itr_bo = m_arwing_bombs.erase(itr_bo);
        } else {
            itr_bo->update();
            itr_bo++;
        }
    }

    std::cout << m_enemies_random.size() << std::endl;
    // update EnemyRandom
    auto itr_en_ra = m_enemies_random.begin();
    while (itr_en_ra != m_enemies_random.end()) {
        if (itr_en_ra->isAlive() == false) {
            itr_en_ra = m_enemies_random.erase(itr_en_ra);
        } else {
            itr_en_ra->update();
            itr_en_ra++;
        }
    }

    // update EnemyUpdown
    auto itr_en_ud = m_enemies_updown.begin();
    while (itr_en_ud != m_enemies_updown.end()) {
        if (itr_en_ud->isAlive() == false) {
            itr_en_ud = m_enemies_updown.erase(itr_en_ud);
        } else {
            itr_en_ud->update();
            itr_en_ud++;
        }
    }

    // update EnemyUpdownBomb
    auto itr_en_ud_bo = m_enemy_updown_bombs.begin();
    while (itr_en_ud_bo != m_enemy_updown_bombs.end()) {
        if (!itr_en_ud_bo->isAlive()) {
            itr_en_ud_bo = m_enemy_updown_bombs.erase(itr_en_ud_bo);
        } else {
            itr_en_ud_bo->update(m_arwing.getPos());
            itr_en_ud_bo++;
        }
    }

    // update AttackCarrier
    auto itr_ac = m_attack_carriers.begin();
    while (itr_ac != m_attack_carriers.end()) {
        if (itr_ac->isAlive() == false) {
            itr_ac = m_attack_carriers.erase(itr_ac);
        } else {
            itr_ac->update(m_arwing.getPos(), m_arwing.getVel(), m_arwing.getAcc());
            itr_ac++;
        }
    }

    // update AttackCarrierBomb
    auto itr_bo_fi_bo = m_attack_carrier_bombs.begin();
    while (itr_bo_fi_bo != m_attack_carrier_bombs.end()) {
        if (itr_bo_fi_bo->isAlive() == false) {
            itr_bo_fi_bo = m_attack_carrier_bombs.erase(itr_bo_fi_bo);
        } else {
            itr_bo_fi_bo->update(m_arwing.getPos());
            itr_bo_fi_bo++;
        }
    }

    // update Container
    auto itr_co = m_containers.begin();
    while (itr_co != m_containers.end()) {
        if (itr_co->isAlive() == false) {
            itr_co = m_containers.erase(itr_co);
        } else {
            itr_co->update();
            itr_co++;
        }
    }
}

void StarFox::makeObject()
{
    constexpr int ATTACK_CARRIER_NUM = 1;
    if (0.5 < m_timer and m_timer < 1.5) {
        for (int i = 0; i < ATTACK_CARRIER_NUM; i++) {
            AttackCarrier attack_carrier{0, 10000, 0};
            addAttackCarrier(attack_carrier);
        }
    }

    // make object by Arwing
    //m_arwing.update();

    // make object by EnemyRandom
    //auto itr_en_ra = m_enemies_random.begin();
    //while (itr_en_ra != m_enemies_random.end()) {
    //    if (itr_en_ra->isAlive() == false) {
    //        itr_en_ra = m_enemies_random.erase(itr_en_ra);
    //    } else {
    //        itr_en_ra->update();
    //        itr_en_ra++;
    //    }
    //}

    // make object by EnemyUpdown
    //auto itr_en_ud = m_enemies_updown.begin();
    //while (itr_en_ud != m_enemies_updown.end()) {
    //    if (itr_en_ud->isAlive() == false) {
    //        itr_en_ud = m_enemies_updown.erase(itr_en_ud);
    //    } else {
    //        itr_en_ud->update();
    //        itr_en_ud++;
    //    }
    //}

    // make object by EnemyUpdown
    for (auto itr_en = m_enemies_updown.begin(); itr_en != m_enemies_updown.end();
         ++itr_en) {
        switch (itr_en->makeObject()) {
        case 0: {
            State enemy_updown_pos = itr_en->getPos();

            EnemyUpdownBomb enemy_updown_bomb{enemy_updown_pos};

            //addEnemyUpdownBomb(enemy_updown_bomb);
            break;
        }
        default:
            break;
        }
    }

    // make object by AttackCarrier
    for (auto itr_ac = m_attack_carriers.begin(); itr_ac != m_attack_carriers.end();
         ++itr_ac) {
        switch (itr_ac->makeObject()) {
        case 0: {
            State attack_carrier_pos = itr_ac->getPos();
            GLdouble phai = itr_ac->getPhai() - Params::PI / 2.0;
            State arwing_pos = m_arwing.getPos();
            State right_up = {50, -200, 100};
            State right_down = {50, -200, -100};

            AttackCarrierBomb attack_carrier_bomb_up{attack_carrier_pos + right_up.mul(phai),
                (arwing_pos - attack_carrier_pos + right_up.mul(phai)) * 300};
            AttackCarrierBomb attack_carrier_bomb_down{attack_carrier_pos + right_down.mul(phai),
                (arwing_pos - attack_carrier_pos + right_down.mul(phai)) * 300};

            addAttackCarrierBomb(attack_carrier_bomb_up);
            addAttackCarrierBomb(attack_carrier_bomb_down);
            break;
        }
        case 1: {
            State attack_carrier_pos = itr_ac->getPos();
            GLdouble phai = itr_ac->getPhai() - Params::PI / 2.0;
            State arwing_pos = m_arwing.getPos();
            State right_up = {50, -200, 100};

            AttackCarrierBomb attack_carrier_bomb_up{attack_carrier_pos + right_up.mul(phai),
                (arwing_pos - attack_carrier_pos + right_up.mul(phai)) * 300};

            addAttackCarrierBomb(attack_carrier_bomb_up);
            break;
        }
        case 2: {
            State attack_carrier_pos = itr_ac->getPos();
            GLdouble phai = itr_ac->getPhai() - Params::PI / 2.0;
            State arwing_pos = m_arwing.getPos();
            State right_down = {50, -200, -100};

            AttackCarrierBomb attack_carrier_bomb_down{attack_carrier_pos + right_down.mul(phai),
                (arwing_pos - attack_carrier_pos + right_down.mul(phai)) * 300};

            addAttackCarrierBomb(attack_carrier_bomb_down);
            break;
        }
        default:
            break;
        }
    }
}

void StarFox::detectCollision()
{
    // {ArwingBeam}と{Container, EnemyRandom, EnemyUpdown,
    //                EnemyUpdownBomb, AttackCarrier, AttackCarrierBomb}
    for (auto itr_be = m_arwing_beams.begin(); itr_be != m_arwing_beams.end(); ++itr_be) {
        if (itr_be->isAlive() == false)
            continue;
        // ArwingBeamとContainer
        for (auto itr_co = m_containers.begin(); itr_co != m_containers.end(); ++itr_co) {
            if (itr_co->isAlive() == false)
                continue;
            auto pos_be = itr_be->getPos();
            auto pos_co = itr_co->getPos();

            auto distance = (pos_be - pos_co).norm();

            if (distance < (itr_be->getCollisionDis() + itr_co->getCollisionDis())) {
                itr_be->getDamage(itr_co->getCauseDamage());
                itr_co->getDamage(itr_be->getCauseDamage());
            }
        }
        // ArwingBeamとEnemyRandom
        for (auto itr_en_ra = m_enemies_random.begin(); itr_en_ra != m_enemies_random.end();
             ++itr_en_ra) {
            if (itr_en_ra->isAlive() == false)
                continue;
            auto pos_be = itr_be->getPos();
            auto pos_en_ra = itr_en_ra->getPos();

            auto distance = (pos_be - pos_en_ra).norm();

            if (distance < (itr_be->getCollisionDis() + itr_en_ra->getCollisionDis())) {
                itr_be->getDamage(itr_en_ra->getCauseDamage());
                itr_en_ra->getDamage(itr_be->getCauseDamage());
            }
        }
        // ArwingBeamとEnemyUpdown
        for (auto itr_en_ud = m_enemies_updown.begin(); itr_en_ud != m_enemies_updown.end();
             ++itr_en_ud) {
            if (itr_en_ud->isAlive() == false)
                continue;
            auto pos_be = itr_be->getPos();
            auto pos_en_ud = itr_en_ud->getPos();

            auto distance = (pos_be - pos_en_ud).norm();

            if (distance < (itr_be->getCollisionDis() + itr_en_ud->getCollisionDis())) {
                itr_be->getDamage(itr_en_ud->getCauseDamage());
                itr_en_ud->getDamage(itr_be->getCauseDamage());
            }
        }
        // ArwingBeamとAttackCarrier
        for (auto itr_ac = m_attack_carriers.begin(); itr_ac != m_attack_carriers.end();
             ++itr_ac) {
            if (!itr_ac->isAlive())
                continue;
            State pos_be = itr_be->getPos();
            std::array<State, 3> pos_ac = itr_ac->getWeakPos();

            const int phase = itr_ac->getPhase();
            if (phase == 0) {
                for (unsigned int i = 0; i < pos_ac.size(); i++) {
                    double distance = (pos_be - pos_ac.at(i)).norm();

                    if (distance < (itr_be->getCollisionDis() + itr_ac->getWeakCollisionDis())) {
                        itr_be->getDamage(itr_ac->getCauseDamage());
                        itr_ac->getEachDamage(i, itr_be->getCauseDamage());
                    }
                }
            } else if (phase == 1) {
                double distance = (pos_be - itr_ac->getPos()).norm();
                if (distance < (itr_be->getCollisionDis() + itr_ac->getCollisionDis())) {
                    itr_be->getDamage(itr_ac->getCauseDamage());
                    itr_ac->getDamage(itr_be->getCauseDamage());
                }
            }
        }
    }
    // {ArwingBomb}と{Container, EnemyRandom, EnemyUpdown,
    //                EnemyUpdownBomb, AttackCarrier, AttackCarrierBomb}
    for (auto itr_bo = m_arwing_bombs.begin(); itr_bo != m_arwing_bombs.end(); ++itr_bo) {
        if (itr_bo->isAlive() == false)
            continue;
        // ArwingBombとContainer
        for (auto itr_co = m_containers.begin(); itr_co != m_containers.end(); ++itr_co) {
            if (itr_co->isAlive() == false)
                continue;
            auto pos_bo = itr_bo->getPos();
            auto pos_co = itr_co->getPos();

            auto distance = (pos_bo - pos_co).norm();

            if (distance < (itr_bo->getCollisionDis() + itr_co->getCollisionDis())) {
                itr_bo->getDamage(itr_co->getCauseDamage());
                itr_co->getDamage(itr_bo->getCauseDamage());
            }
        }
        // ArwingBombとEnemyRandom
        for (auto itr_en_ra = m_enemies_random.begin(); itr_en_ra != m_enemies_random.end();
             ++itr_en_ra) {
            if (itr_en_ra->isAlive() == false)
                continue;
            auto pos_bo = itr_bo->getPos();
            auto pos_en_ra = itr_en_ra->getPos();

            auto distance = (pos_bo - pos_en_ra).norm();

            if (distance < (itr_bo->getCollisionDis() + itr_en_ra->getCollisionDis())) {
                itr_bo->getDamage(itr_en_ra->getCauseDamage());
                itr_en_ra->getDamage(itr_bo->getCauseDamage());
            }
        }
        // ArwingBombとEnemyUpdown
        for (auto itr_en_ud = m_enemies_updown.begin(); itr_en_ud != m_enemies_updown.end();
             ++itr_en_ud) {
            if (not itr_en_ud->isAlive())
                continue;
            auto pos_bo = itr_bo->getPos();
            auto pos_en_ud = itr_en_ud->getPos();

            auto distance = (pos_bo - pos_en_ud).norm();

            if (distance < (itr_bo->getCollisionDis() + itr_en_ud->getCollisionDis())) {
                itr_bo->getDamage(itr_en_ud->getCauseDamage());
                itr_en_ud->getDamage(itr_bo->getCauseDamage());
            }
        }
        // ArwingBombとAttackCarrier
        for (auto itr_ac = m_attack_carriers.begin(); itr_ac != m_attack_carriers.end();
             ++itr_ac) {
            if (not itr_ac->isAlive())
                continue;
            State pos_bo = itr_bo->getPos();
            std::array<State, 3> pos_ac = itr_ac->getWeakPos();

            const int phase = itr_ac->getPhase();
            if (phase == 0) {
                for (unsigned int i = 0; i < pos_ac.size(); i++) {
                    double distance = (pos_bo - pos_ac.at(i)).norm();

                    if (distance < (itr_bo->getCollisionDis() + itr_ac->getWeakCollisionDis())) {
                        itr_bo->getDamage(itr_ac->getCauseDamage());
                        itr_ac->getEachDamage(i, itr_bo->getCauseDamage());
                    }
                }
            } else if (phase == 1) {
                double distance = (pos_bo - itr_ac->getPos()).norm();
                if (distance < (itr_bo->getCollisionDis() + itr_ac->getCollisionDis())) {
                    itr_bo->getDamage(itr_ac->getCauseDamage());
                    itr_ac->getDamage(itr_bo->getCauseDamage());
                }
            }
        }
    }
    // {Arwing}と{Container, EnemyRandom, EnemyUpdown,
    //            EnemyUpdownBomb, AttackCarrier, AttackCarrierBomb}
    if (m_arwing.isAlive()) {
        // ArwingとContainer
        for (auto itr_co = m_containers.begin(); itr_co != m_containers.end(); ++itr_co) {
            if (!itr_co->isAlive())
                continue;
            auto pos_ar = m_arwing.getPos();
            auto pos_co = itr_co->getPos();

            auto distance = (pos_ar - pos_co).norm();

            if (distance < (m_arwing.getCollisionDis() + itr_co->getCollisionDis())) {
                m_arwing.getDamage(itr_co->getCauseDamage());
                itr_co->getDamage(m_arwing.getCauseDamage());
            }
        }
        // ArwingとEnemyRandom
        for (auto itr_en_ra = m_enemies_random.begin(); itr_en_ra != m_enemies_random.end(); ++itr_en_ra) {
            if (!itr_en_ra->isAlive())
                continue;
            auto pos_ar = m_arwing.getPos();
            auto pos_co = itr_en_ra->getPos();
            auto distance = (pos_ar - pos_co).norm();

            if (distance < (m_arwing.getCollisionDis() + itr_en_ra->getCollisionDis())) {
                m_arwing.getDamage(itr_en_ra->getCauseDamage());
                itr_en_ra->getDamage(m_arwing.getCauseDamage());
            }
        }
        // ArwingとEnemyUpdown
        for (auto itr_en_ud = m_enemies_updown.begin(); itr_en_ud != m_enemies_updown.end(); ++itr_en_ud) {
            if (!itr_en_ud->isAlive())
                continue;
            auto pos_ar = m_arwing.getPos();
            auto pos_co = itr_en_ud->getPos();
            auto distance = (pos_ar - pos_co).norm();

            if (distance < (m_arwing.getCollisionDis() + itr_en_ud->getCollisionDis())) {
                m_arwing.getDamage(itr_en_ud->getCauseDamage());
                itr_en_ud->getDamage(m_arwing.getCauseDamage());
            }
        }
    }
}

void StarFox::draw()
{
    // Arwing
    m_arwing.draw();

    // ArwingBeam
    for (auto itr = m_arwing_beams.begin(); itr != m_arwing_beams.end(); ++itr) {
        itr->draw();
    }
    // ArwingBomb
    for (auto itr = m_arwing_bombs.begin(); itr != m_arwing_bombs.end(); ++itr) {
        itr->draw();
    }

    // EnemyRandom
    for (auto itr = m_enemies_random.begin(); itr != m_enemies_random.end(); ++itr) {
        itr->draw();
    }

    // EnemyUpdown
    for (auto itr = m_enemies_updown.begin(); itr != m_enemies_updown.end(); ++itr) {
        itr->draw();
    }

    // EnemyUpdownBomb
    for (auto itr = m_enemy_updown_bombs.begin(); itr != m_enemy_updown_bombs.end(); ++itr) {
        itr->draw();
    }

    // AttackCarrier
    for (auto itr = m_attack_carriers.begin(); itr != m_attack_carriers.end(); ++itr) {
        itr->draw(m_arwing.getPos());
    }

    // AttackCarrierBomb
    for (auto itr = m_attack_carrier_bombs.begin(); itr != m_attack_carrier_bombs.end(); ++itr) {
        itr->draw();
    }

    // Container
    for (auto itr = m_containers.begin(); itr != m_containers.end(); ++itr) {
        itr->draw();
    }

    drawGround();  // Ground
}

void StarFox::drawGround(void)
{
    double ground_max = 20000.0;
    glLineWidth(3.0f);
    glColor3d(0.6, 0.6, 0.6);
    glBegin(GL_LINES);
    //xy平面
    for (double ly = -ground_max; ly <= ground_max; ly += 1000.0) {
        glColor3d(std::abs(ly) / ground_max, 0.0, 0.0);
        glVertex3d(-ground_max, ly, -5000);
        glColor3d(0, std::abs(ly) / ground_max, 0.0);
        glVertex3d(ground_max, ly, -5000);
    }
    for (double lx = -ground_max; lx <= ground_max; lx += 1000.0) {
        glColor3d(std::abs(lx) / ground_max, 0.0, 0.0);
        glVertex3d(lx, ground_max, -5000);
        glColor3d(0, 0, std::abs(lx) / ground_max);
        glVertex3d(lx, -ground_max, -5000);
    }
    // yz平面
    for (double ly = -ground_max; ly <= ground_max; ly += 1000.0) {
        glColor3d(1, 0, std::abs(ly) / ground_max);
        glVertex3d(0, ly, -ground_max);
        glColor3d(std::abs(ly) / ground_max, 0.0, 1.0);
        glVertex3d(0, ly, ground_max);
    }
    for (double lz = -ground_max; lz <= ground_max; lz += 1000.0) {
        glColor3d(std::abs(lz) / ground_max, 0, 1);
        glVertex3d(0, ground_max, lz);
        glColor3d(std::abs(lz) / ground_max, 0, 1);
        glVertex3d(0, -ground_max, lz);
    }
    // zx平面
    for (double lz = -ground_max; lz <= ground_max; lz += 1000.0) {
        glColor3d(0, std::abs(lz) / ground_max, 1);
        glVertex3d(-ground_max, 0, lz);
        glColor3d(1, std::abs(lz) / ground_max, 0);
        glVertex3d(ground_max, 0, lz);
    }
    for (double lx = -ground_max; lx <= ground_max; lx += 1000.0) {
        glColor3d(0, 1, std::abs(lx) / ground_max);
        glVertex3d(lx, 0, -ground_max);
        glColor3d(1, 0, std::abs(lx) / ground_max);
        glVertex3d(lx, 0, ground_max);
    }
    glEnd();

    //// clang-format off
    //glPushMatrix();
    //    glColor3d(0.62, 0.31, 0.18);
    //    glTranslated(0.0, 0.0, -30000.0);
    //    glBegin(GL_QUADS);
    //    glVertex3d(6000.0, 6000.0, 0.0);
    //    glVertex3d(6000.0, -6000.0, 0.0);
    //    glVertex3d(-6000.0, -6000.0, 0.0);
    //    glVertex3d(-6000.0, 6000.0, 0.0);
    //    glEnd();
    //glPopMatrix();
    //// clang-format on

    // clang-format off
    glPushMatrix();
        //glColor3d(0.0, 0.1, 0.5);
        glColor3d(0.0, 0.0, 0.0);
        glutSolidSphere(100000.0, 50, 50);
    glPopMatrix();
    // clang-format on
}
