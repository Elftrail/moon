#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<chrono>
#include"Point.h"
#include"setQuality.h"
#include"GenerationShip.h"
#include"setCoor.h"
#include"chekActivBot.h"
#include"movedShip.h"

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
	setQuality(oponent, false,sArr,sArr);
	setQuality(user, true, sArr, sArr);

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

   //breef text var of set ship
   Text strVarPos [62];
   for (int i = 0; i < 62; i++) 
   {
	   strVarPos[i].setFont(font);
	   strVarPos[i].setPosition(40+20*i, 750);
   }
   String VarPos (L"т-щ капитан! изволите сами заняться боевым порядком? да / нет");

   RectangleShape BotYas;
   BotYas.setPosition(1090, 750);
   BotYas.setSize(Vector2f::Vector2(60, 35));

   RectangleShape BotNo;
   BotNo.setPosition(1190, 750);
   BotNo.setSize(Vector2f::Vector2(80, 35));

   RectangleShape XXXX;
   XXXX.setSize(Vector2f::Vector2(200, 50));
   XXXX.setPosition(100, 750);

   


   
   Clock clok;
   float FPS=0;

   int fast_print_text=0;	//var to print var of set ship     //
   int iterVar=0;			/////////////////////////////////////

   bool PressBotVsrShip = false;

   bool isMove = false;
   bool pressR = false;

   int isMontage = 0; //0 - not used 1 - used now(step 1)  2 - used now(step 2)  3 - final montage
   bool isCorrect = true;// correct position of ship in pool
   


   int corX = 0;
   int corY = 0;

   while (window.isOpen())
   {
	   // mouse chek position
	   int my = Mouse::getPosition(window).y;
	   int mx = Mouse::getPosition(window).x;


	   sf::Event event;

	   while (window.pollEvent(event))
	   {
		   
		 if (event.type == sf::Event::Closed)
			   window.close();

		 if (event.type == Event::MouseButtonPressed)
		 {
			 if (event.key.code == Mouse::Left)
			 {
				movedShip(event,XXXX,isMove,isMontage, isCorrect,mx,my,corX,corY,pressR);
			 }
		 }
		 if (event.type == Event::MouseButtonReleased)
		 {
			 if (event.key.code == Mouse::Left)
			 {
				 movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY,pressR);
			 }
		 }
		 if (event.type == sf::Event::KeyPressed && isMontage > 0)
		 {
			 movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY,pressR);
		 }

	   }
	   
	   
	   
	   FPS+= clok.getElapsedTime().asMilliseconds();
	
	    

	   if (FPS > 16.6) //60 FPS= print in 16.6 mili sek
	   {
		   
		   window.clear(Color::Black);

		   window.draw(sFon);

		   
		   

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

		   //print bot of position ships user
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
			   if (chekActivBot(mx, my, BotYas)) {
				   strVarPos[53].setFillColor(Color::Red);
				   strVarPos[54].setFillColor(Color::Red);
			   }
			   else 
			   {
				   strVarPos[53].setFillColor(Color::White);
				   strVarPos[54].setFillColor(Color::White);
			   }
			   if (chekActivBot(mx, my, BotNo)) {
				   strVarPos[58].setFillColor(Color::Red);
				   strVarPos[59].setFillColor(Color::Red);
				   strVarPos[60].setFillColor(Color::Red);
				   if (Mouse::isButtonPressed(Mouse::Left)&&!PressBotVsrShip&&iterVar>60) 
				   {
					   PressBotVsrShip = true;
					   GenerationShip(user);
				   }
			   }
			   else
			   {
				   strVarPos[58].setFillColor(Color::White);
				   strVarPos[59].setFillColor(Color::White);
				   strVarPos[60].setFillColor(Color::White);
			   }

			   if (!PressBotVsrShip) { window.draw(strVarPos[i]); }
		   }
		   
		   if (isMove)
		   {
			   XXXX.setPosition(mx - corX, my - corY);
			   
		   }


		   window.draw(XXXX);
		  





		   window.display();

		   
		   FPS = 0;        //сброс счетчика на ноль
		   clok.restart(); //перезапук времени для счетчика
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
