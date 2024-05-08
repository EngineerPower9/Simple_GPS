#pragma once
#include "Common.h"
#include <vector>

using namespace std;

class CamiBase {
public:
	virtual vector<Coordinate> getCamiCoords() = 0;
	virtual void afegeixPunt(Coordinate cord) = 0;
};

