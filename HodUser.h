
#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Point.h"
#include"movedShip.h"
#include"setQuality.h"
#include<ctime>
#include<random>
#include "windows.h"
using namespace sf;
using namespace std;


void HodUser(Point**user, sf::Event& event, bool& GameHod,int y, int x,int &isMontage, int(&Global_DaedhUser)[10][2], Sound * SOUND);