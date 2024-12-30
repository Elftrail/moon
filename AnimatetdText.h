#pragma once
#include <SFML/Graphics.hpp>
#include"chekActivBot.h"
#include"GenerationShip.h"
#include"Point.h"
#include<SFML/Audio.hpp>
 
using namespace sf;

void AnimatedText(int mx, int my, RectangleShape& BotYas, Text* strVarPos, bool& Bot_AutoShip, int iterVar, Point** user, int& MontageVariator, RectangleShape& BotNo, bool& ShipMontage, int& StadyMontage, Sound(&SOUND)[7], bool& BotPlay);
