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
void setQuality(RectangleShape& maket, int MontageVariator)

{

	switch (MontageVariator)
	{
	case 0:
	{
		maket.setSize(Vector2f::Vector2(200, 50));
		maket.setPosition(750, 200);
		//cout << " case  0" << endl;
		break;
	}
	case 1:
		//cout << " case  1" << endl;
	case 2:
	{
		maket.setSize(Vector2f::Vector2(150, 50));
		maket.setPosition(750, 200);
		break;
		//cout << " case  2" << endl;
		
	}
	case 3:
		//cout << " case  3" << endl;
	case 4:
		//cout << " case  4" << endl;
	case 5:
	{
		maket.setSize(Vector2f::Vector2(100, 50));
		maket.setPosition(750, 200);
		break;
		//cout << " case  5" << endl;
	}
	case 6:
	case 7:
	case 8:
	case 9:
	{
		maket.setSize(Vector2f::Vector2(50, 50));
		maket.setPosition(750, 200);
		break;
		//cout << " case  6789" << endl;
	}
	}

}
