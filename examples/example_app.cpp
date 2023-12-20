#include "example_app.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "window_utils.hpp"

#include <stdio.h>


// Generic APP
void App::Render() {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    InternalRender();

    static int display_w, display_h;
    ImVec4 clearColor = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);

    ImGui::Render();
    glfwGetFramebufferSize(window, &display_w, &display_h);

    glViewport(0, 0, display_w, display_h);
    glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w,
                 clearColor.z * clearColor.w, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
    glfwMakeContextCurrent(window);

    glfwSwapBuffers(window);
}

bool App::Init() {
    window = OpenWindow();
    if (window == nullptr) {
        printf("Failed to open window");
        return -1;
    }
    InitImgui(window);
    ImGuiIO &io = ImGui::GetIO();

    ImPlot::GetStyle().FitPadding = ImVec2(0.1,0.1);
    ImVec4 clear_color = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
    return 0;
}

void App::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool App::IsRunning() {
    return !glfwWindowShouldClose(window);
}


// Specific App implementation
void ExampleApp::InternalRender() {
    ImGui::ShowDemoWindow();
    ImPlot::ShowDemoWindow();
}


int main(void) {
    ExampleApp app;
    app.Init();
    while (app.IsRunning()) {
        app.Render();
    }
    app.Shutdown();
    return 0;
}