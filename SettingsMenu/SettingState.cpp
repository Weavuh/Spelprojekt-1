#include "SettingState.h"

using namespace sf;

Texture bgImg2;
Sprite bgSprite2;
Texture settingPointerImg;
Sprite settingPointerSprite;

SettingState::SettingState(GameStateManager* gsm) :
gsm(gsm),
selection(0),
pointerX(370)
{
	init();
}

void SettingState::init()
{
	bgImg2.loadFromFile("Resources/settingsBg.png");
	settingPointerImg.loadFromFile("Resources/feather.png");
	bgSprite2.setTexture(bgImg2);
	bgSprite2.setPosition(0, 0);
	settingPointerSprite.setTexture(settingPointerImg);
	settingPointerSprite.setPosition(400, 250);
	settingPointerSprite.setScale(0.5f, 0.5f);
	settingPointerSprite.rotate(180);
}

void SettingState::update()
{
	if (selection == -1) selection = 2;
	if (selection == 3) selection = 0;
	if (selection == 1) pointerX = 393;
	else pointerX = 482;

	settingPointerSprite.setPosition(540, 220);
}

void SettingState::draw(RenderWindow* window)
{
	window->draw(bgSprite2);
	window->draw(settingPointerSprite);
}
void SettingState::handleInputs(Event* events)
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
		/*if (events->key.code == Keyboard::Return)
		{
			if (selection == 0) gsm->setState(GameStateManager::states::LEVELSTATE);
			if (selection == 1) gsm->setState(GameStateManager::states::SETTINGSTATE);
			if (selection == 2)
			{
				events->type = sf::Event::Closed;
			}
		}*/
		if (events->key.code == Keyboard::Escape){
			gsm->setState(GameStateManager::states::MENUSTATE);
			settingPointerSprite.rotate(180);
		}
	}
}