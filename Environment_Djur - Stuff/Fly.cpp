#include "Fly.h"
#include "Images.h"
#include <vector>
#include <cstdlib>

using namespace std;
using namespace sf;

IntRect rFly;

Fly::Fly(float x, float y) :
x(x),
y(y),
facingRight(false),
timeX(0),
timeY(0)
{
	init();
}

void Fly::init()
{
	//tFly.loadFromFile("Resources/Sprites/eldfluga.png");
	tFly = Images::getTexture(Images::img::FLY);
	rFly = IntRect(0, 0, 24, 14);
	sFly.setTexture(tFly);
	sFly.setPosition(Vector2f(x, y));
	sFly.setOrigin(12, 7);

	vX = 0.7f;
	vY = 0.7f;
}

void Fly::update()
{
	/*int rX = rand() % 10;
	int rY = rand() % 10;

	if (rX % 2 == 0)
	{
	vX *= -1;
	}

	if (rY % 2 == 0)
	{
	vY *= -1;
	}*/

	timeX++;
	timeY++;
	if (timeX >= (rand() % 100) + 20)
	{
		vX *= -1;
		timeX = 0;
	}
	if (timeY >= (rand() % 90) + 35)
	{
		vY *= -1;
		timeY = 0;
	}

	bool tempFacing = facingRight;

	if (vX > 0) facingRight = false;
	if (vX < 0) facingRight = true;

	if (tempFacing != facingRight) sFly.scale(-1.f, 1.f);

	sFly.setTextureRect(rFly);
	sFly.move(vX, vY);
}

void Fly::draw(RenderWindow *window)
{
	window->draw(sFly, BlendAlpha);
}