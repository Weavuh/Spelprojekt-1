#include "GameStateManager.h"
#include "MenuState.h"
#include "LevelState.h"

GameStateManager::GameStateManager() :
currentState(MENUSTATE){
	gameStates.push_back(new MenuState(this));
}

void GameStateManager::setState(int state) {
	gameStates.pop_back();
	currentState = state;
	if (state == states::MENUSTATE) gameStates.push_back(new MenuState(this));
	if (state == states::LEVELSTATE) gameStates.push_back(new LevelState(this));
}

void GameStateManager::update() {
	gameStates[0]->update();
}

void GameStateManager::draw(sf::RenderWindow* window) {
	gameStates[0]->draw(window);
}

void GameStateManager::handleInputs(sf::Event* events) {
	gameStates[0]->handleInputs(events);
}

int GameStateManager::getCurrState() {
	return currentState;
}