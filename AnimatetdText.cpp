#include "AnimatetdText.h"

void AnimatedText(int mx, int my, RectangleShape& BotYas, Text* strVarPos, bool& Bot_AutoShip, int iterVar, Point** user, int& MontageVariator, RectangleShape& BotNo, bool& ShipMontage, int& StadyMontage, Sound (&SOUND)[7], bool& BotPlay )
{
	

		for (int i = 0; i < 61; i++)								// Цицл установки знач. отр. живого текста первого меню
		{
			if (chekActivBot(mx, my, BotYas))
			{
				strVarPos[52].setFillColor(Color::Red);
				strVarPos[53].setFillColor(Color::Red);
				if (!BotPlay)
				{
					
				}
				BotPlay = true;
				if (Mouse::isButtonPressed(Mouse::Left) && !Bot_AutoShip && iterVar > 60)
				{
					Bot_AutoShip = true;
					GenerationShip(user);
					MontageVariator = 10;
					SOUND[0].play();
				}
			}
			else
			{
				BotPlay = false;
				strVarPos[52].setFillColor(Color::White);
				strVarPos[53].setFillColor(Color::White);
			}
			if (chekActivBot(mx, my, BotNo)) {

				strVarPos[57].setFillColor(Color::Red);
				strVarPos[58].setFillColor(Color::Red);
				strVarPos[59].setFillColor(Color::Red);
				if (Mouse::isButtonPressed(Mouse::Left) && !ShipMontage && iterVar > 60)
				{
					SOUND[0].play();
					ShipMontage = true;
					StadyMontage = 0;
				}
			}
			else
			{
				strVarPos[57].setFillColor(Color::White);
				strVarPos[58].setFillColor(Color::White);
				strVarPos[59].setFillColor(Color::White);
			}
		}
	
}
