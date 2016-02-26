#ifndef INCLUDED_DUST
#define INCLUDED_DUST

#include "SFML\Graphics.hpp"

class Particle
{
public:
	enum Mode
	{
		Dust,
		Shroom
	};

	Particle(float x, float y, Mode mode);
	void init();
	void update();
	void draw(sf::RenderWindow *window);
	float getAlpha();
	bool getAlive();
	float getX();
	float getY();
private:
	float x;
	float y;
	float velX;
	float velY;

	sf::Clock clock;
	sf::Time time;

	sf::Texture tParticle;
	sf::Sprite sParticle;
	float a;
	bool alive;
	Mode mode;

	float vX;
	float vY;

	sf::Vector2f velocity;
	float angle;
	float speed;
};

#endif