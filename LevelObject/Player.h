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
	int getX();
	int getY();
	void setX(int i);
	void setY(int i);
	void setClimbing(bool b);
	void finalize();
	bool getHitG();
	bool getHoldingRight();
	bool getHoldingLeft();
	bool getFacingRight();
	void setCanJump(bool b);
	bool getFalling();
	void setVelY(float f);
private:
	// movement
	float x;
	float velX;
	float y;
	float velY;
	float accY;
	// starting jump, in jump
	bool jumping;
	bool inJump;
	// animation timer, frames
	int animeTimer;
	int frameW;
	int frameH;
	// facing right
	bool facingRight;
	// collide on all sides
	bool hitC, hitR, hitL, hitG;
	// for determing which hit should be on
	bool touchL;
	// collision with hitbox above feet for slopes
	bool hitAboveG;
	// gliding and climbing
	bool gliding;
	bool climbing;
	int climbTimer;
	// abilities
	bool canJump;
	bool canGlide;
	bool canFly;
	// holding buttons
	bool holdingRight, holdingLeft;
	// which slope the owl is sliding on
	int sliding;
	int slideTimer;
};

#endif