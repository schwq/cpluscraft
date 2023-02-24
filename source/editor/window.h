#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../common.h"
#include "../error.h"

class Window {
public:
    static Window* get(GLFWwindow*&window, const char* windowTitle, int width, int height);
    void checkGLAD();
    GLFWwindow* returnWindow() {
        return window;
    }
private:
    GLFWwindow*& window;
    const char* windowTitle;
    Window(GLFWwindow*&window, const char* windowTitle, int width, int height);
    
};

#endif