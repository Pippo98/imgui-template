#ifndef EXAMPLE_APP_HPP
#define EXAMPLE_APP_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class App {
public:
    App() = default;
    virtual ~App() = default;
    virtual void Render();
    virtual bool Init();
    virtual void Shutdown();
    virtual bool IsRunning();
protected:
    virtual void InternalRender() = 0;

    GLFWwindow *window;
};

class ExampleApp : public App {
public:
    ExampleApp() = default;
    virtual ~ExampleApp() = default;
protected:
    virtual void InternalRender() override;
};


#endif // EXAMPLE_APP_HPP