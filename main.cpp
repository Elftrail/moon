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
	for (int i = 0; i < sArr; i++)
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
	setQuality(oponent, false, sArr, sArr);
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
	Text strVarPos[62];
	for (int i = 0; i < 62; i++)
	{
		strVarPos[i].setFont(font);
		strVarPos[i].setPosition(40 + 20 * i, 750);
	}
	String VarPos(L"т-щ капитан! изволите сами заняться боевым порядком? да / нет");
	String SHodOp[4];
	SHodOp[0] = {L"Ход противника 3	 " };
	SHodOp[1] = {L"Ход противника 2	 " };
	SHodOp[2] = {L"Ход противника 1	 " };
	SHodOp[3] = {L"Ход противника  " };  //0-14 - Ход противника//15-3 16-2 17-1 18-" "19-20 YX

	String MorBo(L"морской бой");
	String fail(L"Поражение");
	String Win(L"Победа!!!");
	
	String SBotContinue(L"Продолжить?");
	String SHodUs(L"ваш ход");

	Text MorBoy;
	MorBoy.setString(MorBo);
	MorBoy.setPosition(390, 20);
	MorBoy.setFont(font);
	MorBoy.setCharacterSize(80);

	Text  HodUs;
	HodUs.setString(SHodUs);
	HodUs.setFont(font);
	HodUs.setPosition(100, 750);

	Text  HodOp;
	HodOp.setFont(font);
	HodOp.setPosition(100, 750);
	
	Text  BotContinueText;
	BotContinueText.setFont(font);
	BotContinueText.setPosition(450, 750);
	BotContinueText.setString(SBotContinue);
	RectangleShape BotContinue;
	BotContinue.setPosition(450, 750);
	BotContinue.setSize(Vector2f::Vector2(100, 35));



	RectangleShape BotYas;
	BotYas.setPosition(1090, 750);
	BotYas.setSize(Vector2f::Vector2(60, 35));

	RectangleShape BotNo;
	BotNo.setPosition(1190, 750);
	BotNo.setSize(Vector2f::Vector2(80, 35));






	int Animation = 0;

	int PrevBangOp[4]{ -1, -1, -1, -1 };							// координаты предыдущего выстрела У Х Попадание Затопление  
	int PrevBangUs[4]{ -1, -1, -1, -1 };							// координаты предыдущего выстрела РЕЗЕРВ РЕЗЕРВ Попадание Затопление  
	int FPS = 0;													// Счетчик ФПС для привязки динамических событий


	int iterVar = 0;												// Счетчик для перебора массива при выводе живого текста первого меню										

	bool Bot_AutoShip = false;										// Вентиль кнопки автомонтажа кораблей в меню
	bool VENTBotContinue = true;									// Вентиль кнопки продолжить

	bool isMove = false;											// Переменная-вентиль для перетаскивания корабля
	bool pressR = false;											// Переменная для отслеживания R и поворота корабля

	int isMontage = 0;												// Движение корабля по стадиям 
																	// 0 - ничего не тронуто 1 - взяли и двигаем   
																	// 2 - пытаемся положить 3- положить и зафиксировать

	bool gorisont = true;											// Вентиль положения макета 1 - горизонтальное 0 - вертикальное

	bool isCorrect = true;											// Переменная для "Мы кладем корабль коррекно?

	bool ShipMontage = false;										// Вентиль для открытия ручной расстановки кораблей

	int MontageVariator = 0;										// Переменная для выдачи макетов установки 0=4 1,2=3 3,4,5=2 6,7,8,9 =1 10= монтаж произведен 

	bool GameHod = true;											// Переменная для определения хода  1 = игрок, 0 = комп.
	bool GameContinue=true;										// Вентиль для продолжения хода

	int corX = 0;													// Корректировка положения корабл когда его взяли по Х
	int corY = 0;													// Корректировка положения корабл когда его взяли по У

	RectangleShape XXXX;											// Задаем монтажный макет
	setQuality(XXXX, MontageVariator);								// Вызываем функцию настройки состояния

	Clock clok;														// Отсчет времени
	float dalyFrame = 0;											// Счетчик прошедшего времени с момента отрисовки последнего кадра
	Clock kadry;
	int kad = 0;

	Clock TimeAnimation;
	float ZadAnimation = 0;
	Clock TimeZad;													// Время для задержки хода противника
	float Zaderjka = 0;												// Вентиль для задержки хода противника
		
	int Global_Deadh[20];											// Массив координат начала утопленных кораблей user
	int Global_DeadhUser[20];										// Массив координат начала утопленных кораблей op
	for (int i = 0; i < 20; i++) 
	{
		Global_Deadh[i] = -1;
	}
	for (int i = 0; i < 20; i++)
	{
		Global_DeadhUser[i] = -1;
	}


	int After_Bang[9];												// Массив состояний выстрела противника
	for (int i = 0; i < 9; i++)
	{
		After_Bang[i] = -1;
	}


	while (window.isOpen())											// Главный цикл игры
	{
		if (Global_Deadh[19] != -1 && Global_DeadhUser[19] == -1)
		{
			MontageVariator = 11; // fail
		}
		if (Global_Deadh[19] == -1 && Global_DeadhUser[19] != -1)
		{
			MontageVariator = 12; // Win
		}

		dalyFrame = clok.getElapsedTime().asMilliseconds();			// Записываем в счетчик прошедшее с момента рестарта время 
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
						movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY, gorisont);				// Вызвать функцию движения
					}
				}
			}


			if (event.type == Event::MouseButtonReleased)				// Если отпустили на кнопку мыши
			{
				if (event.key.code == Mouse::Left)						// А именно левую
				{
					if (ShipMontage)									// Если вентиль монтажа кораблей открыт
					{
						movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY, gorisont);				// Вызвать функцию движения
					}
				}
			}


			if (event.type == sf::Event::KeyPressed)					// Если нажали на кнопку 
			{
				if (event.key.code == sf::Keyboard::R)					// А именно R
				{
					if (isMontage > 0 && ShipMontage)					// Если стадия монтажа больше 0 и вентиль монтажа кораблей открыт
					{
						movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY, gorisont);				// Вызвать функцию движения
					}
				}
			}

			if (!GameHod && MontageVariator == 10)
			{
				if (chekActivBot(mx, my, BotContinue))
				{
					BotContinueText.setFillColor(Color::Yellow);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						// GameContinue = true;
					}

				}
				if (!chekActivBot(mx, my, BotContinue))
				{
					BotContinueText.setFillColor(Color::White);
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
			for (int y = 0; y < 10; y++)								// Цикл проверки полей на активность
			{
				for (int x = 0; x < 10; x++)
				{
					if (!ShipMontage)
					{
						user[y][x].ChekActiv(mx, my);					// Если монтаж кораблей не происходит выполняем проверку на наличие мыши 
					}
					if (ShipMontage)									// Если происходит монтаж
					{
						ShipMontagePocesser(user, XXXX, gorisont, ShipMontage, isCorrect, x, y, MontageVariator, isMontage, mx, my); // Вызываем функцию монтажа
					}
					oponent[y][x].ChekActiv(mx, my);					// Выполняем проверку на присутствие мыши 

					if (oponent[y][x].GetActivated() && MontageVariator == 10 && GameHod)			// Если клетка противника активна, и монтаж кораблей завершен, и ход игрока
					{
						HodUser(oponent, event, GameHod, y, x, isMontage,Global_DeadhUser);					// Вызываем ход игрока
					}


				}
			}
		}
		Zaderjka = TimeZad.getElapsedTime().asMilliseconds();		// Присваиваем задержке прошедшее время с начала таймера в мс					
		ZadAnimation = TimeAnimation.getElapsedTime().asMilliseconds();

	
		if (Animation == 1)
		{
			if (ZadAnimation > 2800)
			{
				ZadAnimation = 0;
				TimeAnimation.restart();
			}
			
			if (PrevBangOp[0] > -1 && PrevBangOp[0] < 10)
			{
				if (ZadAnimation > 0)
				{
					user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(true);
				}
				if (ZadAnimation > 500 && ZadAnimation < 900)
				{
					user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(false);
				}
				if (ZadAnimation > 900 && ZadAnimation < 1300)
				{
					user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(true);
				}
				if (ZadAnimation > 1300 && ZadAnimation < 1800)
				{
					user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(false);
				}
				if (ZadAnimation > 1800 && ZadAnimation < 2200)
				{
					user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(true);
				}
				if (ZadAnimation > 2200)
				{
				//	user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(false);
				//}
				//if (ZadAnimation > 2600) 
				//{
					user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(false);
					Animation = 0;
				}
			
			}
		}


		if (!GameHod && MontageVariator == 10)						// Если ход противника и монтаж кораблей завершен
		{
			if (Zaderjka > 3002)										// Если прошло 	более3050 мс						
			{
				Zaderjka = 0;											// Обнуляем задержку
				TimeZad.restart();									// Обнуляем таймер

			}
			if (Zaderjka > 3000 && Zaderjka)									// Если задержка более 3000 мс
			{
				TimeZad.restart();								// Обнуляем таймер
				Animation=HodOponent(user, event, GameHod, isMontage, Global_Deadh, After_Bang, PrevBangOp);			// Вызываем функцию хода противника
				VENTBotContinue = true;
			}

		}
		if (GameHod)
		{
			Zaderjka = 0;										// Обнуляем задержку
			TimeZad.restart();									// Обнуляем таймер}
		}
		
	  
	
	   if (dalyFrame > 15)											// Если прошло более 15 милисекунд - отрисовка кадра (15 = +- 60 ФПС)		
	   {
		   if (FPS == 60) { FPS = 0; }								// Если отрисовали 60 кадров - сбрасывам счетчик		

		   window.clear(Color::Black);								// Очищаем окно

		  // window.draw(sFon);										// Выводим фон



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


		   //=============================================================Кнопки и надписи======================================================================//
		   //print coord pools
		   for (int i = 0; i < 2; i++)
		   {
			   window.draw(numerationNUM[i]);
			   for (int j = 0; j < 10; j++)
			   {
				   window.draw(numerationLIT[j][i]);
			   }
		   }

			
		   if (!Bot_AutoShip&&!ShipMontage&&MontageVariator==0)		// Отрисовка живого текста и меню выбора монтажа кораблей
		   {
			   for (int i = 0; i<61; i++)							// Цикл отрисовки живого текста
			   {
				   { window.draw(strVarPos[i]); }					// Отрисовка символов массива живого текста
			   }
		   }
		   if (GameHod && MontageVariator == 10)					// Если ход игрока и монтаж завершен
		   {
			   window.draw(HodUs);									// Написать ваш ход
		   }
		   if (!GameHod && MontageVariator == 10)					// Если ход противника и монтаж завершен
		   {
			   if (VENTBotContinue)
			   {
				   SHodOp[3][15] = ' ';
			   }
			   if (Zaderjka < 1000)
			   {
				   SHodOp[3][15] = '3';
			   }
			   if (Zaderjka > 1000&& Zaderjka < 2000)
			   {
				   SHodOp[3][15] = '2';
			   }
			   if (Zaderjka > 2000 && Zaderjka < 3000)
			   {
				   SHodOp[3][15] = '1';
			   }
			   
			   HodOp.setString(SHodOp[3]);

			  
			   window.draw(HodOp);									// Написать строку с учетом состояния хода
		   }


		   if(MontageVariator<11){ window.draw(MorBoy); }
		   if (MontageVariator == 11) { MorBoy.setString(fail); MorBoy.setPosition(490,20); window.draw(MorBoy); }
		   if (MontageVariator == 12) { MorBoy.setString(Win); MorBoy.setPosition(470, 20); window.draw(MorBoy); }
		   
		



		 
		  
		   
		   
		   
		   
		   
		   
		   window.display();										// Отрисовать всё вышеописанное
		   


		
		 


		   kad++;
		   FPS++;
		   dalyFrame = 0;											// Сброс счетчика 
		   clok.restart();										    // Перезапук времени для счетчика
		   if (kadry.getElapsedTime().asSeconds() > 1) { cout << "FPS == " << kad << endl; kadry.restart(); kad = 0; }
		
		   if (iterVar < 61&& FPS % 3>0)							// Если ФПС % 3  больше нуля И номер символа строки меньше 61
		   {
			   strVarPos[iterVar].setString(VarPos[iterVar]);		// Добавить в массив следующий символ из добовляемых		
			   iterVar++;											// Инкремировать итератор символа
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
