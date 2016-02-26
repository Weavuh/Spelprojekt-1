#include "Leaves.h"
#include "Images.h"
#include <iostream>

using namespace sf;

struct Leaf
{
	Vector2f velocity;
	Time lifetime;
	Sprite sprite;
	float speedX;
	float speedY;
};

Leaves::Leaves(float x, float y) :
x(x),
y(y),
lifetime(seconds(3))
{
	init();
}

void Leaves::init()
{
	//tLeaf.loadFromFile("Resources/Sprites/leaf.png");
	tLeaf = Images::getTexture(Images::img::LEAVE);

	Leaf l0;
	Leaf l1;
	Leaf l2;
	leafVector.push_back(l0);
	leafVector.push_back(l1);
	leafVector.push_back(l2);

	for (size_t i = 0; i < leafVector.size(); i++)
	{
		leafVector[i].sprite.setTexture(tLeaf);
		leafVector[i].sprite.setPosition(x - 65 * i, y + 50 * i);
	}
}

void Leaves::update()
{
	time = clock.getElapsedTime();

	for (size_t i = 0; i < leafVector.size(); i++)
	{
		Leaf &l = leafVector[i];
		l.lifetime -= time;

		float speedX = l.speedX;
		float speedY = l.speedY;

		if (l.lifetime.asMicroseconds() <= 0)
		{
			reset(i);
		}

		l.sprite.move(speedX, speedY);
	}
	clock.restart();
}

void Leaves::draw(RenderWindow *window)
{
	for (size_t i = 0; i < leafVector.size(); i++)
	{
		Leaf &l = leafVector[i];
		window->draw(l.sprite);
	}
}

void Leaves::reset(size_t i)
{
	leafVector[i].speedX = (rand() % 4) + 0.3f;
	leafVector[i].speedY = (rand() % 4) + 0.3f;
	leafVector[i].lifetime = seconds((rand() % 5) + 1);
	leafVector[i].sprite.setPosition(-200, -700);
}