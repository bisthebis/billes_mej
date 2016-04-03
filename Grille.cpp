#include "Grille.h"
#include "easylogging++.h"

#include <cassert>
#include <iostream>



bool Grille::getChecked(int x, int y) const
{
	if(x < 0 || y < 0 || x >= width || y >= height) //En dehors des limites
		return false;

	else return checked[width*y+x];

}

bool Grille::getResult(int x, int y) const
{
	if(x >= width || y >= height) //En dehors des limites
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

	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			const unsigned int x = i+j*width;
			result[x] = getChecked(i,j) ^ getChecked(i-1,j) ^ getChecked(i+1,j) ^ getChecked(i,j-1) ^ getChecked(i, j+1);

		}

	}

}

void Grille::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	synchroniserResult();
	assert(!states.texture); //Pour éviter -Wunused

	sf::CircleShape blanc(50); blanc.setFillColor(sf::Color(180, 180, 180));
	sf::CircleShape noir(50); noir.setFillColor(sf::Color(20, 20, 20));
	sf::CircleShape red(25); red.setFillColor(sf::Color::Red); red.move(25,25);

	target.setView(sf::View(sf::FloatRect(0, 0, 100*width, 100*height)));

	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
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
	for (int j = 0; j < Grille.height; ++j)
	{
		for (int i = 0; i < Grille.width; ++i)
		{
			os << Grille.checked[i+j*Grille.width] << ' ';
		}
		os << endl;

	}

	os << endl << "Result : " << endl;
	for (int j = 0; j < Grille.height; ++j)
	{
		for (int i = 0; i < Grille.width; ++i)
		{
			os << Grille.result[i+j*Grille.width] << ' ';
		}
		os << endl;

	}

	return os;
}

void Grille::computeLine(int j)
{
	for (int i = 0; i < width; ++i)
	checked[i+height*j] = !getResult(i, j-1);

	synchroniserResult();


}

void Grille::computeRange(int j, int n)
{
	synchroniserResult();
	for (int x = j; x < j+n; ++x)
	computeLine(x);
}

void Grille::resize(int x, int y)
{
	width = x;
	height = y;
	checked.resize(x*y);
	result.resize(x*y);

	for (int i = 0; i < x*y; ++i)
		checked[i] = false;

	synchroniserResult();

	LOG(INFO) << "Successful resize";

}

void Grille::solve()
{
		if(width > height) resize(height, width);

		const unsigned long n_tentatives = (1 << width);

		char a;
		for (unsigned long i = 0; i < n_tentatives; ++i)
		{
				auto firstLine = deserializeBool(i, width);
				for (int n = 0; n < width*height; ++n)
				checked[n] = false;
				for (int n = 0; n < width; ++n)
				checked[n] = firstLine[n];

				computeRange(1, height-1);
				if(isCorrect())
				std::cin >> a;
		}

}

bool Grille::isCorrect()
{
	for (bool e : result)
		if(!e)
		return false;

	return true;
}

unsigned long serializeBool(std::vector<bool>& vec)
{
	unsigned long value = 0;
	const int N = vec.size();
	for (int i = 0; i < N; ++i)
	{
		value += (vec[i] << i);
	}

	return value;
}
std::vector<bool> deserializeBool(unsigned long src, int n)
{
		std::vector<bool> v(n, false);
		for (int i = 0; i < n; ++i)
		{
			v[i] = (1 << i) & src;
		}


		return v;
}
