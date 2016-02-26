#ifndef INCLUDED_STEAM
#define INCLUDED_STEAM

#include "SFML\Graphics.hpp"

struct SteamParticle;

class Steam
{
public:
	Steam(float x, float y, unsigned int count, int degree);
	void init();
	void update();
	void draw(sf::RenderWindow *window);
	void reset(std::size_t i);
	float getAlpha();
	bool getAlive();
	float getX();
	float getY();
	void setEmitter(sf::Vector2f p);
	sf::Sprite getHitbox();
private:
	float x;
	float y;
	float velX;
	float velY;
	int degree;

	sf::Clock clock;
	sf::Time time;
	sf::Time lifetime;

	sf::Texture tSteam;
	sf::Sprite sSteam;
	sf::Texture tHitbox;
	sf::Sprite sHitbox;
	float a;
	bool alive;

	float vX;
	float vY;

	//sf::Vector2f velocity;
	sf::Vector2f emitter;
	std::vector<SteamParticle> particles;
	sf::VertexArray vertices;

	//float angle;
	//float speed;
};

#endif