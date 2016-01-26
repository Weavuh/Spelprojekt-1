//#include <SFML/Graphics.hpp>
#include "Chunk.h"
#include "GameObj.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	sf::CircleShape shapeP(30.f);
	shapeP.setFillColor(sf::Color(100, 100, 0, 255));
	shapeP.setPosition(sf::Vector2f(120, 120));

	//sf::View view(sf::FloatRect(0, 0, 100, 100));
	//window.setView(view);

	sf::Texture texture1;
	sf::Texture texture2;
	sf::Texture texture3;
	sf::Texture texture4;
	sf::Texture texture5;
	sf::Texture texture6;
	sf::Texture texture7;
	sf::Texture texture8;
	sf::Texture texture9;
	texture1.loadFromFile("Concept001_1.jpg");
	texture2.loadFromFile("Concept001_2.jpg");
	texture3.loadFromFile("Concept001_3.jpg");
	texture4.loadFromFile("Concept001_4.jpg");
	texture5.loadFromFile("Concept001_5.jpg");
	texture6.loadFromFile("Concept001_6.jpg");
	texture7.loadFromFile("Concept001_7.jpg");
	texture8.loadFromFile("Concept001_8.jpg");
	texture9.loadFromFile("Concept001_9.jpg");

	sf::Texture gameObjTexture;
	gameObjTexture.loadFromFile("GameObj1.jpg");

	sf::RectangleShape shape(sf::Vector2f(100, 100));

	Chunk chunk1(texture1, sf::Vector2f(0, 0), false);
	Chunk chunk2(texture2, sf::Vector2f(0, 360), false);
	Chunk chunk3(texture3, sf::Vector2f(0, 720), false);
	Chunk chunk4(texture4, sf::Vector2f(640, 0), false);
	Chunk chunk5(texture5, sf::Vector2f(640, 360), false);
	Chunk chunk6(texture6, sf::Vector2f(640, 720), false);
	Chunk chunk7(texture7, sf::Vector2f(1280, 0), false);
	Chunk chunk8(texture8, sf::Vector2f(1280, 360), false);
	Chunk chunk9(texture9, sf::Vector2f(1280, 720), false);

	vector<Chunk> chunkList;
	chunkList.push_back(chunk1);
	chunkList.push_back(chunk2);
	chunkList.push_back(chunk3);
	chunkList.push_back(chunk4);
	chunkList.push_back(chunk5);
	chunkList.push_back(chunk6);
	chunkList.push_back(chunk7);
	chunkList.push_back(chunk8);
	chunkList.push_back(chunk9);

	GameObj gameObj(chunkList[0], sf::Vector2f(400, 300), gameObjTexture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			shapeP.move(-3, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			shapeP.move(3, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			shapeP.move(0, 3);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			shapeP.move(0, -3);
		}

		//view.reset(sf::FloatRect(sf::Vector2f(shapeP.getPosition().x + shapeP.getRadius(), shapeP.getPosition().y + shapeP.getRadius()), 100, 100));
		//view.setCenter(sf::Vector2f(shapeP.getPosition().x + shapeP.getRadius(), shapeP.getPosition().y + shapeP.getRadius()));
		
		//view.move(sf::Vector2f(shapeP.getPosition().x + shapeP.getRadius(), shapeP.getPosition().y + shapeP.getRadius()));

		for (vector<Chunk>::size_type i = 0; i < chunkList.size(); i++)
		{
			chunkList[i].Update();

			if (shapeP.getPosition().x + shapeP.getRadius() + 45 >= chunkList[i].getPosition().x &&
				shapeP.getPosition().x + shapeP.getRadius() - 45 <= chunkList[i].getPosition().x + chunkList[i].getSprite().getTextureRect().width &&
				shapeP.getPosition().y + shapeP.getRadius() + 45 >= chunkList[i].getPosition().y &&
				shapeP.getPosition().y + shapeP.getRadius() - 45 <= chunkList[i].getPosition().y + chunkList[i].getSprite().getTextureRect().height)
			{
				chunkList[i].setAlive(true);
			}
			else
				chunkList[i].setAlive(false);
		}

		gameObj.Update();



		window.clear();

		for (vector<Chunk>::size_type i = 0; i < chunkList.size(); i++)
		{
			chunkList[i].Draw(window);
		}

		gameObj.Draw(window, chunkList[0]);

		window.draw(shapeP);

		window.display();
	}
	return 0;
}