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

	const unsigned int n = width*height;		
	
	for (unsigned int j = 0; j < height; ++j)
	{
		for (unsigned int i = 0; i < width; ++i)
		{
			const unsigned int x = i+j*width;
			result[x] = getChecked(i,j) ^ getChecked(i-1,j) ^ getChecked(i+1,j) ^ getChecked(i,j-1) ^ getChecked(i, j+1);

		}

	}	

}



std::ostream& operator<<(std::ostream& os, const Grille& Grille)
{
	using std::endl;


	os << "Grille de dimension : " << Grille.width << 'x' << Grille.height << endl;
	os << "Checked : " << endl;
	for (unsigned int j = 0; j < Grille.height; ++j)
	{
		for (unsigned int i = 0; i < Grille.width; ++i)
		{
			os << Grille.checked[i+j*Grille.width] << ' ';
		}
		os << endl;

	}	

	os << endl << "Result : " << endl;
	for (unsigned int j = 0; j < Grille.height; ++j)
	{
		for (unsigned int i = 0; i < Grille.width; ++i)
		{
			os << Grille.result[i+j*Grille.width] << ' ';
		}
		os << endl;

	}	

}
