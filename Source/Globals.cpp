#include "Globals.h"

uint windowWidth = 1200;
uint windowHeight = 800;
bool cameraShouldMove = true;
bool freeCursor = false;
bool firstMouse = true;
float lastX = static_cast<float>(windowWidth / 2);
float lastY = static_cast<float>(windowHeight / 2);
std::vector<Block> gl_Blocks;
