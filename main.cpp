#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<chrono>
#include"Point.h"
#include"setQuality.h"
#include"GenerationShip.h"
#include"setCoor.h"

using namespace std;
using namespace sf;





int main()

{	//declaration and initialization size arr oponent and user//

	const int sArr = 10;//size arr pools (const=10)
	
	//declaration and initialization dynamic arr oponent//
	
	Point** oponent = { new Point * [sArr] {} };
	for (int  i = 0; i < sArr; i++)
	{
		oponent[i] = new Point[sArr]{};
	}

	//declaration poole from user//
	Point** user = { new Point * [sArr] {} };
	for (int i = 0; i < sArr; i++)
	{
		user[i] = new Point[sArr]{};
	}

	//Quality setting to an pools user and oponent//
	setQuality(oponent, false);
	setQuality(user, true);

	//generation ships oponent
	GenerationShip(oponent);

	//Declaration Window//
	RenderWindow window(VideoMode(1350, 850), "looock! this is Saylor Moon!!!!");

	//Declaration and initialization back space image//
   Texture Fon;
   Sprite sFon;
   Fon.loadFromFile("sprits/Fon.png");
   sFon.setTexture(Fon);
  
   //Declaration Fonts//
   Font font;
   font.loadFromFile("Text.ttf");
 
   Text numerationNUM[2];
   Text numerationLIT[10][2];
  
   setCoor(numerationLIT, numerationNUM, font);
   /*numerationNUM[0].setString(L" 1 2 3 4 5 6 7 8 9 10");
   numerationNUM[1].setString(L" 1 2 3 4 5 6 7 8 9 10");
   numerationNUM[0].setPosition(100, 140);
   numerationNUM[1].setPosition(750, 140);
   numerationNUM[0].setFont(font);
   numerationNUM[1].setFont(font);
   numerationNUM[0].setCharacterSize(50);
   numerationNUM[1].setCharacterSize(50);

   String literals_for_num(L"ÀÁÂÃÄÅÆÇÈÊ");
   for (int i = 0; i < 10; i++)
   {
	   for (int j = 0; j < 2; j++) 
	   {
		   numerationLIT[i][j].setString(literals_for_num[i]);
		   numerationLIT[i][j].setFont(font);
		   numerationLIT[i][j].setCharacterSize(50);
		   if (j == 0)
		   {
			   numerationLIT[i][j].setPosition(45, 190 + i * 50);
		   }
		   if (j == 1)
		   {
			   numerationLIT[i][j].setPosition(695, 190 + i * 50);
		   }
	   }
   }*/
   
   



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

		// mouse chek position
		int my = Mouse::getPosition(window).y;
		int mx = Mouse::getPosition(window).x;
		
		
		//print poole oponent and user
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				user[y][x].ChekActiv(mx, my);
				window.draw(user[y][x].GetSprite());
				oponent[y][x].ChekActiv(mx, my);
				window.draw(oponent[y][x].GetSprite());
			}
		}

		//print coord pools
		for (int i = 0; i < 2; i++)
		{
			window.draw(numerationNUM[i]);
			for (int j = 0; j < 10; j++) 
			{
				window.draw(numerationLIT[j][i]);
			}
		}
		

		window.display();
	}

	


	
	




	for (int i = 0; i < sArr; i++)
	{
		delete[] oponent[i];
		delete[] user[i];
	}
	delete[] oponent;
	delete[] user;

	return 0;
}
