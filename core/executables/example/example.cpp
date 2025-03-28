#include "example.hpp"
#include "app_utils/app.hpp"
#include "imgui.hpp"
#include <cstdlib>

class ExampleApp : public App {
protected:
  virtual void Draw() override {
    ImGui::Begin("Example");
    ImGui::Text("Hello, world!");
    if (ImGui::Button("Close")) {
      glfwSetWindowShouldClose(window, true);
    }
    ImGui::End();

    ImGui::ShowDemoWindow();
    ImPlot::ShowDemoWindow();
    ImPlot3D::ShowDemoWindow();
  }
};

int main(void) {
  ExampleApp app;
  app.SetTitle("Example");
  app.Init();
  app.Run();
  return EXIT_SUCCESS;
}
