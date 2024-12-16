#include "HodOponent.h"
random_device system_random;						// ������ ���������� ��� �������


void HodOponent(Point** user, sf::Event& event, bool& GameHod, int& isMontage)
{
	if (!GameHod)									// ���� ��� ����������
	{
		bool restart;								// ��������� ���������� ��������
		int seed = system_random();					// ��������� ���������� ��� �������� �������
		srand(seed);								// �������� �����	
		do
		{
			restart = false;						// ��������� �������		
			int bangX = rand() % 10;				// ��������� �������
			int bangY = rand() % 10;				// ��������� ������

			switch (user[bangY][bangX].GetStatus())	// �������� ����� ������ ��� ������������� ��������� ��������	
			{
			case 0:									// ���� � ��������� ������ �����
			{
				user[bangY][bangX].SetStatus(1);	// ���������� � ������ "����"	
				GameHod = !GameHod;					// ��������� ��� � ������
				break;								// �������� �� �����
			}
			case 3:									// ���� � ������ �������
			{
				user[bangY][bangX].SetStatus(2);	// ���������� � ������ ���������


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

				break;								// �������� �� �����
			}
			default:								// ���� � ������ ������ ��������
			{
				restart = true;						// ���������� �������
				break;								// �������� �� �����
			}
			}
			} while (restart);							// ���� ������� �������- ������������� ����

		}
	}

