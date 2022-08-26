#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <irrKlang/irrKlang.h>

#include "Text.h"
#include "Shader.h"
#include "UIElement.h"

enum ButtonType
{
	BLANK, BLANK_BORDER, TEXT, TEXT_BORDER
};

class Button : public UIElement
{
public:
	static std::unique_ptr<Shader> buttonShader;
	static glm::mat4 projection;
	static unsigned* windowWidth, * windowHeight;

	GLuint VAO, VBO;
	float xMargin, yMargin, borderWidth;
	glm::vec4 bgColor, hoverColor, borderColor;
	Text* text = nullptr;

	void(*func)();
	bool hovering = false;

	ButtonType buttonType;

	Button(float x, float y, float width, float height, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)());
	Button(float x, float y, float width, float height, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)());
	Button(Text* text, float xMargin, float yMargin, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)());
	Button(Text* text, float xMargin, float yMargin, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)());
	~Button();

	static void init(unsigned* WW, unsigned* WH);
	static void cleanup();
	void update(Update update);
	void render();
};

