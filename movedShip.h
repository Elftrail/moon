#pragma once
#include<SFML/Graphics.hpp>
#include"chekActivBot.h"
#include<iostream>


//sf::Event& Пулл эвентов, sf::RectangleShape& Спрайт корабля, bool& isMove, int& isMontage, bool& isCorrect, int mx, int my, int& corX, int& corY , горизонт
void movedShip(sf::Event& event, sf::RectangleShape& XXXX, bool& isMove, int& isMontage, bool& isCorrect, int mx, int my, int& corX, int& corY,bool& Gorisont);