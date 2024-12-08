
#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
using namespace std;
using namespace sf;


class Pool
{
	Sprite pool;
	int Status;
	bool activ = false;//chek activated poole
	bool part;//cher pool for urer or AI
	int size = 50;//size of pool (50*50)
	Vector2f position;// position pool of window
	//RectangleShape pool;//sqare of pool

	/*1*/Texture ActivMissPool;
	/*2*/Texture ActivPool;
	/*3*/Texture ActivPoolBang;
	/*4*/Texture ActivShipPool;
	/*5*/Texture InvalidShipPool;
	/*6*/Texture NoActivMissPool;
	/*7*/Texture NoActivPool;
	/*8*/Texture NoActivPoolBang;
	/*9*/Texture NoActivShipPool;
	/*10*/Texture ValidShipPool;





public:
	//Chek Activity from Mouse (mouse x, mouse,y)

	void ChekActiv(int mx, int my)
	{
		if (mx > position.x && mx<(position.x + size) && my > position.y && my < (position.y + size))
		{

			activ = true;


		}
		else { activ = false; }
		SetTextureSprite();
	}



	///////////////////////////////Set's//////////////////////////////

	//0=void, 1=mis, 2=hit, 3=ship
	void SetStatus(int status_pool)
	{

		Status = status_pool;
		SetTextureSprite();
	}

	//0=NotActivated 1=Activated
	void SetActivated(bool activated)
	{
		activ = activated;
	}


	/*0 = opponent, 1= user*/
	void SetParty(bool party)
	{
		part = party;
	}

	/*void SetSize(int Size)		//the length of the side of the square (if 50 to square = 50x50)
	{
		size = Size;
		Vector2f S(size, size);



	}
	*/
	void SetPosition(int x, int y)		//position square in window
	{
		position.x = x;
		position.y = y;
		pool.setPosition(position);
	}
	////////////////////////////////Get's//////////////////////////////

	int GetStatus()
	{
		return Status;
	}
	bool GetActivated()
	{
		return activ;
	}
	bool GetParty()
	{
		return part;
	}

	int GetSize()
	{
		return size;
	}

	int GetPositionX()
	{
		return position.x;
	}
	int GetPositionY()
	{
		return position.y;
	}
	Sprite GetSprite()
	{
		return pool;
	}
	//init class//
	void GetPool()
	{
		
	}
private:

	void SetTextureSprite()
	{



		////////////////////////////////////////////////////////////////
		//pool statuses:
		//	0 void pool
		//	1 poole is mis  
		//  2 poole is hit
		//  3 poole is ship
		// pool active:
		//	0 Not Aktivated
		//	1 Activated
		// 
		////////////////////////////////////////////////////////////////

		/*1*///ActivMissPool.loadFromFile("sprits/ActivMissPool.png");
		/*2*///ActivPool.loadFromFile("sprits/ActivPool.png");
		/*3*///ActivPoolBang.loadFromFile("sprits/ActivPoolBang.png");
		/*4*///ActivShipPool.loadFromFile("sprits/ActivShipPool.png");
				/*5*///InvalidShipPool.loadFromFile("sprits/InvalidShipPool.png");
		/*6*///NoActivMissPool.loadFromFile("sprits/NoActivMissPool.png");
		/*7*///NoActivPool.loadFromFile("sprits/NoActivPool.png");
		/*8*///NoActivPoolBang.loadFromFile("sprits/NoActivPoolBang.png");
		/*9*///NoActivShipPool.loadFromFile("sprits/NoActivShipPool.png");
				/*10*///ValidShipPool.loadFromFile("sprits/ValidShipPool.png");
		if (Status == 0 && activ == false)
		{
			NoActivPool.loadFromFile("sprits/NoActivPool.png");
			pool.setTexture(NoActivPool);
		}
		else if (Status == 1 && activ == false)
		{
			NoActivMissPool.loadFromFile("sprits/NoActivMissPool.png");
			pool.setTexture(NoActivMissPool);
		}
		else if (Status == 2 && activ == false)
		{
			NoActivPoolBang.loadFromFile("sprits/NoActivPoolBang.png");
			pool.setTexture(NoActivPoolBang);
		}
		else if (Status == 3 && activ == false)
		{
			NoActivShipPool.loadFromFile("sprits/NoActivShipPool.png");
			pool.setTexture(NoActivShipPool);
		}
		else if (Status == 3 && activ == true)
		{
			ActivShipPool.loadFromFile("sprits/ActivShipPool.png");
			pool.setTexture(ActivShipPool);
		}
		else if (Status == 2 && activ == true)
		{
			ActivPoolBang.loadFromFile("sprits/ActivPoolBang.png");
			pool.setTexture(ActivPoolBang);
		}
		else if (Status == 1 && activ == true)
		{
			ActivMissPool.loadFromFile("sprits/ActivMissPool.png");
			pool.setTexture(ActivMissPool);
		}
		else if (Status == 0 && activ == true)
		{
			ActivPool.loadFromFile("sprits/ActivPool.png");
			pool.setTexture(ActivPool);
		}
		else { cout << "ERROR #1 mistake sprite appointment" << endl; }


	}

};