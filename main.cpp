#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<ctime>
#include<chrono>
#include"Point.h"
#include"setQuality.h"
#include"GenerationShip.h"
#include"setCoor.h"
#include"chekActivBot.h"
#include"movedShip.h"
#include"HodUser.h"
#include"HodOponent.h"
#include"MontageShip_2.h"
#include"AnimatetdText.h"
#include"OverRestart.h"

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
	RenderWindow window(VideoMode(1350, 850), "There should have been a Sailor Moon here...");

	//Declaration and initialization back space image//
	Texture Fon;
	Sprite sFon;
	Fon.loadFromFile("sprits/Fon.png");
	sFon.setTexture(Fon);

	//Declaration Fonts//
	Font font;
	font.loadFromFile("Text.ttf");

	String VarPos(L"Ваше поле справа. расставить корабли автоматически? да / нет");
	String SHodOp(L"Ход противника");
	String MorBo(L"морской бой");
	String fail(L"Поражение");
	String Win(L"Победа!!!");
	String SBotRestartText(L"сиграть снова");
	String SBotExitText(L" выйти из игры");
	String SHodUs(L"ваш ход");
	String SMontageText(L"разместите ваши корабли. лкм - установить корабль к - повернуть корабль");

	Text MontageText;
	MontageText.setString(SMontageText);
	MontageText.setPosition(40, 750);
	MontageText.setFont(font);

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
	HodOp.setString(SHodOp);
	
	Text  BotRestartText;
	BotRestartText.setCharacterSize(50);
	BotRestartText.setFont(font);
	BotRestartText.setPosition(270, 750);
	BotRestartText.setString(SBotRestartText);

	Text  BotExitText;
	BotExitText.setCharacterSize(50);
	BotExitText.setFont(font);
	BotExitText.setPosition(720, 750);
	BotExitText.setString(SBotExitText);
	
	Text strVarPos[62];
	for (int i = 0; i < 62; i++)
	{
		strVarPos[i].setFont(font);
		strVarPos[i].setPosition(40 + 20 * i, 750);
	}

	Text numerationNUM[2];
	Text numerationLIT[10][2];
	setCoor(numerationLIT, numerationNUM, font);
	
	
	RectangleShape BotRestart;
	BotRestart.setPosition(268, 750);
	BotRestart.setSize(Vector2f::Vector2(450, 55));

	RectangleShape BotExit;
	BotExit.setPosition(718, 750);
	BotExit.setSize(Vector2f::Vector2(450, 55));



	RectangleShape BotYas;
	BotYas.setPosition(1070, 750);
	BotYas.setSize(Vector2f::Vector2(60, 35));

	RectangleShape BotNo;
	BotNo.setPosition(1170, 750);
	BotNo.setSize(Vector2f::Vector2(80, 35));

	SoundBuffer S_BUFFER[7];
	for (int i = 0; i < 7; i++) 
	{
		switch (i)
		{
		case 0:
			S_BUFFER[i].loadFromFile("sound/Activ.mp3 ");
			break;
		case 1:
			S_BUFFER[i].loadFromFile("sound/BotonPress.mp3 ");
			break;
		case 2:
				S_BUFFER[i].loadFromFile("sound/Fail.mp3 ");
				break; 
		case 3:
					S_BUFFER[i].loadFromFile("sound/Hit.mp3 ");
					break; 
		case 4:
						S_BUFFER[i].loadFromFile("sound/Mis.mp3 ");
						break; 
		case 5:
							S_BUFFER[i].loadFromFile("sound/shipDeadh.mp3 ");
							break; 
		case 6:
		S_BUFFER[i].loadFromFile("sound/Win.mp3 ");
								break;

		default:
			break;
		}
	}
	Sound SOUND[7];
	for (int i = 0; i < 7; i++)
	{
	SOUND[i].setBuffer(S_BUFFER[i]);
	}
	SOUND[4].setVolume(30);



	int Animation = 0;

	int PrevBangAnimation[2]{ -1, -1 };								// координаты предыдущего выстрела У Х Попадание Затопление  
	int FPS = 0;													// Счетчик ФПС для привязки динамических событий


	int iterVar = 0;												// Счетчик для перебора массива при выводе живого текста первого меню										

	bool Bot_AutoShip = false;										// Вентиль кнопки автомонтажа кораблей в меню
	bool VENTBotContinue = true;									// Вентиль кнопки продолжить

	bool isMove = false;											// Переменная-вентиль для перетаскивания корабля
	bool pressR = false;											// Переменная для отслеживания R и поворота корабля

	int StadyMontage = -1;											// Движение корабля по стадиям 
																	//-1 функция не активна 0 - корабль бегает  за мышкой 1 - корабль можно положить  2 - корабль кладем
																	

	bool gorisont = true;											// Вентиль положения макета 1 - горизонтальное 0 - вертикальное

	bool isCorrect = true;											// Переменная для "Мы кладем корабль коррекно?

	bool ShipMontage = false;										// Вентиль для открытия ручной расстановки кораблей

	int MontageVariator = 0;										// Переменная для выдачи макетов установки 0=4 1,2=3 3,4,5=2 6,7,8,9 =1 10= монтаж произведен 

	bool GameHod = true;											// Переменная для определения хода  1 = игрок, 0 = комп.
	bool GameContinue=true;										// Вентиль для продолжения хода
	bool SunWinPlay = false;
	bool SunFailPlay = false;
	bool SunActivBotPlay = false;



	Clock clok;														// Отсчет времени
	float dalyFrame = 0;											// Счетчик прошедшего времени с момента отрисовки последнего кадра
	Clock kadry;
	int kad = 0;

	Clock TimeAnimation;
	float ZadAnimation = 0;
	Clock TimeZad;													// Время для задержки хода противника
	float Zaderjka = 0;												// Вентиль для задержки хода противника
		
	int Global_Deadh[10][2];											// Массив координат начала утопленных кораблей user
	int Global_DeadhUser[10][2];										// Массив координат начала утопленных кораблей op
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 2; j++)
		{
			Global_Deadh[i][j] = -1;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Global_DeadhUser[i][j] = -1;
		}
	}


	int After_Bang[9];												// Массив состояний выстрела противника
	for (int i = 0; i < 9; i++)
	{
		After_Bang[i] = -1;
	}


	while (window.isOpen())											// Главный цикл игры
	{
		if (Global_Deadh[9][0] != -1 && Global_DeadhUser[9][0] == -1)
		{
			MontageVariator = 11;									// fail
		}
		if (Global_Deadh[9][0] == -1 && Global_DeadhUser[9][0] != -1)
		{
			MontageVariator = 12;									// Win
		}

		dalyFrame = clok.getElapsedTime().asMilliseconds();			// Записываем в счетчик прошедшее с момента рестарта время 
		int my = Mouse::getPosition(window).y;						// Получаем положение мыши У
		int mx = Mouse::getPosition(window).x;						// Получаем положение мыши Х


		sf::Event event;

		while (window.pollEvent(event))								// Цикл обработки событий
		{

			if (event.type == sf::Event::Closed)					// Событие нажатия на крестик окна
				window.close();										// Закрываем окно


			if (event.type == Event::MouseButtonPressed&&ShipMontage)				// Если нажали на кнопку мыши
			{
				if (event.key.code == Mouse::Left)						// А именно левую
				{
					if (ShipMontage)									// Если вентиль монтажа кораблей открыт
					{
						
						movedShip(event, StadyMontage, gorisont, isCorrect);				// Вызвать функцию движения
					}
				}
			}


			if (event.type == Event::MouseButtonReleased && ShipMontage)// Если отпустили на кнопку мыши
			{
				if (event.key.code == Mouse::Left)						// А именно левую
				{
					if (ShipMontage)									// Если вентиль монтажа кораблей открыт
					{
						
						movedShip(event, StadyMontage, gorisont, isCorrect);				// Вызвать функцию движения
					}
				}
			}


			if (event.type == sf::Event::KeyPressed && ShipMontage)					// Если нажали на кнопку 
			{
				if (event.key.code == sf::Keyboard::R)					// А именно R
				{
					if (StadyMontage > -1			)					// Если стадия монтажа больше 0 и вентиль монтажа кораблей открыт
					{
						SOUND[0].play();
						movedShip(event, StadyMontage, gorisont, isCorrect);			// Вызвать функцию движения
					}
				}
			}

			if (MontageVariator >10)
			{
				if (!chekActivBot(mx, my, BotRestart))
				{
					BotRestartText.setFillColor(Color::White);
				}
				if (chekActivBot(mx, my, BotRestart))
				{
					BotRestartText.setFillColor(Color::Red);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						SOUND[0].play();
						 OverRestart(user, oponent,Animation, PrevBangAnimation, iterVar, Bot_AutoShip, isMove, pressR, StadyMontage,  gorisont,  isCorrect,  ShipMontage, MontageVariator, GameHod,  GameContinue,Global_Deadh, Global_DeadhUser, After_Bang, SunWinPlay, SunFailPlay);
					}
				}
				if (!chekActivBot(mx, my, BotExit))
				{
					BotExitText.setFillColor(Color::White);
				}
				if (chekActivBot(mx, my, BotExit))
				{
					BotExitText.setFillColor(Color::Red);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						SOUND[0].play();
						window.close();
					}
				}
			}

			if (MontageVariator < 10&&!ShipMontage)
			{
				AnimatedText(mx, my, BotYas, strVarPos, Bot_AutoShip, iterVar, user, MontageVariator, BotNo, ShipMontage, StadyMontage,SOUND, SunActivBotPlay);
			}
			

			
			int Chek_Correct = 0;
			for (int y = 9; y >-1 ; y--)								// Цикл проверки полей на активность
			{
				
				for (int x = 9; x > -1; x--)
				{
					if (!ShipMontage)
					{
						user[y][x].ChekActiv(mx, my);					// Если монтаж кораблей не происходит выполняем проверку на наличие мыши 
						
					}
					if (ShipMontage)									// Если происходит монтаж
					{
						user[y][x].ChekActiv(mx, my);
						if (user[y][x].GetActivated())
						{
							Chek_Correct++;
							MontageShip_2(user, gorisont, ShipMontage, isCorrect, x, y, MontageVariator, StadyMontage);
						}
					}

					oponent[y][x].ChekActiv(mx, my);					// Выполняем проверку на присутствие мыши 

					if (oponent[y][x].GetActivated() && MontageVariator == 10 && GameHod)			// Если клетка противника активна, и монтаж кораблей завершен, и ход игрока
					{
						HodUser(oponent, event, GameHod, y, x, StadyMontage,Global_DeadhUser,SOUND);					// Вызываем ход игрока
					}
				}
			}
			if (Chek_Correct == 0&& ShipMontage) { StadyMontage = 0; };
		}
		Zaderjka = TimeZad.getElapsedTime().asMilliseconds();		// Присваиваем задержке прошедшее время с начала таймера в мс					
		ZadAnimation = TimeAnimation.getElapsedTime().asMilliseconds();

	
		if (Animation == 1)
		{
			if (ZadAnimation > 1800)
			{
				ZadAnimation = 0;
				TimeAnimation.restart();
			}
			
			if (PrevBangAnimation[0] > -1 && PrevBangAnimation[0] < 10)
			{
				if (ZadAnimation > 0)
				{
					user[PrevBangAnimation[0]][PrevBangAnimation[1]].SetAnimation(true);
				}
				if (ZadAnimation > 300 && ZadAnimation < 600)
				{
					user[PrevBangAnimation[0]][PrevBangAnimation[1]].SetAnimation(false);
				}
				if (ZadAnimation > 600 && ZadAnimation < 900)
				{
					user[PrevBangAnimation[0]][PrevBangAnimation[1]].SetAnimation(true);
				}
				if (ZadAnimation > 900 && ZadAnimation < 1200)
				{
					user[PrevBangAnimation[0]][PrevBangAnimation[1]].SetAnimation(false);
				}
				if (ZadAnimation > 1200 && ZadAnimation < 1500)
				{
					user[PrevBangAnimation[0]][PrevBangAnimation[1]].SetAnimation(true);
				}
				if (ZadAnimation > 1500)
				{
					user[PrevBangAnimation[0]][PrevBangAnimation[1]].SetAnimation(false);
					Animation = 0;
				}
			
			}
		}


		if (!GameHod && MontageVariator == 10)						// Если ход противника и монтаж кораблей завершен
		{
			if (Zaderjka > 2010)//2010									// Если прошло 	более3050 мс						
			{
				Zaderjka = 0;										// Обнуляем задержку
				TimeZad.restart();									// Обнуляем таймер

			}
			if (Zaderjka >2000)// 2000 )								// Если задержка более 3000 мс
			{
				TimeZad.restart();								// Обнуляем таймер
				Animation=HodOponent(user, event, GameHod, StadyMontage, Global_Deadh, After_Bang, PrevBangAnimation,SOUND);			// Вызываем функцию хода противника
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

		   if (MontageVariator < 10 && ShipMontage)
		   {
			   MorBoy.setString(MorBo);
			   { window.draw(MontageText); }
		   }
		   if (!Bot_AutoShip&&!ShipMontage&&MontageVariator==0)		// Отрисовка живого текста и меню выбора монтажа кораблей
		   {
			   for (int i = 0; i<60; i++)							// Цикл отрисовки живого текста
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
			   window.draw(HodOp);									// Написать строку с учетом состояния хода
		   }
		   if (MontageVariator > 10)
		   {
			    window.draw(BotRestartText); 
				window.draw(BotExitText);

		   }

		   if(MontageVariator<11){ window.draw(MorBoy); }
		   if (MontageVariator == 11) 
		   {
			   MorBoy.setString(fail); 
			   MorBoy.setPosition(450,20);
			   window.draw(MorBoy); 
			   if (!SunFailPlay)
			   {
				   MorBoy.setString(MorBo);
				   SOUND[2].play();
				   SunFailPlay = true;
			   }
			
		   
		   
		   
		   }
		   if (MontageVariator == 12)
		   {
		    MorBoy.setString(Win); 
		   MorBoy.setPosition(470, 20);
		   window.draw(MorBoy); 
		   if (!SunWinPlay)
		   {
			   SOUND[6].play();
			   SunWinPlay = true;
			   MorBoy.setString(MorBo);
		   }
		   }

		   window.display();										// Отрисовать всё вышеописанное
		   

		   kad++;
		   FPS++;
		   dalyFrame = 0;											// Сброс счетчика 
		   clok.restart();										    // Перезапук времени для счетчика
		   //if (kadry.getElapsedTime().asSeconds() > 1) { cout << "FPS == " << kad << endl; kadry.restart(); kad = 0; }

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
