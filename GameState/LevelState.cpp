#include "LevelState.h"

using namespace sf;

Texture levelBgImg;
Sprite levelBgSprite;

LevelState::LevelState(GameStateManager* gsm) :
gsm(gsm)
{
	init();
}

void LevelState::init() 
{
	levelBgImg.loadFromFile("Resources/levelBg.png");
	levelBgSprite.setTexture(levelBgImg);
	levelBgSprite.setPosition(0, 0);
	player = new Player();
}

void LevelState::update() 
{
	player->update();
}

void LevelState::draw(RenderWindow* window)
{
	window->draw(levelBgSprite);
	player->draw(window);
}

void LevelState::handleInputs(Event* events)
{
	player->handleInputs(events);
}