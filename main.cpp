#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;

class Pool
{
	Sprite pool;
	int Status;
	bool activ;//chek activated poole
	bool party;//cher pool for urer or AI
	int size;//size of pool (50*50)
	Vector2f position;// position pool of window

public:
///////////////////////////////Set's//////////////////////////////
void SetStatus(int status_pool)		//0=void, 1=mis, 2=hit, 3=ship
{
	Status = status_pool;
}

void SetActivated(bool activated)	//0=NotActivated 1=Activated
{
	activ = activated;
}

void SetParty(bool activated)		//0 = opponent, 1= user
{
	activ = activated;
}

void SetSize(int Size)		//the length of the side of the square (if 50 to square = 50x50)
{
	size = Size;
}

void SetPosition(int x, int y)		//position square in window
{
	position.x = x;
	position.y = y;
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
	return activ;
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
private:
	
	void SetTextureSprite()
	{
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
		/*1*/ActivMissPool.loadFromFile("sprits/ActivMissPool.png");
		/*2*/ActivPool.loadFromFile("sprits/ActivPool.png");
		/*3*/ActivPoolBang.loadFromFile("sprits/ActivPoolBang.png");
		/*4*/ActivShipPool.loadFromFile("sprits/ActivShipPool.png");
		/*5*/InvalidShipPool.loadFromFile("sprits/InvalidShipPool.png");
		/*6*/NoActivMissPool.loadFromFile("sprits/NoActivMissPool.png");
		/*7*/NoActivPool.loadFromFile("sprits/NoActivPool.png");
		/*8*/NoActivPoolBang.loadFromFile("sprits/NoActivPoolBang.png");
		/*9*/NoActivShipPool.loadFromFile("sprits/NoActivShipPool.png");
		/*10*/ValidShipPool.loadFromFile("sprits/ValidShipPool.png");
		
		
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
		
		
		if (Status == 0 && activ==false) 
		{
			pool.setTexture(NoActivPool);
		}
		else if (Status == 1 &&activ==false)
		{
			pool.setTexture(NoActivMissPool);
		}
		else if (Status == 2 && activ == false)
		{
			pool.setTexture(NoActivPoolBang);
		}
		else if (Status == 3 && activ == false)
		{
			pool.setTexture(NoActivShipPool);
		}
		else if (Status == 3 && activ == true)
		{
			pool.setTexture(ActivShipPool);
		}
		else if (Status == 2 && activ == true)
		{
			pool.setTexture(ActivPoolBang);
		}
		else if (Status == 1 && activ == true)
		{
			pool.setTexture(ActivMissPool);
		}
		else if (Status == 0 && activ == true)
		{
			pool.setTexture(ActivPool);
		}
		else { cout << "ERROR #1 mistake sprite appointment" << endl; }


	}

};



int main()

{
	
	
	//объ€вл€ем окно//
	RenderWindow window(VideoMode(1350, 850), "looock! this is Saylor Moon!!!!");
	
	//ќбъ€вл€ем текстуры дл€ спрайтов полей//

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
   /*11*/Texture Fon;

	//ссылаем текстуры   на файл текстур//

    /*1*/ActivMissPool.loadFromFile("sprits/ActivMissPool.png");
	/*2*/ActivPool.loadFromFile("sprits/ActivPool.png");
	/*3*/ActivPoolBang.loadFromFile("sprits/ActivPoolBang.png");
	/*4*/ActivShipPool.loadFromFile("sprits/ActivShipPool.png");
	/*5*/InvalidShipPool.loadFromFile("sprits/InvalidShipPool.png");
	/*6*/NoActivMissPool.loadFromFile("sprits/NoActivMissPool.png");
	/*7*/NoActivPool.loadFromFile("sprits/NoActivPool.png");
	/*8*/NoActivPoolBang.loadFromFile("sprits/NoActivPoolBang.png");
	/*9*/NoActivShipPool.loadFromFile("sprits/NoActivShipPool.png");
   /*10*/ValidShipPool.loadFromFile("sprits/ValidShipPool.png");
   /*11*/Fon.loadFromFile("sprits/Fon.png");
	

	//объ€вл€ем спрайты //
   Sprite sFon;

   sFon.setTexture(Fon);
  



   
 
   

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(Color::Black);
		

		window.draw(sFon);
		int my = Mouse::getPosition(window).y;
		int mx = Mouse::getPosition(window).x;
		
		
		window.display();
	}
	return 0;
}
