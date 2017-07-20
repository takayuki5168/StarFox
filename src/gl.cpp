#include <iostream>
#include <cmath>
#include <thread>
#include <GL/glut.h>
#include <random>
#include "include/gl.hpp"
#include "include/params.hpp"
#include "include/arwing.hpp"
#include "include/enemy_random.hpp"
#include "include/enemy_updown.hpp"
#include "include/attack_carrier.hpp"
#include "include/attack_carrier_bomb.hpp"
#include "include/arwing_bomb.hpp"
#include "include/arwing_beam.hpp"
#include "include/container.hpp"
#include "include/util.hpp"

namespace GL
{
StarFox starfox;
int gl_timer = 0;
std::ifstream wii_input;

bool is_beam = false;
bool is_bomb = false;

void init()
{
    constexpr int CONTAINER_NUM = 60;
    constexpr int ENEMY_RANDOM_NUM = 20;
    constexpr int ENEMY_UPDOWN_NUM = 15;
    std::random_device rand;

    for (int i = 0; i < ENEMY_RANDOM_NUM; i++) {
        EnemyRandom enemy_random{rand() % 4000 - 2000.0,
            rand() % 4000 - 2000.0,
            rand() % 4000 - 2000.0};
        GL::starfox.addEnemyRandom(enemy_random);
    }

    for (int i = 0; i < ENEMY_UPDOWN_NUM; i++) {
        EnemyUpdown enemy_updown{rand() % 8000 - 4000.0,
            rand() % 8000 - 4000.0,
            rand() % 8000 - 4000.0};
        GL::starfox.addEnemyUpdown(enemy_updown);
    }

    for (int i = 0; i < CONTAINER_NUM; i++) {
        Container container{rand() % 10000 - 5000.0,
            rand() % 10000 - 5000.0,
            rand() % 10000 - 5000.0,
            300 /*rand() % 50 + 50*/};
        GL::starfox.addContainer(container);
    }
}

void display(void)
{
    gl_timer++;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (Params::mode) {
    case 0:  // Normal Mode
        break;
    case 1:  // Wii Remocon Mode
        setAccUsingWii();
        break;
    case 2:  // VR Mode
        setAccUsingCv();
        break;
    default:
        break;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0,
        static_cast<double>(Params::WINDOW_WIDTH) / static_cast<double>(Params::WINDOW_HEIGHT),
        0.1, 200000.0);

    starfox.update();  // 更新

    starfox.makeObject();  // オブジェクトの生成

    starfox.detectCollision();  // 当たり判定

    // 視点の更新
    auto pos = starfox.getArwingPos();
    auto vel = starfox.getArwingVel();

    gluLookAt(
        //0, 0, 10000,
        //0, 0, 0,
        //0.0, 1.0, 0.0);
        pos.x - vel.x * 100,
        pos.y - vel.y * 100,
        pos.z + 200 /*- state.vel_z * 30*/,
        pos.x,
        pos.y,
        pos.z,
        0.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, Params::WINDOW_WIDTH, Params::WINDOW_HEIGHT);

    starfox.draw();  // 描画

    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int)
{
    constexpr double NORMAL_ACC = 0.02;
    constexpr double HIGHSPEED_ACC = 3;
    double acc_lr = 0.0, acc_fb = 0.0, acc_ud = 0.0;

    const State arwing_pos = starfox.getArwingPos();
    const State arwing_vel = starfox.getArwingVel();
    const State arwing_acc = starfox.getArwingAcc();

    if (key == 'k') {
        acc_ud = NORMAL_ACC;
    }
    if (key == 'j') {
        acc_ud = -NORMAL_ACC;
    }
    if (key == 'l') {
        acc_lr = NORMAL_ACC;
    }
    if (key == 'h') {
        acc_lr = -NORMAL_ACC;
    }
    if (key == 'z') {  // Rotate
        starfox.setArwingRotate(10);
    }
    if (key == 'x') {  // Acc
        acc_fb = HIGHSPEED_ACC;
    }
    if (key == 'a') {  // Beam
        starfox.addArwingBeam(ArwingBeam{
            arwing_pos,
            arwing_vel / arwing_vel.norm() * 40.0,
            arwing_acc, 0});
    }
    if (key == 's') {  // Bomb
        starfox.addArwingBomb(ArwingBomb{
            arwing_pos,
            arwing_vel / arwing_vel.norm() * 10.0});
    }

    starfox.updateArwingAcc(acc_lr, acc_fb, acc_ud);
}

void keyboardUp(unsigned char key, int, int)
{
    if (key == 'k') {
        starfox.setArwingAccZero(2);
    }
    if (key == 'j') {
        starfox.setArwingAccZero(2);
    }
    if (key == 'l') {
        starfox.setArwingAccZero(0);
    }
    if (key == 'h') {
        starfox.setArwingAccZero(0);
    }
    if (key == 'x') {
        starfox.setArwingAccZero(1);
    }
}

void keyboardSpecial(int key, int, int)
{
    constexpr double NORMAL_ACC = 0.02;
    double acc_lr = 0.0, acc_fb = 0.0, acc_ud = 0.0;

    if (key == GLUT_KEY_UP) {
        acc_ud = NORMAL_ACC;
    }
    if (key == GLUT_KEY_DOWN) {
        acc_ud = -NORMAL_ACC;
    }
    if (key == GLUT_KEY_RIGHT) {
        acc_lr = NORMAL_ACC;
    }
    if (key == GLUT_KEY_LEFT) {
        acc_lr = -NORMAL_ACC;
    }
    starfox.updateArwingAcc(acc_lr, acc_fb, acc_ud);
}

void keyboardSpecialUp(int key, int, int)
{
    if (key == GLUT_KEY_UP) {
        starfox.setArwingAccZero(2);
    }
    if (key == GLUT_KEY_DOWN) {
        starfox.setArwingAccZero(2);
    }
    if (key == GLUT_KEY_RIGHT) {
        starfox.setArwingAccZero(0);
    }
    if (key == GLUT_KEY_LEFT) {
        starfox.setArwingAccZero(0);
    }
}

void idle(void)
{
    glutPostRedisplay();
}

void setAccUsingCv()
{
    auto pos = SharedData::getPos();
    int x = pos.first;
    int y = pos.second;
    auto area = SharedData::getArea();

    //std::cout << x << " " << y << " " << area << std::endl;

    if (area > 3000) {
        return;
    }

    constexpr int WINDOW_HEIGHT = 480;
    constexpr int WINDOW_WIDTH = 640;
    constexpr double NORMAL_ACC = 0.00004;
    double acc_lr = 0.0, acc_fb = 0.0, acc_ud = 0.0;

    const State arwing_pos = starfox.getArwingPos();
    const State arwing_vel = starfox.getArwingVel();
    const State arwing_acc = starfox.getArwingAcc();

    acc_ud = NORMAL_ACC * -(y - WINDOW_WIDTH / 2.0);
    acc_lr = NORMAL_ACC * -(x - WINDOW_HEIGHT / 2.0);
    //std::cout << acc_ud << " " << acc_lr << " " << area << std::endl;
    if (gl_timer % 20 == 0) {  // Beam
        starfox.addArwingBeam(ArwingBeam{
            arwing_pos,
            arwing_vel / arwing_vel.norm() * 40.0,
            arwing_acc, 0});
    }

    starfox.updateArwingAcc(acc_lr, acc_fb, acc_ud);
}

void setAccUsingWii()
{
    std::string po1, po2, po3, po4, po5, po6;
    wii_input.open("wii_input.txt", std::ifstream::in);
    if (wii_input.eof()) {
        wii_input.close();
        return;
    }
    wii_input >> po1 >> po2 >> po3 >> po4 >> po5 >> po6;
    //std::cout << po3 << std::endl;
    if (po3 != "0" and po3 != "1") {
        wii_input.close();
        return;
    }
    int pitch = 0, roll = 0, beam = 0, bomb = 0, rotate = 0, acc = 0;
    pitch = std::stoi(po1);
    roll = std::stoi(po2);
    beam = std::stoi(po3);
    bomb = std::stoi(po4);
    rotate = std::stoi(po5);
    acc = std::stoi(po6);

    constexpr double NORMAL_ACC = 0.02;
    constexpr double HIGHSPEED_ACC = 3;
    double acc_lr = 0.0, acc_fb = 0.0, acc_ud = 0.0;

    const State arwing_pos = starfox.getArwingPos();
    const State arwing_vel = starfox.getArwingVel();
    const State arwing_acc = starfox.getArwingAcc();

    acc_ud = -pitch * NORMAL_ACC * Params::PI / 180.0;
    acc_lr = -roll * NORMAL_ACC * Params::PI / 180.0;
    if (beam > 0) {  // Beam
        if (!is_beam) {
            starfox.addArwingBeam(ArwingBeam{
                arwing_pos,
                arwing_vel / arwing_vel.norm() * 40.0,
                arwing_acc, 0});
            is_beam = true;
        }
    } else {
        is_beam = false;
    }
    if (bomb > 0) {  // Bomb
        if (!is_bomb) {
            starfox.addArwingBomb(ArwingBomb{
                arwing_pos,
                arwing_vel / arwing_vel.norm() * 10.0});
            is_bomb = true;
        }
    } else {
        is_bomb = false;
    }
    if (rotate > 0) {  // Rotate
        starfox.setArwingRotate(10);
    }
    if (acc > 0) {  // Acc
        acc_fb = HIGHSPEED_ACC;
    }

    starfox.updateArwingAcc(acc_lr, acc_fb, acc_ud);
    wii_input.close();
}

}  // namespce GL
