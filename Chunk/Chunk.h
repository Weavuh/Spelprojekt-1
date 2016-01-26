#ifndef INCLUDED_CHUNK
#define INCLUDED_CHUNK

#include <SFML/Graphics.hpp>

class Chunk
{
public:
	Chunk(sf::Texture texture, sf::Vector2f position, bool alive);
	~Chunk();

	void Update();
	void Draw(sf::RenderWindow &window);

	sf::Vector2f getPosition();
	sf::Sprite getSprite();
	bool getAlive();

	void setAlive(bool alive);
private:
	sf::Sprite mSprite;
	sf::Texture mTexture;
	sf::Vector2f mPosition;
	bool mAlive;
};

#endif