#include"setQuality.h"

void setQuality(Point** arr, bool par,int sizeX,int sizeY)
{

	if (par)
	{
		for (int y = 0; y < sizeY; y++)
		{
			for (int x = 0; x < sizeX; x++)
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
		for (int y = 0; y < sizeY; y++)
		{
			for (int x = 0; x < sizeX; x++)
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
void setQuality(Point* arr, bool par, int sizeX)
{

	if (par)
	{
		
			for (int x = 0; x < sizeX; x++)
			{
				int size = arr[x].GetSize();
				arr[x].LoadTexture();
				arr[x].SetParty(par);
				arr[x].SetPosition(size * 15 + size * x, size * 4);
				arr[x].SetStatus(0);


			}
		
	}
	else
	{
		
			for (int x = 0; x < sizeX; x++)
			{
				int size = arr[x].GetSize();
				arr[x].LoadTexture();
				arr[x].SetParty(par);
				arr[x].SetPosition(size * 2 + size * x, size * 4 + size);
				arr[x].SetStatus(0);


			}
		
	}


}
void setQuality(Point* arr, bool par, int sizeX,int status)
{

	if (par)
	{

		for (int x = 0; x < sizeX; x++)
		{
			int size = arr[x].GetSize();
			arr[x].LoadTexture();
			arr[x].SetParty(par);
			arr[x].SetPosition(size * 15 + size * x, size * 4 + size );
			arr[x].SetStatus(status);


		}

	}
	else
	{

		for (int x = 0; x < sizeX; x++)
		{
			int size = arr[x].GetSize();
			arr[x].LoadTexture();
			arr[x].SetParty(par);
			arr[x].SetPosition(size * 2 + size * x, size * 4 + size );
			arr[x].SetStatus(status);


		}

	}


}
