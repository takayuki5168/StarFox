#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <GL/glut.h>
#include "include/starfox.hpp"
#include "include/gl.hpp"
#include "include/color_tracking.hpp"
#include "include/params.hpp"

int main(int argc, char* argv[])
{
    Params::mode = 0;
    if (argc > 1) {
        if (std::string(argv[1]) == "-h") {
            std::cout << "[StarFox] Usage : ./main -w or ./main -v" << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "-w") {
            std::cout << "[StarFox] Wii Remocon Mode" << std::endl;
            Params::mode = 1;
        } else if (std::string(argv[1]) == "-v") {
            std::cout << "[StarFox] VR Mode" << std::endl;
            Params::mode = 2;
        } else {
            std::cout << "[StarFox] KeyBoard Mode" << std::endl;
        }
    }

    std::unique_ptr<std::thread> opencv_thread = nullptr;
    switch (Params::mode) {
    case 0: {  // KeyBoard Mode
        break;
    }
    case 1: {  // Wii Remocon Mode
        break;
    }
    case 2: {  // VR Mode
        opencv_thread.reset(new std::thread{[=] {
            CV::trackRed();
        }});
        std::this_thread::sleep_for(std::chrono::seconds(5));
        break;
    }
    default:
        break;
    }

    GL::init();

    glutInit(&argc, argv);

    glutInitWindowPosition(Params::WINDOW_POS_X, Params::WINDOW_POS_Y);
    glutInitWindowSize(Params::WINDOW_WIDTH, Params::WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow(Params::WINDOW_TITLE);

    glutDisplayFunc(GL::display);
    glutKeyboardFunc(GL::keyboard);
    glutKeyboardUpFunc(GL::keyboardUp);
    glutSpecialFunc(GL::keyboardSpecial);
    glutSpecialUpFunc(GL::keyboardSpecialUp);
    glutIdleFunc(GL::idle);

    StarFox::init();

    glutMainLoop();

    return 0;
}
