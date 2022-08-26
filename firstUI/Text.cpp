#include "Text.h"

std::unique_ptr<Shader> Text::textShader = nullptr;
std::map<GLchar, FTChar> Text::FTChars;
GLuint Text::VAO, Text::VBO;

FT_Library Text::ftlib;
FT_Face Text::face;

glm::mat4 Text::projection;
unsigned Text::pixelHeight;

unsigned* Text::windowWidth;
unsigned* Text::windowHeight;

Text::Text(std::string text, float centerX, float centerY, float scaleX, float scaleY, glm::vec4 textColor)
	: text(text)
	, realX(0.0f)
	, realY(0.0f)
	, UIElement(centerX, centerY, 0.0f, 0.0f)
	, scaleX(scaleX)
	, scaleY(scaleY)
	, textColor(textColor)
{
	for (std::string::const_iterator c = text.begin(); c != text.end(); c++)
	{
		FTChar ch = Text::FTChars[*c];

		if (!(c == text.end() - 1))
			this->width += (ch.Advance >> 6) * this->scaleX;
		else
		{
			this->width += ch.Bearing.x * this->scaleX;
			this->width += ch.Size.x * this->scaleX;
		}
	}

	this->height = Text::FTChars['T'].Size.y * this->scaleY;

	this->realX = (centerX * *Text::windowWidth) - (this->width / 2.0f);
	this->realY = (centerY * *Text::windowHeight) - (this->height / 2.0f);
}

Text::~Text()
{
}

void Text::init(unsigned* WW, unsigned* WH, unsigned pixelHeight)
{
	// freetype setup
	if (FT_Init_FreeType(&Text::ftlib))
	{
		std::cout << "failed to initialize freetype" << std::endl;
		return;
	}

	if (FT_New_Face(Text::ftlib, "fonts/arial.ttf", 0, &face))
	{
		std::cout << "failed to load arial.ttf" << std::endl;
		return;
	}

	Text::windowWidth = WW;
	Text::windowHeight = WH;

	Text::projection = glm::ortho(0.0f, (float)(*WW), 0.0f, (float)(*WH));
	Text::textShader = std::unique_ptr<Shader>(new Shader("shaders/text.vert", "shaders/text.frag", true));

	Text::pixelHeight = pixelHeight;
	FT_Set_Pixel_Sizes(Text::face, 0, Text::pixelHeight);

	for (unsigned char c = 0; c < 128; c++)
	{
		if (FT_Load_Char(Text::face, c, FT_LOAD_RENDER))
		{
			std::cout << "failed to load glyph: " << (char)c << std::endl;
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			Text::face->glyph->bitmap.width,
			Text::face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			Text::face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		FTChar character
		{
			texture,
			glm::ivec2(Text::face->glyph->bitmap.width, Text::face->glyph->bitmap.rows),
			glm::ivec2(Text::face->glyph->bitmap_left, Text::face->glyph->bitmap_top),
			static_cast<unsigned int>(Text::face->glyph->advance.x)
		};

		Text::FTChars.insert(std::pair<char, FTChar>(c, character));
	}

	FT_Done_Face(Text::face);
	FT_Done_FreeType(Text::ftlib);

	glGenVertexArrays(1, &Text::VAO);
	glGenBuffers(1, &Text::VBO);

	glBindVertexArray(Text::VAO);
	glBindBuffer(GL_ARRAY_BUFFER, Text::VBO);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Text::update(Update update)
{
	this->projection = glm::ortho(0.0f, (float)update.newWW, 0.0f, (float)update.newWH);

	this->scaleX *= (float)update.newWW / (float)update.oldWW;
	this->scaleY *= (float)update.newWH / (float)update.oldWH;

	this->width = 0.0f;
	for (std::string::const_iterator c = this->text.begin(); c != this->text.end(); c++)
	{
		FTChar ch = Text::FTChars[*c];

		if (!(c == this->text.end() - 1))
			this->width += (ch.Advance >> 6) * this->scaleX;
		else
		{
			this->width += ch.Bearing.x * this->scaleX;
			this->width += ch.Size.x * this->scaleX;
		}
	}

	this->height = Text::FTChars['T'].Size.y * this->scaleY;
}

void Text::cleanup()
{
	for (unsigned char c = 0; c < 128; c++)
		glDeleteTextures(1, &Text::FTChars[c].TextureID);
	
	glDeleteVertexArrays(1, &Text::VAO);
	glDeleteBuffers(1, &Text::VBO);

	Text::textShader->deleteShader();
}

void Text::render()
{
	this->realX = (this->centerX * *Text::windowWidth) - (this->width / 2.0f);
	this->realY = (this->centerY * *Text::windowHeight) - (this->height / 2.0f);

	glBindVertexArray(Text::VAO);

	Text::textShader->use();
	Text::textShader->setMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(Text::projection));
	Text::textShader->set4fv("textColor", 1, glm::value_ptr(this->textColor));

	glActiveTexture(GL_TEXTURE0);

	for (std::string::const_iterator c = this->text.begin(); c != this->text.end(); c++)
	{
		FTChar ch = Text::FTChars[*c];

		float xpos = this->realX + (ch.Bearing.x * scaleX);
		float ypos = this->realY - ((ch.Size.y - ch.Bearing.y) * scaleY);

		float w = ch.Size.x * scaleX;
		float h = ch.Size.y * scaleY;

		float vertices[6][4]
		{
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, Text::VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		this->realX += (ch.Advance >> 6) * scaleX;
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
