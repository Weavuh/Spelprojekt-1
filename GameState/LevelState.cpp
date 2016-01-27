#include "LevelState.h"
#include "Collision.h"
#include <SFML\Audio.hpp>

Texture levelBgImg;
Sprite levelBgSprite;
Music bgMusic;

Texture tBackground;
Texture tCollisionG;
Texture tCollisionR;
Texture tCollisionL;
Texture tCollisionC;

Sprite collG;
Sprite collR;
Sprite collL;
Sprite collC;

LevelState::LevelState(GameStateManager* gsm) :
gsm(gsm)
{
	init();
}

void LevelState::init() 
{
	levelBgImg.loadFromFile("Resources/levelBg.png");
	levelBgSprite.setTexture(levelBgImg);
	levelBgSprite.setPosition(0, 0);
	bgMusic.openFromFile("Resources/Koncept2.wav");
	player = new Player();
	bgMusic.setLoop(true);

	tCollisionG.loadFromFile("Resources/cGround1.png");
	tCollisionR.loadFromFile("Resources/cWall1.png");
	tCollisionL.loadFromFile("Resources/CollisionLeftWall.png", IntRect(0, 0, 1280, 720));
	tCollisionC.loadFromFile("Resources/cCeiling.png", IntRect(0, 0, 1280, 720));
	
	collG.setTexture(tCollisionG);
	collR.setTexture(tCollisionR);
	collL.setTexture(tCollisionL);
	collC.setTexture(tCollisionC);

	Sprite temp;

	ground.push_back(&collG);
	rWall.push_back(&collR);
	//lWall.push_back(&collL);
	ceiling.push_back(&collC);

	// för varje sak
	Collision::CreateTextureAndBitmask(tCollisionG, "Resources/cGround1.png");
	Collision::CreateTextureAndBitmask(tCollisionR, "Resources/cWall1.png");
	Collision::CreateTextureAndBitmask(tCollisionL, "Resources/CollisionLeftWall.png");
	Collision::CreateTextureAndBitmask(tCollisionC, "Resources/cCeiling.png");
	bgMusic.play();
}

void LevelState::update()
{
	player->update();

	player->setHitG(false);
	player->setHitL(false);
	player->setHitR(false);
	player->setHitC(false);
	player->setHitAboveG(false);

	for (int i = 0; i < ground.size(); i++)
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
	for (int i = 0; i < rWall.size(); i++)
	{
		if (Collision::PixelPerfectTest(player->getSprite(), *rWall[i], 0) == true /*&& Collision::PixelPerfectTest(sprite, sprite2) != true && Collision::PixelPerfectTest(sprite, sprite3) != true && Collision::PixelPerfectTest(sprite, sprite4) != true && Collision::PixelPerfectTest(sprite, sprite5) != true*/)
		{
			if (player->movingRight() && !player->getTouchL()) player->setHitR(true);
			else player->setHitL(true);
		}
	}
	//for (int i = 0; i < lWall.size(); i++)
	//{
	//	if (Collision::PixelPerfectTest(player->getSprite(), *lWall[i], 0) == true /*&& Collision::PixelPerfectTest(sprite, sprite2) != true && Collision::PixelPerfectTest(sprite, sprite3) != true && Collision::PixelPerfectTest(sprite, sprite4) != true && Collision::PixelPerfectTest(sprite, sprite5) != true*/)
	//	{
	//		
	//		
	//	}
	//}
	for (int i = 0; i < ceiling.size(); i++)
	{
		if (Collision::PixelPerfectTest(player->getSprite(), *ceiling[i], 0) == true /*&& Collision::PixelPerfectTest(sprite, sprite2) != true && Collision::PixelPerfectTest(sprite, sprite3) != true && Collision::PixelPerfectTest(sprite, sprite4) != true && Collision::PixelPerfectTest(sprite, sprite5) != true*/)
		{
			player->setHitC(true);
		}
	}
}

void LevelState::draw(RenderWindow* window)
{
	window->draw(levelBgSprite);
	player->draw(window);
	window->draw(collG);
	window->draw(collR);
	window->draw(collC);
}

void LevelState::handleInputs(Event* events)
{
	player->handleInputs(events);
}