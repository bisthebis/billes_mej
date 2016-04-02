#ifndef DEF_GRILLE_MEJ
#define DEF_GRILLE_MEJ


#include <iostream>
#include <vector>


struct Grille
{
	unsigned int width, height;
	std::vector<bool> checked;
	std::vector<bool> result;

	Grille(unsigned int w = 5, unsigned int h = 5) : width(w), height(h), checked(w*h, false), result(w*h, false) {}
	~Grille(){}



};

#endif
