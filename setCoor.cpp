#include "setCoor.h"

void setCoor(sf::Text (& numerationLIT)[10][2], sf::Text(& numerationNUM)[2], sf::Font (&font))
{
	numerationNUM[0].setString(L" 1 2 3 4 5 6 7 8 9 10");
	numerationNUM[1].setString(L" 1 2 3 4 5 6 7 8 9 10");
	numerationNUM[0].setPosition(100, 140);
	numerationNUM[1].setPosition(750, 140);
	numerationNUM[0].setFont(font);
	numerationNUM[1].setFont(font);
	numerationNUM[0].setCharacterSize(50);
	numerationNUM[1].setCharacterSize(50);

	sf::String literals_for_num(L"¿¡¬√ƒ≈∆«» ");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			numerationLIT[i][j].setString(literals_for_num[i]);
			numerationLIT[i][j].setFont(font);
			numerationLIT[i][j].setCharacterSize(50);
			if (j == 0)
			{
				numerationLIT[i][j].setPosition(45, 190 + i * 50);
			}
			if (j == 1)
			{
				numerationLIT[i][j].setPosition(695, 190 + i * 50);
			}
		}
	}

}
