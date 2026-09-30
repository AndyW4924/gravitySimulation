
#include<GLFW/glfw3.h>
#include<math.h>
#include<vector>
#include<chrono>
#include<iostream>
void DrawCircle(float centerX, float centerY, float radius, float steps);
int main()
{
    using clock = std::chrono::steady_clock;
    auto lastTime = clock::now();
    GLFWwindow* window;
    std::vector<float> position = { 320.0f,400.0f };
    float radius = 50.0f;
    std::vector<float> speed = {0.0f};
    float acceleration = 1960.0f;
    float energyWaste = 0.95f;
    int windowHeight = 480;
    int windowLength = 640;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowLength, windowHeight, "Gravity Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glOrtho(0, windowLength, 0, windowHeight,-1, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        auto currentTime = clock::now();
        std::chrono::duration<double> elapsed = currentTime - lastTime;
        double deltaTime = elapsed.count();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        DrawCircle(position[0], position[1], radius, 100.0f);
        speed[0] += acceleration * deltaTime;
        position[1] -= speed[0]*deltaTime;
        if (position[1] - radius <=0 )
        {
            position[1] = radius;
            speed[0] = (-1) * speed[0] * energyWaste;
        }
        if(position[1] + radius >= windowHeight)
        {
            position[1] = windowHeight-radius;
            speed[0] = (-1) * speed[0];
        }
        lastTime = currentTime;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
void DrawCircle(float centerX,float centerY, float radius, float steps) 
{
        glBegin(GL_TRIANGLE_FAN);
        glVertex2d(centerX, centerY);
        for (int i = 0; i <= 100; i++)
        {
            float angle = 3.14159263589 * 2.0f*i / steps;
            float x = centerX + radius * cos(angle);
            float y = centerY + radius * sin(angle);
            glVertex2d(x, y);

        }
        glEnd();
}
