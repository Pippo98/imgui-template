#ifndef WINDOW_UTILS_HPP
#define WINDOW_UTILS_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include <stdio.h>

static void GlwfErrorCallback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static GLFWwindow *OpenWindow() {
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
    GLFWwindow *window = glfwCreateWindow(w, h, "example_1", nullptr, nullptr);

    if (window == nullptr) {
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);// Enable vsync
    glEnable(GL_MULTISAMPLE);

    if (glewInit() != GLEW_OK) {
        return nullptr;
    }

    glfwShowWindow(window);

    return window;
}

static void InitImgui(GLFWwindow *window) {
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

#endif // WINDOW_UTILS_HPP