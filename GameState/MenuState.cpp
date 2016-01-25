#include "MenuState.h"

using namespace sf;

Texture bgImg;
Sprite bgSprite;
Texture menuPointerImg;
Sprite menuPointerSprite;

MenuState::MenuState(GameStateManager* gsm) :
gsm(gsm),
selection(0) 
{
	init();
}

void MenuState::init() 
{
	bgImg.loadFromFile("Resources/menuBg2.png");
	menuPointerImg.loadFromFile("Resources/feather.png");
	bgSprite.setTexture(bgImg);
	bgSprite.setPosition(0, 0);
	menuPointerSprite.setTexture(menuPointerImg);
	menuPointerSprite.setPosition(370, 400);
}

void MenuState::update() 
{
	if (selection == -1) selection = 2;
	if (selection == 3) selection = 0;

	menuPointerSprite.setPosition(500, 400 + 210 * selection);
}

void MenuState::draw(RenderWindow* window) 
{
	window->draw(bgSprite);
	window->draw(menuPointerSprite);
}

void MenuState::handleInputs(Event* events)
{
	if (events->type == Event::KeyPressed)
	{
		if (events->key.code == Keyboard::Up)
		{
			selection--;
		}
		if (events->key.code == Keyboard::Down)
		{
			selection++;
		}
		if (events->key.code == Keyboard::Return)
		{
			if (selection == 0) gsm->setState(GameStateManager::states::LEVELSTATE);
			if (selection == 1) {}
			if (selection == 2)
			{
				events->type = sf::Event::Closed;
			}
		}
	}
}