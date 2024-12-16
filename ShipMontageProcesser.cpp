#include "ShipMontageProcesser.h"



	void ShipMontagePocesser(Point** user, RectangleShape& XXXX, bool& gorisont, bool& ShipMontage, bool& isCorrect, int x, int y, int& MontageVariator, int& isMontage, int mx, int my)
	{
		if (gorisont)														// Если положение горизонтально
		{
			user[y][x].ChekActiv(XXXX.getPosition().x - 30 + XXXX.getSize().x, XXXX.getPosition().y + XXXX.getSize().y / 2);   // Проверка на активацию по крайнему правому положению макетного спрайта - 30 пикселй
		}
		if (!gorisont)														// Если положение вертикально
		{
			user[y][x].ChekActiv(XXXX.getPosition().x + XXXX.getSize().x / 2, XXXX.getPosition().y - 30 + XXXX.getSize().y);   // Проверка на активацию по крайнему правому положению макетного спрайта - 30 пикселй
		}
		if (MontageVariator == 0)											// Если стадия вариатора = 0
		{
			if (gorisont)													// Если вентиль макета =1
			{
				if (user[y][x].GetActivated() && (x - 3) > -1)				// Если клетка активна и мы не вываливаемся за границу поля
				{
					isCorrect = true;										// Это коректно
					user[y][x - 1].SetActivated(true);						// 	
					user[y][x - 2].SetActivated(true);						// Активируем 3 клетки от активной влево
					user[y][x - 3].SetActivated(true);						//

					if (isMontage == 3 && isCorrect)						// Если монтаж в стадии 3
					{
						MontageVariator++;									// Переключаем вариатор на следующий вариант
						setQuality(XXXX, MontageVariator);					// Вызываем функцию настройки состояния
						isMontage = 0;										// переводим стадию монтажа на ноль
						user[y][x].SetStatus(3);							//
						user[y][x - 1].SetStatus(3);						// Монтируем корабль 
						user[y][x - 2].SetStatus(3);						//
						user[y][x - 3].SetStatus(3);						//


					}
				}
				if (user[y][x].GetActivated() && (x - 3) == -1)				// Если клетка активна и мы вываливаемся за границу поля на одну клетку
				{
					isCorrect = false;										// Это не кректное положение
					user[y][x].SetActivated(true, isCorrect);				//
					user[y][x - 1].SetActivated(true, isCorrect);			// 	
					user[y][x - 2].SetActivated(true, isCorrect);			// Активируем 2 клетки от активной влево + пишем их неправильными
				}
				if (user[y][x].GetActivated() && (x - 3) == -2)				// Если клетка активна и мы вываливаемся за границу поля на две клетки
				{
					isCorrect = false;										// Это не кректно
					user[y][x].SetActivated(true, isCorrect);				//
					user[y][x - 1].SetActivated(true, isCorrect);			// Активируем 1 клетку от активной влево + пишем их неправильным

				}
			}
			else if (!gorisont)												// Если корабль в вертикальномположении
			{																// Если вентиль макета =0
				if (user[y][x].GetActivated() && (y - 3) > -1)				// Если клетка активна и мы не вываливаемся за границу поля
				{
					isCorrect = true;										// Это коректное положение
					user[y - 1][x].SetActivated(true);						// 	
					user[y - 2][x].SetActivated(true);						// Активируем 3 клетки от активной вверх
					user[y - 3][x].SetActivated(true);						//

					if (isMontage == 3)										// Если монтаж в стадии 3
					{
						user[y][x].SetStatus(3);							//
						user[y - 1][x].SetStatus(3);						// Монтируем корабль 
						user[y - 2][x].SetStatus(3);						//
						user[y - 3][x].SetStatus(3);						//
						MontageVariator++;									// Переключаем вариатор на следующий вариант
						setQuality(XXXX, MontageVariator);					// Вызываем функцию настройки состояния
						isMontage = 0;										// Переводим стадию монтажа на ноль
						gorisont = true;									// Возвращаем горизонт наместо
					}
				}
				if (y == 9 && my > user[6][x].GetPositionY() + user[6][x].GetSize() / 2)								// При проверке 9 го поля если мышь по У ниже 6-го поля на1/2
				{
					if (mx > user[y][x].GetPositionX() && mx < user[y][x].GetPositionX() + user[y][x].GetSize())		// Если мышь по Х попдает в этот столбец
					{
						isCorrect = false;									// Это не корекное положение корабля
						user[y - 1][x].SetActivated(true, isCorrect);		// 	
						user[y - 2][x].SetActivated(true, isCorrect);		// Активируем 3 нижние клетки по активному столбцу 
						user[y][x].SetActivated(true, isCorrect);			// а также делаем их некоректными
					}
				}
			}

		}
		if (MontageVariator == 1 || MontageVariator == 2)					// Обсчет 3-х палубного макета
		{
			if (gorisont)													// Если корабль горизонтален
			{
				if (user[y][x].GetActivated() && (x - 2) > -1)				// Если клетка активна и мы не вываливаемся за границу поля
				{
					bool Nixuya = false;									// Переменная для контроля присутствия корабля рядом
					for (int ychek = -1; ychek < 2; ychek++)				// Двойной цикл обсчета положения
					{														//
						for (int xchek = -3; xchek < 2; xchek++)			//	
						{
							if (x + xchek > -1 && x + xchek < 11)			// Если при проверке мы не вываливаемся за массив по Х
							{
								if (y + ychek > -1 && y + ychek < 10)		// Если при проверке мы не вываливаемся за массив по У
								{
									if (user[y + ychek][x + xchek].GetStatus() == 3)	// Проверяем наличие корабля
									{
										Nixuya = true;						// Если корабль - нихая нельзя = истина
									}
								}
							}
						}
					}
					if (!Nixuya)											// Если нихуя нельзя = ложь									
					{
						isCorrect = true;									// Это коректно
						user[y][x - 1].SetActivated(true, isCorrect);		// 	
						user[y][x - 2].SetActivated(true, isCorrect);		// Активируем 2 клетки от активной влево
					}
					if (Nixuya)												// Если нихая нельзя = истин
					{
						isCorrect = false;									// Положение не коректно
						user[y][x].SetActivated(true, isCorrect);			// Активируем активную 2 клетки от активной влево
						user[y][x - 1].SetActivated(true, isCorrect);		// И описываем их некоректными
						user[y][x - 2].SetActivated(true, isCorrect);		// 
					}


					if (isMontage == 3 && isCorrect)						// Если монтаж в стадии 3 и положение корректно
					{
						MontageVariator++;									// Переключаем вариатор на следующий вариант
						setQuality(XXXX, MontageVariator);					// Вызываем функцию настройки состояния
						isMontage = 0;										// Переводим стадию монтажа на ноль
						user[y][x].SetStatus(3);							//
						user[y][x - 1].SetStatus(3);						// Монтируем корабль 
						user[y][x - 2].SetStatus(3);						//

					}
				}
				if (user[y][x].GetActivated() && (x - 2) == -1)				// Если клетка активна и мы вываливаемся за границу поля на одну клетку
				{
					isCorrect = false;										// Это не кректное положение
					user[y][x].SetActivated(true, isCorrect);				//
					user[y][x - 1].SetActivated(true, isCorrect);			// Активируем 2 клетки от активной влево + пишем их неправильными	
				}
			}
			else if (!gorisont)
			{																// Если вентиль макета =0
				if (user[y][x].GetActivated() && (y - 2) > -1)				// Если клетка активна и мы не вываливаемся за границу поля
				{
					bool Nixuya = false;									// Переменная для котроля присутствия корабля рядом
					for (int xchek = -1; xchek < 2; xchek++)
					{
						for (int ychek = -3; ychek < 2; ychek++)			// Двойной цикл обсчета положения
						{
							if (x + xchek > -1 && x + xchek < 11)			// Если при проверке мы не вываливаемся за массив по Х
							{
								if (y + ychek > -1 && y + ychek < 10)		// Если при проверке мы не вываливаемся за массив по У
								{
									if (user[y + ychek][x + xchek].GetStatus() == 3)		// Проверяем наличие корабля
									{
										Nixuya = true;						// Если корабль - нихая нельзя = истина
									}
								}
							}
						}
					}
					if (!Nixuya)											// Если нихая нельзя = ложь		
					{
						isCorrect = true;									// Это корректное положение
						user[y - 1][x].SetActivated(true);					// 	
						user[y - 2][x].SetActivated(true);					// Активируем 2 клетки от активной вверх
					}
					if (Nixuya)												// Если нихая нельзя = истина
					{
						isCorrect = false;									// Это не корректное положение
						user[y][x].SetActivated(true, isCorrect);			//
						user[y - 1][x].SetActivated(true, isCorrect);		// Активируем точку и 2 точки от нее вверх 	
						user[y - 2][x].SetActivated(true, isCorrect);		// Описываем их некоректными
					}




					if (isMontage == 3 && isCorrect)						// Если монтаж в стадии 3
					{
						user[y][x].SetStatus(3);							//
						user[y - 1][x].SetStatus(3);						// Монтируем корабль 
						user[y - 2][x].SetStatus(3);						//
						MontageVariator++;									// Переключаем вариатор на следующий вариант
						setQuality(XXXX, MontageVariator);					// Вызываем функцию настройки состояния
						isMontage = 0;										// Переводим стадию монтажа на ноль
						gorisont = true;									// Возвращаем горизонт наместо
					}

				}
				if (y == 9 && my > user[7][x].GetPositionY() + user[7][x].GetSize() / 2)								// При проверке 9 го поля если мышь по У ниже 6-го поля на1/2
				{
					if (mx > user[y][x].GetPositionX() && mx < user[y][x].GetPositionX() + user[y][x].GetSize())		// Если мышь по Х попдает в этот столбец
					{
						isCorrect = false;									// Это не корекное положение корабля
						user[y - 2][x].SetActivated(false);					//
						user[y - 1][x].SetActivated(true, isCorrect);		// Активируем 2 нижние клетки по активному столбцу 
						user[y][x].SetActivated(true, isCorrect);			// а также делаем их некоректными
					}
				}
			}
		}
		if (MontageVariator == 3 || MontageVariator == 4 || MontageVariator == 5)	// Обсчет 2-х палубного макета
		{
			if (gorisont)													// Если положение горизонтально
			{
				if (user[y][x].GetActivated() && (x - 1) > -1)				// Если клетка активна и мы не вываливаемся за границу поля
				{
					bool Nixuya = false;									// Переменная для котроля присутствия корабля рядом
					for (int ychek = -1; ychek < 2; ychek++)
					{
						for (int xchek = -2; xchek < 2; xchek++)			// Двойной цикл обсчета положения
						{
							if (x + xchek > -1 && x + xchek < 11)			// Если при проверке мы не вываливаемся за массив по Х	
							{
								if (y + ychek > -1 && y + ychek < 10)		// Если при проверке мы не вываливаемся за массив по У
								{
									if (user[y + ychek][x + xchek].GetStatus() == 3)   // Проверяем наличие корабля
									{
										Nixuya = true;						// Если корабль - нихая нельзя = истина
									}
								}
							}
						}
					}
					if (!Nixuya)											// Если нихуя = ложь
					{
						isCorrect = true;									// Положение коректно
						user[y][x - 1].SetActivated(true);					// Активируем 1 клетки от активной влево
					}
					if (Nixuya)												// Если нихуя = истина
					{
						{
							isCorrect = false;								// Это не кректное положение
							user[y][x].SetActivated(true, isCorrect);		// Активируем  клетку некорректной
							user[y][x - 1].SetActivated(true, isCorrect);	// и клетку слева от неё тоже	
						}
					}

					if (isMontage == 3)										// Если монтаж в стадии 3
					{
						user[y][x].SetStatus(3);							//
						user[y][x - 1].SetStatus(3);						// Монтируем корабль 
						MontageVariator++;									// Переключаем вариатор на следующий вариант
						setQuality(XXXX, MontageVariator);					// Вызываем функцию настройки состояния
						isMontage = 0;										// Переводим стадию монтажа на ноль
					}
				}
				if (user[y][x].GetActivated() && (x - 1) == -1)				// Если клетка активна и мы вываливаемся за границу поля на одну клетку
				{
					isCorrect = false;										// Это не кректное положение
					user[y][x].SetActivated(true, isCorrect);				// Активируем  клетку некорректной
				}
			}
			else if (!gorisont)												// Если положение вертикальное
			{																// Если вентиль макета =0
				if (user[y][x].GetActivated() && (y - 1) > -1)				// Если клетка активна и мы не вываливаемся за границу поля
				{
					bool Nixuya = false;									// Переменная для котроля присутствия корабля рядом
					for (int ychek = -2; ychek < 2; ychek++)
					{
						for (int xchek = -1; xchek < 2; xchek++)			// Двойной цикл поска корабля
						{
							if (x + xchek > -1 && x + xchek < 11)			// Если при опросе мы не вывалимся по Х
							{
								if (y + ychek > -1 && y + ychek < 10)		// Если при опросе мы не вывалимся по У
								{
									if (user[y + ychek][x + xchek].GetStatus() == 3)	// Опрос клетки если там корабль
									{
										Nixuya = true;						// То нихуя = истина
									}
								}
							}
						}
					}
					if (!Nixuya)											// Если нихуя = ложь
					{
						isCorrect = true;									// это коректное положение
						user[y - 1][x].SetActivated(true);					// Активируем сверху клетку 
					}
					if (Nixuya)												// Если Нихуя = истина
					{
						{
							isCorrect = false;								// Это не кректное положение
							user[y][x].SetActivated(true, isCorrect);		// Активируем  клетку некорректной
							user[y - 1][x].SetActivated(true, isCorrect);	// Активируем  клетку сверху некорректной
						}
					}


					if (isMontage == 3)										// Если монтаж в стадии 3
					{
						user[y][x].SetStatus(3);							//
						user[y - 1][x].SetStatus(3);						// Монтируем корабль 
						MontageVariator++;									// Переключаем вариатор на следующий вариант
						setQuality(XXXX, MontageVariator);					// Вызываем функцию настройки состояния
						isMontage = 0;										// Переводим стадию монтажа на ноль
						gorisont = true;									// Возвращаем горизонт наместо
					}

				}
				if (y == 9 && my > user[8][x].GetPositionY() + user[8][x].GetSize() / 3)								// При проверке 9 го поля если мышь по У ниже 6-го поля на1/2
				{
					if (mx > user[y][x].GetPositionX() && mx < user[y][x].GetPositionX() + user[y][x].GetSize())		// Если мышь по Х попдает в этот столбец
					{
						isCorrect = false;									// Это не корекное положение корабля
						user[y][x].SetActivated(true, isCorrect);			// Активируем клетку некоректной
					}
				}
			}
		}
		if (MontageVariator == 6 || MontageVariator == 7 || MontageVariator == 8 || MontageVariator == 9)	// Обсчет 1-х палубного макета
		{
			if (user[y][x].GetActivated())									// Если клетка активна 
			{
				bool Nixuya = false;										// Переменная для котроля присутствия корабля рядом
				for (int ychek = -1; ychek < 2; ychek++)
				{
					for (int xchek = -1; xchek < 2; xchek++)				// Двойной цикл обсчета
					{
						if (x + xchek > -1 && x + xchek < 11)				// Если не вываливаемся по Х
						{
							if (y + ychek > -1 && y + ychek < 10)			// И не вываливаемся по У
							{
								if (user[y + ychek][x + xchek].GetStatus() == 3)  // Проверяем наличие корабля
								{
									Nixuya = true;							// Если он есть - Нихуя = истина
								}
							}
						}
					}
				}
				if (!Nixuya)												// Если нихуя - ложь
				{
					isCorrect = true;										// Это коректно
					user[y][x].SetActivated(true, isCorrect);				// активируем клетку
				}
				if (Nixuya)													// Если нихуя = истина
				{
					{
						isCorrect = false;									// Это не кректное положение
						user[y][x].SetActivated(true, isCorrect);			// Активируем  клетку некорректной
					}
				}
				if (isMontage == 3)											// Если монтаж в стадии 3
				{											
					user[y][x].SetStatus(3);								// Монтируем корабль 
					MontageVariator++;										// Переключаем вариатор на следующий вариант
					setQuality(XXXX, MontageVariator);						// Вызываем функцию настройки состояния
					isMontage = 0;											// Переводим стадию монтажа на ноль
					if (MontageVariator > 9)								// Если вариатор прешагнул 9 вариантов
					{
						ShipMontage = false;								// Если все корабли расставлены = вывалится из монтажа
					}
				}
			}

		}
	}
	
