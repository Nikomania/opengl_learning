#include <iostream>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGTH 600
#define WINDOW_NAME "Carrijo's window"


#define KEY_HOLDING GLFW_PRESS
#define KEY_RELEASE GLFW_RELEASE
#define INFO_LOG_SIZE 512

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void checkCompilationStatus(unsigned int vertexShaderID);
void checkLinkingStatus(unsigned int shaderProgramID);

int main() {
    std::cout << "Initializing glfw...\n";

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    std::cout << "glfw initilization completed! Creating a new window...\n";
    GLFWwindow* window = glfwCreateWindow(
            WINDOW_WIDTH,
            WINDOW_HEIGTH,
            WINDOW_NAME,
            NULL,
            NULL
    );
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    std::cout << "Window created! Checking GLAD initialization...\n";
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << "GLAD initialized successfully!\n";


    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    std::cout << "Creating Vertex Buffer Object (VBO) and Vertex Array Object (VAO)...\n";

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    std::cout << "VBO and VAO created! Initializing shaders...\n";

    const char* vertexShaderSource = "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0"
    ;
   
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    std::cout << "First shader's compilation...\n";
    checkCompilationStatus(vertexShader);
    std::cout << "Compilation completed!\n";
    
    const char* fragmentShaderSource = "#version 460 core\n"
        "out vec4 FragColor;\n\n"
        "void main() {\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}"
    ;

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    std::cout << "Second shader's compilation...\n";
    checkCompilationStatus(fragmentShader);
    std::cout << "Compilation completed!\n";

    std::cout << "Linking shaders...\n";
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    checkLinkingStatus(shaderProgram);

    std::cout << "Shaders initialized successfully! Running program..\n";
    

    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
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

void checkCompilationStatus(unsigned int vertexShaderID) {
    int success;
    char infoLog[INFO_LOG_SIZE];
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShaderID, INFO_LOG_SIZE, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
            infoLog << std::endl;

        char* error_msg;
        sprintf(error_msg, "Shader compilation error, for ID %d!", vertexShaderID);
        throw std::runtime_error(error_msg); 
    }
}

void checkLinkingStatus(unsigned int shaderProgramID) {
    int success;
    char infoLog[INFO_LOG_SIZE];
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgramID, INFO_LOG_SIZE, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::LINK_FAILED\n" <<
            infoLog << std::endl;

        char* error_msg;
        sprintf(error_msg, "Shader linking error, for ID %d!", shaderProgramID);
        throw std::runtime_error(error_msg); 
    }
}
