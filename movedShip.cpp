#include "movedShip.h"


void movedShip(sf::Event& event, int& StadyMontage, bool& Gorisont,bool isCorrect)
{

		if (event.type == sf::Event::MouseButtonPressed)				
		{
			if (event.key.code == sf::Mouse::Left)										
			{
				if (StadyMontage == 0)											
				{
					StadyMontage = 1;
				}
			}
		}

		if (event.type == sf::Event::MouseButtonReleased )	
		{
			if (event.key.code == sf::Mouse::Left)
			{
				if (StadyMontage == 1 && isCorrect)
				{
					StadyMontage = 2;
				}
				else
				{
					StadyMontage = 0;
				}
			}
			else { StadyMontage = 0; };
		}




		if (event.key.code == sf::Keyboard::R && StadyMontage > -1)							
		{
			Gorisont = !Gorisont;	
			
		}
		//std::cout << "сработал шипмувед" << std::endl;
	}

