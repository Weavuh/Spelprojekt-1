#include "LevelState.h"
#include "Collision.h"
#include <SFML\Audio.hpp>

// backgrounds
Texture tBg1;
Sprite sBg1;
Sprite sBg1B;
Texture tBg2;
Sprite sBg2;

// platforms
Texture tCollisionG1;
Texture tCollisionG2;
Texture tCollisionW1;
Texture tCollisionW2;
Texture tCollisionC;

Sprite collG1;
Sprite collG1B;
Sprite collG2;
Sprite collG3;
Sprite collW1;
Sprite collW2;
Sprite collW3;
Sprite collC;

// foreground
Texture tForeGround1;
Sprite sForeGround1;

// audio
Music bgMusic;

LevelState::LevelState(GameStateManager* gsm) :
gsm(gsm),
escape(false)
{
	init();
}

void LevelState::init() 
{
	// background
	tBg1.loadFromFile("Resources/levelBg.png");
	sBg1.setTexture(tBg1);
	sBg1.setPosition(0, 0);
	sBg1B.setTexture(tBg1);
	sBg1B.setPosition(-1920, 0);
	
	tBg2.loadFromFile("Resources/levelBg2.png");
	sBg2.setTexture(tBg2);
	sBg2.setPosition(0, 0);

	// audio
	bgMusic.openFromFile("Resources/Koncept2.wav");
	bgMusic.setLoop(true);

	// player
	player = new Player();

	// bunny
	bunny = new Bunny();

	// shroom
	shroom = new Shroom(730, 760, -30);

	// camera view
	view = View(FloatRect(0, 0, 1920, 1080));

	// platforms
	tCollisionG1.loadFromFile("Resources/cGroundPull.png");
	tCollisionG2.loadFromFile("Resources/cGround2B.png");
	tCollisionW1.loadFromFile("Resources/cWallPull.png");
	tCollisionW2.loadFromFile("Resources/cWallPull2.png");
	tCollisionC.loadFromFile("Resources/cCeiling.png");
	
	collG1.setTexture(tCollisionG1);
	collG1.setPosition(-100, 600);
	collG2.setTexture(tCollisionG1);
	collG2.setPosition(-1800, 550);
	collG3.setTexture(tCollisionG2);
	collG3.setPosition(-1050, 550);
	collW1.setTexture(tCollisionW1);
	collW1.setPosition(-100+1187, 600+134);
	collW2.setTexture(tCollisionW2);
	collW2.setPosition(-100, 600);
	collW3.setTexture(tCollisionW1);
	collW3.setPosition(-1800 + 1187, 550 + 134);
	collC.setTexture(tCollisionC);
	collC.setPosition(100, 400);

	ground.push_back(&collG1);
	ground.push_back(&collG2);
	ground.push_back(&collG3);
	wall.push_back(&collW1);
	wall.push_back(&collW2);
	wall.push_back(&collW3);
	//ceiling.push_back(&collC);

	Collision::CreateTextureAndBitmask(tCollisionG1, "Resources/cGroundPull.png");
	Collision::CreateTextureAndBitmask(tCollisionG2, "Resources/cGround2B.png");
	Collision::CreateTextureAndBitmask(tCollisionW1, "Resources/cWallPull.png");
	Collision::CreateTextureAndBitmask(tCollisionW2, "Resources/cWallPull2.png");
	Collision::CreateTextureAndBitmask(tCollisionC, "Resources/cCeiling.png");

	// looped stuff
	//collG1B = collG1;
	//collG1B.setPosition(-400 + 5100, 600);
	//ground.push_back(&collG1B);

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
	// update bunny
	bunny->update();

	// update shroom
	shroom->update();

	// update player
	player->update();
	if (player->getX() > 4800) player->setX(-5000);
	if (player->getX() < -5000) player->setX(4800);

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
			if (Collision::PixelPerfectTest(player->getFeet(), *ground[i], 0) /*&& Collision::PixelPerfectTest(sprite, sprite2) != true && Collision::PixelPerfectTest(sprite, sprite3) != true && Collision::PixelPerfectTest(sprite, sprite4) != true && Collision::PixelPerfectTest(sprite, sprite5) != true*/)
			{
				player->setHitG(true);
			}
			if (Collision::PixelPerfectTest(player->getAboveFeet(), *ground[i], 0))
			{
				player->setHitAboveG(true);
			}
		}
	}
	for (int i = 0; i < wall.size(); i++)
	{
		if (Collision::PixelPerfectTest(player->getSprite(), *wall[i], 0))
		{
			if (player->movingRight() && !player->getTouchL()) player->setHitR(true);
			else player->setHitL(true);
			// check if wall size is correct, player stands on ground and key is held while owl is turned that way
			if (wall[i]->getGlobalBounds().height == 90 && player->getHitG() && 
				(player->getFacingRight() && player->getHoldingRight()) ||
				(!player->getFacingRight() && player->getHoldingLeft())) player->setClimbing(true);
		}
	}
	for (int i = 0; i < ceiling.size(); i++)
	{
		if (Collision::PixelPerfectTest(player->getSprite(), *ceiling[i], 0))
		{
			player->setHitC(true);
		}
	}

	// check trigger bunny
	if (player->getX() < -300 && bunny->getCurrentTrigger() == 0) 
	{
		bunny->setTriggered(true);
	}

	// check bounce shrooms
	if (!isOffScreen(shroom->getSprite()))
	{
		if (Collision::PixelPerfectTest(player->getFeet(), shroom->getSprite(), 0) && player->getFalling())
		{
			player->setVelY(shroom->getBounce());
			shroom->setUsed(true);
		}
	}
		

	// update camera, background and foreground
	int tempX = view.getCenter().x;
	int tempY = view.getCenter().y;
	view.setCenter(player->getX(), player->getY());
	if (view.getCenter().y > 600) view.setCenter(view.getCenter().x, 600);
	sForeGround1.move(-((view.getCenter().x - tempX) * 2), 0);
	sBg1.move(((view.getCenter().x - tempX) * 0.3), view.getCenter().y - tempY);
	sBg1B.move(((view.getCenter().x - tempX) * 0.3), view.getCenter().y - tempY);
	sBg2.move(((view.getCenter().x - tempX) * 0.1), view.getCenter().y - tempY);

	// loop backgrounds
	if (sBg1.getPosition().x + sBg1.getGlobalBounds().width < view.getCenter().x - 1000) sBg1.setPosition(sBg1B.getPosition().x + 1920, sBg1.getPosition().y);
	else if (sBg1.getPosition().x > view.getCenter().x + 1000) sBg1.setPosition(sBg1B.getPosition().x - 1920, sBg1.getPosition().y);
	if (sBg1B.getPosition().x + sBg1B.getGlobalBounds().width < view.getCenter().x - 1000) sBg1B.setPosition(sBg1.getPosition().x + 1920, sBg1B.getPosition().y);
	else if (sBg1B.getPosition().x > view.getCenter().x + 1000) sBg1B.setPosition(sBg1.getPosition().x - 1920, sBg1B.getPosition().y);

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

	// draw bunny
	bunny->draw(window);

	// draw shroom
	shroom->draw(window);

	// draw platforms
	if (!isOffScreen(collG1)) window->draw(collG1);
	if (!isOffScreen(collG2)) window->draw(collG2);
	if (!isOffScreen(collG3)) window->draw(collG3);
	if (!isOffScreen(collW1)) window->draw(collW1);
	if (!isOffScreen(collW2)) window->draw(collW2);
	if (!isOffScreen(collW3)) window->draw(collW3);
	//if (!isOffScreen(collC)) window->draw(collC);

	//if (!isOffScreen(collG1B)) window->draw(collG1B);

	// draw foreground
	if (!isOffScreen(sForeGround1)) window->draw(sForeGround1);

	if (escape)
	{
		view.setSize(1920, 1080);
		view.setCenter(960, 540);
		window->setView(view);
		player->finalize();
		gsm->setState(GameStateManager::states::MENUSTATE);
	}
}

void LevelState::handleInputs(Event* events)
{
	// update player inputs
	player->handleInputs(events);

	if (events->type == Event::KeyPressed)
	{
		if (events->key.code == Keyboard::Escape)
		{
			escape = true;
		}
	}
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