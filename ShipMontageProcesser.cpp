#include "ShipMontageProcesser.h"



	void ShipMontagePocesser(Point** user, RectangleShape& XXXX, bool& gorisont, bool& ShipMontage, bool& isCorrect, int x, int y, int& MontageVariator, int& isMontage, int mx, int my)
	{
		if (gorisont)														// ���� ��������� �������������
		{
			user[y][x].ChekActiv(XXXX.getPosition().x - 30 + XXXX.getSize().x, XXXX.getPosition().y + XXXX.getSize().y / 2);   // �������� �� ��������� �� �������� ������� ��������� ��������� ������� - 30 �������
		}
		if (!gorisont)														// ���� ��������� �����������
		{
			user[y][x].ChekActiv(XXXX.getPosition().x + XXXX.getSize().x / 2, XXXX.getPosition().y - 30 + XXXX.getSize().y);   // �������� �� ��������� �� �������� ������� ��������� ��������� ������� - 30 �������
		}
		if (MontageVariator == 0)											// ���� ������ ��������� = 0
		{
			if (gorisont)													// ���� ������� ������ =1
			{
				if (user[y][x].GetActivated() && (x - 3) > -1)				// ���� ������ ������� � �� �� ������������ �� ������� ����
				{
					isCorrect = true;										// ��� ��������
					user[y][x - 1].SetActivated(true);						// 	
					user[y][x - 2].SetActivated(true);						// ���������� 3 ������ �� �������� �����
					user[y][x - 3].SetActivated(true);						//

					if (isMontage == 3 && isCorrect)						// ���� ������ � ������ 3
					{
						MontageVariator++;									// ����������� �������� �� ��������� �������
						setQuality(XXXX, MontageVariator);					// �������� ������� ��������� ���������
						isMontage = 0;										// ��������� ������ ������� �� ����
						user[y][x].SetStatus(3);							//
						user[y][x - 1].SetStatus(3);						// ��������� ������� 
						user[y][x - 2].SetStatus(3);						//
						user[y][x - 3].SetStatus(3);						//


					}
				}
				if (user[y][x].GetActivated() && (x - 3) == -1)				// ���� ������ ������� � �� ������������ �� ������� ���� �� ���� ������
				{
					isCorrect = false;										// ��� �� �������� ���������
					user[y][x].SetActivated(true, isCorrect);				//
					user[y][x - 1].SetActivated(true, isCorrect);			// 	
					user[y][x - 2].SetActivated(true, isCorrect);			// ���������� 2 ������ �� �������� ����� + ����� �� �������������
				}
				if (user[y][x].GetActivated() && (x - 3) == -2)				// ���� ������ ������� � �� ������������ �� ������� ���� �� ��� ������
				{
					isCorrect = false;										// ��� �� �������
					user[y][x].SetActivated(true, isCorrect);				//
					user[y][x - 1].SetActivated(true, isCorrect);			// ���������� 1 ������ �� �������� ����� + ����� �� ������������

				}
			}
			else if (!gorisont)												// ���� ������� � ���������������������
			{																// ���� ������� ������ =0
				if (user[y][x].GetActivated() && (y - 3) > -1)				// ���� ������ ������� � �� �� ������������ �� ������� ����
				{
					isCorrect = true;										// ��� ��������� ���������
					user[y - 1][x].SetActivated(true);						// 	
					user[y - 2][x].SetActivated(true);						// ���������� 3 ������ �� �������� �����
					user[y - 3][x].SetActivated(true);						//

					if (isMontage == 3)										// ���� ������ � ������ 3
					{
						user[y][x].SetStatus(3);							//
						user[y - 1][x].SetStatus(3);						// ��������� ������� 
						user[y - 2][x].SetStatus(3);						//
						user[y - 3][x].SetStatus(3);						//
						MontageVariator++;									// ����������� �������� �� ��������� �������
						setQuality(XXXX, MontageVariator);					// �������� ������� ��������� ���������
						isMontage = 0;										// ��������� ������ ������� �� ����
						gorisont = true;									// ���������� �������� �������
					}
				}
				if (y == 9 && my > user[6][x].GetPositionY() + user[6][x].GetSize() / 2)								// ��� �������� 9 �� ���� ���� ���� �� � ���� 6-�� ���� ��1/2
				{
					if (mx > user[y][x].GetPositionX() && mx < user[y][x].GetPositionX() + user[y][x].GetSize())		// ���� ���� �� � ������� � ���� �������
					{
						isCorrect = false;									// ��� �� �������� ��������� �������
						user[y - 1][x].SetActivated(true, isCorrect);		// 	
						user[y - 2][x].SetActivated(true, isCorrect);		// ���������� 3 ������ ������ �� ��������� ������� 
						user[y][x].SetActivated(true, isCorrect);			// � ����� ������ �� ������������
					}
				}
			}

		}
		if (MontageVariator == 1 || MontageVariator == 2)					// ������ 3-� ��������� ������
		{
			if (gorisont)													// ���� ������� ������������
			{
				if (user[y][x].GetActivated() && (x - 2) > -1)				// ���� ������ ������� � �� �� ������������ �� ������� ����
				{
					bool Nixuya = false;									// ���������� ��� �������� ����������� ������� �����
					for (int ychek = -1; ychek < 2; ychek++)				// ������� ���� ������� ���������
					{														//
						for (int xchek = -3; xchek < 2; xchek++)			//	
						{
							if (x + xchek > -1 && x + xchek < 11)			// ���� ��� �������� �� �� ������������ �� ������ �� �
							{
								if (y + ychek > -1 && y + ychek < 10)		// ���� ��� �������� �� �� ������������ �� ������ �� �
								{
									if (user[y + ychek][x + xchek].GetStatus() == 3)	// ��������� ������� �������
									{
										Nixuya = true;						// ���� ������� - ����� ������ = ������
									}
								}
							}
						}
					}
					if (!Nixuya)											// ���� ����� ������ = ����									
					{
						isCorrect = true;									// ��� ��������
						user[y][x - 1].SetActivated(true, isCorrect);		// 	
						user[y][x - 2].SetActivated(true, isCorrect);		// ���������� 2 ������ �� �������� �����
					}
					if (Nixuya)												// ���� ����� ������ = �����
					{
						isCorrect = false;									// ��������� �� ��������
						user[y][x].SetActivated(true, isCorrect);			// ���������� �������� 2 ������ �� �������� �����
						user[y][x - 1].SetActivated(true, isCorrect);		// � ��������� �� ������������
						user[y][x - 2].SetActivated(true, isCorrect);		// 
					}


					if (isMontage == 3 && isCorrect)						// ���� ������ � ������ 3 � ��������� ���������
					{
						MontageVariator++;									// ����������� �������� �� ��������� �������
						setQuality(XXXX, MontageVariator);					// �������� ������� ��������� ���������
						isMontage = 0;										// ��������� ������ ������� �� ����
						user[y][x].SetStatus(3);							//
						user[y][x - 1].SetStatus(3);						// ��������� ������� 
						user[y][x - 2].SetStatus(3);						//

					}
				}
				if (user[y][x].GetActivated() && (x - 2) == -1)				// ���� ������ ������� � �� ������������ �� ������� ���� �� ���� ������
				{
					isCorrect = false;										// ��� �� �������� ���������
					user[y][x].SetActivated(true, isCorrect);				//
					user[y][x - 1].SetActivated(true, isCorrect);			// ���������� 2 ������ �� �������� ����� + ����� �� �������������	
				}
			}
			else if (!gorisont)
			{																// ���� ������� ������ =0
				if (user[y][x].GetActivated() && (y - 2) > -1)				// ���� ������ ������� � �� �� ������������ �� ������� ����
				{
					bool Nixuya = false;									// ���������� ��� ������� ����������� ������� �����
					for (int xchek = -1; xchek < 2; xchek++)
					{
						for (int ychek = -3; ychek < 2; ychek++)			// ������� ���� ������� ���������
						{
							if (x + xchek > -1 && x + xchek < 11)			// ���� ��� �������� �� �� ������������ �� ������ �� �
							{
								if (y + ychek > -1 && y + ychek < 10)		// ���� ��� �������� �� �� ������������ �� ������ �� �
								{
									if (user[y + ychek][x + xchek].GetStatus() == 3)		// ��������� ������� �������
									{
										Nixuya = true;						// ���� ������� - ����� ������ = ������
									}
								}
							}
						}
					}
					if (!Nixuya)											// ���� ����� ������ = ����		
					{
						isCorrect = true;									// ��� ���������� ���������
						user[y - 1][x].SetActivated(true);					// 	
						user[y - 2][x].SetActivated(true);					// ���������� 2 ������ �� �������� �����
					}
					if (Nixuya)												// ���� ����� ������ = ������
					{
						isCorrect = false;									// ��� �� ���������� ���������
						user[y][x].SetActivated(true, isCorrect);			//
						user[y - 1][x].SetActivated(true, isCorrect);		// ���������� ����� � 2 ����� �� ��� ����� 	
						user[y - 2][x].SetActivated(true, isCorrect);		// ��������� �� ������������
					}




					if (isMontage == 3 && isCorrect)						// ���� ������ � ������ 3
					{
						user[y][x].SetStatus(3);							//
						user[y - 1][x].SetStatus(3);						// ��������� ������� 
						user[y - 2][x].SetStatus(3);						//
						MontageVariator++;									// ����������� �������� �� ��������� �������
						setQuality(XXXX, MontageVariator);					// �������� ������� ��������� ���������
						isMontage = 0;										// ��������� ������ ������� �� ����
						gorisont = true;									// ���������� �������� �������
					}

				}
				if (y == 9 && my > user[7][x].GetPositionY() + user[7][x].GetSize() / 2)								// ��� �������� 9 �� ���� ���� ���� �� � ���� 6-�� ���� ��1/2
				{
					if (mx > user[y][x].GetPositionX() && mx < user[y][x].GetPositionX() + user[y][x].GetSize())		// ���� ���� �� � ������� � ���� �������
					{
						isCorrect = false;									// ��� �� �������� ��������� �������
						user[y - 2][x].SetActivated(false);					//
						user[y - 1][x].SetActivated(true, isCorrect);		// ���������� 2 ������ ������ �� ��������� ������� 
						user[y][x].SetActivated(true, isCorrect);			// � ����� ������ �� ������������
					}
				}
			}
		}
		if (MontageVariator == 3 || MontageVariator == 4 || MontageVariator == 5)	// ������ 2-� ��������� ������
		{
			if (gorisont)													// ���� ��������� �������������
			{
				if (user[y][x].GetActivated() && (x - 1) > -1)				// ���� ������ ������� � �� �� ������������ �� ������� ����
				{
					bool Nixuya = false;									// ���������� ��� ������� ����������� ������� �����
					for (int ychek = -1; ychek < 2; ychek++)
					{
						for (int xchek = -2; xchek < 2; xchek++)			// ������� ���� ������� ���������
						{
							if (x + xchek > -1 && x + xchek < 11)			// ���� ��� �������� �� �� ������������ �� ������ �� �	
							{
								if (y + ychek > -1 && y + ychek < 10)		// ���� ��� �������� �� �� ������������ �� ������ �� �
								{
									if (user[y + ychek][x + xchek].GetStatus() == 3)   // ��������� ������� �������
									{
										Nixuya = true;						// ���� ������� - ����� ������ = ������
									}
								}
							}
						}
					}
					if (!Nixuya)											// ���� ����� = ����
					{
						isCorrect = true;									// ��������� ��������
						user[y][x - 1].SetActivated(true);					// ���������� 1 ������ �� �������� �����
					}
					if (Nixuya)												// ���� ����� = ������
					{
						{
							isCorrect = false;								// ��� �� �������� ���������
							user[y][x].SetActivated(true, isCorrect);		// ����������  ������ ������������
							user[y][x - 1].SetActivated(true, isCorrect);	// � ������ ����� �� �� ����	
						}
					}

					if (isMontage == 3)										// ���� ������ � ������ 3
					{
						user[y][x].SetStatus(3);							//
						user[y][x - 1].SetStatus(3);						// ��������� ������� 
						MontageVariator++;									// ����������� �������� �� ��������� �������
						setQuality(XXXX, MontageVariator);					// �������� ������� ��������� ���������
						isMontage = 0;										// ��������� ������ ������� �� ����
					}
				}
				if (user[y][x].GetActivated() && (x - 1) == -1)				// ���� ������ ������� � �� ������������ �� ������� ���� �� ���� ������
				{
					isCorrect = false;										// ��� �� �������� ���������
					user[y][x].SetActivated(true, isCorrect);				// ����������  ������ ������������
				}
			}
			else if (!gorisont)												// ���� ��������� ������������
			{																// ���� ������� ������ =0
				if (user[y][x].GetActivated() && (y - 1) > -1)				// ���� ������ ������� � �� �� ������������ �� ������� ����
				{
					bool Nixuya = false;									// ���������� ��� ������� ����������� ������� �����
					for (int ychek = -2; ychek < 2; ychek++)
					{
						for (int xchek = -1; xchek < 2; xchek++)			// ������� ���� ����� �������
						{
							if (x + xchek > -1 && x + xchek < 11)			// ���� ��� ������ �� �� ��������� �� �
							{
								if (y + ychek > -1 && y + ychek < 10)		// ���� ��� ������ �� �� ��������� �� �
								{
									if (user[y + ychek][x + xchek].GetStatus() == 3)	// ����� ������ ���� ��� �������
									{
										Nixuya = true;						// �� ����� = ������
									}
								}
							}
						}
					}
					if (!Nixuya)											// ���� ����� = ����
					{
						isCorrect = true;									// ��� ��������� ���������
						user[y - 1][x].SetActivated(true);					// ���������� ������ ������ 
					}
					if (Nixuya)												// ���� ����� = ������
					{
						{
							isCorrect = false;								// ��� �� �������� ���������
							user[y][x].SetActivated(true, isCorrect);		// ����������  ������ ������������
							user[y - 1][x].SetActivated(true, isCorrect);	// ����������  ������ ������ ������������
						}
					}


					if (isMontage == 3)										// ���� ������ � ������ 3
					{
						user[y][x].SetStatus(3);							//
						user[y - 1][x].SetStatus(3);						// ��������� ������� 
						MontageVariator++;									// ����������� �������� �� ��������� �������
						setQuality(XXXX, MontageVariator);					// �������� ������� ��������� ���������
						isMontage = 0;										// ��������� ������ ������� �� ����
						gorisont = true;									// ���������� �������� �������
					}

				}
				if (y == 9 && my > user[8][x].GetPositionY() + user[8][x].GetSize() / 3)								// ��� �������� 9 �� ���� ���� ���� �� � ���� 6-�� ���� ��1/2
				{
					if (mx > user[y][x].GetPositionX() && mx < user[y][x].GetPositionX() + user[y][x].GetSize())		// ���� ���� �� � ������� � ���� �������
					{
						isCorrect = false;									// ��� �� �������� ��������� �������
						user[y][x].SetActivated(true, isCorrect);			// ���������� ������ �����������
					}
				}
			}
		}
		if (MontageVariator == 6 || MontageVariator == 7 || MontageVariator == 8 || MontageVariator == 9)	// ������ 1-� ��������� ������
		{
			if (user[y][x].GetActivated())									// ���� ������ ������� 
			{
				bool Nixuya = false;										// ���������� ��� ������� ����������� ������� �����
				for (int ychek = -1; ychek < 2; ychek++)
				{
					for (int xchek = -1; xchek < 2; xchek++)				// ������� ���� �������
					{
						if (x + xchek > -1 && x + xchek < 11)				// ���� �� ������������ �� �
						{
							if (y + ychek > -1 && y + ychek < 10)			// � �� ������������ �� �
							{
								if (user[y + ychek][x + xchek].GetStatus() == 3)  // ��������� ������� �������
								{
									Nixuya = true;							// ���� �� ���� - ����� = ������
								}
							}
						}
					}
				}
				if (!Nixuya)												// ���� ����� - ����
				{
					isCorrect = true;										// ��� ��������
					user[y][x].SetActivated(true, isCorrect);				// ���������� ������
				}
				if (Nixuya)													// ���� ����� = ������
				{
					{
						isCorrect = false;									// ��� �� �������� ���������
						user[y][x].SetActivated(true, isCorrect);			// ����������  ������ ������������
					}
				}
				if (isMontage == 3)											// ���� ������ � ������ 3
				{											
					user[y][x].SetStatus(3);								// ��������� ������� 
					MontageVariator++;										// ����������� �������� �� ��������� �������
					setQuality(XXXX, MontageVariator);						// �������� ������� ��������� ���������
					isMontage = 0;											// ��������� ������ ������� �� ����
					if (MontageVariator > 9)								// ���� �������� ��������� 9 ���������
					{
						ShipMontage = false;								// ���� ��� ������� ����������� = ��������� �� �������
					}
				}
			}

		}
	}
	
