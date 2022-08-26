#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "UIElement.h"

struct FTChar
{
	GLuint TextureID;
	glm::ivec2   Size;
	glm::ivec2   Bearing;
	unsigned int Advance;
};

class Text : public UIElement
{
public:
	static std::unique_ptr<Shader> textShader;
	static std::map<GLchar, FTChar> FTChars;
	static GLuint VAO, VBO;
	static FT_Library ftlib;
	static FT_Face face;
	static glm::mat4 projection;
	static unsigned pixelHeight;
	static unsigned* windowWidth, *windowHeight;

	std::string text;
	float realX, realY, scaleX, scaleY;
	glm::vec4 textColor;

	Text(std::string text, float centerX, float centerY, float scaleX, float scaleY, glm::vec4 textColor);
	~Text();

	static void init(unsigned* WW, unsigned* WH, unsigned pixelHeight);
	void update(Update update);
	static void cleanup();
	void render();
};

