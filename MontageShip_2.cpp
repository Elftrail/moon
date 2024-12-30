#include "MontageShip_2.h"

void MontageShip_2(Point** user, bool& gorisont, bool& ShipMontage, bool& isCorrect, int x, int y, int& MontageVariator, int& StadyMontage)
{
	int D = -1;
	switch (MontageVariator)
	{
	case 0:
		D = 4;
		break;
	case 1:
	case 2:
		D = 3;
		break;
	case 3:
	case 4:
	case 5:
		D = 2;
		break;
	case 6:
	case 7:
	case 8:
	case 9:
		D = 1;
		break;
	}

	bool chekSoul=true;
	if (gorisont)
	{
		int fyx_schet = 0;
		if (x > -1 && x < 10-D+1)
		{
			for (int fy = -1; fy < 2; fy++)
			{
				for (int fx = -1; fx < D+1; fx++) 
				{
					if (y + fy > -1 && y + fy<10 && x + fx>-1 && x + fx < 10) 
					{
						if (user[y + fy][x + fx].GetStatus() == 3) { fyx_schet++; }
					}
				}
			}
			if (fyx_schet == 0)
			{
				isCorrect = true;
				for (int i = 0; i < D; i++)
				{
					user[y][x + i].SetActivated(1);
				}
				if (StadyMontage == 2)
				{
					for (int i = 0; i < D; i++)
					{
						user[y][x + i].SetStatus(3);
						StadyMontage = 0;
					}
					MontageVariator++;
				}
			}
			
		}
		if (x > 10-D||fyx_schet > 0)
		{
			isCorrect = false;
			for (int i = 0; i < D; i++)
			{
				if (x + i < 10)
				{
					user[y][x + i].SetActivated(1,0);
				}
			}
		}
	}








	if (!gorisont)
	{
		int fyx_schet = 0;
		if (y > -1 && y < 10 - D + 1)
		{
			for (int fx = -1; fx < 2; fx++)
			{
				for (int fy = -1; fy < D + 1; fy++)
				{
					if (y + fy > -1 && y + fy<10 && x + fx>-1 && x + fx < 10)
					{
						if (user[y + fy][x + fx].GetStatus() == 3) { fyx_schet++; }
					}
				}
			}
			if (fyx_schet == 0)
			{
				isCorrect = true;
				for (int i = 0; i < D; i++)
				{
					user[y + i][x].SetActivated(1);
				}
				if (StadyMontage == 2)
				{
					for (int i = 0; i < D; i++)
					{
						user[y + i][x].SetStatus(3);
						StadyMontage = 0;
					}
					MontageVariator++;
				}
			}

		}
		if (y > 10 - D || fyx_schet > 0)
		{
			isCorrect = false;
			for (int i = 0; i < D; i++)
			{
				if (y + i < 10)
				{
					user[y + i][x].SetActivated(1, 0);
				}
			}
		}
	}

	if (MontageVariator == 10) { ShipMontage = false; }
}
