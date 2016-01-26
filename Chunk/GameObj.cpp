#include "GameObj.h"
#include <cstdlib>
#include <iostream>

using namespace std;

GameObj::GameObj(Chunk chunk, sf::Vector2f position, sf::Texture texture) :
mChunk(chunk),
mPosition(position),
mTexture(texture)
{
}

GameObj::~GameObj()
{
}

void GameObj::Update()
{
	mSprite.setPosition(sf::Vector2f(mChunk.getPosition().x + mPosition.x, mChunk.getPosition().y + mPosition.y));
}

void GameObj::Draw(sf::RenderWindow &window, Chunk chunk)
{
	mSprite.setTexture(mTexture);

	if (chunk.getAlive() == true)
	{
		window.draw(mSprite);
	}
}

Chunk GameObj::getChunk()
{
	return mChunk;
}