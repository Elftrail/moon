#include "HodUSer.h"


void HodUser(Point**oponent, sf::Event& event, bool& GameHod, int y, int x, int &isMontage,int* Global_DaedhUser)
{
	if (GameHod) 
	{
		if (event.type == sf::Event::MouseButtonPressed)								// ������ ���� ���� �� ������� ��� ������ ������� = 0
		{
			if (event.key.code == sf::Mouse::Left)										// � ������ ����� �������
			{
				isMontage = 1;														// ������� ������� �� ������ = 1
			}
		}
		if (event.type == sf::Event::MouseButtonReleased && isMontage == 1)
		{
			if (event.key.code == sf::Mouse::Left)										// � ������ ����� �������
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
								if (CONTI > 0) { CONTI = 0; cout << "�������� ������ User" << endl; continue; }

								int YY = 0;
								int YYSCHET = 0;
								int XX = 0;
								int XXSCHET = 0;
								if (oponent[Y][X].GetStatus() == 2)

								{
									cout << "���� ��������� �� ��� � ������ " << Y << "  " << X << endl;
									bool cherprev = true;
									if (Y - 1 > -1)
									{
										if (oponent[Y - 1][X].GetStatus() == 2 || oponent[Y - 1][X].GetStatus() == 3)
										{
											cherprev = false;
											cout << "�������� ������ �� ������ ������������ (�� �����) " << endl;
										}
										else
										{
											cout << "�������� ������ �� ������ ������������ (�����) " << endl;
										}

									}
									else { cout << "�������� ������ �� ������ ������������ (�������) " << endl; }
									if (X - 1 > -1)
									{
										if (oponent[Y][X - 1].GetStatus() == 2 || oponent[Y][X - 1].GetStatus() == 3)
										{
											cherprev = false;
											cout << "�������� ������ �� X ������������ (�� �����) " << endl;
										}
										else
										{
											cout << "�������� ������ �� X ������������ (�����) " << endl;
										}

									}
									else { cout << "�������� ������ �� X ������������ (�������) " << endl; }
									if(!cherprev){ cout << "������ �������� ������������" << endl << endl ; }
									



									if (cherprev)
									{
										cout << "������ �������� ������������ ������ ������ �� ���������" << endl;
										for (int smeY = 1; smeY < 4; smeY++)
										{
											cout << "������ ����� �� � �� ��������� ����� �+ " << smeY << endl;
											if (Y + smeY < 10)
											{
												if (oponent[Y + smeY][X].GetStatus() == 0 || oponent[Y + smeY][X].GetStatus() == 1)
												{
													cout << "���� Y ��������� �� ���� ��� ��� � �������� ������ � �����  0 � ���������  " << YYSCHET << endl;
													YY = 0;
													break;
												}
												if (oponent[Y + smeY][X].GetStatus() == 3)
												{
													cout << "���� Y ��������� �� ������� � �������� ������ � �����  -1 " << endl;
													YY = -1;
													break;
												}
												if (oponent[Y + smeY][X].GetStatus() == 2)
												{
													YYSCHET++;
													cout << "���� Y ��������� �� ��� � ��������� ������ �� ��������� " << YYSCHET << endl;
												}


											}
										}
										for (int smeX = 1; smeX < 4; smeX++)
										{
											cout << "������ ����� �� � �� ��������� ����� X+ " << smeX << endl;
											if (X + smeX < 10)
											{
												if (oponent[Y][X + smeX].GetStatus() == 0 || oponent[Y][X + smeX].GetStatus() == 1)
												{
													cout << "���� X ��������� �� ���� ��� ��� � �������� ������ � �����  0 � ���������  " << YYSCHET << endl;
													XX = 0;
													break;
												}
												if (oponent[Y][X + smeX].GetStatus() == 3)
												{
													cout << "���� X ��������� �� ������� � �������� ������ � �����  -1 " << endl;
													XX = -1;
													break;
												}
												if (oponent[Y][X + smeX].GetStatus() == 2)
												{
													XXSCHET++;
													cout << "���� X ��������� �� ��� � ��������� ������ �� ��������� " << YYSCHET << endl;
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
											cout << "�������� ����� �������� � ����� 00 - ��������� ������ ����� ������ �������"  << endl;
											
											if (YYSCHET > 0) 
											{
												cout << "������ ������� ����� �� �" << endl;
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
												cout << "������ ������� ����� �� X" << endl;
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
												cout << "������ ������� ����� ������ ����� ������" << endl;
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
											cout << "�������� ����� �������� � ����� -10 ������� �� � ������� �� �����" << endl;

										}
										else if (YY == 0 && XX == -1)
										{
											cout << "�������� ����� �������� � ����� -01 ������� �� � ������� �� �����" << endl;

										}
									}




									cout << "=================����� �������� ����==================================" << endl << endl << endl;
									
								}
								




							}
						}
						break;
					}
					}
				}
				isMontage = 0;														// ������� ������� �� ������ = 1
			}
		}

	}


}
