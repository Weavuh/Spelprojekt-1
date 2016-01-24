#include "MenuState.h"

using namespace sf;

Texture bgImg;
Sprite bgSprite;

MenuState::MenuState(GameStateManager* gsm) :
gsm(gsm),
selection(0) {
	init();
}

void MenuState::init() {
	bgImg.loadFromFile("Resources/menuBg.png");
	bgSprite.setTexture(bgImg);
	bgSprite.setPosition(0, 0);
}

void MenuState::update() {



	if (selection == -1) selection = 2;
	if (selection == 3) selection = 0;
}

void MenuState::draw(sf::RenderWindow* window) {
	window->draw(bgSprite);
}