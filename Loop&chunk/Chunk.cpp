#include "Chunk.h"

Chunk::Chunk(sf::Texture texture, sf::Vector2f position, bool alive) :
mTexture(texture),
mPosition(position),
mAlive(alive)
{
}

Chunk::~Chunk()
{
}

sf::Vector2f Chunk::getPosition()
{
	return mPosition;
}

bool Chunk::getAlive()
{
	return mAlive;
}

void Chunk::setAlive(bool alive)
{
	mAlive = alive;
}

sf::Sprite Chunk::getSprite()
{
	return mSprite;
}

void Chunk::setPosition(sf::Vector2f position)
{
	mPosition = position;
}

void Chunk::Update()
{
	mSprite.setPosition(mPosition);
}

void Chunk::Draw(sf::RenderWindow &window)
{
	mSprite.setTexture(mTexture);
	if (mAlive == true)
	{
		window.draw(mSprite);
	}
}
