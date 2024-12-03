#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;



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
   Sprite poolpro[10][10];
   Sprite poolus[10][10];
   Sprite sFon;

   sFon.setTexture(Fon);


   for (int y = 0; y < 10; y++)
   {
	   for (int x = 0; x < 10; x++)
	   {
		   poolpro[y][x].setPosition(100 + (x * 50), 200 + (y * 50));
		   poolpro[y][x].setTexture(NoActivPool);


	   }
   }
  
   for (int y = 0; y < 10; y++)
   {
	   for (int x = 0; x < 10; x++)
	   {
		   poolus[y][x].setPosition(800 + (x * 50), 200 + (y * 50));
		   poolus[y][x].setTexture(NoActivPool);


	   }
   }
 
   

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
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++) 
			{
				if ((mx > 100 + (50 * x)) && (mx < 150 + 50 * x))
				{
					if ((my > 200 + (y * 50)) && (my < 250 + (y * 50))) 
					{
						poolpro[y][x].setTexture(ActivPool);

					}
					else
					{
						poolpro[y][x].setTexture(NoActivPool);
					}
				}
				else
				{
					poolpro[y][x].setTexture(NoActivPool);
				}
				
				
				window.draw(poolpro[x][y]);
				


				window.draw(poolus[x][y]);
			}
		}
		window.display();
	}

	return 0;
}
