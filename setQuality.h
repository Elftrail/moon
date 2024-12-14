#pragma once
#include <SFML/Graphics.hpp>
#include"Point.h"
using namespace std;
using namespace sf;

void setQuality(Point** arr, bool par, int sizeX, int sizeY);

/// arr, 0 = opponent, 1= user, size
void setQuality(Point* arr, bool par, int sizeX);

/// arr, 0 = opponent, 1= user, size,status 0=void, 1=mis, 2=hit, 3=ship
void setQuality(Point* arr, bool par, int sizeX, int status);

// «адает монтажный макет и его положение
void setQuality(RectangleShape& maket, int MontageVariator);