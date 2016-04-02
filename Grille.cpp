#include "Grille.h"

#include <cassert>



bool Grille::getChecked(unsigned int x, unsigned int y)
{
	if(x < 0 || y < 0 || x >= width || y >= height) //En dehors des limites
		return false;

	else return checked[width*y+x];

}

bool Grille::getResult(unsigned int x, unsigned int y)
{
	if(x < 0 || y < 0 || x >= width || y >= height) //En dehors des limites
		return false;

	else return result[width*y+x];
}

bool Grille::checkDimensions()
{
	unsigned int n = width*height;
	assert(n == result.size());
	assert(n == checked.size());

	return true;
}

void Grille::synchroniserResult()
{
	assert(checkDimensions());

	unsigned int n = width*height;		

}
