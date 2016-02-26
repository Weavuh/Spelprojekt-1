#ifndef INCLUDED_LEAFES
#define INCLUDED_LEAFES

#include "SFML\Graphics.hpp"

struct Leaf;

class Leaves
{
public:
	Leaves(float x, float y);
	void init();
	void update();
	void draw(sf::RenderWindow* window);
	void reset(std::size_t i);
private:
	float x;
	float y;
	float velX;
	float velY;
	sf::Texture tLeaf;
	sf::Sprite sLeaf;

	std::vector<Leaf> leafVector;
	sf::Clock clock;
	sf::Time time;
	sf::Time lifetime;
};

#endif