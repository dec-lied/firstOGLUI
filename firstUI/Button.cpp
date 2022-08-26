#include "Button.h"

std::unique_ptr<Shader> Button::buttonShader = nullptr;
glm::mat4 Button::projection;

unsigned* Button::windowWidth;
unsigned* Button::windowHeight;

Button::Button(float x, float y, float width, float height, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)())
	: UIElement(x, y, width, height)
	, bgColor(bgColor)
	, hoverColor(hoverColor)
	, func(func)
{
	this->buttonType = ButtonType::BLANK;

	GLfloat vertices[18]
	{
		(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tl
		(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
		(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tr
 
		(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
		(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // br
		(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f  // tr
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0x00);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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
{
	this->buttonType = ButtonType::BLANK_BORDER;

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0x00);

	GLfloat vertices[36]
	{
		(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tl
		(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
		(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tr
																					   
		(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
		(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // br
		(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tr

		((this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // tl
		((this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // bl
		((this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // tr
																																				   
		((this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // bl
		((this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // br
		((this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f  // tr
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Button::Button(Text* text, float xMargin, float yMargin, glm::vec4 bgColor, glm::vec4 hoverColor, void(*func)())
	: text(text)
	, UIElement
	(
		text->centerX, 
		text->centerY, 
		(text->width / *Button::windowWidth) + ((text->width / *Button::windowWidth) * xMargin), 
		(text->height / *Button::windowHeight) + ((text->height / *Button::windowHeight) * yMargin)
	)
	, xMargin(xMargin)
	, yMargin(yMargin)
	, bgColor(bgColor)
	, hoverColor(hoverColor)
	, func(func)
{
	this->buttonType = ButtonType::TEXT;

	GLfloat vertices[18]
	{
		(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tl
		(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
		(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tr

		(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
		(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // br
		(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f  // tr
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0x00);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Button::Button(Text* text, float xMargin, float yMargin, float borderWidth, glm::vec4 bgColor, glm::vec4 hoverColor, glm::vec4 borderColor, void(*func)())
	: text(text)
	, UIElement
	(
		text->centerX,
		text->centerY,
		(text->width / *Button::windowWidth) + ((text->width / *Button::windowWidth) * xMargin),
		(text->height / *Button::windowHeight) + ((text->height / *Button::windowHeight) * yMargin)
	)
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
		(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tl
		(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
		(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tr

		(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
		(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // br
		(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tr

		((this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // tl
		((this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // bl
		((this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // tr
																																				   
		((this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // bl
		((this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // br
		((this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f  // tr
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Button::~Button()
{
	if (this->buttonType == ButtonType::TEXT || this->buttonType == ButtonType::TEXT_BORDER)
		delete this->text;
}

void Button::init(unsigned* WW, unsigned* WH)
{
	Button::windowWidth = WW;
	Button::windowHeight = WH;

	Button::projection = glm::ortho(0.0f, (float)(*WW), 0.0f, (float)(*WH));
	Button::buttonShader = std::unique_ptr<Shader>(new Shader("shaders/button.vert", "shaders/button.frag", true));
}

void Button::cleanup()
{
	Button::buttonShader->deleteShader();
}

void Button::update(Update update)
{
	this->projection = glm::ortho(0.0f, (float)update.newWW, 0.0f, (float)update.newWH);

	switch (this->buttonType)
	{
		case ButtonType::BLANK:
		{
			GLfloat vertices[18]
			{
				(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tl
				(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
				(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tr

				(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
				(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // br
				(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f  // tr
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
				(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tl
				(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
				(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tr

				(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
				(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // br
				(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tr

				((this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // tl
				((this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // bl
				((this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // tr

				((this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // bl
				((this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // br
				((this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f  // tr
			};

			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			break;
		}

		case ButtonType::TEXT:
		{
			GLfloat vertices[18]
			{
				(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tl
				(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
				(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tr

				(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
				(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // br
				(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f  // tr
			};

			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			this->text->update(update);

			break;
		}

		case ButtonType::TEXT_BORDER:
		{
			GLfloat vertices[36]
			{
				(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tl
				(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
				(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tr

				(this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // bl
				(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // br
				(this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth), (this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight), 0.0f, // tr

				((this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // tl
				((this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // bl
				((this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // tr

				((this->centerX * *Button::windowWidth) - ((this->width / 2.0f) * *Button::windowWidth)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // bl
				((this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) - ((this->height / 2.0f) * *Button::windowHeight)) - (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f, // br
				((this->centerX * *Button::windowWidth) + ((this->width / 2.0f) * *Button::windowWidth)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), ((this->centerY * *Button::windowHeight) + ((this->height / 2.0f) * *Button::windowHeight)) + (((this->width / 2.0f) * *Button::windowWidth) * this->borderWidth), 0.0f  // tr
			};

			glBindVertexArray(this->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			this->text->update(update);

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
			std::cout << "failed to recognize button type" << std::endl;
			break;
	}
}
