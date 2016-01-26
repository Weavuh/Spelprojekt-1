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
y(800),
velY(0),
accY(0),
jumping(false),
canJump(false),
animeTimer(0),
frameW(0),
frameH(0),
facingRight(true)
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
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		velX = 6;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		velX = -6;
	}
	else velX = 0;

	// update movement
	if (y < 700)
	{
		accY = 0.7;
		canJump = false;
	}
	else canJump = true;
	if (jumping)
	{
		velY = -15;
		//jumpSound.play();
		jumping = false;
	}

	x += velX;
	velY += accY;
	if (velY > 20) velY = 20;
	y += velY;

	if (y >= 700)
	{
		y = 700;
		velY = 0;
	}
	
	playerSprite.setPosition(x, y);

	// update animations
	if (velY < 0) frameH = 2;
	else if (velY > 0) frameH = 3;
	else if (velX != 0) frameH = 1;
	else frameH = 0;

	animeTimer++;
	if (animeTimer == 15)
	{
		animeTimer = 0;
		frameW++;
	}

	if (frameH < 2 && frameW > 3) frameW = 0;
	if (frameH > 1 && frameW > 1) frameW = 0;

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
		if (events->key.code == Keyboard::Z)
		{
			if (canJump) jumping = true;
		}
	}
}