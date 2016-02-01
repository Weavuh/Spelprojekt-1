#include "Player.h"
#include <SFML\Audio.hpp>

using namespace sf;

Texture playerImg;
Sprite playerSprite;
IntRect playerRect;

SoundBuffer jumpBuffer;
Sound jumpSound;

Player::Player() :
x(600),
velX(0),
y(500),
velY(0),
accY(0),
jumping(false),
animeTimer(0),
frameW(0),
frameH(0),
facingRight(true),
hitC(false),
hitG(false),
hitL(false),
touchL(false),
hitR(false),
hitAboveG(false),
gliding(false),
climbing(false),
climbTimer(0),
canJump(true),
canGlide(true),
canFly(false),
holdingLeft(false),
holdingRight(false),
sliding(0),
slideTimer(0)
{
	init();
}

void Player::init()
{
	playerImg.loadFromFile("Resources/owl.png");
	playerRect = IntRect(0, 0, 150, 200);
	playerSprite.setTexture(playerImg);
	playerSprite.setTextureRect(playerRect);
	playerSprite.setPosition(x, y);
	playerSprite.setOrigin(75, 100);
	jumpBuffer.loadFromFile("Resources/soft-slidertick.wav");
	jumpSound.setBuffer(jumpBuffer);
}

void Player::update()
{
	// update holding inputs
	holdingLeft = false;
	holdingRight = false;
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		velX = 6;
		holdingRight = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		velX = -6;
		holdingLeft = true;
	}
	else velX = 0;

	if (Keyboard::isKeyPressed(Keyboard::Z) && !hitG && velY > 0 && canGlide)
	{
		gliding = true;
	}
	else gliding = false;

	// update movement
	if (!hitG)
	{
		accY = 0.7;
	}
	if (jumping)
	{
		velY = -15;
		//jumpSound.play();
		jumping = false;
		inJump = true;
	}

	if (climbing)
	{
		climbTimer++;
		velX = 0;
		velY = 0;
		accY = 0;
		if (climbTimer < 45)
		{
			velY = -2;
		}
		else if (climbTimer < 110)
		{
			velY = 0;
			if (facingRight) velX = 2;
			else velX = -2;
		}
		
		if (climbTimer == 110)
		{
			climbing = false;
			climbTimer = 0;
		}
	}

	if (sliding == 1)
	{
		slideTimer++;
		if (slideTimer < 100)
		{
			velX = -5;
			velY = 5;
		}
		else if (slideTimer == 100)
		{
			sliding = 0;

		}
	}

	if (hitG && velY >= 0)
	{
		accY = 0;
		velY = 0;
		if (inJump) inJump = false;
	}
	if (hitG && hitAboveG)
	{
		//inJump = false;
		y -= 2;
	}
	if (hitR && velX >= 0)
	{
		velX = 0;
	}
	if (hitL && velX <= 0)
	{
		touchL = true;
		velX = 0;
	}
	else touchL = false;
	if (hitC && velY < 0)
	{
		velY = 0;
	}

	x += velX;
	velY += accY;
	if (velY > 20) velY = 20;
	if (velY > 1 && gliding) velY = 1;
	y += velY;
	
	playerSprite.setPosition(x, y);

	// update animations
	if (climbing) frameH = 5;
	else if (gliding && velY > 0) frameH = 4;
	else if (velY < 0) frameH = 2;
	else if (velY > 4) frameH = 3;
	else if (velX != 0) frameH = 1;
	else frameH = 0;

	animeTimer++;
	if (animeTimer == 15)
	{
		animeTimer = 0;
		frameW++;
	}

	if (frameH == 5 && frameW > 2) frameW = 0;
	else if (frameH < 2 && frameW > 3) frameW = 0;
	else if (frameH > 1 && frameH < 5 && frameW > 1) frameW = 0;

	bool tempFacing = facingRight;

	if (velX > 0) facingRight = true;
	if (velX < 0) facingRight = false;

	if (tempFacing != facingRight) playerSprite.scale(-1.f, 1.f);

	playerRect.left = frameW * 150;
	playerRect.top = frameH * 200;
	playerSprite.setTextureRect(playerRect);
}

void Player::draw(RenderWindow* window)
{
	window->draw(playerSprite);
}

void Player::handleInputs(Event* events)
{
	if (events->type == Event::KeyPressed)
	{
		if (events->key.code == Keyboard::Z && canJump)
		{
			if (canFly) jumping = true;
			else if (!inJump) jumping = true;
		}
		if (events->key.code == Keyboard::Return)
		{
			y = 600;
			x = 500;
		}
	}
}

void Player::setHitC(bool b)
{
	hitC = b;
}
void Player::setHitR(bool b)
{
	hitR = b;
}
void Player::setHitL(bool b)
{
	hitL = b;
}
void Player::setHitG(bool b)
{
	hitG = b;
}
void Player::setHitAboveG(bool b)
{
	hitAboveG = b;
}

Sprite Player::getSprite()
{
	return playerSprite;
}

Sprite Player::getFeet()
{
	Sprite temp = playerSprite;
	IntRect tempRect = IntRect(0, 0, 150, 10);
	temp.setTextureRect(tempRect);
	temp.setPosition(x, y + 190);
	return temp;
}

Sprite Player::getAboveFeet()
{
	Sprite temp = playerSprite;
	IntRect tempRect = IntRect(0, 0, 130, 5);
	temp.setTextureRect(tempRect);
	temp.setPosition(x, y + 190);
	return temp;
}

bool Player::movingRight()
{
	return (velX >= 0);
}

bool Player::getTouchL()
{
	return touchL;
}

int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

void Player::setX(int i)
{
	x = i;
}

void Player::setY(int i)
{
	y = i;
}

void Player::setClimbing(bool b)
{
	climbing = b;
}

void Player::finalize()
{
	if (!facingRight)
	{
		playerSprite.scale(-1.f, 1.f);
	}
}

bool Player::getHitG()
{
	return hitG;
}

bool Player::getHoldingLeft()
{
	return holdingLeft;
}

bool Player::getHoldingRight()
{
	return holdingRight;
}

bool Player::getFacingRight()
{
	return facingRight;
}

void Player::setCanJump(bool b)
{
	canJump = b;
}

bool Player::getFalling()
{
	return (velY > 0);
}

void Player::setVelY(float f)
{
	velY = f;
}