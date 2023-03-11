#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../Common.h"
#include "../LogSystem.h"

class Window {
public:
    static Window* get(const char* windowTitle, int width, int height);
    void checkGLAD();
    GLFWwindow* returnWindow() {
        return window;
    }
private:
    GLFWwindow* window;
    const char* windowTitle;
    Window(const char* windowTitle, int width, int height);
    
};

#endif