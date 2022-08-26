#include "UIManager.h"

std::vector<UIElement*> Yui::UIElements;
irrklang::ISoundEngine* Yui::soundEngine = irrklang::createIrrKlangDevice();
std::vector<std::pair<UIElement*, Update>> Yui::updateQueue;
unsigned Yui::scene;
bool Yui::toClose = false;

void Yui::addElement(UIElement* element)
{
	Yui::UIElements.push_back(element);
}

void Yui::removeElement(UIElement* element)
{
	int index;
	bool contains = false;

	for (int i = 0; i < Yui::UIElements.size(); i++)
	{
		if (Yui::UIElements[i] == element)
		{
			index = i;
			contains = true;
			break;
		}
	}

	if (contains)
	{
		Yui::UIElements.erase(Yui::UIElements.begin() + index);
		std::cout << "element removed sucessfully. new size: " << Yui::UIElements.size() << std::endl;
	}
	else
		std::cout << "element not found in Yui list" << std::endl;
}

void Yui::purgeElements()
{
	for (int i = UIElements.size() - 1; i >= 0; i--)
	{
		delete Yui::UIElements[i];
		Yui::UIElements.pop_back();
	}
}

void Yui::pushUpdateQueue(std::pair<UIElement*, Update> updateInfo)
{
	Yui::updateQueue.push_back(updateInfo);
}

void Yui::commitUpdateQueue()
{
	for (const std::pair<UIElement*, Update>& updateInfo : Yui::updateQueue)
		updateInfo.first->update(updateInfo.second);

	Yui::updateQueue.clear();
}

void Yui::renderAll()
{
	for (UIElement* element : Yui::UIElements)
		element->render();
}

void Yui::loadScene(unsigned sceneID)
{
	switch (sceneID)
	{
	case 0:
		Yui::scene = sceneID;
		Yui::purgeElements();

		Yui::addElement
		(
			new Text("Main Menu", 0.5f, 0.90f, 1.75f, 1.75f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		);

		Yui::addElement
		(
			new Button
			(
				new Text("Play", 0.5f, 0.5f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				2.0f, 1.25f, 0.03f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(1);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("Level Select", 0.5f, 0.3f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.0f, 1.25f, 0.015f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(2);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("Quit", 0.5f, 0.1f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				2.0f, 1.25f, 0.03f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::toClose = true;
					Yui::purgeElements();
				}
			)
		);

		break;

	case 1:
		Yui::scene = sceneID;
		Yui::purgeElements();

		Yui::addElement
		(
			new Text("Play", 0.5f, 0.90f, 1.75f, 1.75f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		);

		Yui::addElement
		(
			new Text("Nothing here. Click the button to return to the main menu.", 0.5f, 0.5f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		);

		Yui::addElement
		(
			new Button
			(
				new Text("Return", 0.5f, 0.15f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				2.0f, 1.5f, 0.025f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick2.mp3");
					Yui::loadScene(0);
				}
			)
		);

		break;

	case 2:
		Yui::scene = sceneID;
		Yui::purgeElements();

		Yui::addElement
		(
			new Text("Level Select", 0.5f, 0.90f, 1.75f, 1.75f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		);

		Yui::addElement
		(
			new Button
			(
				new Text("1 ", 0.2f, 0.65f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				4.0f, 2.0f, 0.035f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(3);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("2 ", 0.4f, 0.65f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				4.0f, 2.0f, 0.035f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(3);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("3 ", 0.6f, 0.65f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				4.0f, 2.0f, 0.035f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(3);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("4 ", 0.8f, 0.65f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				4.0f, 2.0f, 0.035f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(3);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("5 ", 0.2f, 0.525f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				4.0f, 2.0f, 0.035f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(3);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("6 ", 0.4f, 0.525f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				4.0f, 2.0f, 0.035f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(3);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("7 ", 0.6f, 0.525f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				4.0f, 2.0f, 0.035f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(3);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("8 ", 0.8f, 0.525f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				4.0f, 2.0f, 0.035f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(3);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("9 ", 0.2f, 0.4f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				4.0f, 2.0f, 0.035f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(3);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("10", 0.4f, 0.4f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.65f, 2.0f, 0.035f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(3);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("11", 0.6f, 0.4f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				2.0f, 2.0f, 0.035f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(3);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("12", 0.8f, 0.4f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				1.65f, 2.0f, 0.035f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick.mp3");
					Yui::loadScene(3);
				}
			)
		);

		Yui::addElement
		(
			new Button
			(
				new Text("Back", 0.5f, 0.15f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				2.0f, 1.5f, 0.025f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick2.mp3");
					Yui::loadScene(0);
				}
			)
		);

		break;

	case 3:

		Yui::scene = sceneID;
		Yui::purgeElements();

		Yui::addElement
		(
			new Text("Sample Level", 0.5f, 0.90f, 1.75f, 1.75f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		);

		Yui::addElement
		(
			new Text("Nothing here. Click the button to return to level select.", 0.5f, 0.5f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
		);

		Yui::addElement
		(
			new Button
			(
				new Text("Return", 0.5f, 0.15f, 1.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
				2.0f, 1.5f, 0.025f, glm::vec4(0.92f, 0.92f, 0.92f, 1.0f), glm::vec4(0.96f, 0.96f, 0.96f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), []()
				{
					Yui::soundEngine->play2D("audio/flick2.mp3");
					Yui::loadScene(2);
				}
			)
		);

		break;

	default:
		loadScene(0);
		break;
	}
}