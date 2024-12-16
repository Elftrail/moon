#include "HodOponent.h"
random_device system_random;						// Вводим переменную для рандома


void HodOponent(Point** user, sf::Event& event, bool& GameHod, int& isMontage)
{
	if (!GameHod)									// Если ход противника
	{
		bool restart;								// Обьявляем переменную рестарта
		int seed = system_random();					// Обьявляем переменную для хранения рандома
		srand(seed);								// Вызываем сранд	
		do
		{
			restart = false;						// Выключаем рестарт		
			int bangX = rand() % 10;				// Рандомный столбец
			int bangY = rand() % 10;				// Рандомная строка

			switch (user[bangY][bangX].GetStatus())	// Обьявлям набор свичей для интерпритации рандомных значений	
			{
			case 0:									// Если в рандомной клетке пусто
			{
				user[bangY][bangX].SetStatus(1);	// Записываем в клетку "Мимо"	
				GameHod = !GameHod;					// Переводим ход к игроку
				break;								// Выпадаем из свича
			}
			case 3:									// Если в клетке корабль
			{
				user[bangY][bangX].SetStatus(2);	// Записываем в клетку попадание


				int x = 0;

				for (int Y = 0; Y < 10; Y++)
				{
					for (int X = 0; X < 10; X++)
					{
						if (user[Y][X].GetStatus() == 2)
						{
							for (int smeY = -1; smeY < 2; smeY++)
							{
								for (int smeX = -1; smeX < 2; smeX++)
								{
									if ((Y + smeY) < 10 && (Y + smeY) > -1 && (X + smeX) < 10 && (X + smeX) > -1)
									{
										if (user[Y + smeY][X + smeX].GetStatus() == 3)
										{
											++x;
											cout << "x== " << x << endl;
											break;
										}
									}
								}
							}
						}
					}
				}
				if (x == 0)
				{
					for (int Y = 0; Y < 10; Y++)
					{
						for (int X = 0; X < 10; X++)
						{
							if (user[Y][X].GetStatus() == 2)
							{
								for (int smeY = -1; smeY < 2; smeY++)
								{
									for (int smeX = -1; smeX < 2; smeX++)
									{
										if ((Y + smeY) < 10 && (Y + smeY) > -1 && (X + smeX) < 10 && (X + smeX) > -1)
										{
											if (user[Y + smeY][X + smeX].GetStatus() == 0)
											{
												user[Y + smeY][X + smeX].SetStatus(1);
											}
										}
									}
								}
							}
						}
					}
				}

				break;								// Выпадаем из свича
			}
			default:								// Если в клетке другие значения
			{
				restart = true;						// Активируем рестарт
				break;								// Выпадаем из свича
			}
			}
			} while (restart);							// Если рестарт активен- перезапускаем цикл

		}
	}

