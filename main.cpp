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

	String VarPos(L"���� ���� ������. ���������� ������� �������������? �� / ���");
	String SHodOp(L"��� ����������");
	String MorBo(L"������� ���");
	String fail(L"���������");
	String Win(L"������!!!");
	String SBotRestartText(L"������� �����");
	String SBotExitText(L" ����� �� ����");
	String SHodUs(L"��� ���");
	String SMontageText(L"���������� ���� �������. ��� - ���������� ������� � - ��������� �������");

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

	int PrevBangAnimation[2]{ -1, -1 };								// ���������� ����������� �������� � � ��������� ����������  
	int FPS = 0;													// ������� ��� ��� �������� ������������ �������


	int iterVar = 0;												// ������� ��� �������� ������� ��� ������ ������ ������ ������� ����										

	bool Bot_AutoShip = false;										// ������� ������ ����������� �������� � ����
	bool VENTBotContinue = true;									// ������� ������ ����������

	bool isMove = false;											// ����������-������� ��� �������������� �������
	bool pressR = false;											// ���������� ��� ������������ R � �������� �������

	int StadyMontage = -1;											// �������� ������� �� ������� 
																	//-1 ������� �� ������� 0 - ������� ������  �� ������ 1 - ������� ����� ��������  2 - ������� ������
																	

	bool gorisont = true;											// ������� ��������� ������ 1 - �������������� 0 - ������������

	bool isCorrect = true;											// ���������� ��� "�� ������ ������� ��������?

	bool ShipMontage = false;										// ������� ��� �������� ������ ����������� ��������

	int MontageVariator = 0;										// ���������� ��� ������ ������� ��������� 0=4 1,2=3 3,4,5=2 6,7,8,9 =1 10= ������ ���������� 

	bool GameHod = true;											// ���������� ��� ����������� ����  1 = �����, 0 = ����.
	bool GameContinue=true;										// ������� ��� ����������� ����
	bool SunWinPlay = false;
	bool SunFailPlay = false;
	bool SunActivBotPlay = false;



	Clock clok;														// ������ �������
	float dalyFrame = 0;											// ������� ���������� ������� � ������� ��������� ���������� �����
	Clock kadry;
	int kad = 0;

	Clock TimeAnimation;
	float ZadAnimation = 0;
	Clock TimeZad;													// ����� ��� �������� ���� ����������
	float Zaderjka = 0;												// ������� ��� �������� ���� ����������
		
	int Global_Deadh[10][2];											// ������ ��������� ������ ���������� �������� user
	int Global_DeadhUser[10][2];										// ������ ��������� ������ ���������� �������� op
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


	int After_Bang[9];												// ������ ��������� �������� ����������
	for (int i = 0; i < 9; i++)
	{
		After_Bang[i] = -1;
	}


	while (window.isOpen())											// ������� ���� ����
	{
		if (Global_Deadh[9][0] != -1 && Global_DeadhUser[9][0] == -1)
		{
			MontageVariator = 11;									// fail
		}
		if (Global_Deadh[9][0] == -1 && Global_DeadhUser[9][0] != -1)
		{
			MontageVariator = 12;									// Win
		}

		dalyFrame = clok.getElapsedTime().asMilliseconds();			// ���������� � ������� ��������� � ������� �������� ����� 
		int my = Mouse::getPosition(window).y;						// �������� ��������� ���� �
		int mx = Mouse::getPosition(window).x;						// �������� ��������� ���� �


		sf::Event event;

		while (window.pollEvent(event))								// ���� ��������� �������
		{

			if (event.type == sf::Event::Closed)					// ������� ������� �� ������� ����
				window.close();										// ��������� ����


			if (event.type == Event::MouseButtonPressed&&ShipMontage)				// ���� ������ �� ������ ����
			{
				if (event.key.code == Mouse::Left)						// � ������ �����
				{
					if (ShipMontage)									// ���� ������� ������� �������� ������
					{
						
						movedShip(event, StadyMontage, gorisont, isCorrect);				// ������� ������� ��������
					}
				}
			}


			if (event.type == Event::MouseButtonReleased && ShipMontage)// ���� ��������� �� ������ ����
			{
				if (event.key.code == Mouse::Left)						// � ������ �����
				{
					if (ShipMontage)									// ���� ������� ������� �������� ������
					{
						
						movedShip(event, StadyMontage, gorisont, isCorrect);				// ������� ������� ��������
					}
				}
			}


			if (event.type == sf::Event::KeyPressed && ShipMontage)					// ���� ������ �� ������ 
			{
				if (event.key.code == sf::Keyboard::R)					// � ������ R
				{
					if (StadyMontage > -1			)					// ���� ������ ������� ������ 0 � ������� ������� �������� ������
					{
						SOUND[0].play();
						movedShip(event, StadyMontage, gorisont, isCorrect);			// ������� ������� ��������
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
			for (int y = 9; y >-1 ; y--)								// ���� �������� ����� �� ����������
			{
				
				for (int x = 9; x > -1; x--)
				{
					if (!ShipMontage)
					{
						user[y][x].ChekActiv(mx, my);					// ���� ������ �������� �� ���������� ��������� �������� �� ������� ���� 
						
					}
					if (ShipMontage)									// ���� ���������� ������
					{
						user[y][x].ChekActiv(mx, my);
						if (user[y][x].GetActivated())
						{
							Chek_Correct++;
							MontageShip_2(user, gorisont, ShipMontage, isCorrect, x, y, MontageVariator, StadyMontage);
						}
					}

					oponent[y][x].ChekActiv(mx, my);					// ��������� �������� �� ����������� ���� 

					if (oponent[y][x].GetActivated() && MontageVariator == 10 && GameHod)			// ���� ������ ���������� �������, � ������ �������� ��������, � ��� ������
					{
						HodUser(oponent, event, GameHod, y, x, StadyMontage,Global_DeadhUser,SOUND);					// �������� ��� ������
					}
				}
			}
			if (Chek_Correct == 0&& ShipMontage) { StadyMontage = 0; };
		}
		Zaderjka = TimeZad.getElapsedTime().asMilliseconds();		// ����������� �������� ��������� ����� � ������ ������� � ��					
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


		if (!GameHod && MontageVariator == 10)						// ���� ��� ���������� � ������ �������� ��������
		{
			if (Zaderjka > 2010)//2010									// ���� ������ 	�����3050 ��						
			{
				Zaderjka = 0;										// �������� ��������
				TimeZad.restart();									// �������� ������

			}
			if (Zaderjka >2000)// 2000 )								// ���� �������� ����� 3000 ��
			{
				TimeZad.restart();								// �������� ������
				Animation=HodOponent(user, event, GameHod, StadyMontage, Global_Deadh, After_Bang, PrevBangAnimation,SOUND);			// �������� ������� ���� ����������
				VENTBotContinue = true;
			}

		}
		if (GameHod)
		{
			Zaderjka = 0;										// �������� ��������
			TimeZad.restart();									// �������� ������}
		}
		
	  
	
	   if (dalyFrame > 15)											// ���� ������ ����� 15 ���������� - ��������� ����� (15 = +- 60 ���)		
	   {
		   if (FPS == 60) { FPS = 0; }								// ���� ���������� 60 ������ - ��������� �������		

		   window.clear(Color::Black);								// ������� ����

		  // window.draw(sFon);										// ������� ���
 
		   //print poole oponent and user
		   for (int y = 0; y < 10; y++)
		   {
			   for (int x = 0; x < 10; x++)
			   {
				   window.draw(user[y][x].GetSprite());
				   window.draw(oponent[y][x].GetSprite());
			   }
		   }


		   //=============================================================������ � �������======================================================================//
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
		   if (!Bot_AutoShip&&!ShipMontage&&MontageVariator==0)		// ��������� ������ ������ � ���� ������ ������� ��������
		   {
			   for (int i = 0; i<60; i++)							// ���� ��������� ������ ������
			   {
				   { window.draw(strVarPos[i]); }					// ��������� �������� ������� ������ ������
			   }
		   }
		   if (GameHod && MontageVariator == 10)					// ���� ��� ������ � ������ ��������
		   {
			   window.draw(HodUs);									// �������� ��� ���
		   }
		   if (!GameHod && MontageVariator == 10)					// ���� ��� ���������� � ������ ��������
		   {
			   window.draw(HodOp);									// �������� ������ � ������ ��������� ����
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

		   window.display();										// ���������� �� �������������
		   

		   kad++;
		   FPS++;
		   dalyFrame = 0;											// ����� �������� 
		   clok.restart();										    // ��������� ������� ��� ��������
		   //if (kadry.getElapsedTime().asSeconds() > 1) { cout << "FPS == " << kad << endl; kadry.restart(); kad = 0; }

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
