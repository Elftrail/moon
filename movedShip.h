#pragma once
#include<SFML/Graphics.hpp>
#include"chekActivBot.h"
#include<iostream>


//sf::Event& ���� �������, sf::RectangleShape& ������ �������, bool& isMove, int& isMontage, bool& isCorrect, int mx, int my, int& corX, int& corY , ��������
void movedShip(sf::Event& event, sf::RectangleShape& XXXX, bool& isMove, int& isMontage, bool& isCorrect, int mx, int my, int& corX, int& corY,bool& Gorisont);