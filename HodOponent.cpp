#include "HodOponent.h"
random_device system_random;						// Вводим переменную для рандома

//After_Bang 
//              ЯЧЕЙКА						||		ЗНАЧЕНИЕ
// 
// [0] - Активация записи предыдущего хода__-1 нет поврежденных кораблей  
//___________________________________________1 есть данные предыдущего попадания
// 
// [1] - Ось стрельбы_______________________-1 Ось не определена 
//__________________________________________ 1 Ось Х
//__________________________________________ 2 Ось У
// 
// [2] - Направление стрельбы_______________-1 Направление не определено
//__________________________________________ 1 Направление +
//__________________________________________ 2 Направление -
// 
// [3] - Координаты предыдущего попадания У_-1 Координаты отсутствуют
//__________________________________________ 0-9 Координата
// 
// [4] - Координаты предыдущего попадания Х -1 Координаты отсутствуют
//___________________________________________0-9 Координата
// [5]										 РЕЗЕРВ
// [6]										 РЕЗЕРВ
// [7]										 РЕЗЕРВ
// [8]										 РЕЗЕРВ
void after_bang(int Y, int X, int* After_Bang, Point** user, int& bangY,int& bangX)
{	

	//cout << " Старт обработки следуещего хода противника ";
	//cout << " с кодом After_Bang : " << endl;
	/*for (int i = 0; i < 9; i++)
	{
		cout << "' " << After_Bang[i] << " ' ";
	}
	cout << endl;*/


	//Производим проверки по границам полей у клетки предыдущего попадания
	bool prox_plus = true;
	bool prox_minus = true;
	bool proy_plus = true;
	bool proy_minus = true;
	//по У
	if (After_Bang[3] + 1 > 9) { proy_plus = false; }
	if (After_Bang[3] - 1 < 0) { proy_minus = false; }
	//по Х
	if (After_Bang[4] + 1 > 9) { prox_plus = false; }
	if (After_Bang[4] - 1 < 0) { prox_minus = false; }
	//Пытаемся определить ось следующей атаки

	// ищем попадания рядом
	if (After_Bang[1] == -1) 
	{// по игреку
		//cout << " Ось стрельбы не определена. Запуск поиска оси по хитам рядом " << endl;
		if (proy_plus) 
		{
			if (user[After_Bang[3] + 1][After_Bang[4]].GetStatus() == 2) 
			{
				After_Bang[1] = 2; 
				//cout << " Ось стрельбы установлена по У(по У+1 от прошлого попадания ХИТ) " << endl;
			}
			
		}
		if (proy_minus)
		{
			if (user[After_Bang[3] - 1][After_Bang[4]].GetStatus() == 2) 
			{
				After_Bang[1] = 2;
			//cout << " Ось стрельбы установлена по У (по У-1 от прошлого попадания ХИТ) " << endl;
			}
			
		}
		// по Х
		if (prox_plus)
		{
			if (user[After_Bang[3]][After_Bang[4]+1].GetStatus() == 2)
			{
				After_Bang[1] = 1;
				//cout << " Ось стрельбы установлена по Х(по Х+1 от прошлого попадания ХИТ) " << endl;
			}
			
		}
		if (prox_minus)
		{
			if (user[After_Bang[3]][After_Bang[4]-1].GetStatus() == 2) 
			{
				After_Bang[1] = 1;
			//cout << " Ось стрельбы установлена по Х (по Х-1 от прошлого попадания ХИТ) " << endl;
			}
			
		}
		if (After_Bang[1] == -1)
		{
			//cout << " Ось стрельбы по хитам не определена. Запуск поиска оси по мисам и границам " << endl;
			
			//опрос по У
			if (proy_plus&&user[After_Bang[3] + 1][After_Bang[4]].GetStatus() == 1||!proy_plus)
			{
				if (proy_minus && user[After_Bang[3] - 1][After_Bang[4]].GetStatus() == 1||!proy_minus)
				{
					After_Bang[1] = 1;
					//cout << " Ось стрельбы установлена по Х " << endl;
				}
			}
			// опрос по X
			if (prox_plus && user[After_Bang[3]][After_Bang[4]+1].GetStatus() == 1 ||!prox_plus)
			{
				if (prox_minus && user[After_Bang[3]][After_Bang[4]-1].GetStatus() == 1 || !prox_minus)
				{
					After_Bang[1] = 2;
					//cout << " Ось стрельбы установлена по Y " << endl;
				}
			}
		}
	}
	//если ось не определили
	if (After_Bang[1] == -1)
	{
		//cout << " Ось стрельбы установить не удалось. Активирована рандомная стельба по ближайшим возможным клеткам " << endl;
		int seed = system_random();
		srand(seed);
		bool rest_rand = false;

		do {
			rest_rand = false;
			int napr = rand() % 4;
			switch (napr)
			{
			case 0:
				//cout << " Рандомный выстрел влево " << endl;
				if (prox_minus)
				{
					bangX = After_Bang[4] - 1;
					bangY = After_Bang[3];
					if (user[bangY][bangX].GetStatus() == 1)
					{
						rest_rand = true;
						//cout << " Ошибка выстрела влево - в клетке уже МИС. РЕСТАРТ РАНДОМА " << endl;
					}

				}
				else if (!prox_minus)
				{
					rest_rand = true;
					//cout << " Ошибка выстрела влево - граница поля. РЕСТАРТ РАНДОМА " << endl;
				}
				break;
			case 1:
				//cout << " Рандомный выстрел вверх " << endl;
				if (proy_minus)
				{
					bangX = After_Bang[4];
					bangY = After_Bang[3]-1;
					if (user[bangY][bangX].GetStatus() == 1)
					{
						rest_rand = true;
					//cout << " Ошибка выстрела вверх - в клетке уже МИС. РЕСТАРТ РАНДОМА " << endl;
					}

				}
				else if (!proy_minus)
				{
					rest_rand = true;
					//cout << " Ошибка выстрела вверх - граница поля. РЕСТАРТ РАНДОМА " << endl;
				}
				break;
			case 2:
				//cout << " Рандомный выстрел вправо " << endl;
				if (prox_plus)
				{
					bangX = After_Bang[4] + 1;
					bangY = After_Bang[3];
					if (user[bangY][bangX].GetStatus() == 1)
					{
						rest_rand = true;
						//cout << " Ошибка выстрела вправо - в клетке уже МИС. РЕСТАРТ РАНДОМА " << endl;
					}

				}
				else if (!prox_plus)
				{
					rest_rand = true;
					//cout << " Ошибка выстрела вправо - граница поля. РЕСТАРТ РАНДОМА " << endl;
				}
				break;
			case 3:
				//cout << " Рандомный выстрел вниз " << endl;
				if (proy_plus)
				{
					bangX = After_Bang[4];
					bangY = After_Bang[3]+1;
					if (user[bangY][bangX].GetStatus() == 1)
					{
						rest_rand = true;
					//	cout << " Ошибка выстрела вниз - в клетке уже МИС. РЕСТАРТ РАНДОМА " << endl;
					}

				}
				else if (!proy_plus)
				{
					rest_rand = true;
				//	cout << " Ошибка выстрела вниз - граница поля. РЕСТАРТ РАНДОМА " << endl;
				}
				break;
			default:
				break;
			}
		}while (rest_rand);

	}


	// если определили ось Х
	if (After_Bang[1] == 1/*&&After_Bang[2]==-1*/)
	{
		//cout << " Запуск учета предыдущих ХИТОВ " << endl;
		//
		//cout << " Проверка состояний НАПРАВЛЕНИЯ СТРЕЛЬБЫ " << endl;
		if(After_Bang[2] == -1)
		{
			//cout << "1.Напрвление не задано. Запуск установки направления стрельбы по оси в +" << endl;
			for (int i = 0; i < 6; i++)
			{
				if (After_Bang[4] + i > 9)
				{
					After_Bang[2] = 2;
					//cout << " Проврка завершена по X+. Уперлись в границу. Нарпкаление установлено в X- " << endl;
					break;
				}
				if (user[After_Bang[3]][After_Bang[4]+i].GetStatus()==1)
				{
					After_Bang[2] = 2;
					//cout << " Проврка завершена поX +. Уперлись в МИС. Нарпкаление установлено в X- " << endl;
					break;
				}
				if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 0|| user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 3)
				{
					//cout << " Проврка завершена по X+. Уперлись в ВОИД или КОРАБЛЬ. Нарпкаление не установлено " << endl;
					break;
				}
				
			}
		}
		if ( After_Bang[2] == -1)
		{
			//cout << "2. Напрвление не задано. Запуск установки направления стрельбы по оси в - " << endl;
			for (int i = 0; i > -6; i--)
			{
				if (After_Bang[4] + i < 0)
				{
					After_Bang[2] = 1;
					//cout << "2,1 Проврка завершена по X-. Уперлись в границу. Нарпкаление установлено в + " << endl;
					break;
				}
				if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 1)
				{
					After_Bang[2] = 1;
					//cout << "2,2 Проврка завершена по X-. Уперлись в МИС. Нарпкаление установлено в + " << endl;
					break;
				}
				if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 0|| user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 3)
				{
					//cout << "2,3 Проврка завершена по X -. Уперлись в ВОИД или КОРАБЛЬ. Нарпкаление не установлено " << endl;
					break;
				}
			}
		}

	}
	if (After_Bang[2] == -1) 
	{
		bool REST = false;
		//cout << " 3,Установить направление стрельбы по клеткам радом не удалось. " << endl;
		do {
			REST = false;
			int napr = rand() % 2;
			switch (napr)
			{
			case 0:
			//	cout << " Установлено случайное направление + " << endl;
				After_Bang[2] = 1;
				break;
			case 1:
			//	cout << " Установлено случайное направление - " << endl;
				After_Bang[2] = 2;
				break;

			default:
				REST = true;
				break;
			}

		} while (REST);
	}

		//bool REST = false;
		
		if (After_Bang[1] == 1)
		{
			bool REST = false;
			//cout << "Расчет СТРЕЛЬБЫ по ПРЕДУСТАНОВЛЕННОЙ оси Х " << endl;
			do {
				REST = false;
				if (After_Bang[2] == 1)
				{
					//cout << " Запуск обработки следующего выстрела по ПРЕДУСТАНОВЛЕННОМУ НАПРВЛЕНИЮ X+ " << endl;
						
						for (int i = 1; i < 5; i++)
						{
							if (After_Bang[4] + i < 10)
							{
								if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 2)
								{
									//cout << "наткнулись на хит по Х+"<<i << endl;
								
								}
								if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 1)
								{
								//	cout << "наткнулись на МИС по Х+" << i << endl;
								//	cout << "РЕВЕРС НАПРАВЛЕНИЯ" << endl;
									After_Bang[2] = 2;
									REST = true;
									break;
								}
								if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 0|| user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 3)
								{
									//cout << "наткнулись на неизвесную клетку по Х+" << i << endl;
									//cout << "Выстрел производим по неизвесной клетке" << endl;
									bangX = After_Bang[4] + i;
									bangY = After_Bang[3];
									break;
								}

							}
							else 
							{ 
								//cout << "Расчет по Х+ уперся в границу РЕВЕРС НАПРАВЛЕНИЯ" << endl;
								After_Bang[2] = 2;
								REST = true;
								break;
							}
						}

					


				}
				
				if (After_Bang[2] == 2)
				{
					//cout << " Запуск обработки следующего выстрела по ПРЕДУСТАНОВЛЕННОМУ НАПРВЛЕНИЮ X- " << endl;
						for (int i = -1; i > -5; i--)
						{
							if (After_Bang[4] + i > -1)
							{
								if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 2)
								{
									//cout << "наткнулись на хит по Х-" << i << endl;
									//continue;
								}
								if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 1)
								{
									//cout << "наткнулись на МИС по Х-" << i << endl;
									//cout << "РЕВЕРС НАПРАВЛЕНИЯ" << endl;
									After_Bang[2] = 1;
									REST = true;
									break;
								}
								if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 0 || user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 3)
								{
									//cout << "наткнулись на неизвесную клетку по Х-" << i << endl;
									//cout << "Выстрел производим по неизвесной клетке" << endl;
									bangX = After_Bang[4] + i;
									bangY = After_Bang[3];
									break;
								}

							}
							else
							{
								//cout << "Расчет по Х- уперся в границу РЕВЕРС НАПРАВЛЕНИЯ" << endl;
								After_Bang[2] = 1;
								REST = true;
								break;
							}
						}
					
				}
			} while (REST);
		}


		if (After_Bang[1] == 2)
		{
			bool REST = false;
			//cout << "Расчет СТРЕЛЬБЫ по ПРЕДУСТАНОВЛЕННОЙ оси Y " << endl;
			do {
				REST = false;
				if (After_Bang[2] == 1)
				{
				//	cout << " Запуск обработки следующего выстрела по ПРЕДУСТАНОВЛЕННОМУ НАПРВЛЕНИЮ У+ " << endl;
					
						for (int i = 1; i < 5; i++)
						{
							if (After_Bang[3] + i < 10)
							{
								if (user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 2)
								{
								//	cout << "наткнулись на хит по Y+" << i << endl;
									//continue;
								}
								if (user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 1)
								{
								//	cout << "наткнулись на МИС по Y+" << i << endl;
								//	cout << "РЕВЕРС НАПРАВЛЕНИЯ" << endl;
									After_Bang[2] = 2;
									REST = true;
									break;
								}
								if (user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 0 || user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 3)
								{
								//	cout << "наткнулись на неизвесную клетку по Y+" << i << endl;
								//	cout << "Выстрел производим по неизвесной клетке" << endl;
									bangX = After_Bang[4];
									bangY = After_Bang[3]+i;
									break;
								}

							}
							else
							{
							//	cout << "Расчет по Y+ уперся в границу РЕВЕРС НАПРАВЛЕНИЯ" << endl;
								After_Bang[2] = 2;
								REST = true;
								break;
							}
						}

					//}


				}

				if (After_Bang[2] == 2)
				{
					//cout << " Запуск обработки следующего выстрела по ПРЕДУСТАНОВЛЕННОМУ НАПРВЛЕНИЮ У+ " << endl;
					
						for (int i = -1; i > -5; i--)
						{
							if (After_Bang[3] + i > -1)
							{
								if (user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 2)
								{
								//	cout << "наткнулись на хит по Y-" << i << endl;
									//continue;
								}
								if (user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 1)
								{
								//	cout << "наткнулись на МИС по Y-" << i << endl;
								//	cout << "РЕВЕРС НАПРАВЛЕНИЯ" << endl;
									After_Bang[2] = 1;
									REST = true;
									break;
								}
								if (user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 0 || user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 3)
								{
								//	cout << "наткнулись на неизвесную клетку по Y-" << i << endl;
								//	cout << "Выстрел производим по неизвесной клетке" << endl;
									bangX = After_Bang[4];
									bangY = After_Bang[3]+i;
									break;
								}

							}
							else
							{
								//cout << "Расчет по Y- уперся в границу РЕВЕРС НАПРАВЛЕНИЯ" << endl;
								After_Bang[2] = 1;
								REST = true;
								break;
							}
						}



				}



			} while (REST);

		}


















	//cout << "Обработка завершена с кодом After_Bang : " << endl;
	//for ( int i = 0; i <9; i++)
	//{
	//	cout <<"' " << After_Bang[i] << " ' ";
	//}
	//cout  << endl;
	//cout <<"Следующий выстрел произведется по клетке Y " << bangY<<" X "<<bangX << endl;


}

int HodOponent(Point** user, sf::Event& event, bool& GameHod, int& isMontage, int(&Global_Daedh)[10][2], int* After_Bang, int* PrevBangAnimation, Sound* SOUND)
{
			
	for (int i = 0; i < 2; i++)						// Записываем в строку состояния выстрела
	{
		PrevBangAnimation[i] = -1;
	}												
	if (!GameHod)									// Если ход противника
	{
		bool restart;								// Обьявляем переменную рестарта
		int seed = system_random();					// Обьявляем переменную для хранения рандома
		int bangX = -1;
		int bangY = -1;



		srand(seed);								// Вызываем сранд	
		do
		{
			restart = false;						// Выключаем рестарт

			if (After_Bang[0] == -1)
			{
				bangX = rand() % 10;				// Рандомный столбец
				bangY = rand() % 10;				// Рандомная строка
				//cout << " Предыдущего попадания небыло. произведен случайный выстрел" << endl;
			}


			if (After_Bang[0] == 1)
			{
				//cout << " в базе есть предыдущее попадание . запись функции следующего удара" << endl;
				after_bang(After_Bang[3], After_Bang[4], After_Bang, user,bangY,bangX);
			}


			switch (user[bangY][bangX].GetStatus())	// Обьявлям набор свичей для интерпритации рандомных значений	
			{
			case 0:									// Если в рандомной клетке пусто
			{
				//cout << " ===============МИМО============================" << endl;
				SOUND[4].play();
				user[bangY][bangX].SetStatus(1);	// Записываем в клетку "Мимо"	
				GameHod = !GameHod;					// Переводим ход к игроку
				PrevBangAnimation[0] = bangY;
				PrevBangAnimation[1] = bangX;
				break;								// Выпадаем из свича

			}
			case 3:									// Если в клетке корабль
			{
				//cout << " ===============ПОПАДАНИЕ============================" << endl;
				SOUND[3].play();
				After_Bang[0] = 1;					// Активация ИИ противника	
				After_Bang[3] = bangY;				// запись в значений выстрела по У
				After_Bang[4] = bangX;				// И по Х тоже
				PrevBangAnimation[0] = bangY;
				PrevBangAnimation[1] = bangX;
				user[bangY][bangX].SetStatus(2);	// Записываем в клетку попадание

				

				//cout << " ===============начало опроса затопления============================" << endl;
				for (int Y = 0; Y < 10; Y++)		// Запускаем обход на предмет утопленых кораблей
				{
					int CONTI = 0;								//
					for (int X = 0; X < 10; X++)	//
					{
						
						
						for (int i = 0; i < 10; i++)
						{
							
								if (Global_Daedh[i][0] == Y && Global_Daedh[i][1] == X)
								{
									CONTI++;
									break;
								}
							
						}
						if (CONTI > 0) { /*cout << "ранее затопленных кораблей учтено =" << CONTI<<endl;*/ CONTI = 0; continue; }
						//cout << "итерация опроса  = " << Y << X << endl;

						int YY = -5;																			// Преременная для кода завершения опроса 
						int YYSCHET = 0;																	// Преременная- счетчик для кода завершения опроса 
						int XX = -5;																			// Преременная для кода завершения опроса 
						int XXSCHET = 0;																	// Преременная- счетчик для кода завершения опроса
						if (user[Y][X].GetStatus() == 2)                                                    // Если натыкаемся на ХИТ
						{
							//cout << "проверка предыдущего хита по У" << endl;
							bool cherprev = true;															// Инициализируем проверку Клеток пред обрабатываемой 
							if (Y - 1 > -1)																	// Если не вываливаемся за границу
							{
								//cout << "проверка предыдущего хита по У прошла проврку по границе" << endl;
								if (user[Y - 1][X].GetStatus() == 2 || user[Y - 1][X].GetStatus() == 3)		// Если натыкаемся на ХИТ или Корабль
								{
									//cout << "проверка предыдущего хита по У завершена ЛОЖЬЮ " << endl;
									cherprev = false;														// Чек превью по У 
								}
							}
							
							//cout << "проверка предыдущего хита по Х" << endl;
							if (X - 1 > -1)																	// Если не вываливаемся за границу по Х
							{
								//cout << "проверка предыдущего хита по Х прошла проврку по границе" << endl;
								if (user[Y][X - 1].GetStatus() == 2 || user[Y][X - 1].GetStatus() == 3)		// Если натыкаемся на ХИТ или Корабль
								{
									//cout << "проверка предыдущего хита по Х завершена ЛОЖЬЮ " << endl;
									cherprev = false;														// Чек по Х -
								}
							}
							else {/* cout << "проверка предыдущего хита по Х положительна - граница " << endl; */}

							if (cherprev)																	// Если превью проверка ++
							{
								//cout << "ПРЕВЬЮ проверка завершена положительно. запуск обхода со смещением по У " << endl;
								for (int smeY = 1; smeY < 5; smeY++)										// Запуск Цикла по У со смещением опрос У+
								{
									//cout << "итерация смещения = y + "<< smeY << endl;
									
									if (Y + smeY < 10)														// Если не вываливаемся за границу
									{
										//cout << " У проверка на границу при смещении пройдена " << endl;
										if (user[Y + smeY][X].GetStatus() == 0 || user[Y + smeY][X].GetStatus() == 1)		// Если нткнулись на пустоту
										{
											//cout << " У проверка со смещением завершена с кодом 0 - наткнулись на мис или войд " << endl;
											YY = 0;																			// Проврка по У +
											break;
										}
										if (user[Y + smeY][X].GetStatus() == 3)												// Если натыкаемся на корабль 
										{
											//cout << " У проверка со смещением завершена с кодом -1 - наткнулись на корабль " << endl;
											YY = -1;																		// Проврка по У -
									
											break;

										}
										if (user[Y + smeY][X].GetStatus() == 2)												// Если наткнулись на ХИТ
										{
											//cout << " У проверка со смещением наткнулась на ХИТ. продолжаем проверку" << endl;
											YYSCHET++;																		// Продолжаем обход с инкрементацией счечика
										}
										


									}
									else
									{
										//cout << " У проверка со смещением завершена с кодом 0  наткнулись на границу " << endl;
										YY = 0;																			// Проврка по У +
										break;
									}
								}
								//cout << "итерация смещения по У завершена. начало смещения по Х"  << endl;
								for (int smeX = 1; smeX < 5; smeX++)														// Запуск Цикла по Х со смещением опрос Х+
								{
									//cout << "итерация смещения = Х + " << smeX << endl;
									if (X + smeX < 10)																		// Если не вываливаемся за границу
									{
										if (user[Y][X + smeX].GetStatus() == 0 || user[Y][X + smeX].GetStatus() == 1)		// Если нткнулись на пустоту
										{
											XX = 0;																			// Проврка по Х +
											break;
											//cout << " X проверка со смещением завершена с кодом 0 - наткнулись на мис или войд " << endl;
										}
										if (user[Y][X + smeX].GetStatus() == 3)												// Если натыкаемся на корабль
										{
											//cout << " У проверка со смещением завершена с кодом -1 - наткнулись на корабль " << endl;
											XX = -1;																		// Проврка по Х -

											break;
										}
										if (user[Y][X + smeX].GetStatus() == 2)												// Если наткнулись на ХИТ
										{
											//cout << " У проверка со смещением наткнулась на ХИТ. продолжаем проверку" << endl;
											XXSCHET++;																		// Продолжаем обход с инкрементацией счечика
										}
									}
									else
									{
										//cout << " Х проверка со смещением завершена с кодом 0 - наткнулись на границу " << endl;
										XX = 0;																			// Проврка по У +
										break;
									}

								}
								//cout << "ПРОВЕРКА СМЕЩЕНИЯ ЗАВЕРШЕНА ";
								if (YY == 0 && XX == 0)																		// Если обход завершен с кодом 00
								{
									//cout << "С КОДОМ 00. начата обработка пустых клеток вокруг затопленного корабля " << endl;
									//cout << "==================================================================== " << endl;
									//cout << "=================КОРАБЛЬ++ЗАТОПЛЕН================================== " << endl;
									//cout << "==================================================================== " << endl;
									SOUND[5].play();

									After_Bang[0] = -1;
									for (int i = 0; i < 10; i++)
									{
										if (Global_Daedh[i][0] == -1)
										{
											Global_Daedh[i][0] = Y;
											Global_Daedh[i][1] = X;
											
											break;
										}
									}
									
									
									if (YYSCHET > 0)																		// Если счетчик хитов по у больше 0
									{
										for (int xkor = -1; xkor < 2; xkor++)												// Перебираем клетки вокрук хитов
										{
											for (int ykor = -1; ykor < YYSCHET + 2; ykor++)
											{
												if (Y + ykor > -1 && Y + ykor<10 && X + xkor>-1 && X + xkor < 10)			// Если не вываливаемся
												{
													if (user[Y + ykor][X + xkor].GetStatus() == 0)							// Если наткнулись на войд
													{
														user[Y + ykor][X + xkor].SetStatus(1);								// ставим там мис
													}
												}
											}
										}
									}
									else if (XXSCHET > 0)																	// Если счетчик хитов по Х больше 0
									{
										for (int ykor = -1; ykor < 2; ykor++)												// Перебираем клетки вокрук хитов
										{
											for (int xkor = -1; xkor < XXSCHET + 2; xkor++)
											{
												if (Y + ykor > -1 && Y + ykor<10 && X + xkor>-1 && X + xkor < 10)			// Если не вываливаемся
												{
													if (user[Y + ykor][X + xkor].GetStatus() == 0)							// Если наткнулись на войд
													{
														user[Y + ykor][X + xkor].SetStatus(1);								// ставим там мис
													}
												}
											}
										}
									}
									else if (XXSCHET == 0 && YYSCHET == 0)													// Если счетчики хитов ==0 значит это 1-пал-к 
									{
										for (int ykor = -1; ykor < 2; ykor++)												// Перебираем клетки вокрук хитов
										{
											for (int xkor = -1; xkor < 2; xkor++)
											{
												if (Y + ykor > -1 && Y + ykor<10 && X + xkor>-1 && X + xkor < 10)			// Если не вываливаемся
												{
													if (user[Y + ykor][X + xkor].GetStatus() == 0)							// Если наткнулись на войд
													{
														user[Y + ykor][X + xkor].SetStatus(1);								// ставим там мис
													}
												}
											}
										}
									}

								}
								else 
								{
									//cout << "С КОДОМ  Y "<<YY<<"X "<<XX << " Корабль не затоплен" << endl;
								}
							}
						}
					}
				}
				break;
			}
			default:								// Если в клетке другие значения
			{
				restart = true;						// Активируем рестарт
				break;								// Выпадаем из свича
			}
			}


		} while (restart);							// Если рестарт активен- перезапускаем цикл


	}
	
	if (After_Bang[0] == -1)
	{
		//cout << " Состояние AFTER BANG : " << endl;
		for (int i = 0; i < 9; i++)
		{
			After_Bang[i] = -1;
		//	cout << After_Bang[i];
		}
		//cout << endl;
	}
		return 1;
	}

