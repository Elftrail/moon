#include "HodUSer.h"


void HodUser(Point**oponent, sf::Event& event, bool& GameHod, int y, int x, int &isMontage,int(&Global_DaedhUser)[10][2], Sound* SOUND)
{
	if (GameHod) 
	{
		if (event.type == sf::Event::MouseButtonPressed)								// Первый клик мыши по кораблю при стадии монтажа = 0
		{
			if (event.key.code == sf::Mouse::Left)										// А именно левой кнопкой
			{
				isMontage = 1;														// перевод монтажа на стадию = 1
			}
		}
		if (event.type == sf::Event::MouseButtonReleased && isMontage == 1)
		{
			if (event.key.code == sf::Mouse::Left)										// А именно левой кнопкой
			{
				if (oponent[y][x].GetActivated() && oponent[y][x].GetStatus() != 1 && oponent[y][x].GetStatus() != 2)
				{
					switch (oponent[y][x].GetStatus())
					{
					case 0:
					{
						SOUND[4].play();
						oponent[y][x].SetStatus(1);
						GameHod = !GameHod;
						
						break;
					}
					case 3:
					{
						SOUND[3].play();
						oponent[y][x].SetStatus(2);
						
						for (int Y = 0; Y < 10; Y++)
						{
							for (int X = 0; X < 10; X++)
							{
								int CONTI = 0;
								for (int i = 0; i < 10; i++)
								{

									if (Global_DaedhUser[i][0] == Y && Global_DaedhUser[i][1] == X)
									{
										CONTI++;
										break;
									}

								}
								if (CONTI > 0) { CONTI = 0; /*cout << "пропущен обсчет User" << endl*/; continue; }

								int YY = 0;
								int YYSCHET = 0;
								int XX = 0;
								int XXSCHET = 0;
								if (oponent[Y][X].GetStatus() == 2)

								{
									//cout << "Цикл наткнулся на хит в клетке " << Y << "  " << X << endl;
									bool cherprev = true;
									if (Y - 1 > -1)
									{
										if (oponent[Y - 1][X].GetStatus() == 2 || oponent[Y - 1][X].GetStatus() == 3)
										{
											cherprev = false;
											//cout << "проверка превью по игреку отрицательна (не пусто) " << endl;
										}
										else
										{
											//cout << "проверка превью по игреку положительна (пусто) " << endl;
										}

									}
									//else { cout << "проверка превью по игреку положительна (граница) " << endl; }
									if (X - 1 > -1)
									{
										if (oponent[Y][X - 1].GetStatus() == 2 || oponent[Y][X - 1].GetStatus() == 3)
										{
											cherprev = false;
									//		cout << "проверка превью по X отрицательна (не пусто) " << endl;
										}
										else
										{
									//		cout << "проверка превью по X положительна (пусто) " << endl;
										}

									}
									//else { cout << "проверка превью по X положительна (граница) " << endl; }
									//if(!cherprev){ cout << "Превью проверка ОТРИЦАТЕЛЬНА" << endl << endl ; }
									



									if (cherprev)
									{
									//	cout << "Превью проверка положительна Запуск опроса со смещением" << endl;
										for (int smeY = 1; smeY < 4; smeY++)
										{
									//		cout << "Запуск Цикла по У со смещением опрос У+ " << smeY << endl;
											if (Y + smeY < 10)
											{
												if (oponent[Y + smeY][X].GetStatus() == 0 || oponent[Y + smeY][X].GetStatus() == 1)
												{
										//			cout << "цикл Y наткнулся на войд или мис и завершил работу с кодом  0 и счетчиком  " << YYSCHET << endl;
													YY = 0;
													break;
												}
												if (oponent[Y + smeY][X].GetStatus() == 3)
												{
											//		cout << "цикл Y наткнулся на корабль и завершил работу с кодом  -1 " << endl;
													YY = -1;
													break;
												}
												if (oponent[Y + smeY][X].GetStatus() == 2)
												{
													YYSCHET++;
												//	cout << "цикл Y наткнулся на хит и продолжил работу со счетчиком " << YYSCHET << endl;
												}


											}
											else
											{
												YY = 0;																			// Проврка по У +
												break;
											}
										}
										for (int smeX = 1; smeX < 4; smeX++)
										{
											//cout << "Запуск Цикла по Х со смещением опрос X+ " << smeX << endl;
											if (X + smeX < 10)
											{
												if (oponent[Y][X + smeX].GetStatus() == 0 || oponent[Y][X + smeX].GetStatus() == 1)
												{
												//	cout << "цикл X наткнулся на войд или мис и завершил работу с кодом  0 и счетчиком  " << YYSCHET << endl;
													XX = 0;
													break;
												}
												if (oponent[Y][X + smeX].GetStatus() == 3)
												{
													//cout << "цикл X наткнулся на корабль и завершил работу с кодом  -1 " << endl;
													XX = -1;
													break;
												}
												if (oponent[Y][X + smeX].GetStatus() == 2)
												{
													XXSCHET++;
													//cout << "цикл X наткнулся на хит и продолжил работу со счетчиком " << YYSCHET << endl;
												}
											}else
											{
												XX = 0;																			// Проврка по У +
												break;
											}
										}
										if (YY == 0 && XX == 0)																		// Если обход завершен с кодом 00
										{
											//cout << "С КОДОМ 00. начата обработка пустых клеток вокруг затопленного корабля " << endl;
											//cout << "==================================================================== " << endl;
											//cout << "=================КОРАБЛЬ++ЗАТОПЛЕН================================== " << endl;
											//cout << "==================================================================== " << endl;
											SOUND[5].play();
											for (int i = 0; i < 10; i++)
											{
												if (Global_DaedhUser[i][0] == -1)
												{
													Global_DaedhUser[i][0] = Y;
													Global_DaedhUser[i][1] = X;

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
															if (oponent[Y + ykor][X + xkor].GetStatus() == 0)							// Если наткнулись на войд
															{
																oponent[Y + ykor][X + xkor].SetStatus(1);								// ставим там мис
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
															if (oponent[Y + ykor][X + xkor].GetStatus() == 0)							// Если наткнулись на войд
															{
																oponent[Y + ykor][X + xkor].SetStatus(1);								// ставим там мис
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
															if (oponent[Y + ykor][X + xkor].GetStatus() == 0)							// Если наткнулись на войд
															{
																oponent[Y + ykor][X + xkor].SetStatus(1);								// ставим там мис
															}
														}
													}
												}
											}

										}
										else
										{
											//cout << "С КОДОМ  Y " << YY << "X " << XX << " Корабль не затоплен" << endl;
										}
									}




									//cout << "=================Конец проверки хита==================================" << endl << endl << endl;
									
								}
								




							}
						}
						break;
					}
					}
				}
				isMontage = 0;														// перевод монтажа на стадию = 1
			}
		}

	}


}
