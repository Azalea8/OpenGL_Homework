#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "learnopengl/shader_s.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(){
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader1("../shader/homework2/texture1.vs", "../shader/homework2/texture1.fs");

    // 所有的顶点相关信息
    float vertices[] = {
            // 中心
            0.0, 0.0, -1.0,1.0f, 0.0f, 0.0f, 1.0f,

            // 大圆弧
            float(cos(0*M_PI/5)), float(sin(0*M_PI/5)), -1.0,1.0f, 0.0f, 0.0f, 1.0f,
            float(cos(2*M_PI/5)), float(sin(2*M_PI/5)), -1.0,1.0f, 0.0f, 0.0f, 1.0f,
            float(cos(4*M_PI/5)), float(sin(4*M_PI/5)), -1.0,1.0f, 0.0f, 0.0f, 1.0f,
            float(cos(6*M_PI/5)), float(sin(6*M_PI/5)), -1.0,1.0f, 0.0f, 0.0f, 1.0f,
            float(cos(8*M_PI/5)), float(sin(8*M_PI/5)), -1.0,1.0f, 0.0f, 0.0f, 1.0f,

            // 小圆弧
            0.5f * float(cos(M_PI/5)), 0.5f * float(sin(M_PI/5)), -1.0,1.0f, 0.0f, 0.0f, 1.0f,
            0.5f * float(cos(3*M_PI/5)), 0.5f * float(sin(3*M_PI/5)), -1.0,1.0f, 0.0f, 0.0f, 1.0f,
            0.5f * float(cos(5*M_PI/5)), 0.5f * float(sin(5*M_PI/5)), -1.0,1.0f, 0.0f, 0.0f, 1.0f,
            0.5f * float(cos(7*M_PI/5)), 0.5f * float(sin(7*M_PI/5)), -1.0,1.0f, 0.0f, 0.0f, 1.0f,
            0.5f * float(cos(9*M_PI/5)), 0.5f * float(sin(9*M_PI/5)), -1.0,1.0f, 0.0f, 0.0f, 1.0f,

            -10.0, -10.0, -1.0,0.0f, 0.0f, 1.0f, 1.0f,
            -10.0, 10.0, -1.0,0.0f, 0.0f, 1.0f, 1.0f,
            10.0, -10.0, -1.0,0.0f, 0.0f, 1.0f, 1.0f,
            10.0, 10.0, -1.0,0.0f, 0.0f, 1.0f, 1.0f,

            // 中心
            0.0, 0.0, -1.0,0.0f, 1.0f, 0.0f, 1.0f,

            // 大圆弧
            float(cos(0*M_PI/5)), float(sin(0*M_PI/5)), -1.0,0.0f, 1.0f, 0.0f, 1.0f,
            float(cos(2*M_PI/5)), float(sin(2*M_PI/5)), -1.0,0.0f, 1.0f, 0.0f, 1.0f,
            float(cos(4*M_PI/5)), float(sin(4*M_PI/5)), -1.0,0.0f, 1.0f, 0.0f, 1.0f,
            float(cos(6*M_PI/5)), float(sin(6*M_PI/5)), -1.0,0.0f, 1.0f, 0.0f, 1.0f,
            float(cos(8*M_PI/5)), float(sin(8*M_PI/5)), -1.0,0.0f, 1.0f, 0.0f, 1.0f,

            // 小圆弧
            0.5f * float(cos(M_PI/5)), 0.5f * float(sin(M_PI/5)), -1.0,0.0f, 1.0f, 0.0f, 1.0f,
            0.5f * float(cos(3*M_PI/5)), 0.5f * float(sin(3*M_PI/5)), -1.0,0.0f, 1.0f, 0.0f, 1.0f,
            0.5f * float(cos(5*M_PI/5)), 0.5f * float(sin(5*M_PI/5)), -1.0,0.0f, 1.0f, 0.0f, 1.0f,
            0.5f * float(cos(7*M_PI/5)), 0.5f * float(sin(7*M_PI/5)), -1.0,0.0f, 1.0f, 0.0f, 1.0f,
            0.5f * float(cos(9*M_PI/5)), 0.5f * float(sin(9*M_PI/5)), -1.0,0.0f, 1.0f, 0.0f, 1.0f,
    };

    unsigned int indices_1[] = {
            0, 6, 1,
            0, 6, 2,
            0, 7, 2,
            0, 7, 3,
            0, 8, 3,
            0, 8, 4,
            0, 9, 4,
            0, 9, 5,
            0, 10, 5,
            0, 10,1,
    };

    unsigned int indices_3[] = {
            15, 21, 16,
            15, 21, 17,
            15, 22, 17,
            15, 22, 18,
            15, 23, 18,
            15, 23, 19,
            15, 24, 19,
            15, 24, 20,
            15, 25, 20,
            15, 25,16,
    };

    unsigned int indices_2[] = {
            11, 12, 13,
            12, 13, 14,
    };

    // 绑定状态
    unsigned int VBO, VAO, EBO[3];
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(3, EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_1), indices_1, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_2), indices_2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_3), indices_3, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // 解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float X1 = 0;
    float Y1 = 0;
    float X2 = 4;
    float Y2 = 4;

    float Vx1 = 0.003;
    float Vy1 = 0.005;

    float Vx2 = 0.006;
    float Vy2 = 0.002;

    float Height = 10;
    float Width = 10;

    float R = 1;
    float Rv = 0.0005;
    // glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        X1 += Vx1;
        Y1 += Vy1;
        if(X1 + 1 > Width || X1 - 1 < -Width){
            X1 -= Vx1;
            Vx1 = -Vx1;
        }
        if(Y1 + 1 > Height || Y1 - 1 < -Height){
            Y1 -= Vy1;
            Vy1 = -Vy1;
        }
        glm::mat4 model1 = glm::mat4(1.0f);
        model1 = glm::translate(model1, glm::vec3(X1, Y1, 0.0));
        float angle = 50.0f;
        model1 = glm::rotate(model1, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

        X2 += Vx2;
        Y2 += Vy2;
        if(X2 + R >= Width || X2 - R <= -Width){
            X2 -= Vx2;
            Vx2 = -Vx2;
        }
        if(Y2 + R >= Height || Y2 - R <= -Height){
            Y2 -= Vy2;
            Vy2 = -Vy2;
        }

        R += Rv;
        if (R > 3) Rv = -Rv;
        if (R < 1) Rv = -Rv;

        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, glm::vec3(X2, Y2, 0.0));
        angle = 100.0f;
        model2 = glm::rotate(model2, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        model2 = glm::scale(model2, glm::vec3(R, R, R));

        float X = std::fabs(X1 - X2);
        float Y = std::fabs(Y1 - Y2);
        float r = std::sqrt(X * X + Y * Y);
        if (r < 1 + R) {
            Vx2 = -Vx2;
            Vy2 = -Vy2;
            Vx1 = -Vx1;
            Vy1 = -Vy1;
        }

        glm::mat4 view;
        view = glm::lookAt(glm::vec3(0.0, 0.0, 25), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 1.5f, 0.1f, 100.0f);

        glm::mat4 transform1 = projection * view * model1;
        glm::mat4 transform2 = projection * view * glm::mat4(1.0f);
        glm::mat4 transform3 = projection * view * model2;

        unsigned int transformLoc = glGetUniformLocation(ourShader1.ID, "transform");

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform2));

        ourShader1.use();
        glBindVertexArray(VAO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform1));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform3));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(2, EBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}