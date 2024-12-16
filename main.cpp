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
#include"ShipMontageProcesser.h"
#include"HodUser.h"
#include"HodOponent.h"


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

 
   

   


   
   
   int FPS = 0;														// ������� ��� ��� �������� ������������ �������

 
   int iterVar=0;													// ������� ��� �������� ������� ��� ������ ������ ������ ������� ����										

   bool Bot_AutoShip = false;										// ������� ������ ����������� �������� � ����

   bool isMove = false;												// ����������-������� ��� �������������� �������
   bool pressR = false;												// ���������� ��� ������������ R � �������� �������

   int isMontage = 0;												// �������� ������� �� ������� 
																	// 0 - ������ �� ������� 1 - ����� � �������   
																	// 2 - �������� �������� 3- �������� � �������������

   bool gorisont = true;											// ������� ��������� ������ 1 - �������������� 0 - ������������

   bool isCorrect = true;											// ���������� ��� "�� ������ ������� ��������?

   bool ShipMontage = false;										// ������� ��� �������� ������ ����������� ��������
   
   int MontageVariator = 0;											// ���������� ��� ������ ������� ��������� 0=4 1,2=3 3,4,5=2 6,7,8,9 =1 10= ������ ���������� 

   bool GameHod = true;												// ���������� ��� ����������� ����  1 = �����, 0 = ����.


   int corX = 0;													// ������������� ��������� ������ ����� ��� ����� �� �
   int corY = 0;													// ������������� ��������� ������ ����� ��� ����� �� �

   RectangleShape XXXX;												// ������ ��������� �����
   setQuality(XXXX, MontageVariator);								// �������� ������� ��������� ���������

   Clock clok;														// ������ �������
   float dalyFrame = 0;												// ������� ���������� ������� � ������� ��������� ���������� �����
   Clock kadry;
   int kad = 0;

   Clock TimeZad;
   float Zaderjka=0;

   while (window.isOpen())											// ������� ���� ����
   {
	   
	   dalyFrame = clok.getElapsedTime().asMilliseconds();			// ���������� � ������� ��������� � ������� �������� ����� 
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
					 movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY,gorisont);				// ������� ������� ��������
				 }
			 }
		 }


		 if (event.type == Event::MouseButtonReleased)				// ���� ��������� �� ������ ����
		 {
			 if (event.key.code == Mouse::Left)						// � ������ �����
			 {
				 if (ShipMontage)									// ���� ������� ������� �������� ������
				 {
					 movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY, gorisont);				// ������� ������� ��������
				 }
			 }
		 }


		 if (event.type == sf::Event::KeyPressed)					// ���� ������ �� ������ 
		 {
			 if (event.key.code == sf::Keyboard::R)					// � ������ R
			 {
				 if (isMontage > 0 && ShipMontage)					// ���� ������ ������� ������ 0 � ������� ������� �������� ������
				 {
					 movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY, gorisont);				// ������� ������� ��������
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
					 MontageVariator = 10;
				 }
			 }
			 else
			 {
				 strVarPos[58].setFillColor(Color::White);
				 strVarPos[59].setFillColor(Color::White);
				 strVarPos[60].setFillColor(Color::White);
			 }
		 }
		 for (int y = 0; y < 10; y++)								// ���� �������� ����� �� ����������
		 {
			 for (int x = 0; x < 10; x++)
			 {
				 if (!ShipMontage)
				 { 
					 user[y][x].ChekActiv(mx, my);					// ���� ������ �������� �� ���������� ��������� �������� �� ������� ���� 
				 }			
				 if (ShipMontage)									// ���� ���������� ������
				 {
					ShipMontagePocesser(user, XXXX, gorisont, ShipMontage, isCorrect, x, y, MontageVariator, isMontage, mx, my); // �������� ������� �������
				 }
				 oponent[y][x].ChekActiv(mx, my);					// ��������� �������� �� ����������� ���� 
				 
				 if(oponent[y][x].GetActivated()&&MontageVariator==10&&GameHod)			// ���� ������ ���������� �������, � ������ �������� ��������, � ��� ������
				 {
					 HodUser(oponent, event, GameHod, y, x, isMontage);					// �������� ��� ������
				 }

			 }
		 }
	   }
	   Zaderjka = TimeZad.getElapsedTime().asMilliseconds();		// ����������� �������� ��������� ����� � ������ ������� � ��					
	   if (!GameHod && MontageVariator == 10)						// ���� ��� ���������� � ������ �������� ��������
	   {
		  
		  if (Zaderjka > 1550)										// ���� ������ 	�����1550 ��						
		  {
			  Zaderjka = 0;											// �������� ��������
			  TimeZad.restart();									// �������� ������
		  }

		  if (Zaderjka > 1500)										// ���� �������� ����� 1500 ��
		  {
			  TimeZad.restart();									// �������� ������
			  HodOponent(user, event, GameHod, isMontage);			// �������� ������� ���� ����������


		  }




		  
	   }

	   
	   
	  
	
	   if (dalyFrame > 15)											// ���� ������ ����� 20� ���������� - ��������� ����� (20� = +- 60 ���)		
	   {
		   if (FPS == 60) { FPS = 0; }								// ���� ���������� 60 ������ - ��������� �������		

		   window.clear(Color::Black);								// ������� ����

		   window.draw(sFon);										// ������� ���



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

			
		   if (!Bot_AutoShip&&!ShipMontage&&MontageVariator==0)		// ��������� ������ ������ � ���� ������ ������� ��������
		   {
			   for (int i = 0; i<61; i++)							// ���� ��������� ������ ������
			   {
				   { window.draw(strVarPos[i]); }					// ��������� �������� ������� ������ ������
			   }
		   }
		   window.display();										// ���������� �� �������������
		   


		
		 


		   kad++;
		   FPS++;
		   dalyFrame = 0;											// ����� �������� 
		   clok.restart();										    // ��������� ������� ��� ��������
		  // if (kadry.getElapsedTime().asSeconds() > 1) { cout << "FPS == " << kad << endl; kadry.restart(); kad = 0; }
		
		   if (iterVar < 61&& FPS % 3>0)							// ���� ��� % 3  ������ ���� � ����� ������� ������ ������ 61
		   {
			   strVarPos[iterVar].setString(VarPos[iterVar]);		// �������� � ������ ��������� ������ �� �����������		
			   iterVar++;											// ������������� �������� �������
		   }
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
