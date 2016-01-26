#include "LevelState.h"
#include <SFML\Audio.hpp>

using namespace sf;

Texture levelBgImg;
Sprite levelBgSprite;
Music bgMusic;

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
	bgMusic.openFromFile("Resources/Koncept2.wav");
	player = new Player();
	bgMusic.setLoop(true);
	//bgMusic.play();
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