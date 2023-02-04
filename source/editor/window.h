#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../common.h"
#include "../error.h"

class Window {
public:
    Window(GLFWwindow*&window, const char* windowTitle, int width, int height);
    GLFWwindow* returnWindow() {
        return window;
    }
    void checkGLAD();
private:
    GLFWwindow*& window;
    const char* windowTitle;
};

#endif