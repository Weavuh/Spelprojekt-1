#ifndef INCLUDED_GAME_OBJ
#define INCLUDED_GAME_OBJ

#include "Chunk.h"

class GameObj
{
public:
	GameObj(Chunk chunk, sf::Vector2f position, sf::Texture texture);
	~GameObj();

	void Update();
	void Draw(sf::RenderWindow &window, Chunk chunk);

	Chunk getChunk();
private:
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	Chunk mChunk;
	sf::Texture mTexture;
	bool mAlive;
};

#endif