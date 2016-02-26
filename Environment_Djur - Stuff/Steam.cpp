#include "Steam.h"
#include "Images.h"

using namespace std;
using namespace sf;


struct SteamParticle
{
	Vector2f velocity;
	Time lifetime;
};


Steam::Steam(float x, float y, unsigned int count, int degree) :
x(x),
y(y),
particles(count),
vertices(Quads, count),
lifetime(seconds(3)),
emitter(0, 0),
degree(degree)
{
	init();
}

void Steam::init()
{
	emitter = Vector2f(x, y);
	//tSteam.loadFromFile("Resources/Sprites/Steam.png");
	tSteam = Images::getTexture(Images::img::STEAM);
	tHitbox.loadFromFile("Resources/ObjectCollision/steamHitBox.png");
	sHitbox.setTexture(tHitbox);

	if (degree == 0)
	{
		sHitbox.setPosition(emitter.x - sHitbox.getTextureRect().width / 2, emitter.y);
		sHitbox.setRotation(0);
	}
	if (degree == 1)
	{
		sHitbox.setPosition(emitter.x + 20, emitter.y + sHitbox.getTextureRect().height / 2);
		sHitbox.setRotation(270);
	}
	if (degree == 2)
	{
		sHitbox.setPosition(emitter.x + sHitbox.getTextureRect().width / 2, emitter.y);
		sHitbox.setRotation(180);
	}
	if (degree == 3)
	{
		sHitbox.setPosition(emitter.x, emitter.y - sHitbox.getTextureRect().height / 2);
		sHitbox.setRotation(90);
	}
}

void Steam::setEmitter(Vector2f p)
{
	emitter = p;
}

void Steam::update()
{
	time = clock.getElapsedTime();

	for (size_t i = 0; i < particles.size(); i++)
	{
		SteamParticle &p = particles[i];
		p.lifetime -= time;


		float disY = (vertices[i].position.y - emitter.y);
		float disX = (vertices[i].position.x - emitter.x);

		if (p.lifetime.asMicroseconds() <= 0 || disY >= 400 || disY <= -400 || disX >= 400 || disX <= -400)
		{
			reset(i);
		}

		vertices[i].position += p.velocity * time.asSeconds();

		float ratio = p.lifetime.asSeconds() / (lifetime.asSeconds() * 2);
		vertices[i].color.a = static_cast<Uint8>(ratio);
	}
	clock.restart();
}

void Steam::draw(RenderWindow *window)
{
	RenderStates states;
	states.texture = &tSteam;
	states.blendMode = BlendAdd;
	window->draw(vertices, states);
	window->draw(sHitbox);
}

void Steam::reset(size_t i)
{
	float angle = (rand() % 70);
	float speed = (rand() % 75) + 50;

	// Down
	if (degree == 0)
		particles[i].velocity = Vector2f(cos(angle) * speed / 2, speed);

	// Right
	if (degree == 1)
		particles[i].velocity = Vector2f(speed, sin(angle) * speed / 2);

	// Up
	if (degree == 2)
		particles[i].velocity = Vector2f(-(cos(angle) * speed / 2), -(speed));

	// Left
	if (degree == 3)
		particles[i].velocity = Vector2f(-(speed), -(sin(angle) * speed / 2));

	particles[i].lifetime = milliseconds((rand() % 50000) + 500);

	vertices[i].position = emitter;
}

Sprite Steam::getHitbox()
{
	return sHitbox;
}