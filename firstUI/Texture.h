#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#ifdef _DEBUG
#include <iostream>
#endif

class Texture
{
public:
	GLuint textureID;

	Texture(const char* imagePath, bool alpha);
	~Texture();

	void bindTexture();
	void unbindTexture();
	void deleteTexture();
	void replaceTexture(const char* imagePath, bool alpha);
};

