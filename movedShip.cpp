#include "movedShip.h"

void movedShip(sf::Event& event, sf::RectangleShape& XXXX, bool& isMove, int& isMontage, bool& isCorrect, int mx, int my, int& corX, int& corY)
{
	int corcorX = 0;																	// ���. ������������� ��� �������� ������� ������� �� ��� �
	int corcorY = 0;														   		    // ���. ������������� ��� �������� ������� ������� �� ��� �
		
	
		if (event.type == sf::Event::MouseButtonPressed && isMontage == 0)				// ������ ���� ���� �� ������� ��� ������ ������� = 0
		{
			if (event.key.code == sf::Mouse::Left)										// � ������ ����� �������
			{
				if (chekActivBot(mx, my, XXXX))											// �������� �� ��������� � ������
				{
					isMontage = 1;														// ������� ������� �� ������ = 1
					isMove = true;														// ��������� �������� �������
				}
			}
		}

		if (event.type == sf::Event::MouseButtonReleased && isMontage == 1)				// ��������� ������ ���� ��� ������ ������ = 1
		{
			if (event.key.code == sf::Mouse::Left)										// � ������ �����
			{
				isMontage = 2;															// ������� ������� �� ������ = 2
			}
		}

		if (event.type == sf::Event::MouseButtonPressed && isMontage == 2)				// ���� ���� ��� ������ ������ �������
		{
			if (event.key.code == sf::Mouse::Left && isCorrect)							// � ������ ����� �������
			{
					isMontage = 3;														// ������� ������� �� ������ = 3
					isMove = false;														// ��������� �������� �������
			}
		}

		if (event.type == sf::Event::MouseButtonReleased && isMontage == 3)				// ��������� ������ ���� ��� ������ ������ = 3
		{
			if (event.key.code == sf::Mouse::Left)										// � ������ �����
			{
				isMontage = 0;															// ������� ������� �� ������ = 0
			}															
		}



		if (event.key.code == sf::Keyboard::R && isMontage > 0)							// ���� �������� R - ������������ ������� �� 90 ��������
		{
																						
			std::cout << "R PRESS" << std::endl;										//	 
			int Y =XXXX.getSize().x;													// ����� ����� � ������ ��� ��������
			XXXX.setSize(sf::Vector2f(XXXX.getSize().y, Y));							//	
																						

			corcorX =mx-XXXX.getPosition().x-25;										//	 
			corcorY =my-XXXX.getPosition().y-25;										//  ��������� �� �������� ������ �������
		}																				//
		
		corX = mx - XXXX.getPosition().x-corcorX;										//  ������������ ���.����������� ��� �������� �������
		corY = my - XXXX.getPosition().y-corcorY;										//	  	   
	}

