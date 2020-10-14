#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <glm/common.hpp>

#include <SPUI/Shader.hpp>
#include <SPUI/Core.hpp>
#include <SPUI/Debug.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void windowResizeUpdateUniforms(int width, int height)
{
    //GLint u_resolution = glGetUniformLocation(shader, "u_resolution");
    //glUniform2f(u_resolution, width, height);
}


void window_size_callback(GLFWwindow* window, int width, int height)
{
    GLCall(glViewport(0, 0, width, height));
    GLCall(windowResizeUpdateUniforms(width, height));

    glClear(GL_COLOR_BUFFER_BIT);
    //glfwSwapBuffers(window);
    glfwPollEvents();
}

enum keys {
    A,
    B,
    C,
    D,
    E
};

bool isKeyPressed(GLFWwindow* window, int key)
{
    int state = glfwGetKey(window, key);
    if (state == GLFW_PRESS)
    {
        return true;
    }
    else
    {
        return false;
    }

}

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        std::cout << "ERROR while initializing glfw" << std::endl;
        return -1;
    }

    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(800, 800, "Test", NULL, NULL);
    if (!window)
    {
        std::cout << "ERROR while creating the window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    unsigned int glewInitResult;
    glewInitResult = glewInit();
    std::cout << (GLenum)glewInitResult << std::endl;
    {
        float vertices[12] = {
            -0.5, -0.5,
             0.5, -0.5,
             0.5,  0.5,
            -0.5,  0.5
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        glm::mat4 proj = glm::ortho(-20.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);

        SPUI::Shader shader("../../../Shaders/rectangle.glsl");
        shader.Compile();
        shader.Bind();
        shader.setUniformMat4f("u_MVP", proj);
        GLenum error;
        error = glGetError();
        if (error != 0)
            std::cout << (GLenum)error << std::endl;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glfwSetWindowSizeCallback(window, window_size_callback);

        float increment = 0.02f;
        float value = 0.4f;

        SPUI::VertexBuffer vb(vertices, 4 * 2 * sizeof(float));

        SPUI::VertexBufferLayout vbl;
        vbl.fPush(2);

        SPUI::VertexArray vao;
        vao.bind();
        vao.addBuffer(vb, vbl);

        SPUI::IndexBuffer ibo(indices, 12);
        ibo.bind();

        float tX = 0.5f;
        float tY = 0.0f;
        float size = 1.0f;
        float rate = 0.1f;

        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);

            glm::mat4 viewport = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
            glm::mat4 translate = glm::translate(glm::mat4(1), glm::vec3(tX, tY, 0));
            glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(size, size, 1.0f));
            glm::mat4 proj = translate * scale * viewport;
            shader.setUniformMat4f("u_MVP", proj);

            if (value > 1.0f)
                increment = -increment;
            if (value < 0.0f)
                increment = -increment;
            value += increment;

            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);

            shader.setUniform1f("u_radius", (float)value);

            shader.setUniform2f("u_resolution", (GLfloat)width, (GLfloat)height);
            shader.setUniform2f("u_size", (GLfloat)(width * 0.5), (GLfloat)(height * 0.5));
            shader.setUniform2f("u_location", (GLfloat)(width * 0.5) - ((GLfloat)(width * 0.25)), (GLfloat)(height * 0.5) - ((GLfloat)(height * 0.25)));

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if (isKeyPressed(window, GLFW_KEY_LEFT) | isKeyPressed(window, GLFW_KEY_Q))
            {
                tX -= 0.1f*rate;
            }
            if (isKeyPressed(window, GLFW_KEY_RIGHT) | isKeyPressed(window, GLFW_KEY_E))
            {
                tX += 0.1f*rate;
            }
            if (isKeyPressed(window, GLFW_KEY_DOWN) | isKeyPressed(window, GLFW_KEY_S))
            {
                tY -= 0.1f*rate;
            }
            if (isKeyPressed(window, GLFW_KEY_UP) | isKeyPressed(window, GLFW_KEY_W))
            {
                tY += 0.1f*rate;
            }
            if (isKeyPressed(window, GLFW_KEY_PAGE_UP))
            {
                size += 0.01f;
            }
            if (isKeyPressed(window, GLFW_KEY_PAGE_DOWN))
            {
                size -= 0.01f;
            }
            if (isKeyPressed(window, GLFW_KEY_ESCAPE))
            {
                glfwSetWindowShouldClose(window, true);
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        shader.Unbind();
    }
    glfwTerminate();
    return 0;
};