#pragma once

#include <string>
#include <iostream>
#include <stb/stb_image.h>

#include "Shader.h"
#include "Texture.h"

#include "UIElement.h"

class Image : public UIElement
{
private:
	GLuint VAO, VBO;
	Texture texture;

public:
	static glm::mat4 projection;
	static std::unique_ptr<Shader> imageShader;
	static void init();

	std::string imgPath;

	Image(std::string imgPath, bool alpha, float centerX, float centerY, float width, float height);

	void render();
	void update();
};

