#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>
#include"Point.h"
#include"movedShip.h"
#include"setQuality.h"
using namespace sf;

//������� ��� ���������� ��� ����������� ��������
void MontageShip_2 (Point** user, bool& gorisont, bool& ShipMontage, bool& isCorrect, int x, int y, int& MontageVariator, int& StadyMontage);