#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include"Point.h"
#include"movedShip.h"
#include"setQuality.h"
#include<ctime>
#include<random>
#include "windows.h"
using namespace sf;
using namespace std;
#include<thread>

void after_bang(int X, int Y, int* after, Point** user);



int HodOponent(Point** oponent, sf::Event& event, bool& GameHod, int& isMontage, int* Global_Daedh, int* After_Bang);