#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include"Point.h"
#include"movedShip.h"
#include"setQuality.h"
using namespace sf;

//������� ��� ���������� ��� ����������� ��������
void ShipMontagePocesser(Point** user, RectangleShape& XXXX, bool& gorisont, bool& ShipMontage, bool& isCorrect, int x, int y, int& MontageVariator, int& isMontage, int mx, int my);