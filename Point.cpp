#include "Point.h"

sf::Sprite pool;

int Status;
bool activ;
//0- опонент 1-игрок
bool part; 
int size = 50;
sf::Vector2f position;
bool IsCorrect = true;
bool Animation= false;

sf::Texture ActivMissPool;
sf::Texture ActivMissPoolAnimation;
sf::Texture ActivPool;
sf::Texture NoCorrectActivPool;
sf::Texture ActivPoolBang;
sf::Texture ActivPoolBangAnimation;
sf::Texture ActivShipPool;
sf::Texture NoCorrectActivShipPool;
sf::Texture InvalidShipPool;
sf::Texture NoActivMissPool;
sf::Texture NoActivMissPoolAnimation;
sf::Texture NoActivPool;
sf::Texture NoActivPoolBang;
sf::Texture NoActivPoolBangAnimation;
sf::Texture NoActivShipPool;
sf::Texture ValidShipPool;


void Point::ChekActiv(int mx, int my)
{
	if ((mx > position.x|| mx == position.x) && mx<(position.x + size) &&( my > position.y || my == position.y )&& my < (position.y + size))
	{
		activ = true;
	}
	else { activ = false; }
	SetTextureSprite();
}
void Point::SetStatus(int status_pool)
{

	Status = status_pool;
	SetTextureSprite();
}

void  Point::SetAnimation(bool Anim) 
{
	Animation = Anim;
	
		SetTextureSprite();

}

void Point::SetActivated(bool activated)
{
	activ = activated;
	SetTextureSprite();
	IsCorrect = true;
}
void Point::SetActivated(bool activated,bool isCorrect)
{
	activ = activated;
	IsCorrect = isCorrect;
	SetTextureSprite();
}



void Point::SetParty(bool party)
{
	part = party;
}

void Point::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
	pool.setPosition(position);
}



void Point::LoadTexture()
{
	
		ActivMissPool.loadFromFile("sprits/ActivMissPool.png");
		ActivPool.loadFromFile("sprits/ActivPool.png");
		NoCorrectActivPool.loadFromFile("sprits/NoCorrectActivPool.png");
		ActivPoolBang.loadFromFile("sprits/ActivPoolBang.png");
		ActivShipPool.loadFromFile("sprits/ActivShipPool.png");
		NoCorrectActivShipPool.loadFromFile("sprits/NoCorrectActivShipPool.png");
		NoActivPool.loadFromFile("sprits/NoActivPool.png");
		NoActivMissPool.loadFromFile("sprits/NoActivMissPool.png");
		NoActivPoolBang.loadFromFile("sprits/NoActivPoolBang.png");
		NoActivShipPool.loadFromFile("sprits/NoActivShipPool.png");

		ActivMissPoolAnimation.loadFromFile("sprits/ActivMissPoolAnimation.png");
		ActivPoolBangAnimation.loadFromFile("sprits/ActivPoolBangAnimation.png");
		NoActivMissPoolAnimation.loadFromFile("sprits/NoActivMissPoolAnimation.png");
		NoActivPoolBangAnimation.loadFromFile("sprits/NoActivPoolBangAnimation.png");
}

int Point::GetStatus()
{
	return Status;
}

bool Point::GetActivated()
{
	return activ;
}

bool Point::GetParty()
{
	return part;
}

int Point::GetSize()
{
	return size;
}

int Point::GetPositionX()
{
	return position.x;
}

int Point::GetPositionY()
{
	return position.y;
}

sf::Sprite Point::GetSprite()
{
	return pool;
}




void Point::SetTextureSprite()
{
	if (Status == 0 && activ == false)
	{
		
		pool.setTexture(NoActivPool);
	}
	else if (Status == 1 && activ == false)
	{
		if (!Animation){pool.setTexture(NoActivMissPool);}
		if (Animation) {pool.setTexture(NoActivMissPoolAnimation);}
	}
	else if (Status == 2 && activ == false)
	{
		
		if (!Animation) {pool.setTexture(NoActivPoolBang);}
		if (Animation) { pool.setTexture(NoActivPoolBangAnimation); }
	}
	else if (Status == 3 && activ == false&&part)
	{
		
		pool.setTexture(NoActivShipPool);
	}
	else if (Status == 3 && activ == false && !part)
	{

		pool.setTexture(NoActivPool);
	}
	else if (Status == 3 && activ == true && part)
	{
		
		pool.setTexture(ActivShipPool);
		if (!IsCorrect)
		{
			pool.setTexture(NoCorrectActivShipPool);
		}
	}
	else if (Status == 3 && activ == true && !part)
	{

		pool.setTexture(ActivPool);
		
	}
	else if (Status == 2 && activ == true)
	{
		
		if (!Animation) { pool.setTexture(ActivPoolBang); }
		if (Animation) { pool.setTexture(ActivPoolBangAnimation); }
	}
	else if (Status == 1 && activ == true)
	{
		
		if (!Animation) { pool.setTexture(ActivMissPool); }
		if (Animation) { pool.setTexture(ActivMissPoolAnimation); }
	}
	else if (Status == 0 && activ == true)
	{
		
		pool.setTexture(ActivPool);
		if (!IsCorrect) 
		{
			pool.setTexture(NoCorrectActivPool);
		}
	}
	//else { std::cout << "ERROR #1 mistake sprite appointment" << std::endl; }
}
