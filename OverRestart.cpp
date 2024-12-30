#include "OverRestart.h"

void OverRestart(Point** user, Point** oponent, int& Animation, int(&PrevBangAnimation)[2], int& iterVar, bool& Bot_AutoShip, bool& isMove, bool& pressR, int& StadyMontage, bool& gorisont, bool& isCorrect, bool& ShipMontage, int& MontageVariator, bool& GameHod, bool& GameContinue, int(&Global_Deadh)[10][2], int(&Global_DeadhUser)[10][2], int(&After_Bang)[9], bool& SunWinPlay,bool& SunWFailPlay)

	
	

	{
			SunWinPlay = 0;
			SunWFailPlay = 0;
		Animation = 0;

		PrevBangAnimation[0] = -1;
		PrevBangAnimation[1] = -1;

		iterVar = 0;

		Bot_AutoShip = false;


		isMove = false;
		pressR = false;

		StadyMontage = -1;



		gorisont = true;

		isCorrect = true;

		ShipMontage = false;

		MontageVariator = 0;

		GameHod = true;
		GameContinue = true;




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

		for (int i = 0; i < 9; i++)
		{
			After_Bang[i] = -1;
		}
		const int sArr = 10;
		setQuality(oponent, false, sArr, sArr);
		setQuality(user, true, sArr, sArr);
		GenerationShip(oponent);


	}

