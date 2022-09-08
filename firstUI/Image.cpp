#include "Image.h"

glm::mat4 Image::projection;
std::unique_ptr<Shader> Image::imageShader;

Image::Image(std::string imgPath, bool alpha, float centerX, float centerY, float width, float height)
	: imgPath(imgPath)
	, texture(imgPath.c_str(), alpha)
	, UIElement(centerX, centerY, width, height)
{
	GLfloat vertices[]
	{
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT),		0.0f, 1.0f, // tl
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT),		0.0f, 0.0f, // bl
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT),		1.0f, 1.0f, // tr

		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT),		0.0f, 0.0f, // bl
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT),		1.0f, 0.0f, // br
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT),		1.0f, 1.0f  // tr
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0x00);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Image::render()
{
	Image::imageShader->use();
	Image::imageShader->setMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(Image::projection));

	glBindVertexArray(this->VAO);
	this->texture.bindTexture();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Image::update()
{
	GLfloat vertices[]
	{
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT),		0.0f, 1.0f, // tl
		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT),		0.0f, 0.0f, // bl
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT),		1.0f, 1.0f, // tr

		(this->centerX * *UIElement::WINDOWWIDTH) - ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT),		0.0f, 0.0f, // bl
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) - ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT),		1.0f, 0.0f, // br
		(this->centerX * *UIElement::WINDOWWIDTH) + ((this->width / 2.0f) * *UIElement::WINDOWWIDTH), (this->centerY * *UIElement::WINDOWHEIGHT) + ((this->height / 2.0f) * *UIElement::WINDOWHEIGHT),		1.0f, 1.0f  // tr
	};

	Image::projection = glm::ortho(0.0f, (float)(*UIElement::WINDOWWIDTH), 0.0f, (float)(*UIElement::WINDOWHEIGHT));

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
}

void Image::init()
{
	Image::projection = glm::ortho(0.0f, (float)(*UIElement::WINDOWWIDTH), 0.0f, (float)(*UIElement::WINDOWHEIGHT));
	Image::imageShader = std::unique_ptr<Shader>(new Shader("shaders/image.vert", "shaders/image.frag", true));
}