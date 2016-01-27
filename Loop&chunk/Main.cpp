#include "Chunk.h"
#include "GameObj.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 360), "SFML works!");
	sf::CircleShape shapeP(30.f);
	shapeP.setFillColor(sf::Color(100, 100, 0, 255));
	shapeP.setPosition(sf::Vector2f(120, 120));

	sf::View view(sf::FloatRect(0, 0, 640, 360));

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

	Chunk chunk10(texture1, sf::Vector2f(1920, 0), false);
	Chunk chunk11(texture2, sf::Vector2f(1920, 360), false);
	Chunk chunk12(texture3, sf::Vector2f(1920, 720), false);
	Chunk chunk13(texture7, sf::Vector2f(-640, 0), false);
	Chunk chunk14(texture8, sf::Vector2f(-640, 360), false);
	Chunk chunk15(texture9, sf::Vector2f(-640, 720), false);

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
	chunkList.push_back(chunk10);
	chunkList.push_back(chunk11);
	chunkList.push_back(chunk12);
	chunkList.push_back(chunk13);
	chunkList.push_back(chunk14);
	chunkList.push_back(chunk15);

	GameObj gameObj(chunkList[0], sf::Vector2f(400, 175), gameObjTexture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.setView(view);


		// Move camera
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			view.move(-3, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			view.move(3, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			view.move(0, 3);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			view.move(0, -3);
		}

		// Activate/deactivate chunks
		for (vector<Chunk>::size_type i = 0; i < chunkList.size(); i++)
		{
			chunkList[i].Update();

			/*if (shapeP.getPosition().x + shapeP.getRadius() + 45 >= chunkList[i].getPosition().x &&
				shapeP.getPosition().x + shapeP.getRadius() - 45 <= chunkList[i].getPosition().x + chunkList[i].getSprite().getTextureRect().width &&
				shapeP.getPosition().y + shapeP.getRadius() + 45 >= chunkList[i].getPosition().y &&
				shapeP.getPosition().y + shapeP.getRadius() - 45 <= chunkList[i].getPosition().y + chunkList[i].getSprite().getTextureRect().height)
			{*/
			if (view.getCenter().x + 330 >= chunkList[i].getPosition().x &&
				view.getCenter().x - 330 <= chunkList[i].getPosition().x + chunkList[i].getSprite().getTextureRect().width &&
				view.getCenter().y + 190 >= chunkList[i].getPosition().y &&
				view.getCenter().y - 190 <= chunkList[i].getPosition().y + chunkList[i].getSprite().getTextureRect().height)
			{
				chunkList[i].setAlive(true);
			}
			else
				chunkList[i].setAlive(false);
		}


		// World loop
		if (view.getCenter().x >= chunkList[9].getPosition().x)
		{
			view.setCenter(sf::Vector2f(1, view.getCenter().y));
		}
		if (view.getCenter().x <= chunkList[0].getPosition().x)
		{
			view.setCenter(sf::Vector2f(1919, view.getCenter().y));
		}

		// Uppdate game object
		gameObj.Update();

		window.clear();

		// Draw chunks
		for (vector<Chunk>::size_type i = 0; i < chunkList.size(); i++)
		{
			chunkList[i].Draw(window);
		}

		// Draw game objekt
		gameObj.Draw(window, chunkList[0]);

		window.draw(shapeP);

		window.display();
	}
	return 0;
}