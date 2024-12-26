#include "HodUSer.h"


void HodUser(Point**oponent, sf::Event& event, bool& GameHod, int y, int x, int &isMontage,int* Global_DaedhUser)
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
						oponent[y][x].SetStatus(1);
						GameHod = !GameHod;
						break;
					}
					case 3:
					{
						oponent[y][x].SetStatus(2);
						
						for (int Y = 0; Y < 10; Y++)
						{
							for (int X = 0; X < 10; X++)
							{
								int CONTI = 0;
								for (int i = 0; i < 20; i++)
								{
									if (Global_DaedhUser[i] == Y && Global_DaedhUser[i + 1] == X)
									{
										CONTI++;
										break;
									}
								}
								if (CONTI > 0) { CONTI = 0; cout << "пропущен обсчет User" << endl; continue; }

								int YY = 0;
								int YYSCHET = 0;
								int XX = 0;
								int XXSCHET = 0;
								if (oponent[Y][X].GetStatus() == 2)

								{
									cout << "Цикл наткнулся на хит в клетке " << Y << "  " << X << endl;
									bool cherprev = true;
									if (Y - 1 > -1)
									{
										if (oponent[Y - 1][X].GetStatus() == 2 || oponent[Y - 1][X].GetStatus() == 3)
										{
											cherprev = false;
											cout << "проверка превью по игреку отрицательна (не пусто) " << endl;
										}
										else
										{
											cout << "проверка превью по игреку положительна (пусто) " << endl;
										}

									}
									else { cout << "проверка превью по игреку положительна (граница) " << endl; }
									if (X - 1 > -1)
									{
										if (oponent[Y][X - 1].GetStatus() == 2 || oponent[Y][X - 1].GetStatus() == 3)
										{
											cherprev = false;
											cout << "проверка превью по X отрицательна (не пусто) " << endl;
										}
										else
										{
											cout << "проверка превью по X положительна (пусто) " << endl;
										}

									}
									else { cout << "проверка превью по X положительна (граница) " << endl; }
									if(!cherprev){ cout << "Превью проверка ОТРИЦАТЕЛЬНА" << endl << endl ; }
									



									if (cherprev)
									{
										cout << "Превью проверка положительна Запуск опроса со смещением" << endl;
										for (int smeY = 1; smeY < 4; smeY++)
										{
											cout << "Запуск Цикла по У со смещением опрос У+ " << smeY << endl;
											if (Y + smeY < 10)
											{
												if (oponent[Y + smeY][X].GetStatus() == 0 || oponent[Y + smeY][X].GetStatus() == 1)
												{
													cout << "цикл Y наткнулся на войд или мис и завершил работу с кодом  0 и счетчиком  " << YYSCHET << endl;
													YY = 0;
													break;
												}
												if (oponent[Y + smeY][X].GetStatus() == 3)
												{
													cout << "цикл Y наткнулся на корабль и завершил работу с кодом  -1 " << endl;
													YY = -1;
													break;
												}
												if (oponent[Y + smeY][X].GetStatus() == 2)
												{
													YYSCHET++;
													cout << "цикл Y наткнулся на хит и продолжил работу со счетчиком " << YYSCHET << endl;
												}


											}
										}
										for (int smeX = 1; smeX < 4; smeX++)
										{
											cout << "Запуск Цикла по Х со смещением опрос X+ " << smeX << endl;
											if (X + smeX < 10)
											{
												if (oponent[Y][X + smeX].GetStatus() == 0 || oponent[Y][X + smeX].GetStatus() == 1)
												{
													cout << "цикл X наткнулся на войд или мис и завершил работу с кодом  0 и счетчиком  " << YYSCHET << endl;
													XX = 0;
													break;
												}
												if (oponent[Y][X + smeX].GetStatus() == 3)
												{
													cout << "цикл X наткнулся на корабль и завершил работу с кодом  -1 " << endl;
													XX = -1;
													break;
												}
												if (oponent[Y][X + smeX].GetStatus() == 2)
												{
													XXSCHET++;
													cout << "цикл X наткнулся на хит и продолжил работу со счетчиком " << YYSCHET << endl;
												}
											}
										}
										if (YY == 0 && XX == 0)
										{
											for (int i = 0; i < 20; i++)
											{
												if (Global_DaedhUser[i] == -1)
												{
													Global_DaedhUser[i] = Y;
													Global_DaedhUser[i + 1] = X;

													break;
												}
											}
											cout << "Вложеный опрос завершен с кодом 00 - требуется обсчет мисов вокруг корабля"  << endl;
											
											if (YYSCHET > 0) 
											{
												cout << "Запуск обсчета мисов по У" << endl;
												for (int xkor = -1; xkor < 2; xkor++) 
												{
													for (int ykor = -1; ykor < YYSCHET + 2; ykor++)
													{
														if(Y+ykor>-1&&Y+ykor<10&& X + xkor>-1 && X + xkor < 10)
														{
															if (oponent[Y + ykor][X + xkor].GetStatus() == 0) 
															{
																oponent[Y + ykor][X + xkor].SetStatus(1);
															}
														}
													}
												}
											}
											else if (XXSCHET > 0)
											{
												cout << "Запуск обсчета мисов по X" << endl;
												for (int ykor = -1; ykor < 2; ykor++)
												{
													for (int xkor = -1; xkor < XXSCHET + 2; xkor++)
													{
														if (Y + ykor > -1 && Y + ykor<10 && X + xkor>-1 && X + xkor < 10)
														{
															if (oponent[Y + ykor][X + xkor].GetStatus() == 0)
															{
																oponent[Y + ykor][X + xkor].SetStatus(1);
															}
														}
													}
												}
											}
											else if (XXSCHET == 0 && YYSCHET == 0)
											{
												cout << "Запуск обсчета мисов вокруг одной клетки" << endl;
												for (int ykor = -1; ykor < 2; ykor++)
												{
													for (int xkor = -1; xkor < 2 ; xkor++)
													{
														if (Y + ykor > -1 && Y + ykor<10 && X + xkor>-1 && X + xkor < 10)
														{
															if (oponent[Y + ykor][X + xkor].GetStatus() == 0)
															{
																oponent[Y + ykor][X + xkor].SetStatus(1);
															}
														}
													}
												}

											}

										}
										else if (YY == -1 && XX == 0)
										{
											cout << "Вложеный опрос завершен с кодом -10 впереди по У корабль не добит" << endl;

										}
										else if (YY == 0 && XX == -1)
										{
											cout << "Вложеный опрос завершен с кодом -01 впереди по Х корабль не добит" << endl;

										}
									}




									cout << "=================Конец проверки хита==================================" << endl << endl << endl;
									
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
