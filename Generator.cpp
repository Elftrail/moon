#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include"classPool.cpp"


using namespace std;
using namespace sf;



//set oponent or user
Pool Generator(Pool (& arrpool)[10][10])
{
	/*��������� �������*/
	int rstr;
	int rsto;
	srand(NULL);

	bool linkor;
	do {
		linkor = false;
		rstr = rand() % 10;//�������� ������ ������ ������ �������
		rsto = rand() % 10;//�������� ������� ������ ������ �������
		arrpool[rstr][rsto].SetStatus(3);


		if (rsto > 3)//�������� �� ������� ����
		{
			for (int i = 0; i < 4; i++)//��������� �����
			{
				arrpool[rstr][rsto].SetStatus(3);
			}

		}
		else if (rstr > 3)// �������� �� ������� ����
		{
			for (int i = 0; i < 4; i++) // ��������� �����
			{
				arrpool[rstr][rsto].SetStatus(3);
			}

		}
		else if (rsto < 7)//�������� �� ������� ����
		{
			for (int i = 0; i < 4; i++)// ��������� ������
			{
				arrpool[rstr][rsto].SetStatus(3);
			}
		}
		else if (rstr < 7)// �������� �� ������� ����
		{
			for (int i = 0; i < 4; i++)// ��������� ����
			{
				arrpool[rstr][rsto].SetStatus(3);
			}
		}
		else { linkor = true; }//������ ���������, ���������� �����

	} while (linkor);
	//
	///*��������� 1-�� ��������*/
	//bool onekre = false;
	//do
	//{
	//	onekre = false;
	//	rstr = rand() * 5 % 9;//�������� ������ ������ ������ 
	//	rsto = rand() / 11 % 9;//��������� ������� ������ ������ 
	//	if (polpro[rstr][rsto] != 'k')
	//	{
	//		if (rsto < 7 && polpro[rstr - 1][rsto - 1] != 'k' && polpro[rstr - 1][rsto] != 'k' && polpro[rstr - 1][rsto + 1] != 'k' && polpro[rstr - 1][rsto + 2] != 'k' && polpro[rstr - 1][rsto + 3] != 'k' && polpro[rstr][rsto - 1] != 'k' && polpro[rstr][rsto] != 'k' && polpro[rstr][rsto + 1] != 'k' && polpro[rstr][rsto + 2] != 'k' && polpro[rstr][rsto + 3] != 'k' && polpro[rstr + 1][rsto - 1] != 'k' && polpro[rstr + 1][rsto] != 'k' && polpro[rstr + 1][rsto + 1] != 'k' && polpro[rstr + 1][rsto + 2] != 'k' && polpro[rstr + 1][rsto + 3] != 'k')
	//		{
	//			for (int i = 0; i < 3; i++)// ��������� ������
	//			{
	//				polpro[rstr][rsto + i] = 'k';
	//			}
	//		}
	//		else if (rstr < 8 && polpro[rstr - 1][rsto - 1] != 'k' && polpro[rstr - 1][rsto] != 'k' && polpro[rstr - 1][rsto + 1] != 'k' && polpro[rstr][rsto - 1] != 'k' && polpro[rstr][rsto] != 'k' && polpro[rstr][rsto + 1] != 'k' && polpro[rstr + 1][rsto - 1] != 'k' && polpro[rstr + 1][rsto] != 'k' && polpro[rstr + 1][rsto + 1] != 'k' && polpro[rstr + 2][rsto - 1] != 'k' && polpro[rstr + 2][rsto] != 'k' && polpro[rstr + 2][rsto + 1] != 'k' && polpro[rstr + 3][rsto - 1] != 'k' && polpro[rstr + 3][rsto] != 'k' && polpro[rstr + 3][rsto + 1] != 'k')
	//		{
	//			for (int i = 0; i < 3; i++)// ��������� ����
	//			{
	//				polpro[rstr + i][rsto] = 'k';
	//			}
	//		}
	//		else { onekre = true; }//������ ��������� ���������� �����

	//	}
	//	else { onekre = true; }//������ ��������� ���������� �����
	//} while (onekre);
	///*��������� 2-�� ��������*/
	//bool twokre = false;
	//do
	//{
	//	twokre = false;
	//	rstr = rand() * 5 % 9;//�������� ������ ������ ������ 
	//	rsto = rand() / 11 % 9;//��������� ������� ������ ������ 
	//	if (polpro[rstr][rsto] != 'k')
	//	{
	//		if (rsto < 7 && polpro[rstr - 1][rsto - 1] != 'k' && polpro[rstr - 1][rsto] != 'k' && polpro[rstr - 1][rsto + 1] != 'k' && polpro[rstr - 1][rsto + 2] != 'k' && polpro[rstr - 1][rsto + 3] != 'k' && polpro[rstr][rsto - 1] != 'k' && polpro[rstr][rsto] != 'k' && polpro[rstr][rsto + 1] != 'k' && polpro[rstr][rsto + 2] != 'k' && polpro[rstr][rsto + 3] != 'k' && polpro[rstr + 1][rsto - 1] != 'k' && polpro[rstr + 1][rsto] != 'k' && polpro[rstr + 1][rsto + 1] != 'k' && polpro[rstr + 1][rsto + 2] != 'k' && polpro[rstr + 1][rsto + 3] != 'k')
	//		{
	//			for (int i = 0; i < 3; i++)// ��������� ������
	//			{
	//				polpro[rstr][rsto + i] = 'k';
	//			}
	//		}
	//		else if (rstr < 8 && polpro[rstr - 1][rsto - 1] != 'k' && polpro[rstr - 1][rsto] != 'k' && polpro[rstr - 1][rsto + 1] != 'k' && polpro[rstr][rsto - 1] != 'k' && polpro[rstr][rsto] != 'k' && polpro[rstr][rsto + 1] != 'k' && polpro[rstr + 1][rsto - 1] != 'k' && polpro[rstr + 1][rsto] != 'k' && polpro[rstr + 1][rsto + 1] != 'k' && polpro[rstr + 2][rsto - 1] != 'k' && polpro[rstr + 2][rsto] != 'k' && polpro[rstr + 2][rsto + 1] != 'k' && polpro[rstr + 3][rsto - 1] != 'k' && polpro[rstr + 3][rsto] != 'k' && polpro[rstr + 3][rsto + 1] != 'k')
	//		{
	//			for (int i = 0; i < 3; i++)// ��������� ����
	//			{
	//				polpro[rstr + i][rsto] = 'k';
	//			}
	//		}
	//		else { twokre = true; }//������ ��������� ���������� �����

	//	}
	//	else { twokre = true; }//������ ��������� ���������� �����
	//} while (twokre);
	///*��������� 3-x ��������*/
	//for (int k = 0; k < 3; k++)
	//{
	//	bool esmin = false;
	//	do
	//	{
	//		esmin = false;
	//		rstr = rand() % 9;//�������� ������ ������ ������ 
	//		rsto = rand() % 9;//��������� ������� ������ ������ 	
	//		if (polpro[rstr][rsto] != 'k')
	//		{
	//			if (rsto < 8)
	//			{
	//				for (int j = -1; j < 2; j++)
	//				{
	//					for (int i = -1; i < 3; i++)
	//					{
	//						if (polpro[rstr + j][rsto + i] == 'k')
	//						{
	//							esmin = true;
	//						}

	//					}

	//				}
	//				if (!esmin)
	//				{
	//					polpro[rstr][rsto] = 'k';
	//					polpro[rstr][rsto + 1] = 'k';
	//				}
	//			}
	//			else if (rstr < 8)
	//			{
	//				for (int j = -1; j < 2; j++)
	//				{
	//					for (int i = -1; i < 3; i++)
	//					{
	//						if (polpro[rstr + i][rsto + j] == 'k')
	//						{
	//							esmin = true;
	//						}

	//					}

	//				}
	//				if (!esmin)
	//				{
	//					polpro[rstr][rsto] = 'k';
	//					polpro[rstr + 1][rsto] = 'k';
	//				}
	//			}
	//			else { esmin = true; }

	//		}
	//		else { esmin = true; }
	//	} while (esmin);
	//}
	///*��������� 4-� ����*/
	//for (int k = 0; k < 4; k++)
	//{
	//	bool shun = false;
	//	do
	//	{
	//		shun = false;
	//		rstr = rand() % 9;//�������� ������ ������ ������ 
	//		rsto = rand() % 9;//��������� ������� ������ ������ 	
	//		if (polpro[rstr][rsto] != 'k')
	//		{
	//			for (int j = -1; j < 2; j++)
	//			{
	//				for (int i = -1; i < 2; i++)
	//				{
	//					if (polpro[rstr + j][rsto + i] == 'k')
	//					{
	//						shun = true;
	//					}

	//				}

	//			}
	//			if (!shun)
	//			{
	//				polpro[rstr][rsto] = 'k';
	//			}
	//		}
	//		else { shun = true; }

	//	} while (shun);
	//}
}