#include "PlayerUI.h"

PlayerUI* PlayerUI::get(Window*& window) {
    static PlayerUI* playerUI  = new PlayerUI(window);
    return playerUI;
}

void PlayerUI::start() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->returnWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void PlayerUI::render() {


    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Log System");                     
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("Camera should move: %s", cameraShouldMove ? "true" : "false");
    ImGui::InputFloat("X fator Terrain: ", &fatorXterrain);
    ImGui::InputFloat("Z fator Terrain: ", &fatorZterrain);
    
    for(uint x = 0; x < vct_uiImguiCheckBox.size(); x++) {
        ImGui::Checkbox(vct_uiImguiCheckBox.at(x).label, vct_uiImguiCheckBox.at(x).value);
    }    

    for(uint x = 0; x < vct_uiImguiFloat.size(); x++) {
        ImGui::InputFloat(vct_uiImguiFloat.at(x).label, vct_uiImguiFloat.at(x).value);
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


}

void PlayerUI::terminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void PlayerUI::addCheckBox(const char* label, bool* value) {
    vct_uiImguiCheckBox.push_back(uiImguiCheckBoxStruct(label, value));
}

