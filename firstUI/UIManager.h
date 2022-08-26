#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <irrKlang/irrKlang.h>

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "UIElement.h"
#include "Button.h"
#include "Text.h"

class Yui
{
public:
	static std::vector<UIElement*> UIElements;
	static irrklang::ISoundEngine* soundEngine;
	static std::vector<std::pair<UIElement*, Update>> updateQueue;
	static unsigned scene;
	static bool toClose;

	static void addElement(UIElement* element);
	static void removeElement(UIElement* element);
	static void purgeElements();

	static void pushUpdateQueue(std::pair<UIElement*, Update> updateInfo);
	static void commitUpdateQueue();

	static void renderAll();

	static void requestSceneChange(unsigned sceneID);
	static void loadScene(unsigned sceneID);
};
