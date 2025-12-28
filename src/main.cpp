#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define WINDOW_WIDTH 1000
#define WINDOW_HEIGTH 1000


#define KEY_HOLDING GLFW_PRESS
#define KEY_RELEASE GLFW_RELEASE

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(
            WINDOW_WIDTH,
            WINDOW_HEIGTH,
            "LearnOpenGL",
            NULL,
            NULL
    );
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == KEY_HOLDING)
        glfwSetWindowShouldClose(window, true);
}

