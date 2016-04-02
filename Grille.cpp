#include "Grille.h"

#include <cassert>



bool Grille::getChecked(unsigned int x, unsigned int y) const
{
	if(x < 0 || y < 0 || x >= width || y >= height) //En dehors des limites
		return false;

	else return checked[width*y+x];

}

bool Grille::getResult(unsigned int x, unsigned int y) const
{
	if(x < 0 || y < 0 || x >= width || y >= height) //En dehors des limites
		return false;

	else return result[width*y+x];
}

bool Grille::checkDimensions() const
{
	unsigned int n = width*height;
	assert(n == result.size());
	assert(n == checked.size());

	return true;
}

void Grille::synchroniserResult() const
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

void Grille::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	synchroniserResult();

	sf::CircleShape blanc(50); blanc.setFillColor(sf::Color(180, 180, 180));
	sf::CircleShape noir(50); noir.setFillColor(sf::Color(20, 20, 20));
	sf::CircleShape red(25); red.setFillColor(sf::Color::Red); red.move(25,25);	
	
	target.setView(sf::View(sf::FloatRect(0, 0, 100*width, 100*height)));
	
	for (unsigned int j = 0; j < height; ++j)
	{
		for (unsigned int i = 0; i < width; ++i)
		{
			sf::Transform trans;
			trans.translate(100*i, 100*j);
			sf::RenderStates pos(trans);
			if(getResult(i,j))
			target.draw(noir, pos);
			else
			target.draw(blanc, pos);

			if(getChecked(i,j))
			target.draw(red, pos);
		}

	}

}	


std::ostream& operator<<(std::ostream& os, const Grille& Grille)
{
	using std::endl;

	Grille.synchroniserResult();

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
