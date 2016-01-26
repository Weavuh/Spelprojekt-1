#include <SFML/Graphics.hpp>
#include "Collision.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "It's a hoot!");

	// Floats 'n stuff
	float owlGravity = 0.0f;

	float owlSpeed = 0.1f;


	// Owl Texture
	sf::Texture tOwl;

	// Background and collision textures
	sf::Texture tBackground;
	sf::Texture tCollisionG;
	sf::Texture tCollisionR;
	sf::Texture tCollisionL;
	sf::Texture tCollisionC;

	// Owl file string
	std::string& sOwl = std::string("owl.png");

	// Background and collision file strings
	std::string& sBackground = std::string("Concept001.png");
	std::string& sCollisionG = std::string("CollisionGround.png");
	std::string& sCollisionR = std::string("CollisionRightWall.png");
	std::string& sCollisionL = std::string("CollisionLeftWall.png");
	std::string& sCollisionC = std::string("CollisionCeiling.png");

	// Font ;3
	sf::Font font;
	if (!font.loadFromFile("comic.ttf"))
	{
	}

	// Text
	sf::Text text;

	// select the font
	text.setFont(font);

	// set the string to display
	text.setString("Hoot hoot.");

	// set the character size
	text.setCharacterSize(24); // in pixels, not points!

	// set the color
	text.setColor(sf::Color::Cyan);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Italic);


	typedef std::vector<sf::Sprite> SpriteVector;

	// Vectors for the collision types
	SpriteVector ground;
	SpriteVector rWall;
	SpriteVector lWall;
	SpriteVector ceiling;

	// Loading the textures from the files
	if (!tOwl.loadFromFile("owl.png"))
	{
	}

	if (!tBackground.loadFromFile("Concept001.png", sf::IntRect(0, 0, 1280, 720)))
	{
	}
	if (!tCollisionG.loadFromFile("CollisionGround.png", sf::IntRect(0, 0, 1280, 720)))
	{
	}
	if (!tCollisionR.loadFromFile("CollisionRightWall.png", sf::IntRect(0, 0, 1280, 720)))
	{
	}
	if (!tCollisionL.loadFromFile("CollisionLeftWall.png", sf::IntRect(0, 0, 1280, 720)))
	{
	}
	if (!tCollisionC.loadFromFile("CollisionCeiling.png", sf::IntRect(0, 0, 1280, 720)))
	{
	}

	// Smoothen textures
	tOwl.setSmooth(true);
	tBackground.setSmooth(true);

	// Create sprites from the textures
	sf::Sprite sprite;
	sprite.setTexture(tOwl);

	sf::Sprite background;
	background.setTexture(tBackground);
	sf::Sprite collG;
	collG.setTexture(tCollisionG);
	sf::Sprite collR;
	collR.setTexture(tCollisionR);
	sf::Sprite collL;
	collL.setTexture(tCollisionL);
	sf::Sprite collC;
	collC.setTexture(tCollisionC);


	// Scale down the owl texture file (Not really necessary, but... ;3 )
	sprite.setScale(0.1f, 0.1f);

	// Insert the collision textures into vectors
	ground.push_back(collG);
	rWall.push_back(collR);
	lWall.push_back(collL);
	ceiling.push_back(collC);

	// Create bitmask for the textures
	Collision::CreateTextureAndBitmask(tOwl, sOwl);
	Collision::CreateTextureAndBitmask(tCollisionG, sCollisionG);
	Collision::CreateTextureAndBitmask(tCollisionR, sCollisionR);
	Collision::CreateTextureAndBitmask(tCollisionL, sCollisionL);
	Collision::CreateTextureAndBitmask(tCollisionC, sCollisionC);

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Hoot text position ;3
		text.setPosition(sprite.getPosition().x + 50, sprite.getPosition().y);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			// Makes the owl jump
			owlGravity = -0.2f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			// Moves the owl to the left
			sprite.move(-owlSpeed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			// Moves the owl to the right.
			sprite.move(owlSpeed, 0);
		}

		// Check the different collision types...
		for (int i = 0; i < ground.size(); i++)
		{
			if (Collision::PixelPerfectTest(sprite, ground[i], 0) == true /*&& Collision::PixelPerfectTest(sprite, sprite2) != true && Collision::PixelPerfectTest(sprite, sprite3) != true && Collision::PixelPerfectTest(sprite, sprite4) != true && Collision::PixelPerfectTest(sprite, sprite5) != true*/)
			{
				sprite.move(0, -0.2f);
				owlGravity = 0;
			}
			else
				owlGravity += 0.0005;
		}
		for (int i = 0; i < rWall.size(); i++)
		{
			if (Collision::PixelPerfectTest(sprite, rWall[i], 0) == true /*&& Collision::PixelPerfectTest(sprite, sprite2) != true && Collision::PixelPerfectTest(sprite, sprite3) != true && Collision::PixelPerfectTest(sprite, sprite4) != true && Collision::PixelPerfectTest(sprite, sprite5) != true*/)
			{
				sprite.move(owlSpeed, 0);
			}
		}
		for (int i = 0; i < lWall.size(); i++)
		{
			if (Collision::PixelPerfectTest(sprite, lWall[i], 0) == true /*&& Collision::PixelPerfectTest(sprite, sprite2) != true && Collision::PixelPerfectTest(sprite, sprite3) != true && Collision::PixelPerfectTest(sprite, sprite4) != true && Collision::PixelPerfectTest(sprite, sprite5) != true*/)
			{
				sprite.move(-owlSpeed, 0);
			}
		}
		for (int i = 0; i < ceiling.size(); i++)
		{
			if (Collision::PixelPerfectTest(sprite, ceiling[i], 0) == true /*&& Collision::PixelPerfectTest(sprite, sprite2) != true && Collision::PixelPerfectTest(sprite, sprite3) != true && Collision::PixelPerfectTest(sprite, sprite4) != true && Collision::PixelPerfectTest(sprite, sprite5) != true*/)
			{
				sprite.move(0, 0.2f);
			}
		}

		// The sprite can fall now ;3
		sprite.move(0, owlGravity);

		window.clear();

		// Draw stoof
		window.draw(background);
		window.draw(sprite);

		// Hoot hoot
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		window.draw(text);

		window.display();
	}

	return 0;
}