#include "Particle.h"
#include "Images.h"

using namespace std;
using namespace sf;



Particle::Particle(float x, float y, Mode mode) :
x(x),
y(y),
mode(mode)
{
	init();
}

void Particle::init()
{
	if (mode == Dust)
	{
		//tParticle.loadFromFile("Resources/Sprites/dust.png");
		tParticle = Images::getTexture(Images::img::DUST);
		sParticle.setTexture(tParticle);
	}

	if (mode == Shroom)
	{
		//tParticle.loadFromFile("Resources/Sprites/shroomParticle.png");
		tParticle = Images::getTexture(Images::img::SHROOMPARTICLE);
		sParticle.setTexture(tParticle);
	}

	sParticle.setPosition(x, y);
	vX = 3;
	vY = 3;
	a = 255;
	alive = true;

	angle = -(rand() % 360) * 3.14f / 360.0f;
	speed = (rand() % 5) + 1;
}

void Particle::update()
{
	if (alive)
	{
		a -= 2.0f;
		sParticle.setColor(sf::Color(255, 255, 255, a));

		if (mode == Shroom && a <= 100)
		{
			velocity.y = 3;
		}
		else
		{
			velocity = Vector2f(cos(angle) * speed, sin(angle) * speed);
			time = clock.getElapsedTime();
		}

		sParticle.move(velocity * time.asSeconds());

		if (a <= 0)
		{
			alive = false;
		}
	}

}

void Particle::draw(RenderWindow *window)
{
	if (alive)
		window->draw(sParticle);
}

float Particle::getAlpha()
{
	return a;
}

bool Particle::getAlive()
{
	return alive;
}

float Particle::getX()
{
	return x;
}

float Particle::getY()
{
	return y;
}