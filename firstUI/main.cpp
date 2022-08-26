#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <irrKlang/irrKlang.h>

#include "Text.h"
#include "Button.h"
#include "Shader.h"
#include "UIManager.h"

unsigned WINDOWWIDTH = 1280, WINDOWHEIGHT = 720;
float aspectRatio;
#define windowScalar 0.825f

float prevTime = 0.0f, currTime, deltaTime;
bool lastClicked = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	for (UIElement* element : Yui::UIElements)
		Yui::pushUpdateQueue(std::pair <UIElement*, Update>(element, Update{ WINDOWWIDTH, WINDOWHEIGHT, (unsigned)width, (unsigned)height }));

	WINDOWWIDTH = width;
	WINDOWHEIGHT = height;

	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || Yui::toClose)
		glfwSetWindowShouldClose(window, true);

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	mouseY = (float)WINDOWHEIGHT - mouseY;

	for (UIElement* element : Yui::UIElements)
	{
		Button* bp = dynamic_cast<Button*>(element);
		if (bp)
		{
			if (mouseX > (element->centerX * WINDOWWIDTH) - ((element->width / 2.0f) * WINDOWWIDTH) && mouseX < (element->centerX * WINDOWWIDTH) + ((element->width / 2.0f) * WINDOWWIDTH) &&
				mouseY > (element->centerY * WINDOWHEIGHT) - ((element->height / 2.0f) * WINDOWHEIGHT) && mouseY < (element->centerY * WINDOWHEIGHT) + ((element->height / 2.0f) * WINDOWHEIGHT))
			{
				bp->hovering = true;
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
				{
					if (!lastClicked)
					{
						lastClicked = true;
						bp->func();
						break;
					}
				}
				else
					lastClicked = false;
			}
			else
				bp->hovering = false;
		}
	}
}

int main()
{
	if (!glfwInit())
	{
		std::cout << "failed to initialize glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 0);

	int monitorX, monitorY;
	glfwGetMonitorPos(glfwGetPrimaryMonitor(), &monitorX, &monitorY);

	const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

#ifdef windowScalar
	WINDOWWIDTH = (unsigned)(videoMode->height * windowScalar); WINDOWHEIGHT = (unsigned)(videoMode->height * windowScalar);
#endif
	aspectRatio = (float)WINDOWHEIGHT / (float)WINDOWWIDTH;

	std::cout << "window resolution: " << WINDOWWIDTH << "x" << WINDOWHEIGHT << ". aspect ratio: " << aspectRatio << std::endl;

	GLFWwindow* window = glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, "OpenGL Application", nullptr, nullptr);
	if (!window)
	{
		std::cout << "failed to initialize window" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0); // vsync off
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowPos
	(
		window,
		monitorX + (videoMode->width - WINDOWWIDTH) / 2,
		monitorY + (videoMode->height - WINDOWHEIGHT) / 2
	);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize glad" << std::endl;
		return -1;
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	Text::init(&WINDOWWIDTH, &WINDOWHEIGHT, 32);
	Button::init(&WINDOWWIDTH, &WINDOWHEIGHT);

	Yui::loadScene(0);

	while (!glfwWindowShouldClose(window))
	{
		// timestep update
		currTime = (float)glfwGetTime();
		deltaTime = currTime - prevTime;
		prevTime = currTime;

		glClearColor(0.945f, 0.827f, 0.827f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);

		Yui::UIElements.reserve(10);
		Yui::updateQueue.reserve(10);

		Yui::commitUpdateQueue();
		Yui::renderAll();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Yui::purgeElements();
	Button::cleanup();
	Text::cleanup();

	glfwDestroyWindow(window);
	glfwTerminate();
}