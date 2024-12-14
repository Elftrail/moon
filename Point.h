#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class Point
{
	sf::Sprite pool;
	int Status;
	bool activ = false;
	bool part;
	int size = 50;
	sf::Vector2f position;

	sf::Texture ActivMissPool;
	sf::Texture ActivPool;
	sf::Texture ActivPoolBang;
	sf::Texture ActivShipPool;
	sf::Texture InvalidShipPool;
	sf::Texture NoActivMissPool;
	sf::Texture NoActivPool;
	sf::Texture NoActivPoolBang;
	sf::Texture NoActivShipPool;
	sf::Texture ValidShipPool;

public:
	//Chek Activity from Mouse (mouse x, mouse,y)
	void ChekActiv(int mx, int my);

	//0=void, 1=mis, 2=hit, 3=ship
	void SetStatus(int status_pool);

	//0=NotActivated 1=Activated
	void SetActivated(bool activated);
	void SetActivated(bool activated, bool isCorrect);
	

	/*0 = opponent, 1= user*/
	void SetParty(bool party);

	//position square in window
	void SetPosition(int x, int y);

	//set defaut texture

	void LoadTexture();


	int GetStatus();
	bool GetActivated();	
	bool GetParty();
	int GetSize();
	int GetPositionX();	
	int GetPositionY();	
	sf::Sprite GetSprite();
private:
	void SetTextureSprite();
};

