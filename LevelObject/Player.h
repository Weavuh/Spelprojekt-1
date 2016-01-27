#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

#include <SFML\Graphics.hpp>

class Player
{
public:
	Player();
	void init();
	void update();
	void draw(sf::RenderWindow* window);
	void handleInputs(sf::Event* events);
	void setHitC(bool b);
	void setHitR(bool b);
	void setHitL(bool b);
	void setHitG(bool b);
	void setHitAboveG(bool b);
	void setHitBelowG(bool b);
	sf::Sprite getSprite();
	sf::Sprite getFeet();
	sf::Sprite getAboveFeet();
	bool movingRight();
	bool getTouchL();
private:
	float x;
	float velX;
	float y;
	float velY;
	float accY;
	bool jumping;
	bool inJump;
	bool canJump;
	int animeTimer;
	int frameW;
	int frameH;
	bool facingRight;
	bool hitC, hitR, hitL, hitG;
	bool touchL;
	bool hitAboveG;
};

#endif