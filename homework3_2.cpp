#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_s.h>

#include <iostream>

// 视口的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 输入控制
void processInput(GLFWwindow* window);

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "lexiaoyuan", NULL, NULL);
    if (window == NULL)
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

    Shader ourShader("../shader/homework3/texture2.vs", "../shader/homework3/texture2.fs");

    // 启用深度测试
    glEnable(GL_DEPTH_TEST);

    // 定义圆柱坐标
    float vertices[120000];
    unsigned int indices[10000];
    float p = 0.0f, r = 0.5f;
    for (int i = 0; i < 20000; i += 2)
    {
        p = i * 3.14f / 180.0;
        vertices[i * 6] = cos(p) * r;
        vertices[i * 6 + 1] = -0.5f;
        vertices[i * 6 + 2] = sin(p) * r;
        // 颜色
        vertices[i * 6 + 3] = 0.5f;
        vertices[i * 6 + 4] = 0.5f;
        vertices[i * 6 + 5] = 0.8f;

        vertices[(i + 1) * 6] = cos(p) * r;
        vertices[(i + 1) * 6 + 1] = 0.5f;
        vertices[(i + 1) * 6 + 2] = sin(p) * r;
        // 颜色
        vertices[(i + 1) * 6 + 3] = 0.5f;
        vertices[(i + 1) * 6 + 4] = 0.1f;
        vertices[(i + 1) * 6 + 5] = 0.2f;
    }
    // 定义圆柱索引
    for (int i = 0; i < 10000; i++)
    {
        indices[i] = i;
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

    /*// 解析顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // 启用顶点属性
    glEnableVertexAttribArray(0);*/

    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
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

        // 绘制图元
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        // 绑定索引缓冲对象
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // 使用线框模式
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // 使用填充模式（默认）
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // 定义模型矩阵
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.3f));

        // 定义观察矩阵
        glm::mat4 view = glm::mat4(1.0f);
        // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        // 定义投影矩阵
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        // 检索矩阵的统一位置
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");

        // 将它们传递给着色器
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

        // 绘制
        glDrawElements(GL_TRIANGLES, 10000, GL_UNSIGNED_INT, 0);

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
