#include "Text.h"
#include "Button.h"
#include "UIManager.h"

unsigned WINDOWWIDTH = 1280, WINDOWHEIGHT = 720;
float ratioW = 1.0f, ratioH = 1.0f;

float prevTime = 0.0f, currTime, deltaTime;
bool lastClicked = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	ratioW *= (float)width / (float)WINDOWWIDTH;
	ratioH *= (float)height / (float)WINDOWHEIGHT;

	WINDOWWIDTH = width;
	WINDOWHEIGHT = height;

	Yui::updateAll();

	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || Yui::toClose)
		glfwSetWindowShouldClose(window, true);

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	for (UIElement* element : Yui::UIElements)
	{
		Button* bp = dynamic_cast<Button*>(element);
		if (bp)
		{
			if (mouseX > (element->centerX * WINDOWWIDTH) - ((element->width / 2.0f) * WINDOWWIDTH) && 
				mouseX < (element->centerX * WINDOWWIDTH) + ((element->width / 2.0f) * WINDOWWIDTH) &&
				((float)WINDOWHEIGHT - mouseY) > (element->centerY * WINDOWHEIGHT) - ((element->height / 2.0f) * WINDOWHEIGHT) && 
				((float)WINDOWHEIGHT - mouseY) < (element->centerY * WINDOWHEIGHT) + ((element->height / 2.0f) * WINDOWHEIGHT))
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
#ifdef _DEBUG
		std::cout << "failed to initialize glfw" << std::endl;
#endif
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int monitorX, monitorY;
	glfwGetMonitorPos(glfwGetPrimaryMonitor(), &monitorX, &monitorY);

	const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	WINDOWWIDTH = (unsigned)(videoMode->height * 0.825f); WINDOWHEIGHT = (unsigned)(videoMode->height * 0.825f);

#ifdef _DEBUG
	std::cout << "window resolution: " << WINDOWWIDTH << "x" << WINDOWHEIGHT << std::endl;
#endif

	GLFWwindow* window = glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, "oglUI", nullptr, nullptr);
	if (!window)
	{
#ifdef _DEBUG
		std::cout << "failed to initialize window" << std::endl;
#endif
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSwapInterval(1); // vsync on
	glfwSetWindowSizeLimits(window, (int)(0.2f * WINDOWHEIGHT), (int)(0.2f * WINDOWHEIGHT), GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwSetWindowPos(window, monitorX + (videoMode->width - WINDOWWIDTH) / 2, monitorY + (videoMode->height - WINDOWHEIGHT) / 2);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
#ifdef _DEBUG
		std::cout << "failed to initialize glad" << std::endl;
#endif
		return -1;
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	Text::init(&WINDOWWIDTH, &WINDOWHEIGHT, &ratioW, &ratioH, 32);
	Button::init(&WINDOWWIDTH, &WINDOWHEIGHT);

	Yui::UIElements.reserve(10);
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