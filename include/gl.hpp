#pragma once

#include <memory>
#include <fstream>
#include "include/starfox.hpp"
#include "include/params.hpp"
#include "include/shared_data.hpp"

namespace GL
{
extern StarFox starfox;
extern int gl_timer;

extern std::ifstream wii_input;
extern bool is_beam;
extern bool is_bomb;

void init(void);

void display(void);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void keyboardSpecial(int key, int x, int y);
void keyboardSpecialUp(int key, int x, int y);
void idle(void);

void setAccUsingCv();
void setAccUsingWii();
}
