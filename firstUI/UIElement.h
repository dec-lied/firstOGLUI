#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Update
{
	unsigned oldWW, oldWH, newWW, newWH;
};

class UIElement
{
public:
	float centerX, centerY, width, height;
	virtual void render() = 0;
	virtual void update(Update update) = 0;

	UIElement(float centerX, float centerY, float width, float height);
};

