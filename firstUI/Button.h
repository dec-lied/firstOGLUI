#pragma once

#include <irrKlang/irrKlang.h>

#include "Shader.h"

#include "Text.h"
#include "UIElement.h"

enum ButtonType
{
	BLANK, BLANK_BORDER, TEXT, TEXT_BORDER
};

class Button : public UIElement
{
private:
	GLuint VAO, VBO;
	ButtonType buttonType;

public:
	static glm::mat4 projection;
	static std::unique_ptr<Shader> buttonShader;
	static void init();
	static void cleanup();

	Text* text = nullptr;
	float xMargin, yMargin, borderWidth;
	glm::vec4 bgColor, hoverColor, borderColor;

	void(*func)();
	bool hovering = false;

	Button(float x, float y, float width, float height, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)());
	Button(float x, float y, float width, float height, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)());
	Button(Text* text, float xMargin, float yMargin, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)());
	Button(Text* text, float xMargin, float yMargin, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)());
	~Button();

	bool isHovering(float mouseX, float mouseY);

	void update();
	void render();
};

