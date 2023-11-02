#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "learnopengl/shader_s.h"

#include <iostream>

// 视口的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 输入控制
void processInput(GLFWwindow* window);

float height(float x, float y){
    return x * x + y * y;
}

// 设置
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // 实例化GLFW窗口
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口对象
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourShader("../shader/homework3/texture3.vs", "../shader/homework3/texture3.fs");

    // 启用深度测试
    glEnable(GL_DEPTH_TEST);

    // 定义坐标
    int Num = 50;
    float vertices[Num * Num * 3 * 2];
    unsigned int indices[(Num-1) * (Num-1) * 2 * 3];
    float x, z = 1, y;
    float ride = 2.0 / Num;
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < Num; i++) {
        x = -1;
        for (int j = 0; j < Num; j++) {
            x += ride;
            y = height(x, z);
            // 坐标
            vertices[count1++] = x;
            vertices[count1++] = y;
            vertices[count1++] = z;

            // 颜色
            vertices[count1++] = 1.0f;
            vertices[count1++] = 0.0f;
            vertices[count1++] = 0.0f;

            if (i - 1 >= 0 && j - 1 >= 0) {
                indices[count2++] = i * Num + j;
                indices[count2++] = (i - 1) * Num + j;
                indices[count2++] = i * Num + (j - 1);
            }
            if (i + 1 < Num && j + 1 < Num) {
                indices[count2++] = i * Num + j;
                indices[count2++] = (i + 1) * Num + j;
                indices[count2++] = i * Num + (j + 1);
            }
        }
        z -= ride;
    }

    // 定义顶点缓冲对象
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // 定义顶点数组对象
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // 定义索引缓冲对象
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // 绑定顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 复制顶点数据到缓冲内存
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 绑定顶点数组对象
    glBindVertexArray(VAO);

    // 绑定索引缓冲对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float )));
    glEnableVertexAttribArray(1);

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        // 绑定顶点数组
        glBindVertexArray(VAO);

        // 绑定索引缓冲对象
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // 使用线框模式
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // 定义模型矩阵
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 view;
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));

        // 定义投影矩阵
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        // 检索矩阵的统一位置
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");

        // 将它们传递给着色器
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // 绘制
        glDrawElements(GL_TRIANGLES, (Num-1) * (Num-1) * 2 * 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // 释放之前分配的资源
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
