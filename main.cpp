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

	String VarPos(L"�-� �������! �������� ���� �������� ������ ��������? �� / ���");
	String SHodOp(L"��� ����������");
	String MorBo(L"������� ���");
	String fail(L"���������");
	String Win(L"������!!!");
	String SBotContinue(L"����������?");
	String SHodUs(L"��� ���");



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
	
	Text  BotContinueText;
	BotContinueText.setFont(font);
	BotContinueText.setPosition(450, 750);
	BotContinueText.setString(SBotContinue);
	
	Text strVarPos[62];
	for (int i = 0; i < 62; i++)
	{
		strVarPos[i].setFont(font);
		strVarPos[i].setPosition(40 + 20 * i, 750);
	}

	Text numerationNUM[2];
	Text numerationLIT[10][2];
	setCoor(numerationLIT, numerationNUM, font);
	
	
	RectangleShape BotContinue;
	BotContinue.setPosition(450, 750);
	BotContinue.setSize(Vector2f::Vector2(100, 35));



	RectangleShape BotYas;
	BotYas.setPosition(1090, 750);
	BotYas.setSize(Vector2f::Vector2(60, 35));

	RectangleShape BotNo;
	BotNo.setPosition(1190, 750);
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

	int PrevBangOp[4]{ -1, -1, -1, -1 };							// ���������� ����������� �������� � � ��������� ����������  
	int PrevBangUs[4]{ -1, -1, -1, -1 };							// ���������� ����������� �������� ������ ������ ��������� ����������  
	int FPS = 0;													// ������� ��� ��� �������� ������������ �������


	int iterVar = 0;												// ������� ��� �������� ������� ��� ������ ������ ������ ������� ����										

	bool Bot_AutoShip = false;										// ������� ������ ����������� �������� � ����
	bool VENTBotContinue = true;									// ������� ������ ����������

	bool isMove = false;											// ����������-������� ��� �������������� �������
	bool pressR = false;											// ���������� ��� ������������ R � �������� �������

	int isMontage = 0;												// �������� ������� �� ������� 
																	// 0 - ������ �� ������� 1 - ����� � �������   
																	// 2 - �������� �������� 3- �������� � �������������

	bool gorisont = true;											// ������� ��������� ������ 1 - �������������� 0 - ������������

	bool isCorrect = true;											// ���������� ��� "�� ������ ������� ��������?

	bool ShipMontage = false;										// ������� ��� �������� ������ ����������� ��������

	int MontageVariator = 0;										// ���������� ��� ������ ������� ��������� 0=4 1,2=3 3,4,5=2 6,7,8,9 =1 10= ������ ���������� 

	bool GameHod = true;											// ���������� ��� ����������� ����  1 = �����, 0 = ����.
	bool GameContinue=true;										// ������� ��� ����������� ����

	int corX = 0;													// ������������� ��������� ������ ����� ��� ����� �� �
	int corY = 0;													// ������������� ��������� ������ ����� ��� ����� �� �

	RectangleShape XXXX;											// ������ ��������� �����
	setQuality(XXXX, MontageVariator);								// �������� ������� ��������� ���������

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
			MontageVariator = 11; // fail
		}
		if (Global_Deadh[9][0] == -1 && Global_DeadhUser[9][0] != -1)
		{
			MontageVariator = 12; // Win
		}

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
						movedShip(event, XXXX, isMove, isMontage, isCorrect, mx, my, corX, corY, gorisont);				// ������� ������� ��������
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

			if (!GameHod && MontageVariator == 10)
			{
				if (!chekActivBot(mx, my, BotContinue))
				{
					BotContinueText.setFillColor(Color::White);
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

					if (oponent[y][x].GetActivated() && MontageVariator == 10 && GameHod)			// ���� ������ ���������� �������, � ������ �������� ��������, � ��� ������
					{
						HodUser(oponent, event, GameHod, y, x, isMontage,Global_DeadhUser,SOUND);					// �������� ��� ������
					}


				}
			}
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
			
			if (PrevBangOp[0] > -1 && PrevBangOp[0] < 10)
			{
				if (ZadAnimation > 0)
				{
					user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(true);
				}
				if (ZadAnimation > 300 && ZadAnimation < 600)
				{
					user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(false);
				}
				if (ZadAnimation > 600 && ZadAnimation < 900)
				{
					user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(true);
				}
				if (ZadAnimation > 900 && ZadAnimation < 1200)
				{
					user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(false);
				}
				if (ZadAnimation > 1200 && ZadAnimation < 1500)
				{
					user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(true);
				}
				if (ZadAnimation > 1500)
				{
					user[PrevBangOp[0]][PrevBangOp[1]].SetAnimation(false);
					Animation = 0;
				}
			
			}
		}


		if (!GameHod && MontageVariator == 10)						// ���� ��� ���������� � ������ �������� ��������
		{
			if (Zaderjka > 10)//)										// ���� ������ 	�����3050 ��						
			{
				Zaderjka = 0;										// �������� ��������
				TimeZad.restart();									// �������� ������

			}
			if (Zaderjka >2)// 2000 )								// ���� �������� ����� 3000 ��
			{
				TimeZad.restart();								// �������� ������
				Animation=HodOponent(user, event, GameHod, isMontage, Global_Deadh, After_Bang, PrevBangOp,SOUND);			// �������� ������� ���� ����������
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

			
		   if (!Bot_AutoShip&&!ShipMontage&&MontageVariator==0)		// ��������� ������ ������ � ���� ������ ������� ��������
		   {
			   for (int i = 0; i<61; i++)							// ���� ��������� ������ ������
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


		   if(MontageVariator<11){ window.draw(MorBoy); }
		   if (MontageVariator == 11) { MorBoy.setString(fail); MorBoy.setPosition(450,20); window.draw(MorBoy); }
		   if (MontageVariator == 12) { MorBoy.setString(Win); MorBoy.setPosition(470, 20); window.draw(MorBoy); }
		   
		



		 
		  
		   
		   
		   
		   
		   
		   
		   window.display();										// ���������� �� �������������
		   


		
		 


		   kad++;
		   FPS++;
		   dalyFrame = 0;											// ����� �������� 
		   clok.restart();										    // ��������� ������� ��� ��������
		   if (kadry.getElapsedTime().asSeconds() > 1) { cout << "FPS == " << kad << endl; kadry.restart(); kad = 0; }

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
