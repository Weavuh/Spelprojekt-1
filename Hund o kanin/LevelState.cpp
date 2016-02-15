#include "LevelState.h"
#include "Collision.h"
#include <SFML\Audio.hpp>

// backgrounds
Texture tBg1;
Sprite sBg1;
Sprite sBg1B;
Texture tBg2;
Sprite sBg2;

// foreground
Texture tForeGround1;
Sprite sForeGround1;

// audio
Music bgMusicA;
Music bgMusicB;
Music bgMusicC;
Music bgMusicD;

LevelState::LevelState(GameStateManager* gsm) :
gsm(gsm),
escape(false),
latestWallSideRight(false),
pauseInitTimer(0)
{
	GameStateManager::setPaused(true);
}

void LevelState::init() 
{
	// background
	tBg1.loadFromFile("Resources/Backgrounds/levelBg.png");
	sBg1.setTexture(tBg1);
	sBg1.setPosition(0, 0);
	sBg1B.setTexture(tBg1);
	sBg1B.setPosition(-1920, 0);
	
	tBg2.loadFromFile("Resources/Backgrounds/levelBg2.png");
	sBg2.setTexture(tBg2);
	sBg2.setPosition(0, 0);

	// foreground
	tForeGround1.loadFromFile("Resources/BackGrounds/foreGround1.png");
	sForeGround1.setTexture(tForeGround1);
	sForeGround1.setPosition(500, 0);

	foreGround.push_back(&sForeGround1);

	// audio
	bgMusicA.openFromFile("Resources/Audio/mainguitar_001.wav");
	bgMusicB.openFromFile("Resources/Audio/bassandstring_001.wav");
	bgMusicC.openFromFile("Resources/Audio/celticharp_001.wav");
	bgMusicD.openFromFile("Resources/Audio/drums_001.wav");
	bgMusicA.setLoop(true);
	bgMusicB.setLoop(true);
	bgMusicC.setLoop(true);
	bgMusicD.setLoop(true);

	// player
	player = new Player();

	// bunny
	bunny = new Bunny();

	// dog
	dog = new Dog();

	// shroom
	shroom = new Shroom(430, 280, -30);

	// big nut
	bigNut = new BigNut(750, 270, -50, 570);

	//slope
	slope = new Slope(-155, 470, 0, false);
	slope2 = new Slope(2430, 468, 1, true);

	// camera view
	view = View(FloatRect(0, 0, 1920, 1080));

	// chunks
	for (ChunkVector::size_type i = 0; i < 7; i++)
	{
		for (ChunkVector::size_type j = 0; j < 3; j++)
		{
			chunks.push_back(new Chunk(i, j, "Resources/Chunks/" + to_string(i) + "_" + to_string(j) + ".png"));
		}
	}

	//for (RectangleVector::size_type i = 0; i < 10; i++)
	//{
	//	for (RectangleVector::size_type j = 0; j < 10; j++)
	//	{
	//		addRect(i, j);
	//	}
	//}

	// chunks
	//addChunk("Resources/Chunks/1_0.png", 1, 0);
	//addChunk("Resources/Chunks/1_6.png", 1, 6);
	//addChunk("Resources/Chunks/2_0.png", 2, 0);
	//addChunk("Resources/Chunks/2_5.png", 2, 5);
	//addChunk("Resources/Chunks/2_6.png", 2, 6);
	//addChunk("Resources/Chunks/3_0.png", 3, 0);
	//addChunk("Resources/Chunks/3_5.png", 3, 5);
	//addChunk("Resources/Chunks/3_6.png", 3, 6);
	//addChunk("Resources/Chunks/4_0.png", 4, 0);
	//addChunk("Resources/Chunks/4_5.png", 4, 5);
	//addChunk("Resources/Chunks/4_6.png", 4, 6);
	//addChunk("Resources/Chunks/5_0.png", 5, 0);
	//addChunk("Resources/Chunks/5_1.png", 5, 1);
	//addChunk("Resources/Chunks/5_2.png", 5, 2);
	//addChunk("Resources/Chunks/5_3.png", 5, 3);
	//addChunk("Resources/Chunks/5_6.png", 5, 6);
	//addChunk("Resources/Chunks/6_0.png", 6, 0);
	//addChunk("Resources/Chunks/6_1.png", 6, 1);
	//addChunk("Resources/Chunks/6_2.png", 6, 2);
	//addChunk("Resources/Chunks/6_3.png", 6, 3);
	//addChunk("Resources/Chunks/6_4.png", 6, 4);
	//addChunk("Resources/Chunks/6_5.png", 6, 5);
	//addChunk("Resources/Chunks/6_6.png", 6, 6);
	//addChunk("Resources/Chunks/7_0.png", 7, 0);
	//addChunk("Resources/Chunks/7_1.png", 7, 1);
	//addChunk("Resources/Chunks/7_2.png", 7, 2);
	//addChunk("Resources/Chunks/7_3.png", 7, 3);
	//addChunk("Resources/Chunks/7_4.png", 7, 4);
	//addChunk("Resources/Chunks/7_5.png", 7, 5);
	//addChunk("Resources/Chunks/7_6.png", 7, 6);
	//addChunk("Resources/Chunks/8_0.png", 8, 0);
	//addChunk("Resources/Chunks/8_1.png", 8, 1);
	//addChunk("Resources/Chunks/8_2.png", 8, 2);
	//addChunk("Resources/Chunks/8_3.png", 8, 3);
	//addChunk("Resources/Chunks/8_5.png", 8, 5);
	//addChunk("Resources/Chunks/8_6.png", 8, 6);
	//addChunk("Resources/Chunks/9_0.png", 9, 0);
	//addChunk("Resources/Chunks/9_1.png", 9, 1);
	//addChunk("Resources/Chunks/9_2.png", 9, 2);
	//addChunk("Resources/Chunks/9_3.png", 9, 3);
	//addChunk("Resources/Chunks/9_4.png", 9, 4);
	//addChunk("Resources/Chunks/9_5.png", 9, 5);
	//addChunk("Resources/Chunks/9_6.png", 9, 6);

	// platforms
	addGround("Resources/Chunks/1_0bG.png", 0, 0);

	addWall("Resources/Chunks/1_0bW.png", 0, 0);
	
	Collision::CreateTextureAndBitmask(*groundT[0], "Resources/Chunks/1_0bG.png");
	Collision::CreateTextureAndBitmask(*wallT[0], "Resources/Chunks/1_0bW.png");
	//Collision::CreateTextureAndBitmask(tCollisionC, "Resources/ObjectCollision/cCeiling.png");

	// looped stuff
	//collG1B = collG1;
	//collG1B.setPosition(-400 + 5100, 600);
	//ground.push_back(&collG1B);

	// play music
	if (!GameStateManager::getMutedMusic())
	{
		bgMusicA.setVolume(0);
		bgMusicA.play();
		bgMusicB.setVolume(0);
		bgMusicB.play();
		bgMusicC.setVolume(0);
		bgMusicC.play();
		bgMusicD.play();
	}
}

void LevelState::update()
{
	if (pauseInitTimer > -1) pauseInitTimer++;
	if (pauseInitTimer == 180)
	{
		pauseInitTimer = -1;
		GameStateManager::setPaused(false);
	}

	// update bunny
	bunny->update();

	// update dog
	dog->update();

	// update shroom
	shroom->update();

	// update nut
	bigNut->update();

	if (!GameStateManager::getPaused())
	{
		// update player
		player->update();
	}

	//if (player->getX() > 4800) player->setX(-5000);
	if (player->getX() < -5000) player->setX(4800);

	player->setHitG(false);
	player->setHitL(false);
	player->setHitR(false);
	player->setHitC(false);
	player->setHitAboveG(false);

	for (ChunkVector::size_type i = 0; i < chunks.size(); i++)
	{
		if (isOffScreenRect(chunks[i]->getRect()) && chunks[i]->getActive())
		{
			chunks[i]->setActive(false);
		}
		else if (!isOffScreenRect(chunks[i]->getRect()) && !chunks[i]->getActive())
		{
			chunks[i]->setActive(true);
		}
	}

	// check collision
	for (int i = 0; i < ground.size(); i++)
	{
		if (!isOffScreen(*ground[i]))
		{
			if (Collision::PixelPerfectTest(player->getFeet(), *ground[i], 0))
			{
				player->setHitG(true);
			}
			if (Collision::PixelPerfectTest(player->getAboveFeet(), *ground[i], 0))
			{
				player->setHitAboveG(true);
			}
		}
	}

	if (Collision::PixelPerfectTest(player->getFeet(), bigNut->getNutG(), 0) && !bigNut->getFalling())
	{
		player->setHitG(true);
	}

	for (int i = 0; i < wall.size(); i++)
	{
		if (Collision::PixelPerfectTest(player->getSprite(), *wall[i], 0) && !player->getSliding())
		{
			if (player->getVelX() > 0)
			{
				player->setHitR(true);
				latestWallSideRight = true;
			}
			if (player->getVelX() < 0)
			{
				player->setHitL(true);
				latestWallSideRight = false;
			}
			if (player->getVelX() == 0)
			{
				if (latestWallSideRight) player->setHitR(true);
				else player->setHitL(true);
			}

			//if (player->movingRight() && !player->getTouchL())
			//{
			//	if (player->getVelX() == 0 && player->getGrabingObject() && !player->getFacingRight()) player->setHitL(true);
			//	else player->setHitR(true);
			//}
			//else player->setHitL(true);
		}
	}
	if (Collision::PixelPerfectTest(player->getSprite(), bigNut->getNutW(), 0) && !player->getGrabingObject())
	{
		if (player->getVelX() > 0)
		{
			player->setHitR(true);
			latestWallSideRight = true;
		}
		if (player->getVelX() < 0)
		{
			player->setHitL(true);
			latestWallSideRight = false;
		}
		if (player->getVelX() == 0)
		{
			if (latestWallSideRight) player->setHitR(true);
			else player->setHitL(true);
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
	if (player->getX() < 550 && bunny->getCurrentTrigger() == 0) 
	{
		bunny->setTriggered(true);
	}

	// check trigger dog
	if (player->getX() > 1400 && dog->getCurrentTrigger() == 0)
	{
		dog->setTriggered(true);
	}

	// big nuts
	if (player->getInteracting())
	{
		if ((Collision::PixelPerfectTest(player->getSprite(), bigNut->getGrabBox(), 0) && player->getHitG() && !player->getSliding()) && 
			(bigNut->getX() > player->getX() && player->getFacingRight() ||
			bigNut->getX() < player->getX() && !player->getFacingRight()))
		{
			player->setGrabingObject(true);
			if (player->getFacingRight()) player->setX(bigNut->getX() - 102);
			else player->setX(bigNut->getX() + 102);
			//player->setX(player->getX())
		}
		else
		{
			player->setGrabingObject(false);
			bigNut->setMovementState(0);
		}
	}
	else
	{
		player->setGrabingObject(false);
		bigNut->setMovementState(0);
	}

	if (player->getGrabingObject())
	{
		if (player->getVelX() > 0)
		{
			bigNut->setMovementState(1);
		}
		else if (player->getVelX() < 0 && !player->getTouchL())
		{
			bigNut->setMovementState(2);
		}
		else bigNut->setMovementState(0);
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

	// check slide slopes
	if (!isOffScreen(slope->getSprite()))
	{
		if (Collision::PixelPerfectTest(player->getSprite(), slope->getSprite(), 0) && player->getFalling())
		{
			player->setSliding(slope->getFacingRight());
		}
	}
	if (!isOffScreen(slope2->getSprite()))
	{
		if (Collision::PixelPerfectTest(player->getSprite(), slope2->getSprite(), 0) && player->getFalling())
		{
			player->setSliding(slope2->getFacingRight());
		}
	}

	// check nut slopes
	if (!isOffScreen(slope->getSprite()) && !isOffScreen(bigNut->getSprite()))
	{
		if (Collision::PixelPerfectTest(bigNut->getGrabBox(), slope->getSprite(), 0))
		{
			if (player->getGrabingObject())
			{
				if (player->getFacingRight()) player->setHitR(true);
				else player->setHitL(true);
			}
			else
			{
			    if (slope->getFacingRight()) bigNut->setInSlope(1);
			    else bigNut->setInSlope(2);
			}
		}
		else bigNut->setInSlope(0);
	}

	// update music
	if (player->getX() > 800 && bgMusicA.getVolume() < 100)
	{
		bgMusicA.setVolume(bgMusicA.getVolume() + 1);
	}
	if (player->getX() > 1700 && bgMusicC.getVolume() < 100)
	{
		bgMusicC.setVolume(bgMusicC.getVolume() + 1);
	}
	if (player->getX() > 2500 && bgMusicB.getVolume() < 100)
	{
		bgMusicB.setVolume(bgMusicB.getVolume() + 1);
	}
	if (player->getX() < 700 && bgMusicD.getVolume() > 0)
	{
		bgMusicD.setVolume(bgMusicD.getVolume() - 1);
	}

	// update camera, background and foreground
	int tempX = view.getCenter().x;
	int tempY = view.getCenter().y;
	view.setCenter(player->getX(), player->getY());
	//if (view.getCenter().y > 600) view.setCenter(view.getCenter().x, 600);
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

	// draw chunks
	for (ChunkVector::size_type i = 0; i < chunks.size(); i++)
	{
		if (chunks[i]->getActive()) chunks[i]->draw(window);
	}
	//for (SpriteVector::size_type i = 0; i < chunks.size(); i++)
	//{
	//	if (!isOffScreen(*chunks[i]))
	//	{
	//		window->draw(*chunks[i]);
	//	}
	//}

	// draw player
	player->draw(window);

	// draw bunny
	bunny->draw(window);

	// draw dog
	dog->draw(window);

	// draw shroom
	shroom->draw(window);

	// big nut
	if (!isOffScreen(bigNut->getSprite())) bigNut->draw(window);

	// draw platforms
	//for (SpriteVector::size_type i = 0; i < ground.size(); i++)
	//{
	//	if (!isOffScreen(ground[i])) window->draw(ground[i]);
	//}
	//for (SpriteVector::size_type i = 0; i < wall.size(); i++)
	//{
	//	if (!isOffScreen(wall[i])) window->draw(wall[i]);
	//}
	//for (SpriteVector::size_type i = 0; i < ceiling.size(); i++)
	//{
	//	if (!isOffScreen(ceiling[i])) window->draw(ceiling[i]);
	//}

	//if (!isOffScreen(collG1B)) window->draw(collG1B);

	slope->draw(window);
	slope2->draw(window);

	// draw foreground
	if (!isOffScreen(sForeGround1)) window->draw(sForeGround1);

	if (escape)
	{
		view.setSize(1920, 1080);
		view.setCenter(960, 540);
		bgMusicA.stop();
		bgMusicB.stop();
		bgMusicC.stop();
		bgMusicD.stop();
		window->setView(view);
		player->finalize();
		gsm->setState(GameStateManager::states::MENUSTATE);
	}
}

void LevelState::handleInputs(Event* events)
{
	if (!GameStateManager::getPaused())
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

bool LevelState::isOffScreenRect(IntRect rect)
{
	// check if object is off screen
	return (rect.left > view.getCenter().x + (view.getSize().x / 2) ||
		rect.left + rect.width < view.getCenter().x - (view.getSize().x / 2) ||
		rect.top > view.getCenter().y + (view.getSize().y / 2) ||
		rect.top + rect.height < view.getCenter().y - (view.getSize().y / 2));
}

//void LevelState::addChunk(String path, int x, int y)
//{
//	chunksT.push_back(new Texture());
//	chunksT.back()->loadFromFile(path);
//	chunks.push_back(new Sprite(*chunksT.back()));
//	chunks.back()->setPosition(x * 2048, y * 2048);
//}

void LevelState::addGround(String path, int x, int y)
{
	groundT.push_back(new Texture());
	groundT.back()->loadFromFile(path);
	ground.push_back(new Sprite(*groundT.back()));
	ground.back()->setPosition(x * 2048, y * 2048);
	Collision::CreateTextureAndBitmask(*groundT.back(), path);
}

void LevelState::addWall(String path, int x, int y)
{
	wallT.push_back(new Texture());
	wallT.back()->loadFromFile(path);
	wall.push_back(new Sprite(*wallT.back()));
	wall.back()->setPosition(x * 2048, y * 2048);
	Collision::CreateTextureAndBitmask(*wallT.back(), path);
}

void LevelState::addRect(int x, int y)
{
	rects.push_back(new IntRect(x * 2048, y * 2048, 2048, 2048));
}