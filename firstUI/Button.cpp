#include "Button.h"

glm::mat4 Button::projection;
std::unique_ptr<Shader> Button::buttonShader = nullptr;

Button::Button(float x, float y, float width, float height, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)())
	: UIElement(x, y, width, height)
	, bgColor(bgColor)
	, hoverColor(hoverColor)
	, func(func)
	, borderColor(glm::vec4(0.0f))
	, borderWidth(0.0f)
	, xMargin(0.0f)
	, yMargin(0.0f)
{
	this->buttonType = ButtonType::BLANK;

	GLfloat vertices[18]
	{
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tl
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tr
 
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // br
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f  // tr
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0x00);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Button::Button(float x, float y, float width, float height, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)())
	: UIElement(x, y, width, height)
	, borderWidth(borderWidth)
	, bgColor(bgColor)
	, hoverColor(hoverColor)
	, borderColor(borderColor)
	, func(func)
	, xMargin(0.0f)
	, yMargin(0.0f)
{
	this->buttonType = ButtonType::BLANK_BORDER;

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0x00);

	GLfloat vertices[36]
	{
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tl
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tr
																					   
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // br
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tr

		((this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // tl
		((this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // bl
		((this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // tr
																																				   
		((this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // bl
		((this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // br
		((this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f  // tr
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Button::Button(Text* text, float xMargin, float yMargin, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)())
	: UIElement
	(
		text->centerX, 
		text->centerY, 
		(text->width / *UIElement::WINDOWWIDTH) + ((text->width / *UIElement::WINDOWWIDTH) * xMargin), 
		(text->height / *UIElement::WINDOWHEIGHT) + ((text->height / *UIElement::WINDOWHEIGHT) * yMargin)
	)
	, text(text)
	, xMargin(xMargin)
	, yMargin(yMargin)
	, bgColor(bgColor)
	, hoverColor(hoverColor)
	, func(func)
	, borderColor(glm::vec4(0.0f))
	, borderWidth(0.0f)
{
	this->buttonType = ButtonType::TEXT;

	GLfloat vertices[18]
	{
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tl
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tr

		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // br
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f  // tr
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0x00);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Button::Button(Text* text, float xMargin, float yMargin, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)())
	: UIElement
	(
		text->centerX,
		text->centerY,
		(text->width / *UIElement::WINDOWWIDTH) + ((text->width / *UIElement::WINDOWWIDTH) * (xMargin * *text->ratioW)),
		(text->height / *UIElement::WINDOWHEIGHT) + ((text->height / *UIElement::WINDOWHEIGHT) * (yMargin * *text->ratioH))
	)
	, text(text)
	, xMargin(xMargin)
	, yMargin(yMargin)
	, borderWidth(borderWidth)
	, bgColor(bgColor)
	, hoverColor(hoverColor)
	, borderColor(borderColor)
	, func(func)
{
	this->buttonType = ButtonType::TEXT_BORDER;

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0x00);

	GLfloat vertices[36]
	{
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tl
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tr

		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // br
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tr

		((this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // tl
		((this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // bl
		((this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // tr
																																				   
		((this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // bl
		((this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // br
		((this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f  // tr
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Button::~Button()
{
	if (this->buttonType == ButtonType::TEXT || this->buttonType == ButtonType::TEXT_BORDER)
		delete this->text;

	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

void Button::init()
{
	Button::projection = glm::ortho(0.0f, (float)(*UIElement::WINDOWWIDTH), 0.0f, (float)(*UIElement::WINDOWHEIGHT));
	Button::buttonShader = std::unique_ptr<Shader>(new Shader("shaders/button.vert", "shaders/button.frag", true));
}

void Button::cleanup()
{
	Button::buttonShader->deleteShader();
}

bool Button::isHovering(float mouseX, float mouseY)
{
	if (mouseX > (this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH) &&
		mouseX < (this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH) &&
		(*UIElement::WINDOWHEIGHT - mouseY) >(this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT) &&
		(*UIElement::WINDOWHEIGHT - mouseY) < (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT))
	{
		this->hovering = true;
		return true;
	}
	else
	{
		this->hovering = false;
		return false;
	}
}


void Button::update()
{
	Button::projection = glm::ortho(0.0f, (float)*UIElement::WINDOWWIDTH, 0.0f, (float)*UIElement::WINDOWHEIGHT);

	switch (this->buttonType)
	{
		case ButtonType::BLANK:
		{
			GLfloat vertices[18]
			{
				(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tl
				(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
				(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tr

				(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
				(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // br
				(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f  // tr
			};

			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			break;
		}

		case ButtonType::BLANK_BORDER:
		{
			GLfloat vertices[36]
			{
				(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tl
				(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
				(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tr

				(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
				(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // br
				(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tr

				((this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // tl
				((this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // bl
				((this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // tr

				((this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // bl
				((this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // br
				((this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f  // tr
			};

			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			break;
		}

		case ButtonType::TEXT:
		{
			this->text->update();

			this->width = (text->width / *UIElement::WINDOWWIDTH) + ((text->width / *UIElement::WINDOWWIDTH) * xMargin);
			this->height = (text->height / *UIElement::WINDOWHEIGHT) + ((text->height / *UIElement::WINDOWHEIGHT) * (yMargin * *text->ratioH));

			GLfloat vertices[18]
			{
				(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tl
				(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
				(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tr

				(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
				(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // br
				(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f  // tr
			};

			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			break;
		}

		case ButtonType::TEXT_BORDER:
		{
			this->text->update();

			this->width = (text->width / *UIElement::WINDOWWIDTH) + ((text->width / *UIElement::WINDOWWIDTH) * xMargin);
			this->height = (text->height / *UIElement::WINDOWHEIGHT) + ((text->height / *UIElement::WINDOWHEIGHT) * (yMargin * *text->ratioH));

			GLfloat vertices[36]
			{
				(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tl
				(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
				(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tr

				(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // bl
				(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // br
				(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT), 0.0f, // tr

				((this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // tl
				((this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // bl
				((this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // tr

				((this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // bl
				((this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) - (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f, // br
				((this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), ((this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT)) + (((this->width / 2.0f) * *UIElement::WINDOWWIDTH) * this->borderWidth), 0.0f  // tr
			};

			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			break;
		}
	}
}

void Button::render()
{
	Button::buttonShader->use();
	Button::buttonShader->setMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(Button::projection));

	switch (this->buttonType)
	{
		case ButtonType::BLANK:
			if (this->hovering)
				Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->hoverColor));
			else
				Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->bgColor));

			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			break;

		case ButtonType::BLANK_BORDER:
			Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->borderColor));
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 6, 6);

			if (this->hovering)
				Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->hoverColor));
			else
				Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->bgColor));

			glDrawArrays(GL_TRIANGLES, 0, 6);
			break;

		case ButtonType::TEXT:
			if (this->hovering)
				Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->hoverColor));
			else
				Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->bgColor));

			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			
			this->text->render();
			break;

		case ButtonType::TEXT_BORDER:
			Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->borderColor));
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 6, 6);

			if (this->hovering)
				Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->hoverColor));
			else
				Button::buttonShader->set4fv("color", 1, glm::value_ptr(this->bgColor));

			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			this->text->render();
			break;

		default:
#ifdef _DEBUG
			std::cout << "failed to recognize button type" << std::endl;
#endif
			break;
	}
}
