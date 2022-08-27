#pragma once

#include <vector>
#include <cstdarg>

#include "Shader.h"

#include "Text.h"
#include "Button.h"

class Yui
{
public:
	static std::vector<UIElement*> UIElements;
	static irrklang::ISoundEngine* soundEngine;

	static bool toClose;
	static unsigned scene;

	static void addElement(UIElement* element);
	static void addElements(unsigned count, ...);
	static void removeElement(UIElement* element);
	static void purgeElements();

	static void updateAll();
	static void renderAll();

	static void loadScene(unsigned sceneID);
};
