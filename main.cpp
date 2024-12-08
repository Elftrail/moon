#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<chrono>
#include"Point.h"
#include"setQuality.h"
#include"GenerationShip.h"

using namespace std;
using namespace sf;





int main()

{	//declaration and initialization size arr oponent and user//

	const int sArr = 10;//size arr pools (const=10)
	
	//declaration and initialization dynamic arr oponent//
	
	Point** oponent = { new Point * [sArr] {} };
	for (int  i = 0; i < sArr; i++)
	{
		oponent[i] = new Point[sArr]{};
	}
	
	//Quality setting to an pools oponent//
	setQuality(oponent,false);

	//declaration poole from user//
	Point** user = { new Point * [sArr] {} };
	for (int i = 0; i < sArr; i++)
	{
		user[i] = new Point[sArr]{};
	}

	//Quality setting to an pools user//
	setQuality(user, true);
	GenerationShip(oponent);


	//Declaration Window//
	RenderWindow window(VideoMode(1350, 850), "looock! this is Saylor Moon!!!!");

	//Declaration and initialization back space image//
   Texture Fon;
   Sprite sFon;
   Fon.loadFromFile("sprits/Fon.png");
   sFon.setTexture(Fon);
  
   
   float summiter=0;
   int iter=0;
  
   
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(Color::Black);

		window.draw(sFon);

		// mouse chek position
		int my = Mouse::getPosition(window).y;
		int mx = Mouse::getPosition(window).x;
		
		
		//print poole oponent and user
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				user[y][x].ChekActiv(mx, my);
				window.draw(user[y][x].GetSprite());
				oponent[y][x].ChekActiv(mx, my);
				window.draw(oponent[y][x].GetSprite());
			}
		}



		window.display();
	}

	


	
	cout << "srednyaya skorost cikla= " <<summiter/iter << endl;




	for (int i = 0; i < sArr; i++)
	{
		delete[] oponent[i];
	}
	delete[] oponent;
	for (int i = 0; i < sArr; i++)
	{
		delete[] user[i];
	}
	delete[] user;

	return 0;
}
