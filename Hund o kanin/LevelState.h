#ifndef INCLUDED_LEVELSTATE
#define INCLUDED_LEVELSTATE

#include "GameState.h"
#include "Player.h"
#include "Bunny.h"
#include "Dog.h"
#include "Shroom.h"
#include "Slope.h"
#include "BigNut.h"
#include "Chunk.h"
#include <vector>

using namespace std;
using namespace sf;

class LevelState : public GameState
{
public:
	LevelState(GameStateManager* gsm);
	virtual void init();
	virtual void update();
	virtual void draw(sf::RenderWindow* window);
	virtual void handleInputs(sf::Event* events);
	bool isOffScreen(Sprite sprite);
	bool isOffScreenRect(IntRect rect);
	void addChunk(String path, int x, int y);
	void addGround(String path, int x, int y);
	void addWall(String path, int x, int y);
	void addRect(int x, int y);
protected:
	GameStateManager* gsm;
private:
	Player* player;
	Bunny* bunny;
	Dog* dog;
	Shroom* shroom;
	Slope* slope;
	Slope* slope2;
	BigNut* bigNut;
	typedef vector<Chunk*> ChunkVector;
	ChunkVector chunks;
	typedef vector<Texture*> TextureVector;
	typedef vector<Sprite*> SpriteVector;
	typedef vector<IntRect*> RectangleVector;
	TextureVector groundT;
	TextureVector wallT;
	TextureVector ceilingT;
	TextureVector chunksT;
	//SpriteVector chunks;
	SpriteVector ground;
	SpriteVector wall;
	SpriteVector ceiling;
	SpriteVector foreGround;
	RectangleVector rects;
	View view;
	bool escape;
	bool latestWallSideRight;
	int pauseInitTimer;
};

#endif
