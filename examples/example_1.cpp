#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "implot.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

GLFWwindow *OpenWindow();
void InitImgui(GLFWwindow *window);
void InitImgui(GLFWwindow *window);
void Dockspace(float width, float height);
void Render(GLFWwindow *window, const ImVec4 &clearColor);

GLFWwindow *window;

int main(void) {
    window = OpenWindow();
    if (window == nullptr) {
        printf("Failed to open window");
        return -1;
    }
    InitImgui(window);
    ImGuiIO &io = ImGui::GetIO();

    ImPlot::GetStyle().FitPadding = ImVec2(0.1,0.1);
    ImVec4 clear_color = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        Dockspace(ImGui::GetMainViewport()->WorkSize.x, ImGui::GetMainViewport()->WorkSize.y);


        Render(window, clear_color);
    }

    return 0;
}

void Render(GLFWwindow *window, const ImVec4 &clearColor) {
    static int display_w, display_h;

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


void GlwfErrorCallback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow *OpenWindow() {
    // Setup window
    glfwSetErrorCallback(GlwfErrorCallback);
    glewExperimental = GL_TRUE;
    if (!glfwInit()) {
        return nullptr;
    }

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#ifndef __APPLE__
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
#endif

    int x, y, w, h;
    glfwGetMonitorWorkarea(monitor, &x, &y, &w, &h);

    glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(w, h, "c-cnc viewer", nullptr, nullptr);

    if (window == nullptr) {
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);// Enable vsync

    if (glewInit() != GLEW_OK) {
        return nullptr;
    }

    glEnable(GL_MULTISAMPLE);
    glfwShowWindow(window);

    return window;
}

void InitImgui(GLFWwindow *window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGuiContext *ctx = ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;// Enable Docking

    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    // io.ConfigViewportsNoDecoration = false;
    // io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
    // io.BackendFlags |= ImGuiBackendFlags_RendererHasViewports;
    // ImGui::GetIO().BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    ImGuiStyle &style = ImGui::GetStyle();
    ImPlot::CreateContext();

    float scaling_x, scaling_y, app_scaling;
    glfwGetWindowContentScale(window, &scaling_x, &scaling_y);

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void Dockspace(float width, float height) {
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGuiWindowFlags host_window_flags = 0;
    host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
    host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("MainDockspace", nullptr, host_window_flags);
    ImGui::PopStyleVar(3);

    ImGui::SetCursorPos({0, 0});

    ImGuiID dockspace_id = ImGui::GetID("DockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags, nullptr);
    ImGui::End();
}