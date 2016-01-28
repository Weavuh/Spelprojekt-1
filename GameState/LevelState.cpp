#include "LevelState.h"
#include "Collision.h"
#include <SFML\Audio.hpp>

// backgrounds
Texture tBg1;
Sprite sBg1;
Texture tBg1B;
Sprite sBg1B;
Texture tBg2;
Sprite sBg2;

// platforms
Texture tCollisionG1, tCollisionG2, tCollisionG3, tCollisionG4, tCollisionG5;
Texture tCollisionW;
Texture tCollisionC;

Sprite collG1, collG2, collG3, collG4, collG5;
Sprite collG1B, collG5B;
Sprite collW;
Sprite collC;

// foreground
Texture tForeGround1;
Sprite sForeGround1;

// audio
Music bgMusic;

LevelState::LevelState(GameStateManager* gsm) :
gsm(gsm)
{
	init();
}

void LevelState::init() 
{
	// background
	tBg1.loadFromFile("Resources/levelBg.png");
	sBg1.setTexture(tBg1);
	sBg1.setPosition(0, 0);
	tBg1B.loadFromFile("Resources/levelBg.png");
	sBg1B.setTexture(tBg1B);
	sBg1B.setPosition(tBg1.getSize().x * -1, 0);
	tBg2.loadFromFile("Resources/levelBg2.png");
	sBg2.setTexture(tBg2);
	sBg2.setPosition(0, 0);

	// audio
	bgMusic.openFromFile("Resources/Koncept2.wav");
	bgMusic.setLoop(true);

	// player
	player = new Player();

	// camera view
	view = View(FloatRect(0, 0, 1920, 1080));

	// platforms
	tCollisionG1.loadFromFile("Resources/cGround1.png");
	tCollisionG2.loadFromFile("Resources/cGround2.png");
	tCollisionG3.loadFromFile("Resources/cGround3.png");
	tCollisionG4.loadFromFile("Resources/cGround4.png");
	tCollisionG5.loadFromFile("Resources/cGround5.png");
	tCollisionW.loadFromFile("Resources/cWall1.png");
	tCollisionC.loadFromFile("Resources/cCeiling.png");
	
	collG1.setTexture(tCollisionG1);
	collG1.setPosition(-400, 600);
	collG2.setTexture(tCollisionG2);
	collG2.setPosition(1200, 700);
	collG3.setTexture(tCollisionG3);
	collG3.setPosition(1700, 700);
	collG4.setTexture(tCollisionG4);
	collG4.setPosition(2300, 700);
	collG5.setTexture(tCollisionG5);
	collG5.setPosition(2700, 700);
	collW.setTexture(tCollisionW);
	collW.setPosition(1000, 700);
	collC.setTexture(tCollisionC);
	collC.setPosition(100, 400);

	ground.push_back(&collG1);
	ground.push_back(&collG2);
	ground.push_back(&collG3);
	ground.push_back(&collG4);
	ground.push_back(&collG5);
	wall.push_back(&collW);
	ceiling.push_back(&collC);

	Collision::CreateTextureAndBitmask(tCollisionG1, "Resources/cGround1.png");
	Collision::CreateTextureAndBitmask(tCollisionG2, "Resources/cGround2.png");
	Collision::CreateTextureAndBitmask(tCollisionG3, "Resources/cGround3.png");
	Collision::CreateTextureAndBitmask(tCollisionG4, "Resources/cGround4.png");
	Collision::CreateTextureAndBitmask(tCollisionG5, "Resources/cGround5.png");
	Collision::CreateTextureAndBitmask(tCollisionW, "Resources/cWall1.png");
	Collision::CreateTextureAndBitmask(tCollisionC, "Resources/cCeiling.png");

	// looped stuff
	collG1B = collG1;
	collG1B.setPosition(-400 + 4000, 600);
	ground.push_back(&collG1B);

	collG5B = collG5;
	collG5B.setPosition(2700 - 4000, 700);
	ground.push_back(&collG5B);

	// foreground
	tForeGround1.loadFromFile("Resources/foreGround1.png");
	sForeGround1.setTexture(tForeGround1);
	sForeGround1.setPosition(500, 0);

	foreGround.push_back(&sForeGround1);

	// play music
	bgMusic.play();
}

void LevelState::update()
{
	// update player
	player->update();
	if (player->getX() > 3700) player->setX(-300);
	if (player->getX() < -300) player->setX(3700);

	player->setHitG(false);
	player->setHitL(false);
	player->setHitR(false);
	player->setHitC(false);
	player->setHitAboveG(false);

	// check collision
	for (int i = 0; i < ground.size(); i++)
	{
		if (!isOffScreen(*ground[i]))
		{
			if (Collision::PixelPerfectTest(player->getFeet(), *ground[i], 0) == true /*&& Collision::PixelPerfectTest(sprite, sprite2) != true && Collision::PixelPerfectTest(sprite, sprite3) != true && Collision::PixelPerfectTest(sprite, sprite4) != true && Collision::PixelPerfectTest(sprite, sprite5) != true*/)
			{
				player->setHitG(true);
			}
			if (Collision::PixelPerfectTest(player->getAboveFeet(), *ground[i], 0) == true /*&& Collision::PixelPerfectTest(sprite, sprite2) != true && Collision::PixelPerfectTest(sprite, sprite3) != true && Collision::PixelPerfectTest(sprite, sprite4) != true && Collision::PixelPerfectTest(sprite, sprite5) != true*/)
			{
				player->setHitAboveG(true);
			}
		}
	}
	for (int i = 0; i < wall.size(); i++)
	{
		if (Collision::PixelPerfectTest(player->getSprite(), *wall[i], 0) == true /*&& Collision::PixelPerfectTest(sprite, sprite2) != true && Collision::PixelPerfectTest(sprite, sprite3) != true && Collision::PixelPerfectTest(sprite, sprite4) != true && Collision::PixelPerfectTest(sprite, sprite5) != true*/)
		{
			if (player->movingRight() && !player->getTouchL()) player->setHitR(true);
			else player->setHitL(true);
		}
	}
	for (int i = 0; i < ceiling.size(); i++)
	{
		if (Collision::PixelPerfectTest(player->getSprite(), *ceiling[i], 0) == true /*&& Collision::PixelPerfectTest(sprite, sprite2) != true && Collision::PixelPerfectTest(sprite, sprite3) != true && Collision::PixelPerfectTest(sprite, sprite4) != true && Collision::PixelPerfectTest(sprite, sprite5) != true*/)
		{
			player->setHitC(true);
		}
	}

	// update camera, background and foreground
	int tempX = view.getCenter().x;
	view.setCenter(player->getX(), player->getY());
	sForeGround1.move(-((view.getCenter().x - tempX) * 2), 0);
	sBg1.move(((view.getCenter().x - tempX) * 0.3), 0);
	sBg1B.move(((view.getCenter().x - tempX) * 0.3), 0);
	sBg2.move(((view.getCenter().x - tempX) * 0.1), 0);

	//if (sBg1.getPosition().x < view.getCenter().x - 1200) sBg1.move(1920, 0);
	//else if (sBg1.getPosition().x > view.getCenter().x + 1200) sBg1.move(-1920, 0);
	if (sBg2.getPosition().x < view.getCenter().x - 1200) sBg2.move(1920, 0);
	//else if (sBg2.getPosition().x > view.getCenter().x + 1200) sBg2.move(-1920, 0);

	if (Keyboard::isKeyPressed(Keyboard::Space) && view.getSize().x < 1920 * 5)
	{
		view.setSize(view.getSize().x * 1.05, view.getSize().y * 1.05);
	}
	else if (!Keyboard::isKeyPressed(Keyboard::Space) && view.getSize().x > 1920)
	{
		view.setSize(view.getSize().x * 0.95, view.getSize().y * 0.95);
	}

}

void LevelState::draw(RenderWindow* window)
{
	// set cameraview
	window->setView(view);

	// draw background
	window->draw(sBg1);
	window->draw(sBg1B);
	window->draw(sBg2);

	// draw player
	player->draw(window);

	// draw platforms
	if (!isOffScreen(collG1)) window->draw(collG1);
	if (!isOffScreen(collG2)) window->draw(collG2);
	if (!isOffScreen(collG3)) window->draw(collG3);
	if (!isOffScreen(collG4)) window->draw(collG4);
	if (!isOffScreen(collG5)) window->draw(collG5);
	if (!isOffScreen(collW)) window->draw(collW);
	if (!isOffScreen(collC)) window->draw(collC);

	if (!isOffScreen(collG1B)) window->draw(collG1B);
	if (!isOffScreen(collG5B)) window->draw(collG5B);

	// draw foreground
	if (!isOffScreen(sForeGround1)) window->draw(sForeGround1);
}

void LevelState::handleInputs(Event* events)
{
	// update player inputs
	player->handleInputs(events);
}

bool LevelState::isOffScreen(Sprite sprite)
{
	// check if object is off screen
	FloatRect temp = sprite.getGlobalBounds();
	return (temp.left > view.getCenter().x + (view.getSize().x / 2) ||
		temp.left + temp.width < view.getCenter().x - (view.getSize().x / 2) ||
		temp.top > view.getCenter().y + (view.getSize().y / 2) ||
		temp.top + temp.height < view.getCenter().y - (view.getSize().y / 2));
}