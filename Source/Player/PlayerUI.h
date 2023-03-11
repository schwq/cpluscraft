#ifndef _PLAYER_UI_H_
#define _PLAYER_UI_H_

#include "../Common.h"
#include "../LogSystem.h"
#include "../Libraries/imgui/imgui.h"
#include "../Libraries/imgui/imgui_impl_glfw.h"
#include "../Libraries/imgui/imgui_impl_opengl3.h"
#include "../Editor/Window.h"
#include "../Globals.h"

enum uiImguiType {
    uiImguiInputFloat,
    uiImguiCheckBox,
    uiImguiText
};

struct uiImguiFloatStruct {
    uiImguiFloatStruct(const char* label, float* value) : label(label), value(value) {}
    const char* label;
    float* value;
    uiImguiType type = uiImguiInputFloat;
};

class uiImguiCheckBoxStruct {
public:
    uiImguiCheckBoxStruct(const char* label, bool* value) : label(label), value(value) {}
    const char* label;
    bool* value;
    uiImguiType type = uiImguiCheckBox;
};

class PlayerUI {
public:

    static PlayerUI* get(Window*& window);
    void start();
    void render();
    void terminate();

    float fatorXterrain;
    float fatorZterrain;

    void addCheckBox(const char* label, bool* value);

private:
    PlayerUI(Window*& window): window(window) {};
    Window*& window;
    std::vector<uiImguiFloatStruct> vct_uiImguiFloat;
    std::vector<uiImguiCheckBoxStruct> vct_uiImguiCheckBox;
};

#endif