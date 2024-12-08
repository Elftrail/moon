#include"setQuality.h"

void setQuality(Point** arr, bool par)
{

	if (par)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				int size = arr[y][x].GetSize();
				arr[y][x].LoadTexture();
				arr[y][x].SetParty(par);
				arr[y][x].SetPosition(size * 15 + size * x, size * 4 + size * y);
				arr[y][x].SetStatus(0);
				

			}
		}
	}
	else
	{
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				int size = arr[y][x].GetSize();
				arr[y][x].LoadTexture();
				arr[y][x].SetParty(par);
				arr[y][x].SetPosition(size * 2 + size * x, size * 4 + size * y);
				arr[y][x].SetStatus(0);
				

			}
		}
	}


}