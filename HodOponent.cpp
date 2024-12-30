#include "HodOponent.h"
random_device system_random;						// ������ ���������� ��� �������

//After_Bang 
//              ������						||		��������
// 
// [0] - ��������� ������ ����������� ����__-1 ��� ������������ ��������  
//___________________________________________1 ���� ������ ����������� ���������
// 
// [1] - ��� ��������_______________________-1 ��� �� ���������� 
//__________________________________________ 1 ��� �
//__________________________________________ 2 ��� �
// 
// [2] - ����������� ��������_______________-1 ����������� �� ����������
//__________________________________________ 1 ����������� +
//__________________________________________ 2 ����������� -
// 
// [3] - ���������� ����������� ��������� �_-1 ���������� �����������
//__________________________________________ 0-9 ����������
// 
// [4] - ���������� ����������� ��������� � -1 ���������� �����������
//___________________________________________0-9 ����������
// [5]										 ������
// [6]										 ������
// [7]										 ������
// [8]										 ������
void after_bang(int Y, int X, int* After_Bang, Point** user, int& bangY,int& bangX)
{	

	//cout << " ����� ��������� ���������� ���� ���������� ";
	//cout << " � ����� After_Bang : " << endl;
	/*for (int i = 0; i < 9; i++)
	{
		cout << "' " << After_Bang[i] << " ' ";
	}
	cout << endl;*/


	//���������� �������� �� �������� ����� � ������ ����������� ���������
	bool prox_plus = true;
	bool prox_minus = true;
	bool proy_plus = true;
	bool proy_minus = true;
	//�� �
	if (After_Bang[3] + 1 > 9) { proy_plus = false; }
	if (After_Bang[3] - 1 < 0) { proy_minus = false; }
	//�� �
	if (After_Bang[4] + 1 > 9) { prox_plus = false; }
	if (After_Bang[4] - 1 < 0) { prox_minus = false; }
	//�������� ���������� ��� ��������� �����

	// ���� ��������� �����
	if (After_Bang[1] == -1) 
	{// �� ������
		//cout << " ��� �������� �� ����������. ������ ������ ��� �� ����� ����� " << endl;
		if (proy_plus) 
		{
			if (user[After_Bang[3] + 1][After_Bang[4]].GetStatus() == 2) 
			{
				After_Bang[1] = 2; 
				//cout << " ��� �������� ����������� �� �(�� �+1 �� �������� ��������� ���) " << endl;
			}
			
		}
		if (proy_minus)
		{
			if (user[After_Bang[3] - 1][After_Bang[4]].GetStatus() == 2) 
			{
				After_Bang[1] = 2;
			//cout << " ��� �������� ����������� �� � (�� �-1 �� �������� ��������� ���) " << endl;
			}
			
		}
		// �� �
		if (prox_plus)
		{
			if (user[After_Bang[3]][After_Bang[4]+1].GetStatus() == 2)
			{
				After_Bang[1] = 1;
				//cout << " ��� �������� ����������� �� �(�� �+1 �� �������� ��������� ���) " << endl;
			}
			
		}
		if (prox_minus)
		{
			if (user[After_Bang[3]][After_Bang[4]-1].GetStatus() == 2) 
			{
				After_Bang[1] = 1;
			//cout << " ��� �������� ����������� �� � (�� �-1 �� �������� ��������� ���) " << endl;
			}
			
		}
		if (After_Bang[1] == -1)
		{
			//cout << " ��� �������� �� ����� �� ����������. ������ ������ ��� �� ����� � �������� " << endl;
			
			//����� �� �
			if (proy_plus&&user[After_Bang[3] + 1][After_Bang[4]].GetStatus() == 1||!proy_plus)
			{
				if (proy_minus && user[After_Bang[3] - 1][After_Bang[4]].GetStatus() == 1||!proy_minus)
				{
					After_Bang[1] = 1;
					//cout << " ��� �������� ����������� �� � " << endl;
				}
			}
			// ����� �� X
			if (prox_plus && user[After_Bang[3]][After_Bang[4]+1].GetStatus() == 1 ||!prox_plus)
			{
				if (prox_minus && user[After_Bang[3]][After_Bang[4]-1].GetStatus() == 1 || !prox_minus)
				{
					After_Bang[1] = 2;
					//cout << " ��� �������� ����������� �� Y " << endl;
				}
			}
		}
	}
	//���� ��� �� ����������
	if (After_Bang[1] == -1)
	{
		//cout << " ��� �������� ���������� �� �������. ������������ ��������� ������� �� ��������� ��������� ������� " << endl;
		int seed = system_random();
		srand(seed);
		bool rest_rand = false;

		do {
			rest_rand = false;
			int napr = rand() % 4;
			switch (napr)
			{
			case 0:
				//cout << " ��������� ������� ����� " << endl;
				if (prox_minus)
				{
					bangX = After_Bang[4] - 1;
					bangY = After_Bang[3];
					if (user[bangY][bangX].GetStatus() == 1)
					{
						rest_rand = true;
						//cout << " ������ �������� ����� - � ������ ��� ���. ������� ������� " << endl;
					}

				}
				else if (!prox_minus)
				{
					rest_rand = true;
					//cout << " ������ �������� ����� - ������� ����. ������� ������� " << endl;
				}
				break;
			case 1:
				//cout << " ��������� ������� ����� " << endl;
				if (proy_minus)
				{
					bangX = After_Bang[4];
					bangY = After_Bang[3]-1;
					if (user[bangY][bangX].GetStatus() == 1)
					{
						rest_rand = true;
					//cout << " ������ �������� ����� - � ������ ��� ���. ������� ������� " << endl;
					}

				}
				else if (!proy_minus)
				{
					rest_rand = true;
					//cout << " ������ �������� ����� - ������� ����. ������� ������� " << endl;
				}
				break;
			case 2:
				//cout << " ��������� ������� ������ " << endl;
				if (prox_plus)
				{
					bangX = After_Bang[4] + 1;
					bangY = After_Bang[3];
					if (user[bangY][bangX].GetStatus() == 1)
					{
						rest_rand = true;
						//cout << " ������ �������� ������ - � ������ ��� ���. ������� ������� " << endl;
					}

				}
				else if (!prox_plus)
				{
					rest_rand = true;
					//cout << " ������ �������� ������ - ������� ����. ������� ������� " << endl;
				}
				break;
			case 3:
				//cout << " ��������� ������� ���� " << endl;
				if (proy_plus)
				{
					bangX = After_Bang[4];
					bangY = After_Bang[3]+1;
					if (user[bangY][bangX].GetStatus() == 1)
					{
						rest_rand = true;
					//	cout << " ������ �������� ���� - � ������ ��� ���. ������� ������� " << endl;
					}

				}
				else if (!proy_plus)
				{
					rest_rand = true;
				//	cout << " ������ �������� ���� - ������� ����. ������� ������� " << endl;
				}
				break;
			default:
				break;
			}
		}while (rest_rand);

	}


	// ���� ���������� ��� �
	if (After_Bang[1] == 1/*&&After_Bang[2]==-1*/)
	{
		//cout << " ������ ����� ���������� ����� " << endl;
		//
		//cout << " �������� ��������� ����������� �������� " << endl;
		if(After_Bang[2] == -1)
		{
			//cout << "1.���������� �� ������. ������ ��������� ����������� �������� �� ��� � +" << endl;
			for (int i = 0; i < 6; i++)
			{
				if (After_Bang[4] + i > 9)
				{
					After_Bang[2] = 2;
					//cout << " ������� ��������� �� X+. �������� � �������. ����������� ����������� � X- " << endl;
					break;
				}
				if (user[After_Bang[3]][After_Bang[4]+i].GetStatus()==1)
				{
					After_Bang[2] = 2;
					//cout << " ������� ��������� ��X +. �������� � ���. ����������� ����������� � X- " << endl;
					break;
				}
				if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 0|| user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 3)
				{
					//cout << " ������� ��������� �� X+. �������� � ���� ��� �������. ����������� �� ����������� " << endl;
					break;
				}
				
			}
		}
		if ( After_Bang[2] == -1)
		{
			//cout << "2. ���������� �� ������. ������ ��������� ����������� �������� �� ��� � - " << endl;
			for (int i = 0; i > -6; i--)
			{
				if (After_Bang[4] + i < 0)
				{
					After_Bang[2] = 1;
					//cout << "2,1 ������� ��������� �� X-. �������� � �������. ����������� ����������� � + " << endl;
					break;
				}
				if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 1)
				{
					After_Bang[2] = 1;
					//cout << "2,2 ������� ��������� �� X-. �������� � ���. ����������� ����������� � + " << endl;
					break;
				}
				if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 0|| user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 3)
				{
					//cout << "2,3 ������� ��������� �� X -. �������� � ���� ��� �������. ����������� �� ����������� " << endl;
					break;
				}
			}
		}

	}
	if (After_Bang[2] == -1) 
	{
		bool REST = false;
		//cout << " 3,���������� ����������� �������� �� ������� ����� �� �������. " << endl;
		do {
			REST = false;
			int napr = rand() % 2;
			switch (napr)
			{
			case 0:
			//	cout << " ����������� ��������� ����������� + " << endl;
				After_Bang[2] = 1;
				break;
			case 1:
			//	cout << " ����������� ��������� ����������� - " << endl;
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
			//cout << "������ �������� �� ����������������� ��� � " << endl;
			do {
				REST = false;
				if (After_Bang[2] == 1)
				{
					//cout << " ������ ��������� ���������� �������� �� ������������������ ���������� X+ " << endl;
						
						for (int i = 1; i < 5; i++)
						{
							if (After_Bang[4] + i < 10)
							{
								if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 2)
								{
									//cout << "���������� �� ��� �� �+"<<i << endl;
								
								}
								if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 1)
								{
								//	cout << "���������� �� ��� �� �+" << i << endl;
								//	cout << "������ �����������" << endl;
									After_Bang[2] = 2;
									REST = true;
									break;
								}
								if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 0|| user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 3)
								{
									//cout << "���������� �� ���������� ������ �� �+" << i << endl;
									//cout << "������� ���������� �� ���������� ������" << endl;
									bangX = After_Bang[4] + i;
									bangY = After_Bang[3];
									break;
								}

							}
							else 
							{ 
								//cout << "������ �� �+ ������ � ������� ������ �����������" << endl;
								After_Bang[2] = 2;
								REST = true;
								break;
							}
						}

					


				}
				
				if (After_Bang[2] == 2)
				{
					//cout << " ������ ��������� ���������� �������� �� ������������������ ���������� X- " << endl;
						for (int i = -1; i > -5; i--)
						{
							if (After_Bang[4] + i > -1)
							{
								if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 2)
								{
									//cout << "���������� �� ��� �� �-" << i << endl;
									//continue;
								}
								if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 1)
								{
									//cout << "���������� �� ��� �� �-" << i << endl;
									//cout << "������ �����������" << endl;
									After_Bang[2] = 1;
									REST = true;
									break;
								}
								if (user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 0 || user[After_Bang[3]][After_Bang[4] + i].GetStatus() == 3)
								{
									//cout << "���������� �� ���������� ������ �� �-" << i << endl;
									//cout << "������� ���������� �� ���������� ������" << endl;
									bangX = After_Bang[4] + i;
									bangY = After_Bang[3];
									break;
								}

							}
							else
							{
								//cout << "������ �� �- ������ � ������� ������ �����������" << endl;
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
			//cout << "������ �������� �� ����������������� ��� Y " << endl;
			do {
				REST = false;
				if (After_Bang[2] == 1)
				{
				//	cout << " ������ ��������� ���������� �������� �� ������������������ ���������� �+ " << endl;
					
						for (int i = 1; i < 5; i++)
						{
							if (After_Bang[3] + i < 10)
							{
								if (user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 2)
								{
								//	cout << "���������� �� ��� �� Y+" << i << endl;
									//continue;
								}
								if (user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 1)
								{
								//	cout << "���������� �� ��� �� Y+" << i << endl;
								//	cout << "������ �����������" << endl;
									After_Bang[2] = 2;
									REST = true;
									break;
								}
								if (user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 0 || user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 3)
								{
								//	cout << "���������� �� ���������� ������ �� Y+" << i << endl;
								//	cout << "������� ���������� �� ���������� ������" << endl;
									bangX = After_Bang[4];
									bangY = After_Bang[3]+i;
									break;
								}

							}
							else
							{
							//	cout << "������ �� Y+ ������ � ������� ������ �����������" << endl;
								After_Bang[2] = 2;
								REST = true;
								break;
							}
						}

					//}


				}

				if (After_Bang[2] == 2)
				{
					//cout << " ������ ��������� ���������� �������� �� ������������������ ���������� �+ " << endl;
					
						for (int i = -1; i > -5; i--)
						{
							if (After_Bang[3] + i > -1)
							{
								if (user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 2)
								{
								//	cout << "���������� �� ��� �� Y-" << i << endl;
									//continue;
								}
								if (user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 1)
								{
								//	cout << "���������� �� ��� �� Y-" << i << endl;
								//	cout << "������ �����������" << endl;
									After_Bang[2] = 1;
									REST = true;
									break;
								}
								if (user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 0 || user[After_Bang[3]+i][After_Bang[4]].GetStatus() == 3)
								{
								//	cout << "���������� �� ���������� ������ �� Y-" << i << endl;
								//	cout << "������� ���������� �� ���������� ������" << endl;
									bangX = After_Bang[4];
									bangY = After_Bang[3]+i;
									break;
								}

							}
							else
							{
								//cout << "������ �� Y- ������ � ������� ������ �����������" << endl;
								After_Bang[2] = 1;
								REST = true;
								break;
							}
						}



				}



			} while (REST);

		}


















	//cout << "��������� ��������� � ����� After_Bang : " << endl;
	//for ( int i = 0; i <9; i++)
	//{
	//	cout <<"' " << After_Bang[i] << " ' ";
	//}
	//cout  << endl;
	//cout <<"��������� ������� ������������ �� ������ Y " << bangY<<" X "<<bangX << endl;


}

int HodOponent(Point** user, sf::Event& event, bool& GameHod, int& isMontage, int(&Global_Daedh)[10][2], int* After_Bang, int* PrevBangAnimation, Sound* SOUND)
{
			
	for (int i = 0; i < 2; i++)						// ���������� � ������ ��������� ��������
	{
		PrevBangAnimation[i] = -1;
	}												
	if (!GameHod)									// ���� ��� ����������
	{
		bool restart;								// ��������� ���������� ��������
		int seed = system_random();					// ��������� ���������� ��� �������� �������
		int bangX = -1;
		int bangY = -1;



		srand(seed);								// �������� �����	
		do
		{
			restart = false;						// ��������� �������

			if (After_Bang[0] == -1)
			{
				bangX = rand() % 10;				// ��������� �������
				bangY = rand() % 10;				// ��������� ������
				//cout << " ����������� ��������� ������. ���������� ��������� �������" << endl;
			}


			if (After_Bang[0] == 1)
			{
				//cout << " � ���� ���� ���������� ��������� . ������ ������� ���������� �����" << endl;
				after_bang(After_Bang[3], After_Bang[4], After_Bang, user,bangY,bangX);
			}


			switch (user[bangY][bangX].GetStatus())	// �������� ����� ������ ��� ������������� ��������� ��������	
			{
			case 0:									// ���� � ��������� ������ �����
			{
				//cout << " ===============����============================" << endl;
				SOUND[4].play();
				user[bangY][bangX].SetStatus(1);	// ���������� � ������ "����"	
				GameHod = !GameHod;					// ��������� ��� � ������
				PrevBangAnimation[0] = bangY;
				PrevBangAnimation[1] = bangX;
				break;								// �������� �� �����

			}
			case 3:									// ���� � ������ �������
			{
				//cout << " ===============���������============================" << endl;
				SOUND[3].play();
				After_Bang[0] = 1;					// ��������� �� ����������	
				After_Bang[3] = bangY;				// ������ � �������� �������� �� �
				After_Bang[4] = bangX;				// � �� � ����
				PrevBangAnimation[0] = bangY;
				PrevBangAnimation[1] = bangX;
				user[bangY][bangX].SetStatus(2);	// ���������� � ������ ���������

				

				//cout << " ===============������ ������ ����������============================" << endl;
				for (int Y = 0; Y < 10; Y++)		// ��������� ����� �� ������� ��������� ��������
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
						if (CONTI > 0) { /*cout << "����� ����������� �������� ������ =" << CONTI<<endl;*/ CONTI = 0; continue; }
						//cout << "�������� ������  = " << Y << X << endl;

						int YY = -5;																			// ����������� ��� ���� ���������� ������ 
						int YYSCHET = 0;																	// �����������- ������� ��� ���� ���������� ������ 
						int XX = -5;																			// ����������� ��� ���� ���������� ������ 
						int XXSCHET = 0;																	// �����������- ������� ��� ���� ���������� ������
						if (user[Y][X].GetStatus() == 2)                                                    // ���� ���������� �� ���
						{
							//cout << "�������� ����������� ���� �� �" << endl;
							bool cherprev = true;															// �������������� �������� ������ ���� �������������� 
							if (Y - 1 > -1)																	// ���� �� ������������ �� �������
							{
								//cout << "�������� ����������� ���� �� � ������ ������� �� �������" << endl;
								if (user[Y - 1][X].GetStatus() == 2 || user[Y - 1][X].GetStatus() == 3)		// ���� ���������� �� ��� ��� �������
								{
									//cout << "�������� ����������� ���� �� � ��������� ����� " << endl;
									cherprev = false;														// ��� ������ �� � 
								}
							}
							
							//cout << "�������� ����������� ���� �� �" << endl;
							if (X - 1 > -1)																	// ���� �� ������������ �� ������� �� �
							{
								//cout << "�������� ����������� ���� �� � ������ ������� �� �������" << endl;
								if (user[Y][X - 1].GetStatus() == 2 || user[Y][X - 1].GetStatus() == 3)		// ���� ���������� �� ��� ��� �������
								{
									//cout << "�������� ����������� ���� �� � ��������� ����� " << endl;
									cherprev = false;														// ��� �� � -
								}
							}
							else {/* cout << "�������� ����������� ���� �� � ������������ - ������� " << endl; */}

							if (cherprev)																	// ���� ������ �������� ++
							{
								//cout << "������ �������� ��������� ������������. ������ ������ �� ��������� �� � " << endl;
								for (int smeY = 1; smeY < 5; smeY++)										// ������ ����� �� � �� ��������� ����� �+
								{
									//cout << "�������� �������� = y + "<< smeY << endl;
									
									if (Y + smeY < 10)														// ���� �� ������������ �� �������
									{
										//cout << " � �������� �� ������� ��� �������� �������� " << endl;
										if (user[Y + smeY][X].GetStatus() == 0 || user[Y + smeY][X].GetStatus() == 1)		// ���� ��������� �� �������
										{
											//cout << " � �������� �� ��������� ��������� � ����� 0 - ���������� �� ��� ��� ���� " << endl;
											YY = 0;																			// ������� �� � +
											break;
										}
										if (user[Y + smeY][X].GetStatus() == 3)												// ���� ���������� �� ������� 
										{
											//cout << " � �������� �� ��������� ��������� � ����� -1 - ���������� �� ������� " << endl;
											YY = -1;																		// ������� �� � -
									
											break;

										}
										if (user[Y + smeY][X].GetStatus() == 2)												// ���� ���������� �� ���
										{
											//cout << " � �������� �� ��������� ���������� �� ���. ���������� ��������" << endl;
											YYSCHET++;																		// ���������� ����� � �������������� �������
										}
										


									}
									else
									{
										//cout << " � �������� �� ��������� ��������� � ����� 0  ���������� �� ������� " << endl;
										YY = 0;																			// ������� �� � +
										break;
									}
								}
								//cout << "�������� �������� �� � ���������. ������ �������� �� �"  << endl;
								for (int smeX = 1; smeX < 5; smeX++)														// ������ ����� �� � �� ��������� ����� �+
								{
									//cout << "�������� �������� = � + " << smeX << endl;
									if (X + smeX < 10)																		// ���� �� ������������ �� �������
									{
										if (user[Y][X + smeX].GetStatus() == 0 || user[Y][X + smeX].GetStatus() == 1)		// ���� ��������� �� �������
										{
											XX = 0;																			// ������� �� � +
											break;
											//cout << " X �������� �� ��������� ��������� � ����� 0 - ���������� �� ��� ��� ���� " << endl;
										}
										if (user[Y][X + smeX].GetStatus() == 3)												// ���� ���������� �� �������
										{
											//cout << " � �������� �� ��������� ��������� � ����� -1 - ���������� �� ������� " << endl;
											XX = -1;																		// ������� �� � -

											break;
										}
										if (user[Y][X + smeX].GetStatus() == 2)												// ���� ���������� �� ���
										{
											//cout << " � �������� �� ��������� ���������� �� ���. ���������� ��������" << endl;
											XXSCHET++;																		// ���������� ����� � �������������� �������
										}
									}
									else
									{
										//cout << " � �������� �� ��������� ��������� � ����� 0 - ���������� �� ������� " << endl;
										XX = 0;																			// ������� �� � +
										break;
									}

								}
								//cout << "�������� �������� ��������� ";
								if (YY == 0 && XX == 0)																		// ���� ����� �������� � ����� 00
								{
									//cout << "� ����� 00. ������ ��������� ������ ������ ������ ������������ ������� " << endl;
									//cout << "==================================================================== " << endl;
									//cout << "=================�������++��������================================== " << endl;
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
									
									
									if (YYSCHET > 0)																		// ���� ������� ����� �� � ������ 0
									{
										for (int xkor = -1; xkor < 2; xkor++)												// ���������� ������ ������ �����
										{
											for (int ykor = -1; ykor < YYSCHET + 2; ykor++)
											{
												if (Y + ykor > -1 && Y + ykor<10 && X + xkor>-1 && X + xkor < 10)			// ���� �� ������������
												{
													if (user[Y + ykor][X + xkor].GetStatus() == 0)							// ���� ���������� �� ����
													{
														user[Y + ykor][X + xkor].SetStatus(1);								// ������ ��� ���
													}
												}
											}
										}
									}
									else if (XXSCHET > 0)																	// ���� ������� ����� �� � ������ 0
									{
										for (int ykor = -1; ykor < 2; ykor++)												// ���������� ������ ������ �����
										{
											for (int xkor = -1; xkor < XXSCHET + 2; xkor++)
											{
												if (Y + ykor > -1 && Y + ykor<10 && X + xkor>-1 && X + xkor < 10)			// ���� �� ������������
												{
													if (user[Y + ykor][X + xkor].GetStatus() == 0)							// ���� ���������� �� ����
													{
														user[Y + ykor][X + xkor].SetStatus(1);								// ������ ��� ���
													}
												}
											}
										}
									}
									else if (XXSCHET == 0 && YYSCHET == 0)													// ���� �������� ����� ==0 ������ ��� 1-���-� 
									{
										for (int ykor = -1; ykor < 2; ykor++)												// ���������� ������ ������ �����
										{
											for (int xkor = -1; xkor < 2; xkor++)
											{
												if (Y + ykor > -1 && Y + ykor<10 && X + xkor>-1 && X + xkor < 10)			// ���� �� ������������
												{
													if (user[Y + ykor][X + xkor].GetStatus() == 0)							// ���� ���������� �� ����
													{
														user[Y + ykor][X + xkor].SetStatus(1);								// ������ ��� ���
													}
												}
											}
										}
									}

								}
								else 
								{
									//cout << "� �����  Y "<<YY<<"X "<<XX << " ������� �� ��������" << endl;
								}
							}
						}
					}
				}
				break;
			}
			default:								// ���� � ������ ������ ��������
			{
				restart = true;						// ���������� �������
				break;								// �������� �� �����
			}
			}


		} while (restart);							// ���� ������� �������- ������������� ����


	}
	
	if (After_Bang[0] == -1)
	{
		//cout << " ��������� AFTER BANG : " << endl;
		for (int i = 0; i < 9; i++)
		{
			After_Bang[i] = -1;
		//	cout << After_Bang[i];
		}
		//cout << endl;
	}
		return 1;
	}

