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

{	
	setlocale(LC_ALL, "rus");
	//declaration and initialization size arr oponent and user//

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
   String VarPos (L"�-� �������! �������� ���� �������� ������ ��������? �� / ���");

   RectangleShape BotYas;
   BotYas.setPosition(1090, 750);
   BotYas.setSize(Vector2f::Vector2(60, 35));

   RectangleShape BotNo;
   BotNo.setPosition(1190, 750);
   BotNo.setSize(Vector2f::Vector2(80, 35));

   RectangleShape XXXX;
   XXXX.setSize(Vector2f::Vector2(200, 50));
   XXXX.setPosition(100, 750);
   

   


   
   Clock clok;														// ������ �������
   float dalyFrame=0;												// ������� ���������� ������� � ������� ��������� ���������� �����
   int FPS = 0;														// ������� ��� ��� �������� ������������ �������

 
   int iterVar=0;													// ������� ��� �������� ������� ��� ������ ������ ������ ������� ����										

   bool Bot_AutoShip = false;										// ������� ������ ����������� �������� � ����

   bool isMove = false;												// ����������-������� ��� �������������� �������
   bool pressR = false;												// ���������� ��� ������������ R � �������� �������

   int isMontage = 0;												// �������� ������� �� ������� 
																	// 0 - ������ �� ������� 1 - ����� � �������   
																	// 2 - �������� �������� 3- �������� � �������������
   bool isCorrect = true;											// ���������� ��� "�� ������ ������� ��������?

   bool ShipMontage = false;										//������� ��� �������� ������ ����������� ��������
   


   int corX = 0;													// ������������� ��������� ������ ����� ��� ����� �� �
   int corY = 0;													// ������������� ��������� ������ ����� ��� ����� �� �

  

   while (window.isOpen())											// ������� ���� ����
   {
	   
	   dalyFrame += clok.getElapsedTime().asMilliseconds();			// ���������� � ������� ��������� � ������� �������� ����� 
	   int my = Mouse::getPosition(window).y;						// �������� ��������� ���� �
	   int mx = Mouse::getPosition(window).x;						// �������� ��������� ���� �


	   sf::Event event;

	   while (window.pollEvent(event))								// ���� ��������� �������
	   {
		   
		 if (event.type == sf::Event::Closed)						// ������� ������� �� ������� ����
			   window.close();										// ��������� ����


		 if (event.type == Event::MouseButtonPressed)				// ���� ������ �� ������ ����
		 {
			 if (event.key.code == Mouse::Left)						// � ������ �����
			 {
				 if (ShipMontage)									// ���� ������� ������� �������� ������
				 {
					 movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY);				// ������� ������� ��������
				 }
			 }
		 }


		 if (event.type == Event::MouseButtonReleased)				// ���� ��������� �� ������ ����
		 {
			 if (event.key.code == Mouse::Left)						// � ������ �����
			 {
				 if (ShipMontage)									// ���� ������� ������� �������� ������
				 {
					 movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY);				// ������� ������� ��������
				 }
			 }
		 }


		 if (event.type == sf::Event::KeyPressed)					// ���� ������ �� ������ 
		 {
			 if (event.key.code == sf::Keyboard::R)					// � ������ R
			 {
				 if (isMontage > 0 && ShipMontage)					// ���� ������ ������� ������ 0 � ������� ������� �������� ������
				 {
					 movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY);				// ������� ������� ��������
				 }
			 }
		 }

		
		 for (int i = 0; i < 61; i++)								// ���� ��������� ����. ���. ������ ������ ������� ����

		 {

			 if (chekActivBot(mx, my, BotYas))
			 {
				 strVarPos[53].setFillColor(Color::Red);
				 strVarPos[54].setFillColor(Color::Red);
				 if (Mouse::isButtonPressed(Mouse::Left) && !ShipMontage && iterVar > 60)
				 {
					 ShipMontage = true;
				 }
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
				 if (Mouse::isButtonPressed(Mouse::Left) && !Bot_AutoShip && iterVar > 60)
				 {
					 Bot_AutoShip = true;
					 GenerationShip(user);
				 }

			 }
			 else
			 {
				 strVarPos[58].setFillColor(Color::White);
				 strVarPos[59].setFillColor(Color::White);
				 strVarPos[60].setFillColor(Color::White);
			 }

			 if (FPS % 3 > 0 && iterVar < 61)						// ���� ��� % 3  ������ ���� � ����� ������� ������ ������ 61
			 {
				 strVarPos[iterVar].setString(VarPos[iterVar]);		// �������� � ������ ��������� ������ �� �����������
				 iterVar++;											// ������������� �������� �������
			 }
		 }

		 int iter = 0;
		 for (int y = 0; y < 10; y++)								// ���� �������� ����� �� ����������
		 {
			 for (int x = 0; x < 10; x++)
			 {
				 if (!ShipMontage) { user[y][x].ChekActiv(mx, my); }
				
				 oponent[y][x].ChekActiv(mx, my);
				 
				 if (ShipMontage)
				 {
					user[y][x].ChekActiv(XXXX.getPosition().x-30+XXXX.getSize().x, XXXX.getPosition().y + XXXX.getSize().y / 2);
					if(user[y][x].GetActivated()&&(x-3)>-1)
					{
						user[y][x - 1].SetActivated(true);
						user[y][x - 2].SetActivated(true);
						user[y][x - 3].SetActivated(true);
						
						
					}
					if (isMontage == 3)
					{
						for (int y = 0; y < 10; y++)
						{
							for (int x = 0; x < 10; x++)
							{
								if(user[y][x].GetActivated())
								{
									user[y][x].SetStatus(3);
								}
							}
						}
					}
				 }
			 }
		 }
		


	   }

	   
	   
	
	
	   if (dalyFrame > 20000)										// ���� ������ ����� 20� ���������� - ��������� ����� (20� = +- 60 ���)		
	   {
		   if (FPS == 60) { FPS = 0; }								// ���� ���������� 60 ������ - ��������� �������		

		   window.clear(Color::Black);

		   window.draw(sFon);



		   if (isMove)												// ���� ����� �������
		   {
			   XXXX.setPosition(mx - corX, my - corY);				// �� ����������� ������� ������� � ����������� �� ��������� ����
		   }

		   //print poole oponent and user
		   for (int y = 0; y < 10; y++)
		   {
			   for (int x = 0; x < 10; x++)
			   {
				   window.draw(user[y][x].GetSprite());
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

			
		   if (!Bot_AutoShip&&!ShipMontage)							// ��������� ������ ������ � ���� ������ ������� ��������
		   {
			   for (int i = 0; i<61; i++)							// ���� ��������� ������ ������
			   {
				   { window.draw(strVarPos[i]); }					// ��������� �������� ������� ������ ������
			   }
		   }

		   if (ShipMontage) {window.draw(XXXX);}					// ���� ���� ������ �������� ���������� ��������� �����

		   window.display();										// ���������� �� �������������



		
		 



		   FPS++;
		   dalyFrame = 0;											// ����� �������� 
		   clok.restart();										    // ��������� ������� ��� ��������


	 
		   
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
