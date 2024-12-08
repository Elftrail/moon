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
 
   //Bref coor pool and set
   Text numerationNUM[2];
   Text numerationLIT[10][2];
   setCoor(numerationLIT, numerationNUM, font);

   Text strVarPos [62];
   for (int i = 0; i < 62; i++) 
   {
	   strVarPos[i].setFont(font);
	   strVarPos[i].setPosition(40+20*i, 750);
   }
   String VarPos (L"т-щ капитан! изволите сами заняться боевым порядком? да / нет");

   
   Clock clok;
   float FPS=0;
   int fast_print_text=0;
   int iterVar=0;
   while (window.isOpen())
   {
	   sf::Event event;
	   while (window.pollEvent(event))
	   {
		   if (event.type == sf::Event::Closed)
			   window.close();
	   }
	   FPS+= clok.getElapsedTime().asMilliseconds();
	
	    

	   if (FPS > 16.6) 
	   {
		   
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

		   
		   cout << fast_print_text << endl;
		  
		   for (int i = 0; i < 61; i++)

		   {
			   if (fast_print_text > 900)
			   {
				   if (iterVar < 61)
				   {
					   
					   strVarPos[iterVar].setString(VarPos[iterVar]);
					   fast_print_text = 0;
					   iterVar++;
				   }

			   }
			   else { fast_print_text++;}
			   window.draw(strVarPos[i]);
		   }




		   window.display();
		   FPS = 0;
		   clok.restart();
	   }
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
