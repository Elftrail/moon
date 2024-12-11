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
   

   


   
   Clock clok;														// Отсчет времени
   float dalyFrame=0;												// Счетчик прошедшего времени с момента отрисовки последнего кадра
   int FPS = 0;														// Счетчик ФПС для привязки динамических событий

 
   int iterVar=0;													// Счетчик для перебора массива при выводе живого текста первого меню										

   bool Bot_AutoShip = false;										// Вентиль кнопки автомонтажа кораблей в меню

   bool isMove = false;												// Переменная-вентиль для перетаскивания корабля
   bool pressR = false;												// Переменная для отслеживания R и поворота корабля

   int isMontage = 0;												// Движение корабля по стадиям 
																	// 0 - ничего не тронуто 1 - взяли и двигаем   
																	// 2 - пытаемся положить 3- положиль и зафиксировали
   bool isCorrect = true;											// Переменная для "Мы кладем корабль коррекно?

   bool ShipMontage = false;										//Вентиль для открытия ручной расстановки кораблей
   


   int corX = 0;													// Корректировка положения корабл когда его взяли по Х
   int corY = 0;													// Корректировка положения корабл когда его взяли по У

  

   while (window.isOpen())											// Главный цикл игры
   {
	   
	   dalyFrame += clok.getElapsedTime().asMilliseconds();			// Записываем в счетчик прошедшее с момента рестарта время 
	   int my = Mouse::getPosition(window).y;						// Получаем положение мыши У
	   int mx = Mouse::getPosition(window).x;						// Получаем положение мыши Х


	   sf::Event event;

	   while (window.pollEvent(event))								// Цикл обработки событий
	   {
		   
		 if (event.type == sf::Event::Closed)						// Событие нажатия на крестик окна
			   window.close();										// Закрываем окно


		 if (event.type == Event::MouseButtonPressed)				// Если нажали на кнопку мыши
		 {
			 if (event.key.code == Mouse::Left)						// А именно левую
			 {
				 if (ShipMontage)									// Если вентиль монтажа кораблей открыт
				 {
					 movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY);				// Вызвать функцию движения
				 }
			 }
		 }


		 if (event.type == Event::MouseButtonReleased)				// Если отпустили на кнопку мыши
		 {
			 if (event.key.code == Mouse::Left)						// А именно левую
			 {
				 if (ShipMontage)									// Если вентиль монтажа кораблей открыт
				 {
					 movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY);				// Вызвать функцию движения
				 }
			 }
		 }


		 if (event.type == sf::Event::KeyPressed)					// Если нажали на кнопку 
		 {
			 if (event.key.code == sf::Keyboard::R)					// А именно R
			 {
				 if (isMontage > 0 && ShipMontage)					// Если стадия монтажа больше 0 и вентиль монтажа кораблей открыт
				 {
					 movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY);				// Вызвать функцию движения
				 }
			 }
		 }

		
		 for (int i = 0; i < 61; i++)								// Цицл установки знач. отр. живого текста первого меню

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

			 if (FPS % 3 > 0 && iterVar < 61)						// Если ФПС % 3  больше нуля И номер символа строки меньше 61
			 {
				 strVarPos[iterVar].setString(VarPos[iterVar]);		// Добавить в массив следующий символ из добовляемых
				 iterVar++;											// Инкремировать итератор символа
			 }
		 }

		 int iter = 0;
		 for (int y = 0; y < 10; y++)								// Цикл проверки полей на активность
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

	   
	   
	
	
	   if (dalyFrame > 20000)										// Если прошло более 20к милисекунд - отрисовка кадра (20к = +- 60 ФПС)		
	   {
		   if (FPS == 60) { FPS = 0; }								// Если отрисовали 60 кадров - сбрасывам счетчик		

		   window.clear(Color::Black);

		   window.draw(sFon);



		   if (isMove)												// Если можно двигать
		   {
			   XXXX.setPosition(mx - corX, my - corY);				// То присваиваем спрайту позицию в зависимости от положения мыши
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

			
		   if (!Bot_AutoShip&&!ShipMontage)							// Отрисовка живого текста и меню выбора монтажа кораблей
		   {
			   for (int i = 0; i<61; i++)							// Цикл отрисовки живого текста
			   {
				   { window.draw(strVarPos[i]); }					// Отрисовка символов массива живого текста
			   }
		   }

		   if (ShipMontage) {window.draw(XXXX);}					// Если идет монтаж кораблей отрисовать монтажный макет

		   window.display();										// Отрисовать всё вышеописанное



		
		 



		   FPS++;
		   dalyFrame = 0;											// Сброс счетчика 
		   clok.restart();										    // Перезапук времени для счетчика


	 
		   
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
