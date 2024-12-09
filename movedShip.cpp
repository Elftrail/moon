#include "movedShip.h"

void movedShip(sf::Event& event, sf::RectangleShape& XXXX, bool& isMove, int& isMontage, bool& isCorrect, int mx, int my, int& corX, int& corY)
{
	int corcorX = 0;																	// доп. корректировка при повороте спрайта корабля по оси Х
	int corcorY = 0;														   		    // доп. корректировка при повороте спрайта корабля по оси У
		
	
		if (event.type == sf::Event::MouseButtonPressed && isMontage == 0)				// Первый клик мыши по кораблю при стадии монтажа = 0
		{
			if (event.key.code == sf::Mouse::Left)										// А именно левой кнопкой
			{
				if (chekActivBot(mx, my, XXXX))											// Проверка на попадание в спрайт
				{
					isMontage = 1;														// перевод монтажа на стадию = 1
					isMove = true;														// разрешаем движение спрайта
				}
			}
		}

		if (event.type == sf::Event::MouseButtonReleased && isMontage == 1)				// Отпущеная кнопка мыши при стадии мотажа = 1
		{
			if (event.key.code == sf::Mouse::Left)										// А именно левая
			{
				isMontage = 2;															// перевод монтажа на стадию = 2
			}
		}

		if (event.type == sf::Event::MouseButtonPressed && isMontage == 2)				// Клик мыши при второй стадии монтажа
		{
			if (event.key.code == sf::Mouse::Left && isCorrect)							// А именно левой кнопкой
			{
					isMontage = 3;														// Перевод монтажа на стадию = 3
					isMove = false;														// Запрещаем движение спрайта
			}
		}

		if (event.type == sf::Event::MouseButtonReleased && isMontage == 3)				// Отпущеная кнопка мыши при стадии мотажа = 3
		{
			if (event.key.code == sf::Mouse::Left)										// А именно левая
			{
				isMontage = 0;															// Перевод монтажа на стадию = 0
			}															
		}



		if (event.key.code == sf::Keyboard::R && isMontage > 0)							// Если нажимаем R - осуществляем поворот на 90 гродусов
		{
																						
			std::cout << "R PRESS" << std::endl;										//	 
			int Y =XXXX.getSize().x;													// Обмен длины и ширины при повороте
			XXXX.setSize(sf::Vector2f(XXXX.getSize().y, Y));							//	
																						

			corcorX =mx-XXXX.getPosition().x-25;										//	 
			corcorY =my-XXXX.getPosition().y-25;										//  Центравка по середине начала спрайта
		}																				//
		
		corX = mx - XXXX.getPosition().x-corcorX;										//  Присваивание доп.корректоров при повороте спрайта
		corY = my - XXXX.getPosition().y-corcorY;										//	  	   
	}

