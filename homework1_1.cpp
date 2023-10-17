#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "cmath"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// 顶点着色器，图方便没有 MVP变换
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
// 两个像素着色器
const char *fragmentShaderSource_0 = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                                   "}\n\0";

const char *fragmentShaderSource_1 = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   FragColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
                                     "}\n\0";

int main(){
    // 初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // 绑定着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader_0 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader_0, 1, &fragmentShaderSource_0, NULL);
    glCompileShader(fragmentShader_0);

    unsigned int fragmentShader_1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader_1, 1, &fragmentShaderSource_1, NULL);
    glCompileShader(fragmentShader_1);

    // 链接渲染管线1
    unsigned int shaderProgram_0 = glCreateProgram();
    glAttachShader(shaderProgram_0, vertexShader);
    glAttachShader(shaderProgram_0, fragmentShader_0);
    glLinkProgram(shaderProgram_0);

    // 链接渲染管线2
    unsigned int shaderProgram_1 = glCreateProgram();
    glAttachShader(shaderProgram_1, vertexShader);
    glAttachShader(shaderProgram_1, fragmentShader_1);
    glLinkProgram(shaderProgram_1);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader_0);
    glDeleteShader(fragmentShader_1);

    // 所有的顶点相关信息
    float vertices[] = {
            // 中心
            0.0, 0.0, 0.0,

            // 大圆弧
            float(cos(0*M_PI/5)), float(sin(0*M_PI/5)), 0.0,
            float(cos(2*M_PI/5)), float(sin(2*M_PI/5)), 0.0,
            float(cos(4*M_PI/5)), float(sin(4*M_PI/5)), 0.0,
            float(cos(6*M_PI/5)), float(sin(6*M_PI/5)), 0.0,
            float(cos(8*M_PI/5)), float(sin(8*M_PI/5)), 0.0,

            // 小圆弧
            0.5f * float(cos(M_PI/5)), 0.5f * float(sin(M_PI/5)), 0.0,
            0.5f * float(cos(3*M_PI/5)), 0.5f * float(sin(3*M_PI/5)), 0.0,
            0.5f * float(cos(5*M_PI/5)), 0.5f * float(sin(5*M_PI/5)), 0.0,
            0.5f * float(cos(7*M_PI/5)), 0.5f * float(sin(7*M_PI/5)), 0.0,
            0.5f * float(cos(9*M_PI/5)), 0.5f * float(sin(9*M_PI/5)), 0.0,
    };

    //选择浅色系三角形
    unsigned int indices_0[] = {
        0, 6, 1,
        //0, 6, 2,
        0, 7, 2,
        //0, 7, 3,
        0, 8, 3,
        //0, 8, 4,
        0, 9, 4,
        //0, 9, 5,
        0, 10, 5,
        //0, 10,1
    };

    //深色
    unsigned int indices_1[] = {
            //0, 6, 1,
            0, 6, 2,
            //0, 7, 2,
            0, 7, 3,
            //0, 8, 3,
            0, 8, 4,
            //0, 9, 4,
            0, 9, 5,
            //0, 10, 5,
            0, 10,1
    };

    // 绑定状态
    unsigned int VBO, VAO, EBO[2];
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(2, EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_0), indices_0, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_1), indices_1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)){
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        // 线框模式
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        // 选择管线1，绘制浅色
        glUseProgram(shaderProgram_0);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

        // 选择管线2，绘制深色
        glUseProgram(shaderProgram_1);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清空内存
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(2, EBO);
    glDeleteProgram(shaderProgram_0);
    glDeleteProgram(shaderProgram_1);

    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}