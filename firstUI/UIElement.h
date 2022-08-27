#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class UIElement
{
public:
	float centerX, centerY, width, height;

	virtual void render() = 0;
	virtual void update() = 0;

	UIElement(float centerX, float centerY, float width, float height);
};

