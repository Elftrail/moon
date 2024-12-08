#include "GenerationShip.h"

int rstr;//rndom string
int rsto;//random collumns
int rvec;//random vector
random_device system_rand;

bool Restart;


void gen2_3X(Point** arr,int Xs/*size ship*/)
{
	int seed = system_rand();
	srand(seed);

	do
	{
			Restart = false;
			rstr = rand()% 10;
			rsto = rand()% 10;
			rvec = rand() % 4;

			if (arr[rstr][rsto].GetStatus() != 3)
			{
				if (rsto > Xs-1&&rvec==0)// gen left
				{
					for (int y = -1; y < 2; y++)
					{
						for (int x = -Xs; x < 2; x++)
						{
							if ((rstr + y) < 10 && (rsto + x) < 10)//chek red line+
							{
								if (((rstr + y) > -1 && (rsto + x) > -1))//chek red line-
								{
									if (arr[rstr + y][rsto + x].GetStatus() == 3) { Restart = true; }
							}
							}
						}
					}
					if (!Restart)
					{
						for (int x = 0; x < Xs; x++)
						{
							arr[rstr][rsto - x].SetStatus(3);
						}
					}
				}
				else if (rstr > Xs-1 && rvec == 1)// gen up
				{
					for (int x = -1; x < 2; x++)
					{
						for (int y = -Xs; y < 2; y++)
						{
							if ((rstr + y) < 10 && (rsto + x) < 10)//chek red line
							{
								if (((rstr + y) > -1 && (rsto + x) > -1))//chek red line-
								{
									if (arr[rstr + y][rsto + x].GetStatus() == 3) { Restart = true; }
								}
							}
						}
					}
					if (!Restart)
					{
						for (int y = 0; y < Xs; y++)
						{
							arr[rstr-y][rsto].SetStatus(3);
						}
					}
				}
				else if (rsto < (11-Xs) && rvec == 2)// gen rirht
				{
					for (int y = -1; y < 2; y++)
					{
						for (int x = -1; x < Xs+1; x++)
						{
							if ((rstr + y) < 10 && (rsto + x) < 10)//chek red line
							{
								if (((rstr + y) > -1 && (rsto + x) > -1))//chek red line-
								{
									if (arr[rstr + y][rsto + x].GetStatus() == 3) { Restart = true; }
								}
							}
						}
					}
					if (!Restart)
					{
						for (int x = 0; x < Xs; x++)
						{
							arr[rstr][rsto + x].SetStatus(3);
						}
					}
				}
				else if (rstr < 11-Xs && rvec == 3)// gen down
				{
					for (int x = -1; x < 2; x++)
					{
						for (int y = -1; y < Xs+1; y++)
						{
							if ((rstr + y) < 10 && (rsto + x) < 10)//chek red line
							{
								if (((rstr + y) > -1 && (rsto + x) > -1))//chek red line-
								{
									if (arr[rstr + y][rsto + x].GetStatus() == 3) { Restart = true; }
								}
							}
						}
					}
					if (!Restart)
					{
						for (int y = 0; y < Xs; y++)
						{
							arr[rstr + y][rsto].SetStatus(3);
						}
					}
				}
				else { Restart = true; }

			}
			else { Restart = true; }//Error restart

	}while (Restart);
				
}



void GenerationShip(Point** arr)
{
	gen2_3X(arr, 4);
	gen2_3X(arr,3);
	gen2_3X(arr,3);
	gen2_3X(arr, 2);
	gen2_3X(arr, 2);
	gen2_3X(arr, 2);
	gen2_3X(arr, 1);
	gen2_3X(arr, 1);
	gen2_3X(arr, 1);
	gen2_3X(arr, 1);
}